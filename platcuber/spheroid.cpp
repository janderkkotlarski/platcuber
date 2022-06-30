#include "spheroid.h"

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

  m_model.materials[0].maps[MAP_DIFFUSE].texture = m_tex2d;

}

void spheroid::set_shading(const Shader &shade)
{ m_model.materials[0].shader = shade; }
