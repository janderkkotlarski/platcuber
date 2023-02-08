#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "raylib.h"

#include <string>
#include <vector>

float dim_scalar(const Vector3 &vect, const int dim);

Vector3 dim_vector(const float scalar, const int dim);

void vector_reflect(Vector3 &invector, const Vector3 &revlector);

Vector3 normal_distance(const Vector3 &normal_posit, const Vector3 &normal_direct, const Vector3 &posit);

bool posit_reflection(const Vector3 &inposit, const Vector3 &revposit);

void reflect(const Vector3 &reflect_posit, const float reflect_dist, const int reflect_dim,
             Vector3 &player_posit, const float player_dist, Vector3 &player_veloc);

Vector3 orbit(const Vector3 &mid_posit, const Vector3 &cos_posit, const Vector3 &sin_posit,
              const float time, const float mult, const float period);

Vector3 strong(const Vector3 &here, const Vector3 &there, const float mult);

void write_as_text(const int &input);

void write_as_text(const float &input);

void writing_text(const std::string &text);

void simple_rotate(Vector3 &element_posit, const std::vector <std::vector<float>> &matrix);

void rotate(const Vector3 &rotation_axis, Vector3 &rotator, const float theta);

#endif // FUNCTIONS_H
