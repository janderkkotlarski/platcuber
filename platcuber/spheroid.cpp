#include "spheroid.h"

#include "raymath.h"

spheroid::spheroid()
{

}

Vector3 spheroid::get_pos() noexcept
{ return m_posit; }

void spheroid::set_pos(const Vector3 &pos)
{ m_posit = pos; }

void spheroid::display()
{
  // DrawSphere(m_posit, 0.5f*m_side, m_color);

  DrawModel(m_model, m_posit, 1.0f, m_color);
}

void spheroid::set_sphere()
{
  m_image = LoadImage("cube_face_spectrum_.png");

  m_tex2d = LoadTextureFromImage(m_image);

  m_model = LoadModelFromMesh(GenMeshSphere(m_side, 25, 50));

  // m_model.materials[0].maps[MAP_DIFFUSE].texture = m_tex2d;

}

void spheroid::set_shading(const Shader &shade)
{ m_model.materials[0].shader = shade; }

void spheroid::move(const Vector3 &posit, const float time)
{
  m_posit = Vector3Add(m_posit, Vector3Scale(m_veloc, 0.5f*time));

  if (m_posit.y <= posit.y + m_side)
  {
    m_posit.y = 2.0f*(posit.y + m_side) - m_posit.y;

    m_veloc.y *= -1.0f;
  }

  m_veloc = Vector3Add(m_veloc, Vector3Scale(m_accel, time));

  m_posit = Vector3Add(m_posit, Vector3Scale(m_veloc, 0.5f*time));

  if (m_posit.y <= posit.y + m_side)
  {
    m_posit.y = 2.0f*(posit.y + m_side) - m_posit.y;

    m_veloc.y *= -1.0f;
  }
}
