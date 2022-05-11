#ifndef CUBOID_H
#define CUBOID_H

#include "raylib.h"

class cuboid
{
private:
  const float m_side
  { 1.0f };

  Vector3 m_posit
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_veloc
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_accel
  { 0.0f, 0.0f, 0.0f };

  Color m_color
  { WHITE };

  Model m_model
  { LoadModelFromMesh(GenMeshCube(m_side, m_side, m_side)) };

public:
  cuboid();

  void display();
};

#endif // CUBOID_H
