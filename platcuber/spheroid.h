#ifndef SPHEROID_H
#define SPHEROID_H

#include "raylib.h"

class spheroid
{
private:
  const float m_radius
  { 2.0f };

  Vector3 m_posit
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_veloc
  { 2.0f, 0.0f, 0.0f };

  Vector3 m_accel
  { 0.0f, -2.0f, 0.0f };

  const float m_spring
  { 0.1f };

  const Vector3 m_spring_center
  { 0.0f, 0.0f, 0.0f };

  Color m_color
  { WHITE };

  const int m_opacity
  { 63 };

  Image m_image;

  Texture2D m_tex2d;

  Mesh m_mesh;

  Model m_model;

public:
  spheroid();

  Vector3 get_posit() const noexcept;

  Vector3 get_veloc() const noexcept;

  Vector3 get_accel() const noexcept;

  float get_radius() const noexcept;

  void set_pos(const Vector3 &posit);

  void set_veloc(const Vector3 &veloc);

  void set_accel(const Vector3 &accel);

  void set_color(const Color &color);

  void display();

  void wiresplay();

  void set_sphere();

  void set_shading(const Shader &shade);

  void move(const Vector3 &posit, const float time);
};

#endif // SPHEROID_H
