#include "viewctor.h"

#include "raymath.h"

viewctor::viewctor()
{
  remeasure();
}

void viewctor::set_posit(const Vector3 &posit)
{
  m_posit = posit;
}

void viewctor::set_direct(const Vector3 &direct)
{
  m_direct = direct;

  remeasure();
}

void viewctor::remeasure()
{
  m_stick_length = Vector3Length(m_direct);

  m_stick_radius = 0.05f*m_stick_length;

  m_sphere_radius = 0.1f*m_stick_length;
}

void viewctor::set_stick()
{
  m_stick = LoadModelFromMesh(GenMeshCylinder(m_stick_radius, m_stick_length, 50));
}

void viewctor::set_sphere()
{
  m_sphere = LoadModelFromMesh(GenMeshSphere(m_sphere_radius,  25, 50));
}

void viewctor::set_on_sphere(const spheroid &sphoid)
{
  const Vector3 base_posit
  { sphoid.get_posit() };

  set_direct(sphoid.get_veloc());

  const Vector3 unit_direct
  { Vector3Normalize(m_direct) };

  const Vector3 radius_direct
  { Vector3Scale(unit_direct, sphoid.get_radius()) };

  set_posit(Vector3Add(base_posit, radius_direct));
}

void viewctor::display()
{
  const Vector3 mid_pos
  { Vector3Add(m_posit, Vector3Scale(m_direct, 0.5f)) };

  DrawModel(m_stick, mid_pos, 1.0f, GREEN);

  DrawModel(m_sphere, m_posit, 1.0f, RED);
}
