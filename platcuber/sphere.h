#ifndef SPHERE_H
#define SPHERE_H

#include "raylib.h"
#include "raymath.h"

class sphere
{
private:
  float m_radius
  { 1.0f };

  Vector3 m_position
  { Vector3Zero() };

  Color m_color
  { WHITE };

  Model m_model;
public:
  sphere();

  void set_radius(const float radius);

  void set_posit(const Vector3 &position);

  void set_color(const Color &chroma);

  void set_sphere();

  void set_shading(Shader &shade);

  void display();
};

#endif // SPHERE_H
