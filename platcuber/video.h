#ifndef VIDEO_H
#define VIDEO_H

#include "raylib.h"

#include "spheroid.h"
#include "cuboid.h"

class video
{
  int m_screen_side
  { 800 };

  bool m_windeath
  { false };

  bool m_repeat
  { true };

  Camera m_camera;

  Shader m_lighting_shader;

  const float m_fps
  { 60.0f };

  Vector3 m_cam_pos
  { -4.0f, 0.0f, 0.0f };

  Vector3 m_cam_target
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_cam_up
  { 0.0f, 0.0f, 1.0f };

  spheroid m_player;

public:
  video();

  void initialize();

  void run();
};

#endif // VIDEO_H
