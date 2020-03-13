
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define DEFAULT_NUM_BODIES 10
#define DEFAULT_NUM_STEPS 1000
#define DIAMETER_OF_SOLAR_SYSTEM 149597870.691    // metres
#define EARTH_VELOCITY 29700.0                      // m/s
#define EARTH_MASS 5972370000000000000000000.0      // kg
#define G_CONST 0.00000000000667408                 //also SI

struct point{
    double x;
    double y;
    double z;
};

double randInRange(double min, double max){
    double range = max - min;
    double randomVal = (double) rand() / RAND_MAX;
    double result = min + randomVal * range;
    return result;
}

int main(int argc, char *argv[]){
    int numBodies, numSteps;
    srand(time(0));

    numBodies = (argc > 1) ? atoi(argv[1]) : DEFAULT_NUM_BODIES;
    numSteps = (argc > 2) ? atoi(argv[2]) : DEFAULT_NUM_STEPS;

    struct point force[numBodies]; 
    struct point velocity[numBodies]; 
    struct point pos[numBodies];
    double mass[numBodies];

    double minMass = EARTH_MASS * 0.1;
    double maxMass = EARTH_MASS * 1000;
    double maxPos = DIAMETER_OF_SOLAR_SYSTEM * 10;

    for(int i = 0; i < numBodies; i++){
        mass[i] = randInRange(minMass, maxMass);
        pos[i].x = randInRange(0, maxPos);
        pos[i].y = randInRange(0, maxPos);
        pos[i].z = randInRange(0, maxPos);
        velocity[i].x = randInRange(0, EARTH_VELOCITY);
        velocity[i].y = randInRange(0, EARTH_VELOCITY);
        velocity[i].z = randInRange(0, EARTH_VELOCITY);
    }

#ifdef DEBUG
    for(int i = 0; i < numBodies; i++){
        printf("Body %d with mass: %f, Pos x: %f, y: %f, z: %f, Vel x: %f, y: %f, z: %f\n", i, mass[i], pos[i].x, pos[i].y, pos[i].z, velocity[i].x, velocity[i].y, velocity[i].z);
    }
#endif
    return 0;
}