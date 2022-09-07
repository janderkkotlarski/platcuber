#ifndef SPHERE_H
#define SPHERE_H

#include "raylib.h"
#include "raymath.h"

class sphere
{
private:
  Vector3 m_position
  { Vector3Zero() };

  float m_radius
  { 1.0f };

  Color m_color
  { WHITE };

  Mesh m_mesh;

  Model m_model;
public:
  sphere();
};

#endif // SPHERE_H
