#include "functions.h"

#include <stdlib.h>

#include "raymath.h"

float dim_scalar(const Vector3& vect, const int dim)
{
  if (dim < 1)
  { return vect.x; }
  else if (dim > 1)
  { return vect.z; }
  else
  { return vect.y; }
}

Vector3 dim_vector(const float scalar, const int dim)
{
  if (dim < 1)
  { return Vector3{ scalar, 0.0f, 0.0f }; }
  else if (dim > 1)
  { return Vector3{ 0.0f, 0.0f, scalar }; }
  else
  { return Vector3{ 0.0f, scalar, 0.0f }; }
}

void vector_reflect(Vector3 &invector, const Vector3 &revlector)
{
  const Vector3 uno_invector
  { Vector3Normalize(invector) };

  const Vector3 uno_revlector
  { Vector3Normalize(revlector) };

  const float dot
  { Vector3DotProduct(uno_invector, uno_revlector) };

  if (dot < 0.0f)
  {
    const Vector3 reflected
    { Vector3Scale(revlector, -2.0f*dot) };

    invector = Vector3Add(invector, reflected);
  }

}

void reflect(const Vector3 &reflect_posit, const float reflect_dist, const int reflect_dim,
             Vector3 &player_posit, const float player_dist, Vector3 &player_veloc)
{
  float sign
  { 1.0f };

  if (reflect_dist != 0.0f)
  { sign = reflect_dist/abs(reflect_dist); }

  const float reflect_point
  { dim_scalar(reflect_posit, reflect_dim) + reflect_dist };

  const float player_point
  { dim_scalar(player_posit, reflect_dim) - sign*player_dist };

  const float delta_point
  { sign*(player_point - reflect_point) };

  if (delta_point <= 0.0f)
  {
    const Vector3 anti2veloc
    { dim_vector(-2.0f*dim_scalar(player_veloc, reflect_dim), reflect_dim) };

    player_veloc = Vector3Add(player_veloc, anti2veloc);

    const float player_dot
    { reflect_point - sign*delta_point + sign*player_dist };

    if (reflect_dim < 1)
    { player_posit.x = player_dot; }
    else if (reflect_dim > 1)
    { player_posit.z = player_dot; }
    else
    { player_posit.y = player_dot; }
  }
}

