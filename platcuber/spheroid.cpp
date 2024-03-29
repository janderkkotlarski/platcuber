#include "spheroid.h"

#include "raymath.h"

#include "functions.h"

spheroid::spheroid()
{

}

Vector3 spheroid::get_posit() const noexcept
{ return m_posit; }

Vector3 spheroid::get_veloc() const noexcept
{ return m_veloc; }

Vector3 spheroid::get_accel() const noexcept
{ return m_accel; }

float spheroid::get_radius() const noexcept
{ return m_radius; }

void spheroid::set_pos(const Vector3 &posit)
{ m_posit = posit; }

void spheroid::set_veloc(const Vector3 &veloc)
{ m_veloc = veloc; }

void spheroid::set_accel(const Vector3 &accel)
{ m_accel = accel; }

void spheroid::no_accel()
{ m_accel = Vector3Zero(); }

void spheroid::add_accel(const Vector3 &accel)
{ m_accel = Vector3Add(m_accel, accel); }

void spheroid::set_color(const Color &color)
{ m_color = color; }

void spheroid::display()
{ DrawModel(m_model, m_posit, 1.0f, m_color); }

void spheroid::wiresplay()
{ DrawModelWires(m_model, m_posit, 1.0f, m_color); }

void spheroid::set_sphere()
{
  m_image = LoadImage("cube_face_spectrum_.png");

  m_tex2d = LoadTextureFromImage(m_image);

  m_model = LoadModelFromMesh(GenMeshSphere(m_radius, 25, 50));

  m_model.materials[0].maps[MAP_DIFFUSE].texture = m_tex2d;

}

void spheroid::set_shading(const Shader &shade)
{ m_model.materials[0].shader = shade; }

void spheroid::move(const Vector3 &posit, const float time)
{  
  m_posit = Vector3Add(m_posit, Vector3Scale(m_veloc, 0.5f*time));

  // reflect(posit, 0.0f, 1, m_posit, m_radius, m_veloc);

  // m_accel.x = m_spring*(m_spring_center.x - m_posit.x);
  // m_accel.z = m_spring*(m_spring_center.z - m_posit.z);

  m_veloc = Vector3Add(m_veloc, Vector3Scale(m_accel, time));

  m_posit = Vector3Add(m_posit, Vector3Scale(m_veloc, 0.5f*time));

  // reflect(posit, 0.0f, 1, m_posit, m_radius, m_veloc);
}
