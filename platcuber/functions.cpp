#include "functions.h"

#include "raymath.h"

#include <vector>

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

bool posit_reflection(const Vector3 &inposit, const Vector3 &revposit)
{
  return false;
}

Vector3 normal_distance(const Vector3 &normal_posit, const Vector3 &normal_direct, const Vector3 &posit)
{
  const Vector3 way
  { Vector3Subtract(posit, normal_posit) };

  const Vector3 uno_direct
  { Vector3Normalize(normal_direct) };

  const float dot_scale
  { Vector3DotProduct(uno_direct, way) };

  const Vector3 normal_way
  { Vector3Scale(uno_direct, dot_scale) };

  return normal_way;
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

Vector3 orbit(const Vector3 &mid_posit, const Vector3 &cos_posit, const Vector3 &sin_posit,
              const float time, const float mult, const float period)
{
  const float phi
  { 2.0f*PI*time*mult/period };

  const Vector3 cosit
  { Vector3Scale(cos_posit, cos(phi)) };

  const Vector3 sinit
  { Vector3Scale(sin_posit, sin(phi)) };

  Vector3 oribt_posit
  { Vector3Add(cosit, sinit) };

  return Vector3Add(oribt_posit, mid_posit);
}

Vector3 strong(const Vector3 &here, const Vector3 &there, const float mult)
{
  return Vector3Scale(Vector3Subtract(there, here), mult);
}

void simple_rotate(Vector3 &element_posit, const std::vector <std::vector<float>> &matrix)
{
  const Vector3 sub
  { matrix[0][0]*element_posit.x + matrix[1][0]*element_posit.z,
    0.0f,
    matrix[0][1]*element_posit.x + matrix[1][1]*element_posit.z
  };

  element_posit = sub;
}

void rotate(const Vector3 &rotation_axis, Vector3 &rotator, const float theta)
{
  const Vector3 unit_axis
  { Vector3Normalize(rotation_axis) };

  const float para_mult
  { Vector3DotProduct(unit_axis, rotator) };

  const Vector3 para_rotator
  { Vector3Scale(unit_axis, para_mult) };

  Vector3 perp_rotator
  { Vector3Subtract(rotator, para_rotator) };

  const Vector3 crossed
  { Vector3CrossProduct(unit_axis, perp_rotator) };

  const Vector3 nura_rotator
  { Vector3Add(Vector3Scale(para_rotator, cos(theta)), Vector3Scale(crossed, sin(theta))) };

  rotator = Vector3Add(para_rotator, nura_rotator);
}
