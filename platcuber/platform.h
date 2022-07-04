#ifndef PLATFORM_H
#define PLATFORM_H

#include "raylib.h"

class platform
{
private:
  const float m_side
  { 1000000.0f };

  Vector3 m_posit
  { 0.0f, 0.0f, 0.0f };

  Color m_color
  { WHITE };

  Model m_model;

public:
  platform();

  Vector3 get_pos() noexcept;

  void set_pos(const Vector3 &pos);

  void display();

  void set_plane();
};

#endif // PLATFORM_H
