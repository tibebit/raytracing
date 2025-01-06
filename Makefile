#Fabio Tiberio SM3201378
FSCAN = -Wall -O1 -fopenmp

all: raytracer
raytracer: main.o scene.o vector.o ppm.o
    gcc $(FSCAN) main.o scene.o vector.o ppm.o -o raytracer
main.o: main.c scene.h ppm.h
    gcc $(FSCAN) -c main.c
ppm.o: ppm.c ppm.h
    gcc $(FSCAN) -c ppm.c
scene.o: scene.c scene.h
    gcc $(FSCAN) -c scene.c
vector.o: vector.c vector.h
    gcc $(FSCAN) -c vector.c
clean:
    rm *.o
