#ifndef PARTICLE_H
#define PARTICLE_H

#include "enum_decs.h"
#include "sphere.h"

#include "raylib.h"
#include "raymath.h"

#include <vector>

class particle
{
private:
  std::vector <particle_type> m_type;

  force_type m_force_type
  { force_type::none };

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

  particle(const force_type ftp);

  particle(const float range);

  force_type get_force_type();

  Vector3 get_posit();

  Vector3 get_veloc();

  float get_mass();

  void set_posit(const Vector3 &posit);
  void set_veloc(const Vector3 &veloc);
  void set_accel(const Vector3 &accel);


  void set_color(const Color &chroma);

  void display(sphere &ball);

  void null_force();  

  void add_force(const Vector3 &force);
  void sub_force(const Vector3 &force);

  void accelerate();

  void move(const float delta);
};

float assign_mass(const particle_type &mass_type);





#endif // PARTICLE_H

