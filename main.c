// Fabio Tiberio SM3201378
#include "scene.h"
#include "ppm.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s [scene_file.txt] [image_file.ppm] [width] [height]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *scene_file = argv[1];
    const char *image_file = argv[2];
    int width = atoi(argv[3]);
    int height = atoi(argv[4]);
    Scene* scene = parse_scene_file(scene_file);

    if (scene == NULL) {
        printf("Errore nel caricamento della scena\n");
        exit(EXIT_FAILURE);
    }

    render_scene(scene, image_file, width, height);
    printf("Successo. Il rendering è stato salvato come %s\n", image_file);
    free(scene);

    exit(EXIT_SUCCESS);
}