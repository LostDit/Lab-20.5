#include <iostream>
#include <locale>

#define MAX_PASSENGERS 20
#define NUM_WAGONS 10

#define PROCESS_WAGONS(func, wagons) \
    for (int i = 0; i < NUM_WAGONS; ++i) { func(wagons[i], i + 1); }

void checkOverfilled(int passengers, int wagon) {
    if (passengers > MAX_PASSENGERS) {
        std::cout << "Вагон " << wagon << " переполнен (" << passengers << " пассажиров)." << std::endl;
    }
}

void checkUnderfilled(int passengers, int wagon) {
    if (passengers < MAX_PASSENGERS) {
        std::cout << "Вагон " << wagon << " имеет свободные места (" << passengers << " пассажиров)." << std::endl;
    }
}

int countTotalPassengers(int passengers) {
    return passengers;
}

int main() {
    setlocale(LC_ALL, "");

    int wagons[NUM_WAGONS];
    std::cout << "Введите количество пассажиров в каждом из 10 вагонов: ";
    for (int i = 0; i < NUM_WAGONS; ++i) {
        std::cin >> wagons[i];
    }

    std::cout << "Анализ заполненности вагонов:" << std::endl;
    PROCESS_WAGONS(checkOverfilled, wagons);
    PROCESS_WAGONS(checkUnderfilled, wagons);

    int totalPassengers = 0;
    for (int i = 0; i < NUM_WAGONS; ++i) {
        totalPassengers += countTotalPassengers(wagons[i]);
    }

    std::cout << "Общее количество пассажиров: " << totalPassengers << std::endl;
    return 0;
}