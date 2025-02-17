#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

const vector<int> NOMINALS = { 100, 200, 500, 1000, 2000, 5000 };
const int MAX_NOTES = 1000;
const string ATM_FILE = "atm_state.bin";

void saveATMState(const vector<int>& atm) {
    ofstream file(ATM_FILE, ios::binary);
    file.write(reinterpret_cast<const char*>(atm.data()), atm.size() * sizeof(int));
    file.close();
}

void loadATMState(vector<int>& atm) {
    ifstream file(ATM_FILE, ios::binary);
    if (file) {
        file.read(reinterpret_cast<char*>(atm.data()), atm.size() * sizeof(int));
    }
    file.close();
}

void printATMState(const vector<int>& atm) {
    setlocale(LC_ALL, "Russian");

    int total = 0;
    cout << "Состояние банкомата:" << endl;
    for (size_t i = 0; i < NOMINALS.size(); i++) {
        cout << NOMINALS[i] << " руб.: " << atm[i] << " шт." << endl;
        total += atm[i] * NOMINALS[i];
    }
    cout << "Общая сумма: " << total << " руб." << endl;
}

void refillATM(vector<int>& atm) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, MAX_NOTES / NOMINALS.size());

    int remaining = MAX_NOTES;
    for (size_t i = 0; i < NOMINALS.size(); i++) {
        atm[i] = min(dist(gen), remaining);
        remaining -= atm[i];
    }
    saveATMState(atm);
    printATMState(atm);
}

bool withdrawMoney(vector<int>& atm, int amount) {
    setlocale(LC_ALL, "Russian");

    vector<int> temp_atm = atm;
    vector<int> to_withdraw(NOMINALS.size(), 0);

    for (int i = NOMINALS.size() - 1; i >= 0; i--) {
        while (amount >= NOMINALS[i] && temp_atm[i] > 0) {
            amount -= NOMINALS[i];
            temp_atm[i]--;
            to_withdraw[i]++;
        }
    }

    if (amount == 0) {
        atm = temp_atm;
        saveATMState(atm);
        printATMState(atm);
        return true;
    }
    else {
        cout << "Невозможно выдать указанную сумму." << endl;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> atm(NOMINALS.size(), 0);
    loadATMState(atm);
    printATMState(atm);

    char command;
    while (true) {
        cout << "Введите команду (+ для пополнения, - для снятия, q для выхода): ";
        cin >> command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (command == '+') {
            refillATM(atm);
        }
        else if (command == '-') {
            int amount;
            cout << "Введите сумму для снятия: ";
            cin >> amount;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите корректное число." << endl;
                continue;
            }

            if (amount % 100 == 0) {
                withdrawMoney(atm, amount);
            }
            else {
                cout << "Сумма должна быть кратна 100." << endl;
            }
        }
        else if (command == 'q') {
            break;
        }
        else {
            cout << "Неизвестная команда." << endl;
        }
    }

    saveATMState(atm);
    return 0;
}
