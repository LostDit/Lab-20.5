#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    string target_fish;
    cout << "������� ��� ����, ������� ������ �������: ";
    cin >> target_fish;

    ifstream river_file("river.txt");
    ofstream basket_file("basket.txt", ios::app);

    if (!river_file) {
        cerr << "������: �� ������� ������� ���� river.txt" << endl;
        return 1;
    }
    if (!basket_file) {
        cerr << "������: �� ������� ������� ���� basket.txt" << endl;
        return 1;
    }

    string fish;
    int count = 0;
    while (river_file >> fish) {
        if (fish == target_fish) {
            basket_file << fish << endl;
            count++;
        }
    }

    river_file.close();
    basket_file.close();

    cout << "�� ������� " << count << " ���(�) ���� " << target_fish << "." << endl;

    return 0;
}