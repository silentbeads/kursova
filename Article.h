#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Структура запису (наукова стаття)
struct Article {
    string title;       // Назва статті
    int authorsCount;   // Кількість авторів (Ключове поле для сортування)
    double impactFactor;// Поле типу double для завдання №10 (статистика)
    int year;           // Рік видання
};

// Прототипи функцій
void expandArray(Article**& arr, int& capacity);
void loadFromFile(Article**& arr, int& size, int& capacity, const string& filename);
void saveToFile(Article** arr, int size, const string& filename);
void printTable(Article** arr, int size);
void addElement(Article**& arr, int& size, int& capacity);

// Алгоритми (Завдання 5)
void shakerSort(Article** arr, int size);
int interpolationSearch(Article** arr, int size, int key);
void searchByTitle(Article** arr, int size, const string& targetTitle); // Додано для загального завдання

// Редагування
void insertBefore(Article**& arr, int& size, int& capacity, int index);
void insertAfter(Article**& arr, int& size, int& capacity, int index);
void replaceElement(Article** arr, int size, int index); // Додано size
void deleteFromIndex(Article**& arr, int& size, int index); // Видалення від обраного до кінця

// Статистика 
void calculateStatistics(Article** arr, int size);

#endif