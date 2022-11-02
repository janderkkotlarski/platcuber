#include "particle.h"

particle::particle()
{

}

void particle::set_posit(const Vector3 &posit)
{ m_posit = posit; }

void particle::set_veloc(const Vector3 &veloc)
{ m_veloc = veloc; }

void particle::set_accel(const Vector3 &accel)
{ m_accel = accel; }

void particle::set_color(const Color &chroma)
{ m_color = chroma; }


void particle::display(sphere &ball)
{
  ball.set_posit(m_posit);

  ball.set_color(m_color);

  ball.set_radius(m_radius);

  ball.display();
}

void particle::move(const float delta)
{
  m_posit = Vector3Add(m_posit, Vector3Scale(m_veloc, delta));
}

float assign_mass(const particle_type &mass_type)
{
  switch (mass_type)
  {
    case particle_type::empty:
      return 0.0f;
      break;
    case particle_type::player:
      return 0.0000001f;
      break;
    case particle_type::mass:
      return 1.0f;
      break;
    case particle_type::planet:
      return 1.0e6f;
      break;
  }

  return 1.0f;
}

