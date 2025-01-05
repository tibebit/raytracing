// Fabio Tiberio SM3201378
#include "scene.h"

Scene* parse_scene_file(const char* filename) {
    FILE* file = fopen(filename, "r");

    // apertura del file con la descrizione della scena
    if (file == NULL) {
        printf("Errore nell'apertura del file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // creazione spazio per la scena
    Scene* scene = malloc(sizeof(Scene));
    if (scene == NULL) {
        printf("Errore nell'allocazione della scena");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // viewport
    if (fscanf(file, "VP %f %f %f\n", &scene->viewport.width, &scene->viewport.height, &scene->viewport.z_depth) != 3) {
        printf("Errore nel parsing del viewport\n");
        fclose(file);
        free(scene);
        exit(EXIT_FAILURE);
    }

    // background della scena
    if (fscanf(file, "BG %hhu %hhu %hhu\n", &scene->background_color.red, &scene->background_color.green, &scene->background_color.blue) != 3) {
        printf("Errore nel parsing del colore di background\n");
        fclose(file);
        free(scene);
        exit(EXIT_FAILURE);
    }

    // totale oggetti sulla scena
    if (fscanf(file, "OBJ_N %d\n", &scene->num_of_spheres) != 1) {
        fprintf(stderr, "Errore nel parsing del numero di oggetti\n");
        fclose(file);
        free(scene);
        exit(EXIT_FAILURE);
    }

    // allocazione spazio per le sfere
    scene->spheres = malloc(scene->num_of_spheres * sizeof(Sphere));
    if (!scene->spheres) {
        perror("Errore nell'allocazione delle sfere");
        fclose(file);
        free(scene);
        exit(EXIT_FAILURE);
    }

    // caratteristiche di ogni sfera
    for (int i = 0; i < scene->num_of_spheres; i++) {
        if (fscanf(file, "S %f %f %f %f %hhu %hhu %hhu\n",
                   &scene->spheres[i].center.x,
                   &scene->spheres[i].center.y,
                   &scene->spheres[i].center.z,
                   &scene->spheres[i].radius,
                   &scene->spheres[i].color.red,
                   &scene->spheres[i].color.green,
                   &scene->spheres[i].color.blue) != 7) {
            printf("Errore nel parsing della sfera %d\n", i + 1);
            fclose(file);
            free(scene->spheres);
            free(scene);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return scene;
}

// determina se e'presente un'intersezione tra singola sfera e raggio
float intersection(Vector origin, Vector ray, Sphere sphere) {
    Vector oc = subtract(origin, sphere.center);

    float a = dot_product(ray, ray);
    float b = 2.0 * dot_product(oc, ray);
    float c = dot_product(oc, oc) - sphere.radius * sphere.radius;

    float delta = b * b - 4 * a * c;

    // nessuna intersezione
    if (delta < 0) {
        return -1.0f;
    }

    // una sola intersezione
    if (delta == 0) {
        return fabsf(-b/2*a);
    }

    // 2 intersezioni, quella piu'vicina alla camera viene scelta
    if (delta > 0) {
        float t1 = fabsf((-b - sqrtf(delta)) / (2 * a));
        float t2 = fabsf((-b + sqrtf(delta)) / (2 * a));
        return t1 > t2 ? t2 : t1;
    }

    return -1.0f;
}

// imposta il colore di un pixel a quello di background della scena
// se il raggio interseca una o più sfere, il pixel assume il colore
// della sfera più vicina
Color get_pixel_color(Vector origin, Vector direction, Scene *scene) {
    float nearest_t = INFINITY;

    Color pixel_color = scene->background_color;

    for (int i = 0; i < scene->num_of_spheres; i++) {
        Sphere *sphere = &scene->spheres[i];
        float t = intersection(origin, direction, *sphere);

        if (t > 0 && t < nearest_t) {
            nearest_t = t;
            pixel_color = sphere->color;
        }
    }

    return pixel_color;
}

