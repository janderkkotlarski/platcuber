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
  // for (int count{ 0 }; count < 100; ++count)
  // init_screen();

  // init_camera();

  light_screen();
  light_camera();

  init_player();

  light_models();
  light_shader();
  light_shadels();
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
  const Vector3 player_pos
  { 2.0f, 4.0f, -2.0f };

  m_player.set_pos(player_pos);

  m_player.set_sphere();
  // m_player.set_shading(m_lighting_shader);
}


void video::light_screen()
{
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic lighting");
}

void video::light_camera()
{
  m_camera.position = Vector3{ 0.0f, 2.0f, 10.0f };      // Camera position
  m_camera.target = Vector3{ 0.0f, 2.0f, 0.0f };      // Camera looking at point
  m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)


  m_camera.fovy = 45.0f;                                // Camera field-of-view Y
  m_camera.type = CAMERA_PERSPECTIVE;                  // Camera mode type

  UpdateCamera(&m_camera);
}

void video::light_models()
{
  m_model = LoadModelFromMesh(GenMeshPlane(10.0f, 10.0f, 3, 3));
  m_cube = LoadModelFromMesh(GenMeshCube(2.0f, 4.0f, 2.0f));
  m_sphere = LoadModelFromMesh(GenMeshSphere(0.2f, 20, 20));
}

void video::light_shader()
{
  m_lighting_shader = LoadShader("base_lighting.vs", "lighting.fs");
  /// This is the local place for the shaders.
  // Shader shader = LoadShader("d:/Cpp/build-platcuber-libray_MinGW-Debug/base_lighting.vs",
  //                     "d:/Cpp/build-platcuber-libray_MinGW-Debug/lighting.fs");
  // shader = LoadShader(TextFormat("resources/shaders/glsl%i/base_lighting.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));

  // Get some required shader locations
  m_lighting_shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(m_lighting_shader, "viewPos");
  // NOTE: "matModel" location name is automatically assigned on shader loading,
  // no need to get the location again if using that uniform name
  m_lighting_shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(m_lighting_shader, "matModel");

  // Ambient light level (some basic lighting)
  m_ambientLoc = GetShaderLocation(m_lighting_shader, "ambient");
  SetShaderValue(m_lighting_shader, m_ambientLoc, m_lighting_color, UNIFORM_VEC4);
}

void video::light_shadels()
{
  m_model.materials[0].shader = m_lighting_shader;
  m_cube.materials[0].shader = m_lighting_shader;
  m_sphere.materials[0].shader = m_lighting_shader;

  m_player.set_shading(m_lighting_shader);
}

void video::light_it()
{
    // Initialization
    //--------------------------------------------------------------------------------------

  m_light_pos = m_player.get_pos();

    Light lights[1] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, Vector3{ 0, 1000, 0 }, Vector3Zero(), m_chroma.get_color(), m_lighting_shader);
    /*
    lights[1] = CreateLight(LIGHT_POINT, Vector3{ 2, 1, 2 }, Vector3Zero(), BLACK, m_lighting_shader);
    lights[2] = CreateLight(LIGHT_POINT, Vector3{ -2, 1, 2 }, Vector3Zero(), BLACK, m_lighting_shader);
    lights[3] = CreateLight(LIGHT_POINT, Vector3{ 2, 1, -2 }, Vector3Zero(), BLACK, m_lighting_shader);

    */

    const Vector3 sphere_pos
    { 2.0f, 1.0f, -2.0f };

    SetCameraMode(m_camera, CAMERA_ORBITAL);  // Set an orbital camera mode

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


        lights[0].color = m_chroma.get_color();

        // if (IsKeyPressed(KEY_Y)) { bulb.enabled = !bulb.enabled; }
        // UpdateLightValues(shader, bulb);


        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_W)) { lights[0].enabled = !lights[0].enabled; }
        /*
        if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }
        */

        // Update light values (actually, only enable/disable them)
        UpdateLightValues(m_lighting_shader, lights[0]);
        /*
        UpdateLightValues(m_lighting_shader, lights[1]);
        UpdateLightValues(m_lighting_shader, lights[2]);
        UpdateLightValues(m_lighting_shader, lights[3]);
        */


        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = { m_camera.position.x, m_camera.position.y, m_camera.position.z };
        SetShaderValue(m_lighting_shader, m_lighting_shader.locs[LOC_VECTOR_VIEW], cameraPos, UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(m_camera);

                // DrawModel(m_cube, Vector3Zero(), 1.0f, WHITE);




                // if (bulb.enabled) DrawSphereEx(bulb.position, 0.2f, 8, 8, GRAY);
                // else DrawSphereWires(bulb.position, 0.2f, 8, 8, ColorAlpha(YELLOW, 0.3f));



                // Draw markers to show where the lights are
                // if (lights[0].enabled) DrawSphereEx(lights[0].position, 0.2f, 8, 8, m_chroma.get_color());
                // else DrawSphereWires(lights[0].position, 0.2f, 8, 8, ColorAlpha(m_chroma.get_color(), 0.3f));





                m_player.display();

                DrawModel(m_sphere, sphere_pos, 1.0f, WHITE);

                DrawModel(m_model, Vector3Zero(), 1.0f, GREEN);
                /*
                if (lights[1].enabled) DrawSphereEx(lights[1].position, 0.2f, 8, 8, RED);
                else DrawSphereWires(lights[1].position, 0.2f, 8, 8, ColorAlpha(RED, 0.3f));
                if (lights[2].enabled) DrawSphereEx(lights[2].position, 0.2f, 8, 8, GREEN);
                else DrawSphereWires(lights[2].position, 0.2f, 8, 8, ColorAlpha(GREEN, 0.3f));
                if (lights[3].enabled) DrawSphereEx(lights[3].position, 0.2f, 8, 8, BLUE);
                else DrawSphereWires(lights[3].position, 0.2f, 8, 8, ColorAlpha(BLUE, 0.3f));
                */

                // DrawGrid(10, 1.0f);


            EndMode3D();

            DrawFPS(10, 10);

            DrawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(m_model);     // Unload the model
    UnloadModel(m_cube);      // Unload the model
    UnloadShader(m_lighting_shader);   // Unload shader

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
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

