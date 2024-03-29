#ifndef FORCE_H
#define FORCE_H

#include "enum_decs.h"
#include "particle.h"

#include "raylib.h"

class force
{
private:
  force_type m_type
  { force_type::none };

  Vector3 m_distance
  { 0.0f, 0.0f, 0.0f };

  float m_mass_here
  { 0.0f };

  float m_mass_there
  { 0.0f };

  const float m_stiffness
  { 0.1f };

  const float m_gravity
  { 1.0f };

  const float m_expo_strength
  { 1.0f };

  const float m_expo_decay
  { 0.01f };

public:

  force();

  void type_reset();

  void type_select(particle &here, particle &there);

  void force_return(particle &here, particle &there);

  Vector3 force_spring();

  Vector3 force_gravity();

  Vector3 force_expo();
};

void juggle(force grip, std::vector <particle> &elements, const float delta);

void showing(std::vector <particle> &elements, sphere &ball);

#endif // FORCE_H
