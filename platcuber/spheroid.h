#ifndef SPHEROID_H
#define SPHEROID_H

#include "raylib.h"

class spheroid
{
private:
  const float m_side
  { 1.0f };

  Vector3 m_posit
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_veloc
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_accel
  { 0.0f, 0.0f, 0.0f };

  Color m_color
  { WHITE };

  Image m_image;

  Texture2D m_tex2d;

  Mesh m_mesh;

  Model m_model;

public:
  spheroid();

  Vector3 get_pos() noexcept;

  void set_pos(const Vector3 &pos);

  void display();

  void set_sphere();

  void set_shading(const Shader &shade);
};

#endif // SPHEROID_H
