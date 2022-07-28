#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "raylib.h"

float dim_scalar(const Vector3 &vect, const int dim);

Vector3 dim_vector(const float scalar, const int dim);

void vector_reflect(Vector3 &invector, const Vector3 &revlector);

Vector3 normal_distance(const Vector3 &normal_posit, const Vector3 &normal_direct, const Vector3 &posit);

bool posit_reflection(const Vector3 &inposit, const Vector3 &revposit);

void reflect(const Vector3 &reflect_posit, const float reflect_dist, const int reflect_dim,
             Vector3 &player_posit, const float player_dist, Vector3 &player_veloc);

#endif // FUNCTIONS_H
