#include "video.h"

#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

video::video()
{
  // initialize();

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(m_screen_side, m_screen_side, "platcuber");

  SetTargetFPS(m_fps);

  m_camera.position = m_cam_pos;    // Camera position
  m_camera.target = m_cam_target;      // Camera looking at point
  m_camera.up = m_cam_up;          // Camera up vector (rotation towards target)
  m_camera.fovy = 45.0f;                                // Camera field-of-view Y
  m_camera.type = CAMERA_PERSPECTIVE;                  // Camera mode type

  // UpdateCamera(&m_camera);

  m_lighting_shader = LoadShader("base_lighting.vs", "lighting.fs");

  m_lighting_shader.locs[LOC_MATRIX_MODEL] =
      GetShaderLocation(m_lighting_shader, "matModel");
  m_lighting_shader.locs[LOC_VECTOR_VIEW] =
      GetShaderLocation(m_lighting_shader, "viewPos");

  // int ambientLoc = GetShaderLocation(m_lighting_shader, "ambient");
  //    SetShaderValue(m_lighting_shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, 0);

  Light bulb
  { CreateLight(LIGHT_POINT, m_cam_pos, m_cam_target, WHITE, m_lighting_shader) };

  m_player.set_sphere();

  m_player.set_shading(m_lighting_shader);
}

void video::initialize()
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(m_screen_side, m_screen_side, "platcuber");

  SetTargetFPS(m_fps);
  m_camera.position = m_cam_pos;    // Camera position
  m_camera.target = m_cam_target;      // Camera looking at point
  m_camera.up = m_cam_up;          // Camera up vector (rotation towards target)


  m_camera.fovy = 45.0f;                                // Camera field-of-view Y
  m_camera.type = CAMERA_PERSPECTIVE;                  // Camera mode type

  UpdateCamera(&m_camera);

  m_lighting_shader = LoadShader("base_lighting.vs", "lighting.fs");
  // LoadShader("base_lighting.vs", "lighting.fs");

  m_lighting_shader.locs[LOC_MATRIX_MODEL] =
      GetShaderLocation(m_lighting_shader, "matModel");
  m_lighting_shader.locs[LOC_VECTOR_VIEW] =
      GetShaderLocation(m_lighting_shader, "viewPos");

  int ambientLoc = GetShaderLocation(m_lighting_shader, "ambient");
  //    SetShaderValue(m_lighting_shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, 0);

  Light bulb;
  // bulb = CreateLight(LIGHT_POINT, m_cam_pos, m_cam_target, WHITE, m_lighting_shader);
  // { CreateLight(LIGHT_POINT, m_cam_pos, m_cam_target, WHITE, m_lighting_shader) };

  m_player.set_sphere();

  m_player.set_shading(m_lighting_shader);

}

void video::run()
{




  // SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  // InitWindow(m_screen_side, m_screen_side, "beatalizer");

  // SetTargetFPS(60);

  while (!m_windeath)                // Detect window close button or ESC key
  {
    if (IsKeyPressed(KEY_DELETE))
    { m_windeath = true; }

    BeginDrawing();
    {
      ClearBackground(BLACK);

      BeginMode3D(m_camera);
      {
        m_player.display();
      }
      EndMode3D();
    }
    EndDrawing();
  }
}
