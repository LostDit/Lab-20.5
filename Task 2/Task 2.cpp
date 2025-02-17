#include <fstream>
#include <iostream>

int main() {
	setlocale(LC_ALL, "Russian");
	std::srand(std::time(nullptr));

	int width, height;
	std::cout << "Введите ширину и высоту картины: ";
	std::cin >> width >> height;

	std::ofstream outFile("pic.txt");
	if (!outFile) {
		std::cerr << "Ошибка при открытии файла!\n";
		return 1;
	}
	
	for (int i = 0; i < height; ++i)	{
		for (int j = 0; j < width; ++j)	{
			outFile << (std::rand() % 2);
		}
		outFile << '\n';
	}

	outFile.close();
	std::cout << "Файл pic.txt успешно создан!\n";
	return 0;
}
