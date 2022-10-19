#include "force.h"

#include "raymath.h"

force::force()
{

}

Vector3 force::force_spring()
{ return Vector3Scale(m_separation, m_stiffness); }

Vector3 force::force_gravity()
{
  const float dist
  { 0.1f };


  return Vector3Zero();
}
