#ifndef VIDEO_H
#define VIDEO_H

#include "raylib.h"

#include "raymath.h"



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

  const int m_fps
  { 60 };

  Vector3 m_cam_pos
  { -8.0f, 0.0f, 0.0f };

  Vector3 m_cam_target
  { -0.0f, 0.0f, 0.0f };

  Vector3 m_cam_up
  { 0.0f, 0.0f, 1.0f };

  Vector3 m_light_pos
  { Vector3Negate(m_cam_pos) };

  spheroid m_player;

  cuboid  m_block;

  Model m_model;
  Model m_cube;

  int m_ambientLoc;

  const float m_lighting_color[4]
  { 0.1f, 0.1f, 0.1f, 1.0f };

public:
  video();

  void initialize();

  void init_screen();

  void init_camera();

  void init_shaders();

  void init_player();

  void light_screen();

  void light_camera();

  void light_models();

  void light_shader();

  void light_it();

  void run();
};

#endif // VIDEO_H
