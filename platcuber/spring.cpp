#include "spring.h"

#include "raymath.h"

spring::spring()
{

}

void spring::accelerate(const Vector3 &posit, Vector3 &accel)
{
  const Vector3 sub_accel
  { Vector3Add(m_posit, Vector3Scale(posit, m_mult)) };

  accel = Vector3Add(accel, sub_accel);
}
