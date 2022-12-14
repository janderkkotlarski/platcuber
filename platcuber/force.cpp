#include "force.h"

#include "raymath.h"

force::force()
{

}

void force::type_reset()
{ m_type = force_type::none; }

void force::type_select(particle &here, particle &there)
{
  m_type = force_type::none;

  m_distance = Vector3Zero();

  m_mass_here = 0.0f;
  m_mass_there = 0.0f;

  if (here.get_force_type() != force_type::none &&
      here.get_force_type() == there.get_force_type())
  {
    m_type = here.get_force_type();

    m_distance = Vector3Subtract(there.get_posit(), here.get_posit());

    m_mass_here = here.get_mass();
    m_mass_there = there.get_mass();
  }
}

Vector3 force::force_spring()
{
  if (m_type == force_type::spring)
  { return Vector3Scale(m_distance, m_stiffness); }

  return Vector3Zero();
}

Vector3 force::force_gravity()
{
  if (m_type == force_type::gravity)
  {
    const float distance
    { 0.1f + Vector3Length(m_distance) };

    const float grav
    { m_gravity*m_mass_here*m_mass_there/(distance*distance*distance) };

    return Vector3Scale(m_distance, grav);
  }

  return Vector3Zero();
}
