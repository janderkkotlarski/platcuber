#include "spring.h"

#include "raymath.h"

spring::spring()
{

}

spring::spring(const Vector3 &posit)
  : m_posit(posit)
{

}

Vector3 spring::accelerate(const Vector3 &posit)
{
  const Vector3 accel
  { Vector3Add(m_posit, Vector3Scale(posit, m_mult)) };

  return accel;
}
