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
    cout << "��������� ���������:" << endl;
    for (size_t i = 0; i < NOMINALS.size(); i++) {
        cout << NOMINALS[i] << " ���.: " << atm[i] << " ��." << endl;
        total += atm[i] * NOMINALS[i];
    }
    cout << "����� �����: " << total << " ���." << endl;
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
        cout << "���������� ������ ��������� �����." << endl;
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
        cout << "������� ������� (+ ��� ����������, - ��� ������, q ��� ������): ";
        cin >> command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (command == '+') {
            refillATM(atm);
        }
        else if (command == '-') {
            int amount;
            cout << "������� ����� ��� ������: ";
            cin >> amount;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������: ������� ���������� �����." << endl;
                continue;
            }

            if (amount % 100 == 0) {
                withdrawMoney(atm, amount);
            }
            else {
                cout << "����� ������ ���� ������ 100." << endl;
            }
        }
        else if (command == 'q') {
            break;
        }
        else {
            cout << "����������� �������." << endl;
        }
    }

    saveATMState(atm);
    return 0;
}