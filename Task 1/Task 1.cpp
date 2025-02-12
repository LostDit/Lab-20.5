#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

bool isValidDate(const std::string& date) {
	
	if (date.length() != 10 || date[2] != '.' || date[5] != '.')
		return false;
	
	try {
		int day = std::stoi(date.substr(0, 2));
		int month = std::stoi(date.substr(3, 2));
		int year = std::stoi(date.substr(6, 4));

		if (month < 1 || month >12 || day < 1 || day >31)
			return false;
		if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
			return false;
		if (month == 2) {
			bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
			if (day > (leap ? 29 : 28))
				return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

bool isValidAmount(const std::string& amount) {
	if (amount.empty()) return false;

	bool hasDot = false;
	for (char c : amount) {
		if (c == '.') {
			if (hasDot) return false;
			hasDot = true;
		}
		else if (!std::isdigit(c)) {
			return false;
		}
	}

	if (amount.front() == '.' || amount.back() == '.')
		return false;

	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");
	std::string firstName, lastName, date, amount;

	std::cout << "Введите имя: ";
	std::cin >> firstName;
	
	std::cout << "Введите фамилию: ";
	std::cin >> lastName;
	
	do {
		std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
		std::cin >> date;
		if (!isValidDate(date))
			std::cout << "Ошибка: некорректный формат даты!\n";
	} while (!isValidDate(date));

	do {
		std::cout << "Введите сумму выплаты: ";
		std::cin >> amount;
		if (!isValidAmount(amount))	{
			std::cout << "Ошибка: сумма должна содержать только цифры!\n";
		}
	} while (!isValidAmount(amount));

	std::ofstream file("bank.txt", std::ios::app);
	if (!file) {
		std::cerr << "Ошибка: не удалось открыть файл!\n";
		return 1;
	}

	file << firstName << " " << lastName << " " << date << " " << amount << "\n";
	file.close();

	std::cout << "Запись успешно добавлена!\n";

	return 0;
}