#include <iostream>
#include <string>


#include <Windows.h>

int findSubstringLightRabinKarp(std::string str, std::string substr) {
	if (substr.length() > str.length()) {
		return -1;
	}
	int allHash{}; //хэш подсроки
	for (char symbol : substr) {
		allHash += static_cast<unsigned char>(symbol);
	}

	int currentHash{}; //подсчет хэша первого окна
	for (int i = 0; i < substr.length(); ++i) {
		char symbol = str[i];
		currentHash += static_cast<unsigned char>(symbol);
	}
	
	
	if (allHash == currentHash) {
		bool firstWindowIsSucced = true;
		for (int i = 0; i < substr.length(); ++i) {
			if (str[i] != substr[i]) {
				firstWindowIsSucced = false;
				break;
			}
		}
		if (firstWindowIsSucced) {
			return 0;
		}
	}

	

	//цикл сдвига
	
	for (int i = 1; i <= (str.length() - substr.length()); ++i) {
		//перемещение окна
		currentHash -= static_cast<unsigned char> (str[i-1]); //убираем лишний символ
		currentHash += static_cast<unsigned char>(str[i + substr.length() - 1]); //добавляем новый, который справа

		if (allHash == currentHash) {
			//более точная проверка уже по символам, когда есть совпадение по хэшу

			bool otherWindowIsSucces = true;
			for (int j = 0; j < substr.length(); ++j) {
				if (str[i+j] != substr[j]) { //сравнение символа из окна и соответствующего символа подсроки
					otherWindowIsSucces = false;
					break;
				}
			}
			if (otherWindowIsSucces) {
				return i;
			}
		}
	}
	return -1;
}



int main() {
	SetConsoleOutputCP(1251);
	std::string str{}, substr{};
	int index{};

	std::cout << "Введите строку, в которой будет осуществляться поиск: ";
	std::getline(std::cin, str);
	do {
		std::cout << "Введите подстроку, которую нужно найти: ";
		std::getline(std::cin, substr);
		index = findSubstringLightRabinKarp(str, substr);
		if (index == -1) {
			std::cout << "Подстрока " << substr << " не найдена\n";
		}
		else {
			std::cout << "Подстрока " << substr << " найдена по индексу " << index << "\n";
		}
	} while (substr != "exit");

	return 0;
}
