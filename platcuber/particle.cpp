#include "particle.h"

particle::particle()
{

}

Vector3 particle::get_posit()
{ return m_posit; }

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

void particle::null_force()
{ m_force = Vector3Zero(); }


void particle::move(const float delta)
{
  m_posit = Vector3Add(m_posit, Vector3Scale(m_veloc, 0.5f*delta));
  m_veloc = Vector3Add(m_veloc, Vector3Scale(m_accel, delta));
  m_posit = Vector3Add(m_posit, Vector3Scale(m_veloc, 0.5f*delta));
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

