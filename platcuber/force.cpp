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

  if (here.get_force_type() != force_type::none &&
      here.get_force_type() == there.get_force_type())
  { m_type = here.get_force_type(); }
}

Vector3 force::force_spring()
{
  if (m_type == force_type::spring)
  { return Vector3Scale(m_distance, m_stiffness); }

  return Vector3Zero();
}

Vector3 force::force_gravity()
{
  const float distance
  { 0.1f + Vector3Length(m_distance) };



  return Vector3Zero();
}
