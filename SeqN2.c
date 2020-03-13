
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define DEFAULT_NUM_BODIES 10
#define DEFAULT_NUM_STEPS 1000
#define SIZE_OF_SOLAR_SYSTEM 149,597,870.691    // metres
#define EARTH_VELOCITY 29700.0                    // m/s
#define EARTH_MASS 5972370000000000000000000.0    // kg
#define G_CONST 0.00000000000667408             //also SI

struct point{
    double x;
    double y;
    double z;
};

int main(int argc, char *argv[]){
    int numBodies, numSteps;
    srand(time(0));

    numBodies = (argc > 1) ? atoi(argv[1]) : DEFAULT_NUM_BODIES;
    numSteps = (argc > 2) ? atoi(argv[2]) : DEFAULT_NUM_STEPS;

    struct point force[numBodies], velocity[numBodies], position[numBodies];
    double mass[numBodies];



    return 0;
}