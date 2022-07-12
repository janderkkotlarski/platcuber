#include "viewctor.h"

viewctor::viewctor()
{
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

  m_stick_mult.y = m_stick_length;

  m_sphere_radius = m_mult*m_stick_radius;

  m_theta = 180.0f*acos(m_direct.y/m_stick_length)/PI;
}

void viewctor::set_stick()
{
  m_stick = LoadModelFromMesh(GenMeshCylinder(m_stick_radius, m_stick_length, 50));
}

void viewctor::set_sphere()
{
  m_sphere = LoadModelFromMesh(GenMeshSphere(m_sphere_radius,  25, 50));
}

void viewctor::posit_on_sphere(const spheroid &sphoid)
{
  const Vector3 base_posit
  { sphoid.get_posit() };

  Vector3 unit_direct
  { Vector3Normalize(m_direct) };

  const Vector3 radius_direct
  { Vector3Scale(unit_direct, sphoid.get_radius()) };

  const Vector3 onsphere
  { Vector3Add(radius_direct, base_posit) };

  set_posit(onsphere);
}

void viewctor::veloc_on_sphere(const spheroid &sphoid)
{
  set_direct(sphoid.get_veloc());

  m_veloc = true;
  m_accel = false;

  posit_on_sphere(sphoid);
}

void viewctor::accel_on_sphere(const spheroid &sphoid)
{
  set_direct(sphoid.get_accel());

  m_accel = true;
  m_veloc = false;

  posit_on_sphere(sphoid);
}

void viewctor::set_in_space()
{
  m_angle += m_delta;
}

void viewctor::display()
{
  Vector3 direct
  { m_direct };

  direct.x = m_direct.z;
  direct.y = 0.0f;
  direct.z = -m_direct.x;

  DrawModel(m_sphere, m_posit, 1.0f, RED);

  if (m_veloc)
  { m_color = BLUE; }

  if (m_accel)
  { m_color = GREEN; }

  DrawModelEx(m_stick, m_posit, direct, m_theta, m_stick_mult, m_color);

  DrawModel(m_sphere, Vector3Add(m_posit, m_direct), 1.0f, RED);
}
