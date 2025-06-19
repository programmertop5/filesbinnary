#define _CRT_SECURE_NO_WARNINGS // Отключает предупреждения безопасности компилятора для некоторых функций C-стандарта
#include <iostream>            // Подключает библиотеку для стандартного ввода/вывода (cout, cin)
#include <Windows.h>           // Подключает библиотеку для функций Windows (GetStdHandle, HANDLE)
#include <cstdio>              // Подключает библиотеку для функций файлового ввода/вывода (fopen, fprintf, fclose, fgets, feof, fscanf_s, fopen_s)
//#include <stdio.h>           // Закомментировано, но это то же, что и <cstdio> в C++

using namespace std;           // Использует стандартное пространство имен (позволяет писать cout вместо std::cout)

void initArray(int arr[], int size) { // Функция для инициализации массива случайными числами
	for (int i = 0; i < size; i++) {   // Цикл по элементам массива
		arr[i] = 1 + rand() % 50;      // Присваивает случайное число от 1 до 50
	}
}

bool printArrayToFile(FILE* descriptor, int arr[], int size) { // Функция для записи массива в файл
	if (descriptor == nullptr) {    // Проверяет, если дескриптор файла недействителен (файл не открыт)
		return false;               // Возвращает false (ошибка)
	}
	for (int i = 0; i < size; i++) { // Цикл по элементам массива
		fprintf(descriptor, "%i Hello %i", arr[i], i); // Записывает отформатированную строку в файл (число, " Hello ", индекс)
		fprintf(descriptor, "\n");  // Записывает символ новой строки в файл
	}
	return true;                    // Возвращает true (успешно)
}

int main() {                        // Главная функция программы
	srand(time(NULL));              // Инициализирует генератор случайных чисел текущим временем
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Получает хэндл стандартного вывода (консоли)
	cout << h << endl;              // Выводит значение хэндла (его адрес)

	

	FILE* fileDescriptor = nullptr; // Объявляет указатель на файловый дескриптор, инициализирует NULL

	

	if ((fileDescriptor = fopen("C:\\Users\\semenyuk_o\\Desktop\\p-48.txt", "w")) == NULL) { // Пытается открыть/создать "p-48.txt" на рабочем столе в режиме "w" (запись)
		cout << "File wasn't successfuly created"; // Если fopen возвращает NULL (ошибка), выводит сообщение
	}
	else {                                     // Если файл успешно открыт/создан
		cout << "File created!!!" << endl;     // Выводит сообщение об успешном создании
		int arr[10];                           // Объявляет массив из 10 целых чисел
		initArray(arr, 10);                    // Инициализирует массив случайными числами
		bool result = printArrayToFile(fileDescriptor, arr, 10); // Записывает массив в файл, получает статус
		result ? cout << "File write status: \033[42mOK\033[0m\n" : cout << "File write status: \033[41m!OK\033[0m\n"; // Выводит статус записи (зеленый OK или красный !OK)
		fclose(fileDescriptor);                // Закрывает файл
	}

	const char* path = "C:\\Users\\semenyuk_o\\Desktop\\p-48.txt"; // Определяет путь к файлу для чтения

	int openResult = fopen_s(&fileDescriptor, path, "r"); // Открывает файл "p-48.txt" в режиме "r" (чтение)
	if (openResult == 0) {                             // Если файл успешно открыт (fopen_s возвращает 0)
		/* // Закомментированный код, демонстрирующий:
			// - Чтение строк из файла с помощью fscanf_s
		*/
		char line[255];                                // Объявляет буфер для строки
		while (fgets(line, sizeof(line), fileDescriptor)) { // Читает строку из файла в 'line' до конца файла
			cout << line;                              // Выводит прочитанную строку на консоль
		}
		fclose(fileDescriptor);                        // Закрывает файл
	}
}
