#include "sphere.h"

sphere::sphere()
{}

void sphere::set_radius(const float radius)
{ m_radius = radius; }

void sphere::set_posit(const Vector3 &position)
{ m_position = position; }

void sphere::set_color(const Color &chroma)
{ m_color = chroma; }

void sphere::set_sphere()
{ m_model = LoadModelFromMesh(GenMeshSphere(1.0f, 25, 50)); }

void sphere::set_shading(Shader &shade)
{ m_model.materials[0].shader = shade; }

void sphere::display()
{ DrawModel(m_model, m_position, m_radius, m_color); }
