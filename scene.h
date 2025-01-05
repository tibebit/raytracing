// Fabio Tiberio SM3201378
#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>
#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Costringiamo la struttura ad essere esattamente di 24 bit (3 byte)
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} __attribute__((packed)) Color;

typedef struct {
    Vector center;
    float radius;
    Color color;
} Sphere;

typedef struct {
    float width;
    float height;
    float z_depth;
} Viewport;

typedef struct {
    Viewport viewport;
    Color background_color;
    int num_of_spheres;
    Sphere* spheres;
} Scene;

Scene* parse_scene_file(const char* filename);

float intersection(Vector origin, Vector direction, Sphere sphere);

Color get_pixel_color(Vector origin, Vector direction, Scene *scene);

void render_scene(Scene *scene, const char *output_filename, int width, int height);

#endif
