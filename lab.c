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

char* convertIntegerIntoCharArray(int number)
{
    unsigned int nDigits = countNumberOfDigits(number);
    char* charArray = malloc(nDigits*sizeof(char));

    for (int i = nDigits-1; i >= 0; --i, number /= 10)
    {
        charArray[i] = (number % 10) + '0';
    }
    return charArray;

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


void createPlanes(struct Plane* planes, char* charId, int nPlanes)
{
    for(int i = 0; i < nPlanes; i++)
    {
        struct Plane plane;
        plane.id = charId;
        //plane.planeType = {};
        plane.isAvailable = true;

        int intId;
        sscanf(charId, "%d", &intId);

        plane.wheels =  createWheels(intId);
        plane.wings =  createWings(intId);

        planes[i] =  plane;
        intId++;

        charId = convertIntegerIntoCharArray(intId);





    }

}

int main(int argc, char** argv) {
    printf("INF2610\n");
    /* Remove comment once the code is completed for the given section to test */
    int id = 1;


    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    
    struct Wheel* wheels;
    wheels = createWheels(id);    
    printf("%d\n", wheels[0].id);

    /* Create wing - [4 points] */
    
    long longId = 123456;
    struct Wing* wings;
    wings = createWings(longId);
    
    printf("%d\n", wings[1].id[8]);

    /* Create plane - [4 points] */
    
    int numberOfPlanes = 3;
    char* planeId = "123";
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    createPlanes(planes, planeId, numberOfPlanes);
    
    printf("Plane 1 ID: %c", planes[0].id[0]);
    printf("%c", planes[0].id[1]);
    printf("%c\n", planes[0].id[2]);
    printf("Wheel ID: %d\n\n", planes[0].wheels[6].id);
   
    printf("Plane 2 ID: %c", planes[1].id[0]);
    printf("%c", planes[1].id[1]);
    printf("%c\n\n", planes[1].id[2]);

    printf("Plane 3 ID: %c", planes[2].id[0]);
    printf("%c", planes[2].id[1]);
    printf("%c\n\n", planes[2].id[2]);

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
