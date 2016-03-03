#include "draw.h"

int width = 640;
int height = 480;

int status = 2;
int size = 19;

void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom);

void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom)
{
  // Set the background
  glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
  // Clear The Screen And The Depth Buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glPointSize(7.5f);
  GLfloat* t = malloc(sizeof(GLfloat) * 100);
  int j;
  for (j = 0; j < 100; j++) {
    t[j] = 0.0;
  }
  t[0] = 50.0f;
  t[1] = 100.0f;
  t[2] = 80.0f;
  t[3] = 150.0f;
  t[4] = 100.0f;
  t[5] = 200.0f;
  t[6] = 90.0f;
  t[7] = 260.0f;
  t[8] = 80.0f;
  t[9] = 300.0f;
  t[10] = 80.0f;
  t[11] = 350.0f;
  t[12] = 90.0f;
  t[13] = 380.0f;
  t[14] = 100.0f;
  t[15] = 420.0f;
  t[16] = 150.0f;
  t[17] = 440.0f;
  t[18] = 220.0f;
  t[19] = 420.0f;
  t[20] = 230.0f;
  t[21] = 370.0f;
  t[22] = 210.0f;
  t[23] = 320.0f;
  t[24] = 200.0f;
  t[25] = 200.0f;
  t[26] = 240.0f;
  t[27] = 120.0f;
  t[28] = 280.0f;
  t[29] = 102.0f;
  t[30] = 320.0f;
  t[31] = 98.0f;
  t[32] = 350.0f;
  t[33] = 105.0f;
  t[34] = 420.0f;
  t[35] = 180.0f;
  t[36] = 430.0f;
  t[37] = 286.0f;

  if ((status % 3 == 2) || (status == 3)) {
    glLineWidth(3.6f);
    glColor3f(0.9f, 0.9f, 0.2f);
    glPolygonMode(GL_FRONT, GL_FILL);
    Draw_Lines(size, t, 35);
    glColor3f(0.2f, 0.3f, 0.9f);
    glPolygonMode(GL_FRONT, GL_LINE);
    Draw_Lines(size, t, 35);
    glColor3f(0.9f, 0.2f, 0.2f);
    glPolygonMode(GL_FRONT, GL_POINT);
    Draw_Lines(size, t, 35);
  }

  int i;
  if (status % 2 == 1) {
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor4f(0.9f, 0.1f, 0.9f, 0.4f);
    for (i = 0; i <= 2 * size - 4; i += 2) {
      Draw_Line(t[i], t[i+1], t[i+2], t[i+3], 35);
    }
  }
  glColor3f(0.2f, 0.9f, 0.2f);
  glBegin(GL_POINTS);
  for (i = 0; i <= 2 * size - 2; i += 2) {
    glVertex3f(t[i], t[i + 1], 1.0);
  }
  glEnd();

  glLineWidth(5.6f);
  glColor4f(0.2f, 0.9f, 0.2f, 0.6f);
  glBegin(GL_LINE_STRIP);
  for (i = 0; i <= 2 * size - 2; i += 2) {
    glVertex3f(t[i], t[i + 1], 1.0);
  }
  glEnd();

  glPopMatrix();

  // Render
  SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{

  SDL_Window *window; // Declare a pointer, main window
  GLfloat dx = -60;
  GLfloat dy =  20;
  GLfloat zoom = 1.0;
  min_x = 0;
  max_x = width;
  min_y = 0;
  max_y = height;

  // Initialize SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0 )
  {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
    "Drawing - OpenGL",            // window title
    SDL_WINDOWPOS_UNDEFINED,    // initial x position
    SDL_WINDOWPOS_UNDEFINED,    // initial y position
    width,                      // width, in pixels
    height,                     // height, in pixels
    SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE        // flags
  );

  // Check that the window was successfully created
  if (window == NULL)
  {
    // In the case that the window could not be made...
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Renderer* displayRenderer = NULL;
  SDL_RendererInfo displayRendererInfo;
  displayRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
  if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
    (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
    fprintf(stderr, "We have no render surface and not accelerated.\n");
  }

  Display_InitGL();

  Display_SetViewport(
    width, height,
    dx,
    dy,
    zoom
  );

  int fullscreen = 0;
  int drag = 0;
  int xcursor = 0;
  int ycursor = 0;
  SDL_Event event;
  int quit = 0;
  time_t t = time(NULL);
  time_t ctime = time(NULL);
  int frames = 0;
  while (!quit)
  {
    Display_SetViewport(
      width, height,
      dx,
      dy,
      zoom
    );
    Display_Render(displayRenderer, width, height, dx, dy, zoom);
    while (SDL_PollEvent(&event)) // User's actions
    {
      switch(event.type)
      {
        case SDL_QUIT: // Close button
          quit = 1;
          break;
        case SDL_KEYUP: // Key release
          if (event.key.keysym.sym == SDLK_f) // F key
          {
            if (fullscreen == 0)
            {
              fullscreen = 1;
              SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
            }
            else if (fullscreen == 1)
            {
              fullscreen = 0;
              SDL_SetWindowFullscreen(window, 0);
            }
          }
          if (event.key.keysym.sym == SDLK_KP_PLUS) {
            size += 1;
          }
          if (event.key.keysym.sym == SDLK_KP_MINUS) {
            size -= 1;
          }
          if (event.key.keysym.sym == SDLK_r)
          {
            zoom = 1.0;
            dx = 0.0;
            dy = 0.0;
          }
          if (event.key.keysym.sym == SDLK_p)
          {
            status += 1;
            status %= 4;
          }
          break;
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
              width = event.window.data1;
              height = event.window.data2;
              break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
              width = event.window.data1;
              height = event.window.data2;
              break;
            default:
              // printf("Window %d got unknown event %d\n", event.window.windowID, event.window.event);
              break;
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT)
            drag = 1;
          break;
        case SDL_MOUSEBUTTONUP:
          if (event.button.button == SDL_BUTTON_LEFT)
            drag = 0;
          break;
        case SDL_MOUSEMOTION:
          xcursor = event.motion.x;
          ycursor = event.motion.y;
          if (drag != 0) {
            dx -= pixelsize * event.motion.xrel * zoom;
            dy += pixelsize * event.motion.yrel * zoom;
          }
          break;
        case SDL_MOUSEWHEEL:
          if (zoom > 0.03) {
            dx = dx + 0.03 * pixelsize * event.wheel.y * (xcursor - width / 2);
            dy = dy - 0.03 * pixelsize * event.wheel.y * (ycursor - height / 2);
          }
          if (event.wheel.y > 0 && zoom > 0.01)
            zoom -= 0.03;
          else if (event.wheel.y < 0)
            zoom += 0.03;
          break;
        default:
          //printf("unknown event");
          break;
      }
    }
    frames++;
    ctime = time(NULL);
    if (t != ctime) {
      t = ctime;
      fprintf(stdout, "%d fps\n", frames);
      frames = 0;
    }
  }

  // Close and destroy the window
  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();

  return EXIT_SUCCESS;

}
