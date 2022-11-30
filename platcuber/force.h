#ifndef FORCE_H
#define FORCE_H

#include "raylib.h"

#include "enum_decs.h"
#include "particle.h"


class force
{
private:
  force_type m_type
  { force_type::none };

  const Vector3 m_distance
  { 0.0f, 0.0f, 0.0f };

  const float m_stiffness
  { 1.0f };

  const float m_gravity
  { 1.0f };
public:

  force();

  void type_reset();

  void type_select(particle &here, particle &there);

  Vector3 force_spring();

  Vector3 force_gravity();

  Vector3 acceleration(const float mass);
};



#endif // FORCE_H
