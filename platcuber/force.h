#ifndef FORCE_H
#define FORCE_H

#include "raylib.h"

enum class force_type
{
  none, gravity, repulse,
  spring
};

class force
{
private:
  force_type m_type
  { force_type::none };

  const Vector3 m_separation
  { 0.0f, 0.0f, 0.0f };

  const float m_stiffness
  { 1.0f };
public:

  force();

  Vector3 force_spring();
};



#endif // FORCE_H