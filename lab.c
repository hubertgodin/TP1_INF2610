/* INF2610 - TP1
/ Matricule 1 : 
/ Matricule 2 : 
*/
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <stdbool.h>

struct Wheel
{
    int id;
    bool isRealWheel;
};
struct Wing
{
    int* id;
};
struct Plane
{
    char* id;
    char planeType[10];
    bool isAvailable;
    struct Wheel* wheels;
    struct Wing* wings;

};

struct Wheel* createWheels(int id)
{
    struct Wheel* wheels = malloc(7*sizeof(struct Wheel));
    for (int i = 0; i < 7; i++) 
    {
        struct Wheel wheel;
        wheel.id = id;
        wheel.isRealWheel = true;
        wheels[i] = wheel;
        id++;
    }
    return wheels;
}
unsigned int countNumberOfDigits(int n) {
    unsigned int nDigits=1;
    while (n/=10) 
    {
        nDigits++;
    }
    
    return nDigits;
}
void populateWingAttributes(struct Wing* wing, int id)
{
    int* planeId = malloc(9*sizeof(int));

    unsigned int nDigits = countNumberOfDigits(id);
    
 
    for (int i = 8; i >= 0; i--)
    {
        if(nDigits>0)
        {
            planeId[i] = id%10;
            id/=10;
            nDigits--;
        }
        else
        {
            planeId[i] = 0;
        }

    }
    wing->id = planeId;
    
}

struct Wing* createWings(long id)
{
    struct Wing* wings = malloc(2*sizeof(struct Wing));

    for(int i = 0; i < 2; i++)
    {
        struct Wing wing;
        populateWingAttributes(&wing, id);
        wings[i] = wing;
        id++;

    }
    return wings;
}



int main(int argc, char** argv) {
    printf("INF2610\n");
    /* Remove comment once the code is completed for the given section to test */
    int id = 1;


    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    
    struct Wheel* wheels;
    wheels = createWheels(id);    
    printf("%d\n", wheels[6].id);

    /* Create wing - [4 points] */
    
    long longId = 123456;
    struct Wing* wings;
    wings = createWings(longId);
    
    printf("%d\n", wings[1].id[8]);

    /* Create plane - [4 points] */
    /*
    int numberOfPlanes = 3;
    Plane* planes = malloc(sizeof(Plane) * numberOfPlanes);
    createPlanes(planes, *id, 3);
    */

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    /*
    Plane plane = planes[0];
    setAvailability(plane, true);
    */

    /* Get available planes - [1 point] */
    /*
    getAvailablePlanes(planes, numberOfPlanes);
    */

    /* Classify planes - [2 points] */
    /*
    Plane plane = planes[1];
    setPlaneType(plane);
    */

    /* Return type specific planes - [2 points] */
    /*
    char planeType[] = "Small";
    getPlanesByType(planes, planeType,numberOfPlanes);
    */
}
