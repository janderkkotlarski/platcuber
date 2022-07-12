#ifndef VIEWCTOR_H
#define VIEWCTOR_H

#include "raylib.h"
#include "raymath.h"

#include "spheroid.h"

class viewctor
{
private:
  Vector3 m_posit
  { 0.0f, 2.0f, 0.0f };

  Vector3 m_direct
  { 2.0f, -11.0f, 6.0f };

  Color m_color
  { WHITE };

  Model m_stick;

  const float m_ratio
  { 0.02f };

  float m_stick_length
  { Vector3Length(m_direct) };

  float m_stick_radius
  { m_ratio*m_stick_length };

  Model m_sphere;

  const float m_mult
  { 2.0f };

  float m_sphere_radius
  { m_mult*m_stick_radius };

  float m_angle
  { 90.0f };

  const float m_delta
  { 0.0f };

  float m_theta
  { 0.0f };

public:
  viewctor();

  void set_posit(const Vector3 &posit);

  void set_direct(const Vector3 &direct);

  void set_on_sphere(const spheroid &sphoid);

  void set_in_space();

  void remeasure();

  void set_stick();

  void set_sphere();

  void display();
};

#endif // VIEWCTOR_H
