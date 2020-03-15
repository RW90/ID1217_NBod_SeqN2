
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define DEFAULT_NUM_BODIES 10
#define DEFAULT_NUM_STEPS 1000
#define DIAMETER_OF_SOLAR_SYSTEM 149597870.691      // metres
#define EARTH_VELOCITY 29700.0                      // m/s
#define EARTH_MASS 5972370000000000000000000.0      // kg
#define G_CONST 0.00000000000667408                 //also SI
#define DELTA_TIME 1                                // seconds in a day

struct point{
    double x;
    double y;
    double z;
};

double read_timer() {
    static bool initialized = false;
    static struct timeval start;
    struct timeval end;
    if( !initialized )
    {
        gettimeofday( &start, NULL );
        initialized = true;
    }
    gettimeofday( &end, NULL );
    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}

double randInRange(double min, double max){
    double range = max - min;
    double randomVal = (double) rand() / ((double) RAND_MAX);
    double result = min + randomVal * range;
    return result;
}

void calculateForces(int numBodies, double mass[], struct point pos[], struct point force[]){
    double totDist, xDist, yDist, zDist, magnitude;
    for(int i = 0; i < numBodies - 1; i++){
        for(int j = i + 1; j < numBodies; j++){
            xDist = pos[i].x - pos[j].x;
            yDist = pos[i].y - pos[j].y;
            zDist = pos[i].z - pos[j].y;
            totDist = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
            magnitude = G_CONST * mass[i] * mass[j] / (totDist * totDist);
            force[i].x -= magnitude*xDist/totDist;
            force[i].y -= magnitude*yDist/totDist;
            force[i].z -= magnitude*zDist/totDist;
            force[j].x += magnitude*xDist/totDist;
            force[j].y += magnitude*yDist/totDist;
            force[j].z += magnitude*zDist/totDist;
        }
    }
}

void moveBodies(int numBodies, double mass[], struct point pos[], struct point velocity[], struct point force[]){
    double deltaVelX;
    double deltaVelY;
    double deltaVelZ;
    double deltaPosX;
    double deltaPosY;
    double deltaPosZ;
    for(int i = 0; i < numBodies; i++){
        deltaVelX = force[i].x / mass[i] * DELTA_TIME;  // f / m * t or a * t
        deltaVelY = force[i].y / mass[i] * DELTA_TIME;
        deltaVelZ = force[i].z / mass[i] * DELTA_TIME;
        deltaPosX = (velocity[i].x + deltaVelX / 2) * DELTA_TIME;   // (v * a*t/2) * t
        deltaPosY = (velocity[i].y + deltaVelY / 2) * DELTA_TIME;
        deltaPosZ = (velocity[i].z + deltaVelZ / 2) * DELTA_TIME;
        velocity[i].x += deltaVelX;
        velocity[i].y += deltaVelY;
        velocity[i].z += deltaVelZ;
        pos[i].x += deltaPosX;
        pos[i].y += deltaPosY;
        pos[i].z += deltaPosZ;
        force[i].x = 0;
        force[i].y = 0;
        force[i].z = 0;
    }
}

int main(int argc, char *argv[]){
    int numBodies, numSteps;
    double startTime, endTime;
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
        force[i].x = 0.0;
        force[i].y = 0.0;
        force[i].z = 0.0;
    }

#ifdef DEBUG
    for(int i = 0; i < numBodies; i++){
        printf("Body %d with mass: %f, Pos x: %f, y: %f, z: %f, Vel x: %f, y: %f, z: %f\n",
         i, mass[i], pos[i].x, pos[i].y, pos[i].z, velocity[i].x, velocity[i].y, velocity[i].z);
    }
#endif

    startTime = read_timer();
    for(int i = 0; i < numSteps; i++){
        calculateForces(numBodies, mass, pos, force);
        #ifdef DEBUG
            if(i % 1024 == 0){
                printf("Planet 2 pos x: %f, y: %f, z: %f\n", pos[1].x, pos[1].y, pos[1].z);
                printf("Planet 2 vel x: %f, y: %f, z: %f\n", velocity[1].x, velocity[1].y, velocity[1].z);
                printf("Planet 2 for x: %f, y: %f, z: %f\n", force[1].x, force[1].y, force[1].z);
            }
        #endif
        moveBodies(numBodies, mass, pos, velocity, force);   
    }
    endTime = read_timer();

    printf("The execution time is %g sec with %d bodies and %d time steps.\n", endTime - startTime, numBodies, numSteps);
    return 0;
}