#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void inputCarFields(Car *car) {
    printf("Введите стоимость: ");
    while (scanf("%d", &car->price) != 1 || car->price <= 0) {
        printf("Неверный ввод. Введите положительное число: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("Введите марку: ");
    char buffer[100];
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    car->brand = malloc(strlen(buffer) + 1);
    if (!car->brand) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    strcpy(car->brand, buffer);
}

// Вывод первых двух полей
void printCarFields(const Car *car) {
    printf("Стоимость: %d\n", car->price);
    printf("Марка: %s\n", car->brand);
}

// Ввод остальных полей
void inputDetails(Details *details) {
    printf("Введите тип кузова: ");
    fgets(details->body_type, MAX_BODY_TYPE_LENGTH, stdin);
    details->body_type[strcspn(details->body_type, "\n")] = '\0';

    printf("Введите объём двигателя: ");
    while (scanf("%f", &details->engine_volume) != 1 || details->engine_volume <= 0) {
        printf("Неверный ввод. Введите положительное число: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
}

// Вывод всей информации
void printCar(const Car *car) {
    printCarFields(car);
    printf("Тип кузова: %s\n", car->details.body_type);
    printf("Объём двигателя: %.2f\n", car->details.engine_volume);
}

// Поиск по стоимости
void findCarsAbovePrice(Car *cars, int count, int minPrice) {
    if (count == 0) {
        printf("Список автомобилей пуст.\n");
        return;
    }
    printf("Автомобили дороже %d:\n", minPrice);
    for (int i = 0; i < count; i++) {
        if (cars[i].price > minPrice) {
            printCar(&cars[i]);
            printf("--------------------\n");
        }
    }
}

// Удаление по марке
int deleteCarsByBrand(Car **cars, int count, const char *brand) {
    int newCount = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp((*cars)[i].brand, brand) == 0) {
            free((*cars)[i].brand);
        } else {
            (*cars)[newCount] = (*cars)[i];
            newCount++;
        }
    }
    Car *temp = realloc(*cars, newCount * sizeof(Car));
    if (temp == NULL && newCount != 0) {
        printf("Ошибка перевыделения памяти!\n");
        return count;
    }
    *cars = temp;
    return newCount;
}