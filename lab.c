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
    bool isRearWheel;
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
    struct Wheel* wheels = malloc(7 * sizeof(struct Wheel));
    for (int i = 0; i<7; i++)
    {
        wheels[i].id = id + i;
        if (i<=2)
        {
            wheels[i].isRearWheel = false;
        }
        else
        wheels[i].isRearWheel = true;
    }
    return wheels;
}

void populateWingAttributes(struct Wing* wing, int id)
{
    wing->id = malloc(9 * sizeof(int));
    for (int i = 0; i<9;i++)
        wing->id[i] = 0;
    
    for (int i = 8; i >= 0 && id > 0; i--)
    {
        wing->id[i] = id % 10;
        id /= 10;
    }
}

struct Wing* createWings(long id)
{
     struct Wing* wings = malloc(2*sizeof(struct Wing));

    for(int i = 0; i < 2; i++)
    {
        struct Wing wing;
        populateWingAttributes(&wings[i], id);
        id++;
    }
    return wings;
}

void createPlanes(struct Plane* planes, char* id, int planeAmount)
{
    for(int i = 0; i < planeAmount; i++)
    {
        strncpy(planes[i].id, id, 10);
        memset(planes[i].planeType, 0, sizeof(planes[i].planeType));
        planes[i].isAvailable = true;
        planes[i].wheels = createWheels(i);
        planes[i].wings = createWings(i);
    }
}

void setAvailability(struct Plane* plane, bool isAvailable)
{
       plane->isAvailable= isAvailable; 
}

getAvailablePlanes(struct Plane* planes, int planeAmount)
{
     for(int i = 0; i < planeAmount; i++)
    {
        if (planes[i].isAvailable == true)
        {
            printf("id: %s\n", planes[i].id);
        }
    }
}

void setPlaneType(struct Plane* plane)
{
    
}
 int main(int argc, char** argv) {
    printf("INF2610\n");
    /* Remove comment once the code is completed for the given section to test */
    int id = 1;


    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    
    Wheel[] wheels;
    wheels = createWheels(id);    
    

    /* Create wing - [4 points] */
    
    long longId = 1;
    Wing[] wings;
    wings = createWings(longId);
    

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
