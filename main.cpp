#define _CRT_SECURE_NO_WARNINGS // Отключает предупреждения для старых функций CRT (небезопасные версии)
#include <iostream>            // Подключает библиотеку для ввода/вывода (cout, cin)
#include <conio.h>             // Подключает библиотеку для _getch() (чтение символа без Enter)
#include <cstdio>              // Подключает библиотеку для файловых операций (fopen_s, fwrite, fread_s, fclose)
#include <cstdlib>             // Подключает библиотеку для srand, rand, exit, system
#include <cstring>             // Подключает библиотеку для strerror_s (описание ошибок)
#include <ctime>               // Подключает библиотеку для time (используется для srand)

using namespace std;           // Использует стандартное пространство имен (cout вместо std::cout)

struct Person {                // Определяет структуру "Person"
	int age;                   //  - Целочисленный возраст
	char name[50];             //  - Массив символов для имени (до 49 символов + null-терминатор)
	char surname[50];          //  - Массив символов для фамилии
};

void printErrorMessage(const char* errorHeader, int errorCode) { // Функция для вывода сообщений об ошибках
	char errorMessage[255];    // Буфер для текста ошибки
	strerror_s(errorMessage, sizeof(errorMessage), errorCode); // Преобразует код ошибки в текст
	cout << errorHeader << ": " << errorMessage << endl;      // Выводит заголовок и текст ошибки
}

char printMenu() {             // Функция для вывода меню и получения выбора пользователя
	cout << "1. Write and read variable" << endl; // Пункт меню: переменная
	cout << "2. Write and read array" << endl;    // Пункт меню: массив
	cout << "3. Write and read struct" << endl;   // Пункт меню: структура
	cout << "4. Exit";                        // Пункт меню: выход
	cout << endl << "Select an option: ";     // Подсказка для ввода
	return _getch();                       // Возвращает нажатый символ без Enter
}

void initArray(int arr[], int size) { // Функция для инициализации массива случайными числами
	for (int i = 0; i < size; i++) {   // Проходит по всем элементам
		arr[i] = -10 + rand() % 20;    // Присваивает случайное число от -10 до 9
	}
}

void printArray(int arr[], int size) { // Функция для вывода массива на консоль
	for (int i = 0; i < size; i++) {   // Проходит по всем элементам
		cout << arr[i] << "\t";        // Выводит элемент и табуляцию
	}
	cout << endl;                      // Переход на новую строку
}

void printPerson(Person p) {       // Функция для вывода данных структуры Person
	cout << "\n-------------- PERSON ----------------\n"; // Разделитель
	cout << "Age: " << p.age << endl;         // Выводит возраст
	cout << "Name: " << p.name << endl;       // Выводит имя
	cout << "Surname: " << p.surname << endl; // Выводит фамилию
	cout << "\n--------------------------------------\n"; // Разделитель
}

