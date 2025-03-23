#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>




typedef struct {
    char body_type[MAX_BODY_TYPE_LENGTH];
    float engine_volume;
} Details;

typedef struct {
    int price;
    char *brand;
    Details details;
} Car;

void inputCarFields(Car *car);
void printCarFields(const Car *car);
void inputDetails(Details *details);
void printCar(const Car *car);
void findCarsAbovePrice(Car *cars, int count, int minPrice);
int deleteCarsByBrand(Car **cars, int count, const char *brand);


#endif
