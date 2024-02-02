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

const int PLANE_TYPE_SIZE = 10;
const int N_WHEELS = 7;
const int WING_ID_SIZE = 9;
const int N_WINGS = 2;
const int MIN_SMALL_ID = 0;
const int MAX_SMALL_ID = 2;
const int MIN_MEDIUM_ID = 3;
const int MAX_MEDIUM_ID = 6;
const int MIN_LARGE_ID = 7;
const int MAX_LARGE_ID = 2;

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
    char planeType[10]; //char planeType[PLANE_TYPE_SIZE]; -->Le code ne compilait pas lorsqu'on le faisait ainsi 
    bool isAvailable;
    struct Wheel* wheels;
    struct Wing* wings;

};



struct Wheel* createWheels(int id)
{
 
    struct Wheel* wheels = malloc(N_WHEELS*sizeof(struct Wheel));
    for (int i = 0; i < N_WHEELS; i++) 
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
char* convertIntegerIntoCharArray(int n)
{
    unsigned int nDigits = countNumberOfDigits(n);
    char* charArray = malloc(nDigits*sizeof(char));

    for (int i = nDigits-1; i >= 0; --i, n /= 10)
    {
        charArray[i] = (n % 10) + '0';
    }
    return charArray;

}

void populateWingAttributes(struct Wing* wing, int id)
{
    
    int* wingId = malloc(WING_ID_SIZE*sizeof(int));

    unsigned int nDigitsInId = countNumberOfDigits(id);
    
 
    for (int i = WING_ID_SIZE-1; i >= 0; i--)
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
    
    struct Wing* wings = malloc(N_WINGS*sizeof(struct Wing));

    for(int i = 0; i < N_WINGS; i++)
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
int reconstructInteger(int* intArray, int size)
{
    int reconstructedInteger = 0;
    int exponent = 0;
    int base = 10;
    for(int i = size; i >= 0; i--)
    {
        reconstructedInteger = reconstructedInteger + (powInt(base,exponent))*intArray[i];
        exponent++;
    }
    return reconstructedInteger;
}

void setAvailability(struct Plane* plane, bool isAvailable)
{
    plane->isAvailable = isAvailable;
}

char** getAvailablePlanes(struct Plane* planes, int nPlanes)
{
    
    int nAvailablePlanes = 0;
    for(int i = 0; i < nPlanes; i++)
    {
        if(planes[i].isAvailable)
        {
            
            nAvailablePlanes++;
        }
    }

    char** availablePlanes = malloc(nAvailablePlanes*sizeof(char*));

    int j = 0;
    for(int i = 0; i < nPlanes; i++)
    {
        if(planes[i].isAvailable)
        {
            availablePlanes[j] = planes[i].id;
            j++;
        }
    }

    

    return availablePlanes;
}


void setPlaneType(struct Plane* plane)
{
    
    int wingId = reconstructInteger(plane->wings[0].id, WING_ID_SIZE);
    int classification = wingId % WING_ID_SIZE;

    if (classification >= MIN_SMALL_ID && classification <= MAX_SMALL_ID) {
        strcpy(plane->planeType, "Small");
    } else if (classification >= MIN_MEDIUM_ID && classification <= MAX_MEDIUM_ID) {
        strcpy(plane->planeType, "Medium");
    } else if (classification >= MIN_LARGE_ID && classification <= MAX_LARGE_ID){
        strcpy(plane->planeType, "Large");
    } else {
        strcpy(plane->planeType, "");
    }
}


struct Plane* getPlanesByType(struct Plane* planes, char planeType[], int nPlanes)
{
    int nPlanesByType = 0;
    for(int i = 0; i< nPlanes; i++)
    {
        if (strcmp(planes[i].planeType, planeType) == 0) 
        {
            nPlanesByType++;
        }
    }
    struct Plane* planesByType = malloc(nPlanesByType*sizeof(struct Plane));
    int j = 0;
    for(int i = 0; i< nPlanes; i++)
    {
        if (strcmp(planes[i].planeType, planeType) == 0) 
        {
            planesByType[j] = planes[i];
            j++;
        }
    }
    return planesByType;
}

int main(int argc, char** argv) {

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
    printf("%d\n", wings[0].id[0]);
  
    
    /* Create plane - [4 points] */
    
    int numberOfPlanes = 3;
    char* planeId = "123";
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    createPlanes(planes, planeId, numberOfPlanes);
    
   
    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    struct Plane plane = planes[0];
    setAvailability(&plane, false);

    
    /* Get available planes - [1 point] */
    

    char** availablePlanes = getAvailablePlanes(planes, numberOfPlanes);
    
    
    /* Classify planes - [2 points] */
    
    //Plane plane = planes[1];
    setPlaneType(&plane);
    
   
    
    /* Return type specific planes - [2 points] */
    
    char planeType[] = "Medium";

    struct Plane* planesByType = getPlanesByType(planes, planeType,numberOfPlanes);

    
    
}