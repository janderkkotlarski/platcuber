#ifndef SPRING_H
#define SPRING_H

#include "raylib.h"

class spring
{
private:
  const Vector3 m_posit
  { 0.0f, 0.0f, 0.0f };

  const Vector3 m_konstant
  { 1.0f, 1.0f, 1.0f };

  const float m_mult
  { -1.0f };

public:
  spring();

  void accelerate(const Vector3 &posit, Vector3 &accel);
};

#endif // SPRING_H
