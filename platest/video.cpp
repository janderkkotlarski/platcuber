#include "video.h"

#include "raylib.h"

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

}

void video::run()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic lighting");

  // Define the camera to look into our 3d world
  Camera camera = { 0 };
  camera.position = Vector3{ 2.0f, 4.0f, 6.0f };    // Camera position
  camera.target = Vector3{ 0.0f, 0.5f, 0.0f };      // Camera looking at point
  camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE;             // Camera mode type

  // Load plane model from a generated mesh
  Model model = LoadModelFromMesh(GenMeshPlane(10.0f, 10.0f, 3, 3));
  Model cube = LoadModelFromMesh(GenMeshCube(2.0f, 4.0f, 2.0f));

  // Shader shader = LoadShader(TextFormat("resources/shaders/glsl%i/base_lighting.vs", GLSL_VERSION),
  //                           TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));

  Shader shader = LoadShader(TextFormat("base_lighting.vs", GLSL_VERSION),
                             TextFormat("lighting.fs", GLSL_VERSION));

  // Get some required shader loactions
  shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
  // NOTE: "matModel" location name is automatically assigned on shader loading,
  // no need to get the location again if using that uniform name
  shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

  // Ambient light level (some basic lighting)
  int ambientLoc = GetShaderLocation(shader, "ambient");

  const float ambience[4]
  {0.1f, 0.1f, 0.1f, 1.0f};


  SetShaderValue(shader, ambientLoc, ambience, UNIFORM_VEC4);

  // Assign out lighting shader to model
  model.materials[0].shader = shader;
  cube.materials[0].shader = shader;

  // Using 4 point lights: gold, red, green and blue
  Light lights[MAX_LIGHTS] = { 0 };
  lights[0] = CreateLight(LIGHT_POINT, Vector3{ -2, 1, -2 }, Vector3Zero(), YELLOW, shader);

  SetCameraMode(camera, CAMERA_ORBITAL);  // Set an orbital camera mode

  SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())            // Detect window close button or ESC key
  {
      // Update
      //----------------------------------------------------------------------------------
      UpdateCamera(&camera);              // Update camera

      // Check key inputs to enable/disable lights
      if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }


      // Update light values (actually, only enable/disable them)
      UpdateLightValues(shader, lights[0]);


      // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
      float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
      SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], cameraPos, UNIFORM_VEC3);
      //----------------------------------------------------------------------------------

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();

          ClearBackground(RAYWHITE);

          BeginMode3D(camera);

              DrawModel(model, Vector3Zero(), 1.0f, WHITE);
              DrawModel(cube, Vector3Zero(), 1.0f, WHITE);

              // Draw markers to show where the lights are
              if (lights[0].enabled) DrawSphereEx(lights[0].position, 0.2f, 8, 8, YELLOW);
              else DrawSphereWires(lights[0].position, 0.2f, 8, 8, ColorAlpha(YELLOW, 0.3f));


              DrawGrid(10, 1.0f);

          EndMode3D();

          DrawFPS(10, 10);

          DrawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, DARKGRAY);

      EndDrawing();
      //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadModel(model);     // Unload the model
  UnloadModel(cube);      // Unload the model
  UnloadShader(shader);   // Unload shader

  CloseWindow();          // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
}
