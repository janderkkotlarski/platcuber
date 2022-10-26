#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "sphere.h"

enum class particle_type
{
  empty, mass, charge, spring, player, fixed, planet
};

class particle
{
private:
  std::vector <particle_type> m_type;

  Vector3 m_posit
  { Vector3Zero() };

  Vector3 m_veloc
  { Vector3Zero() };

  Vector3 m_accel
  { Vector3Zero() };

  float m_range
  { -1.0f };

  float m_mass
  { 1.0f };

  float m_charge
  { 0.0f };

  Color m_color
  { WHITE };

  float m_radius
  { 1.0f };

public:
  particle();

  void set_color(const Color &chroma);

  void display(sphere &ball);
};

float assign_mass(const particle_type &mass_type);



#endif // PARTICLE_H

