#ifndef VIDEO_H
#define VIDEO_H

#include "raylib.h"

#include "raymath.h"


#include "platform.h"
#include "spheroid.h"
#include "cuboid.h"
#include "chromatic.h"

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
  { 0.0f, 0.0f, 0.0f };

  spheroid m_player;

  platform m_platform;

  chromatic m_chroma;

  cuboid  m_block;

  Model m_model;
  Model m_cube;
  Model m_sphere;

  Image m_image;

  Texture m_tex2d;

  int m_ambientLoc;

  float m_time
  { 0.0f };

  const float m_period
  { 8.0f };

  const float m_lighting_color[4]
  { 0.1f, 0.1f, 0.1f, 1.0f };

public:
  video();

  void initialize();

  void init_screen();

  void init_camera();

  void init_shaders();

  void init_platform();

  void init_player();

  void spectral_pogo();

  void spectral_choice();

  void light_screen();

  void light_camera();

  void light_models();

  void light_textures();

  void light_shader();

  void light_shadels();

  void light_it();

  void run();
};

#endif // VIDEO_H
