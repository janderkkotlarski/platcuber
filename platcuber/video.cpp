#include "video.h"



#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"


#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#include "functions.h"

video::video()
{
  initialize();
}

void video::initialize()
{
  light_screen();
  light_camera();

  init_shaders();
  init_platform();

  light_models();
  light_textures();
  // light_shader();

  init_actors();
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
  // m_dark_shader = LoadShader("base_lighting.vs", "lighting.fs");

  m_dark_shader = LoadShader("base_lighting.vs", "dark_fog.fs");

  m_dark_shader.locs[LOC_MATRIX_MODEL] =
      GetShaderLocation(m_dark_shader, "matModel");
  m_dark_shader.locs[LOC_VECTOR_VIEW] =
      GetShaderLocation(m_dark_shader, "viewPos");

  m_ambientLoc = GetShaderLocation(m_dark_shader, "ambient");
  SetShaderValue(m_dark_shader, m_ambientLoc, m_lighting_color, 0);

  m_fog_strength_pos = GetShaderLocation(m_dark_shader, "fogDensity");
  SetShaderValue(m_dark_shader, m_fog_strength_pos, &m_fog_strength, UNIFORM_FLOAT);

  m_lighting_shader = LoadShader("base_lighting.vs", "lighting.fs");

  m_lighting_shader.locs[LOC_MATRIX_MODEL] =
      GetShaderLocation(m_lighting_shader, "matModel");
  m_lighting_shader.locs[LOC_VECTOR_VIEW] =
      GetShaderLocation(m_lighting_shader, "viewPos");

  m_ambientLoc = GetShaderLocation(m_lighting_shader, "ambient");
  SetShaderValue(m_lighting_shader, m_ambientLoc, m_lighting_color, 0);
}

void video::init_actors()
{
  m_ball.set_sphere();

  m_ball.set_shading(m_lighting_shader);

  m_alpha.set_posit(m_alpha_posit);
  m_alpha.set_veloc(m_alpha_veloc);
  m_alpha.set_color(RED);


  m_beta.set_posit(m_beta_posit);
  m_beta.set_veloc(m_beta_veloc);
  m_beta.set_color(BLUE);
}

void video::init_platform()
{
  m_platform.set_plane();
}

void video::light_screen()
{
  const int screenWidth = 1400;
  const int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic lighting");
}

void video::light_camera()
{
  m_camera.position = m_cam_pos;      // Camera position
  m_camera.target = m_cam_target;      // Camera looking at point
  m_camera.up = m_cam_up;

  m_camera.fovy = 45.0f;                                // Camera field-of-view Y
  m_camera.type = CAMERA_PERSPECTIVE;                  // Camera mode type

  UpdateCamera(&m_camera);
}

void video::light_models()
{
  m_model = LoadModelFromMesh(GenMeshPlane(10.0f, 10.0f, 100, 100));
  m_cube = LoadModelFromMesh(GenMeshCube(2.0f, 4.0f, 2.0f));
  m_sphere = LoadModelFromMesh(GenMeshSphere(0.2f, 20, 20));
}

void video::light_textures()
{
  m_image = LoadImage("cube_face_spectrum_.png");

  m_tex2d = LoadTextureFromImage(m_image);

  m_model.materials[0].maps[MAP_DIFFUSE].texture = m_tex2d;
}

void video::roster_deez()
{
  sphere ball;

  for (int x{0}; x < m_side_amount; ++x)
  {
    m_deez.push_back(ball);
  }
}

void video::show_deez()
{
  for (const sphere &ball: m_deez)
  { ball.display(); }
}

void video::light_it()
{
    // Initialization
    //--------------------------------------------------------------------------------------

  m_light_pos = m_light_start_pos;

  /*
  Light dark_light
  { 0 };
  dark_light = CreateLight(LIGHT_POINT, m_light_pos, Vector3Zero(), m_chroma.get_color(), m_dark_shader);
  */

  Light a_light
  { 0 };
  a_light = CreateLight(LIGHT_POINT, m_light_pos, Vector3Zero(), WHITE, m_lighting_shader);



  roster_deez();

  // SetCameraMode(m_camera, CAMERA_ORBITAL);  // Set an orbital camera mode

  SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())            // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&m_camera);              // Update camera

    // if (IsKeyPressed(KEY_Y)) { bulb.enabled = !bulb.enabled; }
    // UpdateLightValues(shader, bulb);


    // Check key inputs to enable/disable lights
    // if (IsKeyPressed(KEY_W)) { dark_light.enabled = !dark_light.enabled; }


    // Update light values (actually, only enable/disable them)
    // UpdateLightValues(m_dark_shader, dark_light);
    // UpdateLightValues(m_lighting_shader, a_light);

    // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
    float cameraPos[3] = { m_camera.position.x, m_camera.position.y, m_camera.position.z };
    // SetShaderValue(m_dark_shader, m_fog_strength_pos, &m_fog_strength, UNIFORM_FLOAT);

    // SetShaderValue(m_dark_shader, m_dark_shader.locs[LOC_VECTOR_VIEW], cameraPos, UNIFORM_VEC3);
    SetShaderValue(m_lighting_shader, m_lighting_shader.locs[LOC_VECTOR_VIEW], cameraPos, UNIFORM_VEC3);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

      ClearBackground(BLACK);

      BeginMode3D(m_camera);
      {
          // m_platform.display();

          DrawGrid(10, 2.0f);


          DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{3.0f, 0.0f, 0.0f}, PURPLE);
          DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, 3.0f}, ORANGE);

          m_alpha.display(m_ball);

          m_beta.display(m_ball);

      }
      EndMode3D();

      DrawFPS(10, 10);

      // DrawText("Use keys [Y] to toggle light", 10, 40, 20, DARKGRAY);

      const float delta
      { 1.0f/float(m_fps) };

      m_time += delta;

      while (m_time >= m_period)
      { m_time -= m_period; }

      m_alpha.null_force();

      m_beta.null_force();

      m_force.type_select(m_alpha, m_beta);
      m_force.force_return(m_alpha, m_beta);

      m_alpha.accelerate();
      m_alpha.move(delta);

      m_beta.accelerate();
      m_beta.move(delta);

      m_fog_strength = m_fog_median + m_fog_median*sin(2.0f*PI*m_time/m_period);

      // UpdateLightValues(m_dark_shader, dark_light);
      UpdateLightValues(m_lighting_shader, a_light);


    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadModel(m_model);     // Unload the model
  UnloadModel(m_cube);      // Unload the model
  UnloadShader(m_dark_shader);   // Unload shader

  CloseWindow();          // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
}

