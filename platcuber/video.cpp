#include "video.h"

#include "rlights.h"
#define RLIGHTS_IMPLEMENT

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

video::video()
{

}

void video::initialize()
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(m_screen_side, m_screen_side, "beatalizer");

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
}

void video::run()
{
  Light bulb;

  initialize();

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
