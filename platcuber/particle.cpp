#include "particle.h"

particle::particle()
{

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
  }

  return 1.0f;
}
