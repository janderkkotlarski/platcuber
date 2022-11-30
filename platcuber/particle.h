#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "force.h"
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

  Vector3 m_force
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

  Vector3 get_posit();

  void set_posit(const Vector3 &posit);
  void set_veloc(const Vector3 &veloc);
  void set_accel(const Vector3 &accel);

  void set_color(const Color &chroma);

  void display(sphere &ball);

  void null_force();

  void add_force(force &fork, particle &part);

  void move(const float delta);
};

float assign_mass(const particle_type &mass_type);



#endif // PARTICLE_H

