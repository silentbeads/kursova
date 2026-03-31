#include <iostream>
#include <windows.h>
#include "Article.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int capacity = 10;
    int size = 0;
    Article** database = new Article * [capacity];

    int choice;
    string filename = "data1.txt";
    int index, key;
    string searchStr;

    do {
        cout << "\n=== ОБЛІК НАУКОВИХ СТАТЕЙ ===" << endl;
        cout << "1. Завантажити з файлу" << endl;
        cout << "2. Додати елемент в кінець" << endl;
        cout << "3. Переглянути всі" << endl;
        cout << "4. Зберегти у файл" << endl;
        cout << "5. Сортування (Шейкер) та Пошук (Інтерполяційний за авторами)" << endl;
        cout << "6. Пошук за назвою статті (Загальна вимога)" << endl;
        cout << "7. Вставити ПЕРЕД елементом" << endl;
        cout << "8. Вставити ПІСЛЯ елемента" << endl;
        cout << "9. Замінити елемент" << endl;
        cout << "10. Видалити елементи (від обраного до кінця)" << endl;
        cout << "11. Статистика (Max/Min/Avg по Impact Factor)" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введіть ім'я файлу (наприклад data1.txt): ";
            cin >> filename;
            loadFromFile(database, size, capacity, filename);
            break;
        case 2:
            addElement(database, size, capacity);
            break;
        case 3:
            printTable(database, size);
            break;
        case 4:
            saveToFile(database, size, filename);
            break;
        case 5:
            shakerSort(database, size);
            cout << "\nВведіть кількість авторів для інтерполяційного пошуку: ";
            cin >> key;
            index = interpolationSearch(database, size, key);
            if (index != -1) {
                cout << "Статтю знайдено під індексом " << index + 1 << ":" << endl;
                cout << database[index]->title << " (Авторів: " << database[index]->authorsCount << ")" << endl;
            }
            else {
                cout << "Статтю з такою кількістю авторів не знайдено." << endl;
            }
            break;
        case 6:
            cout << "Введіть назву (або частину назви) для пошуку: ";
            cin.ignore();
            getline(cin, searchStr);
            searchByTitle(database, size, searchStr);
            break;
        case 7:
            cout << "Введіть номер елемента, перед яким вставити: ";
            cin >> index;
            insertBefore(database, size, capacity, index - 1);
            break;
        case 8:
            cout << "Введіть номер елемента, після якого вставити: ";
            cin >> index;
            insertAfter(database, size, capacity, index - 1);
            break;
        case 9:
            cout << "Введіть номер елемента для заміни: ";
            cin >> index;
            replaceElement(database, size, index - 1);
            break;
        case 10:
            cout << "Введіть номер елемента, починаючи з якого ВИДАЛИТИ ВСІ: ";
            cin >> index;
            deleteFromIndex(database, size, index - 1);
            break;
        case 11:
            calculateStatistics(database, size);
            break;
        case 0:
            cout << "Робота завершена." << endl;
            break;
        default:
            cout << "Невірний вибір." << endl;
        }
    } while (choice != 0);

    // Очищення пам'яті
    for (int i = 0; i < size; i++) delete database[i];
    delete[] database;

    return 0;
}