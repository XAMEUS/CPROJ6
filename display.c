#include "display.h"

GLdouble pixelsize = 1;

GLfloat min_x = -1;
GLfloat max_x = 1;
GLfloat min_y = -1;
GLfloat max_y = 1;

int detail = 0;
int screenshoot = 0;

void Display_InitGL()
{
  // Antialiasing
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  glLineWidth(1.6f);
  glPointSize(3.0f);
  detail = 0;
}


static GLubyte *pixels = NULL;
static png_byte *png_bytes = NULL;
static png_byte **png_rows = NULL;
void screenshot_png(const char *filename, unsigned int width, unsigned int height,
        GLubyte **pixels, png_byte **png_bytes, png_byte ***png_rows) {
  size_t i, nvals;
  const size_t format_nchannels = 4;
  FILE *f = fopen(filename, "wb");
  nvals = format_nchannels * width * height;
  *pixels = realloc(*pixels, nvals * sizeof(GLubyte));
  *png_bytes = realloc(*png_bytes, nvals * sizeof(png_byte));
  *png_rows = realloc(*png_rows, height * sizeof(png_byte*));
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, *pixels);
  for (i = 0; i < nvals; i++)
      (*png_bytes)[i] = (*pixels)[i];
  for (i = 0; i < height; i++)
      (*png_rows)[height - i - 1] = &(*png_bytes)[i * width * format_nchannels];
  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();
  png_infop info = png_create_info_struct(png);
  if (!info) abort();
  if (setjmp(png_jmpbuf(png))) abort();
  png_init_io(png, f);
  png_set_IHDR(
      png,
      info,
      width,
      height,
      8,
      PNG_COLOR_TYPE_RGBA,
      PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);
  png_write_image(png, *png_rows);
  png_write_end(png, NULL);
  fclose(f);
}

// function to reset our viewport after a window resize
void Display_SetViewport(int width, int height, GLfloat dx, GLfloat dy, float zoom)
{
  glViewport(0, 0, (GLint) width, (GLint) height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  pixelsize = (max_y-min_y)/height;

  GLfloat a = (min_x + max_x) / 2 + dx - zoom * (pixelsize * width / 2);
  GLfloat b = (min_x + max_x) / 2 + dx + zoom * (pixelsize * width / 2);
  GLfloat c = (min_y + max_y) / 2 + dy - zoom * (max_y - min_y) / 2;
  GLfloat d = (min_y + max_y) / 2 + dy + zoom * (max_y - min_y) / 2;

  if (fabs(fabs(b) - fabs(a)) < 0.04) detail = 10;
  else detail = 0;

  glOrtho(a, b, c, d,0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (screenshoot)
  {
    printf("Taking screenshoot\n");
    screenshoot = 0;
    screenshot_png("screenshoot.png", width, height, &pixels, &png_bytes, &png_rows);
  }
}
