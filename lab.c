/* INF2610 - TP1
/ Matricule 1 : 2203064
/ Matricule 2 : 
*/

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <stdbool.h>
#include <string.h>


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
    unsigned int nWheels = 7;
    struct Wheel* wheels = malloc(nWheels*sizeof(struct Wheel));
    for (int i = 0; i < nWheels; i++) 
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
int powInt(int base, int exponent) {
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
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
    int sizeOfArrayId = 9;
    int* wingId = malloc(sizeOfArrayId*sizeof(int));

    unsigned int nDigitsInId = countNumberOfDigits(id);
    
 
    for (int i = sizeOfArrayId-1; i >= 0; i--)
    {
        if(nDigitsInId>0)
        {
            wingId[i] = id%10;
            id/=10;
            nDigitsInId--;
        }
        else
        {
            wingId[i] = 0;
        }

    }
    wing->id = wingId;
    
}

struct Wing* createWings(long id)
{
    unsigned int nWings = 2;
    struct Wing* wings = malloc(nWings*sizeof(struct Wing));

    for(int i = 0; i < nWings; i++)
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
        strcpy(plane.planeType, "");
        plane.isAvailable = true;

        int intId;
        sscanf(charId, "%d", &intId); //transformer en integer afin d'utiliser l'ID de Plane pour Wheels et Wings

        plane.wheels =  createWheels(intId);
        plane.wings =  createWings(intId);

        planes[i] =  plane;
        intId++;

        charId = convertIntegerIntoCharArray(intId);





    }

}
int reconstructInt(int* intArray, int size)
{
    int number = 0;
    int exponent = 0;
    int base = 10;
    for(int i = size; i >= 0; i--)
    {
        number = number + (powInt(base,exponent))*intArray[i];
        exponent++;
    }
    return number;
}
void setAvailability(struct Plane* plane, bool isAvailable)
{
    plane->isAvailable = isAvailable;
}

char** getAvailablePlanes(struct Plane* planes, int nPlanes)
{
    char** availablePlanes = malloc(nPlanes*sizeof(char*));
    int nAvailablePlanes = 0;
    for(int i = 0; i < nPlanes; i++)
    {
        if(planes[i].isAvailable)
        {
            availablePlanes[nAvailablePlanes] = planes[i].id;
            nAvailablePlanes++;
        }
    }

    

    return availablePlanes;
}

void setPlaneType(struct Plane* plane)
{
    int nDigitsInWingId = 9;
    int wingId = reconstructInt(plane->wings[0].id, nDigitsInWingId);
    int classification = wingId % 9;

    if (classification >= 0 && classification <= 2) {
        strcpy(plane->planeType, "Small");
    } else if (classification >= 3 && classification <= 6) {
        strcpy(plane->planeType, "Medium");
    } else {
        strcpy(plane->planeType, "Large");
    } 
}
struct Plane* getPlanesByType(struct Plane* planes, char planeType[], int nPlanes)
{
    struct Plane* planesByType = malloc(nPlanes*sizeof(struct Plane));
    int nPlanesByType = 0;
    for(int i = 0; i< nPlanes; i++)
    {
        if (strcmp(planes[i].planeType, planeType) == 0) 
        {
            planesByType[nPlanesByType] = planes[i];
            nPlanesByType++;
        }
    }
    return planesByType;
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
    
    struct Plane plane = planes[0];
    printf("Plane is Available: %d\n", plane.isAvailable);
    setAvailability(&plane, false);
    printf("Plane is Available: %d\n\n", plane.isAvailable );

    /* Get available planes - [1 point] */
    planes[1].isAvailable = false;
    char** availablePlanes = getAvailablePlanes(planes, numberOfPlanes);
    printf("Plane 1 is Available: %d\n", planes[0].isAvailable);
    printf("Plane 2 is Available: %d\n", planes[1].isAvailable);
    printf("Plane 3 is Available: %d\n", planes[2].isAvailable);
    printf("Plane available id %c", availablePlanes[0][0]);
    printf("%c", availablePlanes[0][1]);
    printf("%c\n", availablePlanes[0][2]);
    printf("Plane available id %c", availablePlanes[1][0]);
    printf("%c", availablePlanes[1][1]);
    printf("%c\n", availablePlanes[1][2]);
    /* Classify planes - [2 points] */
    
    //Plane plane = planes[1];
    setPlaneType(&plane);
    printf("%c", plane.planeType[0]);
    printf("%c", plane.planeType[1]);
    printf("%c", plane.planeType[2]);
    printf("%c", plane.planeType[3]);
    printf("%c", plane.planeType[4]);
    printf("%c\n", plane.planeType[5]);

    /* Return type specific planes - [2 points] */
    
    char planeType[] = "Medium";
    setPlaneType(&(planes[0]));
    setPlaneType(&(planes[1]));
    setPlaneType(&(planes[2]));
    struct Plane* planesByType = getPlanesByType(planes, planeType,numberOfPlanes);
    printf("%c", planesByType[0].id[0]);
    printf("%c", planesByType[0].id[1]);
    printf("%c\n", planesByType[0].id[2]);
    
    
}
