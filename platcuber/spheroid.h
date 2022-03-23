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

public:
  spheroid();

  void display();
};

#endif // SPHEROID_H
