#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include "raymath.h"

enum class particle_type
{
  none, mass, charge, spring, player
};

class particle
{
private:
  particle_type m_type
  { particle_type::none };

  Vector3 m_position
  { Vector3Zero() };

  Vector3 m_velocity
  { Vector3Zero() };

  Vector3 m_acceleration
  { Vector3Zero() };

  float m_range
  { 0.0f };

  float m_mass
  { 0.0f };

  float m_charge
  { 0.0f };

public:
  particle();
};

#endif // PARTICLE_H
