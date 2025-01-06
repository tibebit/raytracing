#Fabio Tiberio SM3201378
all: raytracer

raytracer: main.o scene.o vector.o ppm.o
	gcc -Wall -O1 -fopenmp main.o scene.o vector.o ppm.o -o raytracer
main.o: main.c scene.h ppm.h
	gcc -Wall -O1 -fopenmp -c main.c
ppm.o: ppm.c ppm.h
	gcc -Wall -O1 -fopenmp -c ppm.c
scene.o: scene.c scene.h
	gcc -Wall -O1 -fopenmp -c scene.c
vector.o: vector.c vector.h
	gcc -Wall -O1 -fopenmp -c vector.c

clean:
	rm *.o