#ifndef VIEWCTOR_H
#define VIEWCTOR_H

#include "raylib.h"

#include "spheroid.h"

class viewctor
{
private:
  Vector3 m_posit
  { 0.0f, 2.0f, 0.0f };

  Vector3 m_direct
  { 2.0f, 0.0f, 2.0f };

  float m_mult;

  Color m_color
  { WHITE };

  Model m_stick;

  float m_stick_radius
  { 0.05f };

  float m_stick_length
  { 1.0f };

  Model m_sphere;

  float m_sphere_radius
  { 0.1f };

  float m_angle
  { 0.0f };

  const float m_delta
  { 0.1f };

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
