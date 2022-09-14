#ifndef VIDEO_H
#define VIDEO_H

#include "raylib.h"

#include "raymath.h"


#include "platform.h"
#include "spheroid.h"
#include "cuboid.h"
#include "chromatic.h"
#include "viewctor.h"
#include "spring.h"

#include "sphere.h"

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

  Shader m_shader;

  const float m_fog_median
  { 0.02f };

  float m_fog_strength
  { m_fog_median };

  int m_fog_strength_pos
  { 0 };

  const int m_fps
  { 60 };

  Vector3 m_cam_pos
  { 0.0f, 2.0f, 40.0f };

  Vector3 m_cam_target
  { 0.0f, 2.0f, 0.0f };

  Vector3 m_cam_up
  { 0.0f, 1.0f, 0.0f };

  Vector3 m_light_pos
  { 0.0f, 0.0f, 0.0f };

  spheroid m_player;

  platform m_platform;

  viewctor m_veloctor;

  viewctor m_acceltor;

  chromatic m_chroma;

  cuboid m_block;

  spring m_spring
  { Vector3{ 0.0f, 8.0f, 0.0f } };

  const Vector3 m_gravaccel
  { 0.0f, -10.0f, 0.0f };

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

  sphere m_ball;

public:
  video();

  void initialize();

  void init_screen();

  void init_camera();

  void init_shaders();

  void init_actors();

  void init_platform();

  void init_player();

  void init_viewctor();

  void spectral_pogo();

  void spectral_choice();

  void light_screen();

  void light_camera();

  void light_models();

  void light_textures();

  void light_shader();

  void light_shadels();

  void light_it();

};

#endif // VIDEO_H
