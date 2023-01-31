#ifndef VIDEO_H
#define VIDEO_H

#include "enum_decs.h"
#include "platform.h"
#include "force.h"
#include "particle.h"
#include "sphere.h"

#include "raylib.h"
#include "raymath.h"

#include <vector>
#include <chrono>

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

  Shader m_dark_shader;

  const float m_fog_median
  { 0.05f };

  float m_fog_strength
  { m_fog_median };

  int m_fog_strength_pos
  { 0 };

  const int m_fps
  { 60 };

  const int m_fps_mult
  { 200 };

  const int m_cps
  { m_fps*m_fps_mult };

  Vector3 m_cam_pos
  { 0.0f, 20.0f, -20.0f };

  Vector3 m_cam_target
  { 0.0f, 2.0f, 0.0f };

  Vector3 m_cam_up
  { 0.0f, 0.0f, 1.0f };

  const Vector3 m_light_start_pos
  { 0.0f, 100.0f, 0.0f };

  Vector3 m_light_pos
  { 0.0f, 0.0f, 0.0f };

  platform m_platform;

  Model m_model;
  Model m_cube;
  Model m_sphere;

  Image m_image;

  Texture m_tex2d;

  int m_ambientLoc;

  float m_time
  { 0.0f };

  const float m_period
  { 4.0f };

  const float m_mult
  { 1.0f };

  const Vector3 m_mid_posit
  { 0.0f, 2.0f, 0.0f };

  const Vector3 m_cos_posit
  { -6.0f, 0.0f, 0.0f };

  const Vector3 m_sin_posit
  { 3.0f, 0.0f, 3.0f };

  const float m_lighting_color[4]
  { 0.1f, 0.1f, 0.1f, 1.0f };

  sphere m_ball;

  std::vector <sphere> m_deez;

  const float m_seperation
  { 10.0f };

  const int m_side_amount
  { 2 };

  force m_force;

  particle m_alpha
  { force_type::gravity };

  const Vector3 m_alpha_posit
  { 0.0f, 0.0f, -4.0f };

  const Vector3 m_alpha_veloc
  { -1.1f, 0.0f, 0.0f };

  particle m_beta
  { force_type::gravity };

  const Vector3 m_beta_posit
  { Vector3Negate(m_alpha_posit) };

  const Vector3 m_beta_veloc
  { Vector3Negate(Vector3Scale(m_alpha_veloc, 1.2f)) };

  particle m_gamma
  { force_type::gravity };

  const Vector3 m_gamma_posit
  { Vector3Scale(m_alpha_posit, 3.0f) };

  const Vector3 m_gamma_veloc
  { Vector3Negate(Vector3Scale(m_alpha_veloc, -1.2f)) };

  particle m_daleth
  { force_type::gravity };

  const Vector3 m_daleth_posit
  { Vector3Scale(m_alpha_posit, -2.0f) };

  const Vector3 m_daleth_veloc
  { Vector3Negate(Vector3Scale(m_alpha_veloc, 1.0f)) };

  particle m_element
  { force_type::gravity };

  Vector3 m_element_posit
  { Vector3Scale(m_alpha_posit, 1.0f) };

  Vector3 m_element_veloc
  { Vector3Negate(Vector3Scale(m_alpha_veloc, 1.5f)) };

  const int m_element_amount
  { 4 };

  const float m_element_theta
  { 2.0f*PI/float(m_element_amount) };

  const std::vector <std::vector <float>> m_element_rotation
  {
    { 1.0f*cos(m_element_theta), 1.0f*sin(m_element_theta) },
    { 1.0f*-sin(m_element_theta), 1.0f*cos(m_element_theta) }
  };

  // { cos(theta), sin(theta) }
  // { -sin(theta), cos(theta) }

  std::vector <particle> m_elements;



  const float m_strong_mult
  { 0.4f };

  int m_min_loops
  { 1000000000 };

public:
  video();

  void initialize();

  void init_screen();

  void init_camera();

  void init_shaders();

  void init_actors();

  void init_platform();

  void init_player();

  void spectral_pogo();

  void spectral_choice();

  void light_screen();

  void light_camera();

  void light_models();

  void light_textures();

  void light_shadels();

  void roster_deez();

  void show_deez();

  void light_it();

};

#endif // VIDEO_H
