// Fabio Tiberio SM3201378
#ifndef PPM_H
#define PPM_H
#include <sys/mman.h>
#include <unistd.h>
#include "scene.h"

void render_scene(Scene* scene, const char* output_filename, int width, int height);
#endif
