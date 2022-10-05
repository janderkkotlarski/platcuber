#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

#include "raylib.h"
#include "raymath.h"

enum class particle_type
{
  empty, mass, charge, spring, player, fixed
};

class particle
{
private:
  std::vector <particle_type> m_type;

  Vector3 m_position
  { Vector3Zero() };

  Vector3 m_velocity
  { Vector3Zero() };

  Vector3 m_acceleration
  { Vector3Zero() };

  float m_range
  { -1.0f };

  float m_mass
  { 1.0f };

  float m_charge
  { 0.0f };

public:
  particle();
};

float assign_mass(const particle_type &mass_type);

#endif // PARTICLE_H
