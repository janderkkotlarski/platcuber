#include "video.h"



#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"


#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

video::video()
{
  initialize();
}

void video::initialize()
{
  init_screen();

  init_camera();
}

void video::init_screen()
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(m_screen_side, m_screen_side, "platcuber");

  SetTargetFPS(m_fps);
}

void video::init_camera()
{
  m_camera.position = m_cam_pos;    // Camera position
  m_camera.target = m_cam_target;      // Camera looking at point
  m_camera.up = m_cam_up;          // Camera up vector (rotation towards target)


  m_camera.fovy = 45.0f;                                // Camera field-of-view Y
  m_camera.type = CAMERA_PERSPECTIVE;                  // Camera mode type

  UpdateCamera(&m_camera);
}

void video::init_shaders()
{
  m_lighting_shader = LoadShader("base_lighting.vs", "lighting.fs");
  // LoadShader("base_lighting.vs", "lighting.fs");

  m_lighting_shader.locs[LOC_MATRIX_MODEL] =
      GetShaderLocation(m_lighting_shader, "matModel");
  m_lighting_shader.locs[LOC_VECTOR_VIEW] =
      GetShaderLocation(m_lighting_shader, "viewPos");

  const float lighting_color[4]
  { 0.8f, 0.8f, 0.8f, 1.0f };

  const int ambientLoc = GetShaderLocation(m_lighting_shader, "ambient");
  SetShaderValue(m_lighting_shader, ambientLoc, lighting_color, 0);

}

void video::init_player()
{
  m_player.set_sphere();
  // m_player.set_shading(m_lighting_shader);
}

void video::run()
{
  Model erehps = LoadModelFromMesh(GenMeshSphere(2.0f, 20, 20));

  Shader shader = LoadShader("base_lighting.vs", "lighting.fs");

  shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  const int ambientLoc = GetShaderLocation(shader, "ambient");

  const float lighting_color[4]
  { 10.0f, 1.0f, 1.0f, 1.0f };
  SetShaderValue(shader, ambientLoc, lighting_color, UNIFORM_VEC4);

  erehps.materials[0].shader = shader;


  // init_shaders();

  const Vector3 light_target
  { 0.0f, 0.0f, 0.0f };

  const Vector3 light_source
  { 0.0f, 2.0f, 0.0f };

  erehps.materials[0].shader = shader;


  Light bulb
  { CreateLight(LIGHT_POINT, light_source, light_target, RED, shader) };


  // { CreateLight(LIGHT_POINT, m_cam_target, m_cam_target, RED, shader) };

  // init_player();

  // SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  // InitWindow(m_screen_side, m_screen_side, "beatalizer");

  // SetTargetFPS(60);

  while (!m_windeath)                // Detect window close button or ESC key
  {
    if (IsKeyPressed(KEY_DELETE))
    { m_windeath = true; }

    UpdateLightValues(shader, bulb);

    BeginDrawing();
    {


      ClearBackground(BLACK);

      BeginMode3D(m_camera);
      {
        // DrawSphereEx(Vector3{0.0f, 0.0f, 0.0f}, 0.2f, 8, 8, WHITE);

        DrawSphereEx(Vector3{1.0f, 0.0f, 0.0f}, 0.1f, 8, 8, RED);

        DrawSphereEx(Vector3{-1.0f, 0.0f, 0.0f}, 0.1f, 8, 8, GREEN);

        DrawSphereEx(Vector3{0.0f, 1.0f, 0.0f}, 0.1f, 8, 8, YELLOW);

        DrawSphereEx(Vector3{0.0f, -1.0f, 0.0f}, 0.1f, 8, 8, BLUE);

        DrawSphereEx(Vector3{0.0f, 0.0f, 1.0f}, 0.1f, 8, 8, ORANGE);

        DrawSphereEx(Vector3{0.0f, 0.0f, -1.0f}, 0.1f, 8, 8, PURPLE);

        // DrawSphereEx(bulb.position, 0.2f, 8, 8, YELLOW);

        // DrawSphereEx(m_cam_target, 1.0f, 10, 10, GREEN);

        // m_player.display();

        // DrawCubeV(Vector3{ 0.0f, 2.0f, 0.0f }, Vector3{ 0.5f, 0.5f, 0.5f }, RED);

        // m_player.display();

        DrawModel(erehps, light_target, 0.2f, WHITE);
      }
      EndMode3D();
    }
    EndDrawing();
  }
}

