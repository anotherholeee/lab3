#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BODY_TYPE_LENGTH 20

typedef struct {
    char body_type[MAX_BODY_TYPE_LENGTH];
    float engine_volume;
} Details;

typedef struct {
    int price;
    char *brand;
    Details details;
} Car;




int main() {
    Car *cars = NULL;
    int count = 0;
    int choice;

    do {
        printf("\nМеню:\n");
        printf("1. Добавить автомобиль\n");
        printf("2. Показать все автомобили\n");
        printf("3. Найти автомобили дороже указанной цены\n");
        printf("4. Удалить автомобили по марке\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: {
                Car *temp = realloc(cars, (count + 1) * sizeof(Car));
                if (!temp) {
                    printf("Ошибка выделения памяти!\n");
                    break;
                }
                cars = temp;
                inputCarFields(&cars[count]);
                inputDetails(&cars[count].details);
                count++;
                break;
            }
            case 2:
                if (count == 0) {
                    printf("Список пуст.\n");
                } else {
                    for (int i = 0; i < count; i++) {
                        printf("Автомобиль %d:\n", i + 1);
                        printCar(&cars[i]);
                        printf("--------------------\n");
                    }
                }
                break;
            case 3: {
                if (count == 0) {
                    printf("Список пуст.\n");
                    break;
                }
                int minPrice;
                printf("Введите минимальную стоимость: ");
                if (scanf("%d", &minPrice) != 1) {
                    printf("Неверный ввод!\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                findCarsAbovePrice(cars, count, minPrice);
                break;
            }
            case 4: {
                if (count == 0) {
                    printf("Список пуст.\n");
                    break;
                }
                char brand[100];
                printf("Введите марку для удаления: ");
                fgets(brand, 100, stdin);
                brand[strcspn(brand, "\n")] = '\0';
                int newCount = deleteCarsByBrand(&cars, count, brand);
                if (newCount < count) {
                    printf("Удалено %d автомобилей.\n", count - newCount);
                    count = newCount;
                } else {
                    printf("Автомобили марки '%s' не найдены.\n", brand);
                }
                break;
            }
            case 5:
                printf("Выход...\n");
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 5);

    // Освобождение памяти
    for (int i = 0; i < count; i++) {
        free(cars[i].brand);
    }
    free(cars);

    return 0;
}