int main() {                       // Главная функция программы
	srand(time(NULL));             // Инициализирует генератор случайных чисел
	const char* fileVariable = "variable.bin"; // Имя файла для переменной
	const char* fileArray = "array.bin";       // Имя файла для массива
	const char* fileStruct = "struct.bin";     // Имя файла для структуры

	FILE* binnaryFile;             // Указатель на файловый дескриптор
	char errorHeader[] = "Error";  // Заголовок для ошибок
	int fileError = 0;             // Код ошибки файла
	bool isExit = false;           // Флаг выхода из программы

	int value = 10;                // Переменная для записи/чтения (int)
	int arr[5];                    // Массив для записи (int[])
	int arr2[5] = { 0 };           // Массив для чтения (int[]), инициализирован нулями
	initArray(arr, 5);             // Заполняет arr случайными числами

	Person p1 = { 20,"Thomas","Shlepi" }; // Структура для записи (Person)
	Person p2;                             // Структура для чтения (Person)

	while (!isExit) {                   // Основной цикл программы, пока не выбран выход
		system("cls");                  // Очищает экран консоли
		char menu = printMenu();        // Показывает меню, получает выбор

		switch (menu) {                 // Обработка выбора пользователя

		case '1':                       // Если выбрано '1' (переменная)
			system("cls");              // Очищает экран
			fileError = fopen_s(&binnaryFile, fileVariable, "wb"); // Открывает variable.bin для бинарной записи
			if (!binnaryFile) {         // Если файл не открылся
				printErrorMessage(errorHeader, fileError); // Выводит ошибку
				exit(EXIT_FAILURE);     // Завершает программу
			}
			cout << "FILE: " << binnaryFile << endl; // Выводит адрес дескриптора (для отладки)
			fwrite(&value, sizeof(value), 1, binnaryFile); // Записывает 'value' в файл
			// if (fileError != 0) { printErrorMessage(errorHeader, fileError); } // Эта проверка ошибочна для fwrite
			fclose(binnaryFile);        // Закрывает файл
			binnaryFile = nullptr;      // Обнуляет указатель
			value = 0;                  // Обнуляет 'value' перед чтением
			cout << "Value(before read file): " << value << endl; // Показывает обнуленное значение
			fileError = fopen_s(&binnaryFile, fileVariable, "rb"); // Открывает variable.bin для бинарного чтения
			if (!binnaryFile) {         // Если файл не открылся
				printErrorMessage(errorHeader, fileError); // Выводит ошибку
				exit(EXIT_FAILURE);     // Завершает программу
			}
			fread(&value, sizeof(int), 1, binnaryFile); // Читает int из файла в 'value'
			cout << "Value(after read file): " << value << endl; // Показывает прочитанное значение
			fclose(binnaryFile);        // Закрывает файл
			system("pause");            // Ожидает нажатия клавиши
			break;                      // Выход из switch

		case '2':                       // Если выбрано '2' (массив)
			system("cls");              // Очищает экран
			fileError = fopen_s(&binnaryFile, fileArray, "wb"); // Открывает array.bin для бинарной записи
			if (!binnaryFile) {         // Если файл не открылся
				printErrorMessage(errorHeader, fileError); // Выводит ошибку
				exit(EXIT_FAILURE);     // Завершает программу
			}
			cout << "Array before open file: " << endl; // Подсказка
			printArray(arr, 5);         // Выводит исходный массив 'arr'
			fwrite(arr, sizeof(int), sizeof(arr) / sizeof(int), binnaryFile); // Записывает 'arr' в файл
			fclose(binnaryFile);        // Закрывает файл

			fileError = fopen_s(&binnaryFile, fileArray, "rb"); // Открывает array.bin для бинарного чтения
			if (!binnaryFile) {         // Если файл не открылся
				printErrorMessage(errorHeader, fileError); // Выводит ошибку
				exit(EXIT_FAILURE);     // Завершает программу
			}
			fread_s(arr2, sizeof(arr2), sizeof(int), sizeof(arr2) / sizeof(int), binnaryFile); // Читает в 'arr2'
			cout << "Array after reading file: " << endl; // Подсказка
			printArray(arr2, 5);        // Выводит прочитанный массив 'arr2'
			fclose(binnaryFile);        // Закрывает файл
			system("pause");            // Ожидает нажатия клавиши
			break;                      // Выход из switch

		case '3':                       // Если выбрано '3' (структура)
			system("cls");              // Очищает экран
			fileError = fopen_s(&binnaryFile, fileStruct, "wb"); // Открывает struct.bin для бинарной записи
			if (!binnaryFile) {         // Если файл не открылся
				printErrorMessage(errorHeader, fileError); // Выводит ошибку
				exit(EXIT_FAILURE);     // Завершает программу
			}
			cout << "Struct before write file: " << endl; // Подсказка
			printPerson(p1);            // Выводит исходную структуру 'p1'
			fwrite(&p1, sizeof(Person), 1, binnaryFile); // Записывает 'p1' в файл
			fclose(binnaryFile);        // Закрывает файл

			fileError = fopen_s(&binnaryFile, fileStruct, "rb"); // Открывает struct.bin для бинарного чтения
			if (!binnaryFile) {         // Если файл не открылся
				printErrorMessage(errorHeader, fileError); // Выводит ошибку
				exit(EXIT_FAILURE);     // Завершает программу
			}
			fread_s(&p2, sizeof(Person), sizeof(Person), 1, binnaryFile); // Читает в 'p2'
			cout << "Struct after read file: " << endl; // Подсказка
			printPerson(p2);            // Выводит прочитанную структуру 'p2'
			fclose(binnaryFile);        // Закрывает файл
			system("pause");            // Ожидает нажатия клавиши
			break;                      // Выход из switch

		case '4':                       // Если выбрано '4' (выход)
			system("cls");              // Очищает экран
			isExit = true;              // Устанавливает флаг выхода
			cout << "Thank you for using this COOL APP" << endl; // Прощальное сообщение
			break;                      // Выход из switch

		default:                        // Если выбран неизвестный пункт
			system("cls");              // Очищает экран
			cout << "Error! Wrong menu item. Please retry..." << endl; // Сообщение об ошибке
			system("pause");            // Ожидает нажатия клавиши
		}
	}
}
