#include "spheroid.h"

spheroid::spheroid()
{

}

void spheroid::display()
{
  // DrawSphere(m_posit, 0.5f*m_side, m_color);

  DrawModel(m_model, m_posit, 1.0f, m_color);
}

void spheroid::set_sphere()
{ m_model = LoadModelFromMesh(GenMeshSphere(m_side, 30, 30)); }

void spheroid::set_shading(const Shader &shade)
{ m_model.materials[0].shader = shade; }
