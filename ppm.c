// Fabio Tiberio SM3201378
#include "ppm.h"
#include <omp.h>

void render_scene(Scene* scene, const char* output_filename, int width, int height) {
    // buffer per l'header
    char header[32];
    int header_size = snprintf(header, sizeof(header), "P6\n%d %d\n255\n", width, height);

    // la dimensione in memoria del file immagine e'data dai seguenti componenti:
    // lo spazio richiesto dall'header
    // lo spazio per la griglia di pixel (tenendo conto del fatto che
    // ogni pixel occupa 3 byte in memoria)
    int image_size = header_size + 3 * width * height;

    // apertura file
    FILE* file = fopen(output_filename, "wb+");
    if (file == NULL) {
        printf("Errore di apertura del file");
        exit(EXIT_FAILURE);
    }

    // file descriptor
    int fd = fileno(file);

    if (fd < 0) {
        printf("Errore del file descriptor");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // espansione file in memoria
    if (ftruncate(fd, image_size) == -1) {
        printf("Errore con ftruncate");
        fclose(file);
        exit(EXIT_FAILURE);
    }


    void* map = mmap(NULL, image_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (map == MAP_FAILED) {
        printf("Errore con mmap");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // inserisci l'header nel suo spazio
    memcpy(map, header, header_size);

    // da qui in poi scrivi dati binari
    uint8_t* image = (uint8_t*)map + header_size;

    // Posizione della camera sempre assunta in {0,0,0}
    Vector origin = {0, 0, 0};

    // Ogni thread e'indipendente dall'altro dato che lavora sulla
    // propria porzione di memoria. In questo caso
    // e'possibile la coordinazione in maniera automatica
    #pragma omp parallel for
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            // creazione del raggio
            float x = (scene->viewport.width / (width - 1)) * i - scene->viewport.width / 2;
            float y = (scene->viewport.height / (height - 1)) * (height - 1 - j) - scene->viewport.height / 2; // Ribaltamento verticale

            // normalizzazione
            Vector direction = normalize((Vector){x, y, scene->viewport.z_depth});
            // stabilisci intersezione
            Color pixel_color = get_pixel_color(origin, direction, scene);

            // Calcolo dell'indice nel buffer immagine
            int index = (j * width + i) * 3;
            image[index] = pixel_color.red;
            image[index + 1] = pixel_color.green;
            image[index + 2] = pixel_color.blue;
        }
    }

    // forza sincro sul disco
    if (msync(map, image_size, MS_SYNC) == -1) {
        perror("Errore con msync");
    }

    // deallocazione memoria
    if (munmap(map, image_size) == -1) {
        perror("Errore con munmap");
    }

    fclose(file);
}