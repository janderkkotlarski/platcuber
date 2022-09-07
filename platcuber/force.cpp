#include "force.h"

#include "raymath.h"

force::force()
{

}

Vector3 force::force_spring()
{ return Vector3Scale(m_separation, m_stiffness); }
