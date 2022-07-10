#ifndef VIEWCTOR_H
#define VIEWCTOR_H

#include "raylib.h"

#include "spheroid.h"

class viewctor
{
private:
  Vector3 m_posit
  { 3.0f, 0.0f, 0.0f };

  Vector3 m_direct
  { 0.0f, 2.0f, 0.0f };

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
  { 1.0f };

public:
  viewctor();

  void set_posit(const Vector3 &posit);

  void set_direct(const Vector3 &direct);

  void set_on_sphere(const spheroid &sphoid);

  void restick();

  void set_stick();

  void set_sphere();

  void display();
};

#endif // VIEWCTOR_H
