#include "force.h"

#include "raymath.h"

force::force()
{

}

void force::type_reset()
{ m_type = force_type::none; }

Vector3 force::force_spring()
{ return Vector3Scale(m_distance, m_stiffness); }

Vector3 force::force_gravity()
{
  const float distance
  { 0.1f + Vector3Length(m_distance) };



  return Vector3Zero();
}
