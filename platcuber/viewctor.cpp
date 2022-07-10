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
}

void viewctor::set_stick()
{
  m_stick = LoadModelFromMesh(GenMeshCylinder(m_stick_radius, m_stick_length, 50));
}

void viewctor::set_sphere()
{
  m_sphere = LoadModelFromMesh(GenMeshSphere(m_sphere_radius,  25, 50));
}

void viewctor::display()
{
  DrawModel(m_stick, m_direct, 1.0f, GREEN);
}
