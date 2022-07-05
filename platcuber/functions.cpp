#include "functions.h"

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

void reflect(const Vector3 &reflect_posit, const float reflect_dist, const int reflect_dim,
             Vector3 &player_posit, const float player_dist, Vector3 &player_veloc)
{

}

