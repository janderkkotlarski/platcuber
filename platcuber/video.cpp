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

  init_player();
  init_platform();
  init_viewctor();

  light_models();
  light_textures();
  // light_shader();
  light_shadels();

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

  m_alpha.set_color(RED);


  m_beta.set_posit(Vector3{0.0f, 0.0f, 4.0f});
  m_beta.set_veloc(m_beta_veloc);
  m_beta.set_color(BLUE);
}

void video::init_player()
{
  const Vector3 player_pos
  { 0.0f, 4.0f, 0.0f };

  m_player.set_pos(player_pos);

  m_player.set_sphere();
  // m_player.set_shading(m_lighting_shader);
}

void video::init_platform()
{
  m_platform.set_plane();
}

void video::init_viewctor()
{
  m_veloctor.set_stick();
  m_veloctor.set_sphere();
  m_veloctor.veloc_on_sphere(m_player);

  m_acceltor.set_stick();
  m_acceltor.set_sphere();
  m_acceltor.accel_on_sphere(m_player);
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



void video::light_shadels()
{
  // m_model.materials[0].shader = m_dark_shader;
  m_cube.materials[0].shader = m_dark_shader;
  // m_sphere.materials[0].shader = m_lighting_shader;

  m_player.set_shading(m_dark_shader);
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

  const Vector3 n0072_behind
  { 0.0f, -2.0f, 0.0f };

  const Vector3 n0072_before
  { 0.0f, 2.0f, 0.0f };

  const Vector3 n0072_right
  { 1.0f, 0.0f, 0.0f };

  const Vector3 n0072_up
  { 0.0f, 0.0f, 1.0f };

  std::vector <sphere> n0072;

  const float n0072_dist
  { 2.0f };

  const float n0072_side
  { 3.0f };

  const float n0072_min
  { n0072_side/2.0f - 0.5f };

  const float bit
  { 0.001f };

  for (float x{ -n0072_min }; x < 0.0f*n0072_min + bit; x += 1.0f)
  {

    const Vector3 n007_start_x
    { Vector3Add(n0072_behind, n0072_up) };

    const Vector3 n007_pos_x
    { Vector3Scale(Vector3Add(n007_start_x, Vector3Scale(n0072_right, x)), n0072_dist) };

    const Vector3 n007_start_y
    { Vector3Add(n0072_before, n0072_right) };

    const Vector3 n007_pos_y
    { Vector3Scale(Vector3Add(n007_start_y, Vector3Scale(n0072_up, x)), n0072_dist) };

    sphere n007;

    n007.set_sphere();

    n007.set_posit(n007_pos_x);
    n007.set_color(GREEN);

    n007.set_shading(m_dark_shader);

    n0072.push_back(n007);

    n007.set_posit(n007_pos_y);
    n007.set_color(RED);

    n0072.push_back(n007);
  }

  m_light_pos = m_light_start_pos;

  // const float wiggle
  // { 1.0f };

  Light dark_light
  { 0 };
  dark_light = CreateLight(LIGHT_POINT, m_light_pos, Vector3Zero(), m_chroma.get_color(), m_dark_shader);

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

    m_chroma.pogo();
    m_chroma.choose();




    dark_light.color = m_chroma.get_color();

    m_player.set_color(WHITE);

    // if (IsKeyPressed(KEY_Y)) { bulb.enabled = !bulb.enabled; }
    // UpdateLightValues(shader, bulb);


    // Check key inputs to enable/disable lights
    if (IsKeyPressed(KEY_W)) { dark_light.enabled = !dark_light.enabled; }


    // Update light values (actually, only enable/disable them)
    UpdateLightValues(m_dark_shader, dark_light);
    UpdateLightValues(m_lighting_shader, a_light);

    // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
    float cameraPos[3] = { m_camera.position.x, m_camera.position.y, m_camera.position.z };
    SetShaderValue(m_dark_shader, m_fog_strength_pos, &m_fog_strength, UNIFORM_FLOAT);

    SetShaderValue(m_dark_shader, m_dark_shader.locs[LOC_VECTOR_VIEW], cameraPos, UNIFORM_VEC3);
    SetShaderValue(m_lighting_shader, m_lighting_shader.locs[LOC_VECTOR_VIEW], cameraPos, UNIFORM_VEC3);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

      ClearBackground(BLACK);

      BeginMode3D(m_camera);


          // m_platform.display();

          DrawGrid(10, 2.0f);


          DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{3.0f, 0.0f, 0.0f}, PURPLE);
          DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, 3.0f}, ORANGE);

          // m_player.display();
          // m_veloctor.display();
          // m_acceltor.display();

          // for (sphere &n007: n0072)
          // { n007.display(); }



          m_alpha.display(m_ball);

          m_beta.display(m_ball);

          // show_deez();

          // m_ball.display();


      EndMode3D();

      DrawFPS(10, 10);

      // DrawText("Use keys [Y] to toggle light", 10, 40, 20, DARKGRAY);

      const float delta
      { 1.0f/float(m_fps) };

      m_time += delta;

      while (m_time >= m_period)
      { m_time -= m_period; }

      m_force.type_select(m_beta, m_alpha);

      m_beta.null_force();

      m_beta.add_force(m_force.force_spring());

      m_beta.accelerate();

      // m_beta.set_accel(strong(m_beta.get_posit(), m_alpha.get_posit(), m_strong_mult));

      // m_beta.accelerate(m_force, m_alpha);

      m_beta.move(delta);


      // m_ball.set_posit(orbit(m_mid_posit, m_cos_posit, m_sin_posit, m_time, m_mult, m_period));

      // lights[0].position.x = anchor.x + wiggle*cos(0.5f*PI*m_time);
      // lights[0].position.y = anchor.y + wiggle*cos(0.5f*PI*m_time);
      // lights[0].position.z = anchor.z + wiggle*sin(0.5f*PI*m_time);

      m_fog_strength = m_fog_median + m_fog_median*sin(2.0f*PI*m_time/m_period);

      UpdateLightValues(m_dark_shader, dark_light);
      UpdateLightValues(m_lighting_shader, a_light);


      // m_player.set_accel(m_spring.accelerate(m_player.get_posit()));
      // m_player.add_accel(m_gravaccel);
      // m_player.move(m_platform.get_pos(), delta);
      // m_viewctor.set_in_space();
      // m_veloctor.veloc_on_sphere(m_player);
      // m_acceltor.accel_on_sphere(m_player);

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

