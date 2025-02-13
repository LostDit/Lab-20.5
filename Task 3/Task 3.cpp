#include <iostream>
#include <locale>

#define MAX_PASSENGERS 20
#define NUM_WAGONS 10

#define PROCESS_WAGONS(func, wagons) \
    for (int i = 0; i < NUM_WAGONS; ++i) { func(wagons[i], i + 1); }

void checkOverfilled(int passengers, int wagon) {
    if (passengers > MAX_PASSENGERS) {
        std::cout << "����� " << wagon << " ���������� (" << passengers << " ����������)." << std::endl;
    }
}

void checkUnderfilled(int passengers, int wagon) {
    if (passengers < MAX_PASSENGERS) {
        std::cout << "����� " << wagon << " ����� ��������� ����� (" << passengers << " ����������)." << std::endl;
    }
}

int countTotalPassengers(int passengers) {
    return passengers;
}

int main() {
    setlocale(LC_ALL, "");

    int wagons[NUM_WAGONS];
    std::cout << "������� ���������� ���������� � ������ �� 10 �������: ";
    for (int i = 0; i < NUM_WAGONS; ++i) {
        std::cin >> wagons[i];
    }

    std::cout << "������ ������������� �������:" << std::endl;
    PROCESS_WAGONS(checkOverfilled, wagons);
    PROCESS_WAGONS(checkUnderfilled, wagons);

    int totalPassengers = 0;
    for (int i = 0; i < NUM_WAGONS; ++i) {
        totalPassengers += countTotalPassengers(wagons[i]);
    }

    std::cout << "����� ���������� ����������: " << totalPassengers << std::endl;
    return 0;
}