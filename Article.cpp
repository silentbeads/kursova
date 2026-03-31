#include "Article.h"

// --- Допоміжні функції пам'яті ---
void expandArray(Article**& arr, int& capacity) {
    int newCapacity = capacity == 0 ? 2 : capacity * 2;
    Article** newArr = new Article * [newCapacity];
    for (int i = 0; i < capacity; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
}

// --- 1. Введення з файлу ---
void loadFromFile(Article**& arr, int& size, int& capacity, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) delete arr[i];
    size = 0;

    while (!file.eof()) {
        if (size >= capacity) expandArray(arr, capacity);
        Article* temp = new Article;
        getline(file, temp->title);
        if (temp->title.empty()) { delete temp; break; }

        file >> temp->authorsCount >> temp->impactFactor >> temp->year;
        file.ignore();

        arr[size++] = temp;
    }
    file.close();
    cout << "Дані завантажено. Кількість записів: " << size << endl;
    printTable(arr, size);
}

// --- 4. Виведення у файл ---
void saveToFile(Article** arr, int size, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка запису у файл!" << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        file << arr[i]->title << endl;
        file << arr[i]->authorsCount << " " << arr[i]->impactFactor << " " << arr[i]->year << endl;
    }
    file.close();
    cout << "Дані успішно збережено у " << filename << endl;
}

// --- 3. Перегляд (Таблиця) ---
void printTable(Article** arr, int size) {
    cout << string(75, '-') << endl;
    cout << "| No | " << setw(30) << left << "Назва статті"
        << "| " << setw(8) << "Авторів"
        << "| " << setw(8) << "Impact"
        << "| " << setw(6) << "Рік" << " |" << endl;
    cout << string(75, '-') << endl;

    for (int i = 0; i < size; i++) {
        cout << "| " << setw(2) << i + 1 << " | "
            << setw(30) << left << arr[i]->title.substr(0, 29)
            << "| " << setw(8) << right << arr[i]->authorsCount
            << "| " << setw(8) << arr[i]->impactFactor
            << "| " << setw(6) << arr[i]->year << " |" << endl;
    }
    cout << string(75, '-') << endl;
}

// --- 2. Додавання в кінець ---
void addElement(Article**& arr, int& size, int& capacity) {
    if (size >= capacity) expandArray(arr, capacity);
    Article* temp = new Article;
    cout << "Введіть назву статті: ";
    cin.ignore();
    getline(cin, temp->title);
    cout << "Кількість авторів: "; cin >> temp->authorsCount;
    cout << "Impact Factor: "; cin >> temp->impactFactor;
    cout << "Рік видання: "; cin >> temp->year;
    arr[size++] = temp;
    printTable(arr, size);
}

// --- 5. Шейкерне сортування (за кількістю авторів) ---
void shakerSort(Article** arr, int size) {
    int left = 0;
    int right = size - 1;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = left; i < right; i++) {
            if (arr[i]->authorsCount > arr[i + 1]->authorsCount) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        right--;

        for (int i = right; i > left; i--) {
            if (arr[i - 1]->authorsCount > arr[i]->authorsCount) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        left++;
    }
    cout << "Масив відсортовано за кількістю авторів." << endl;
    printTable(arr, size);
}

// --- 5. Інтерполяційний пошук (за кількістю авторів) ---
int interpolationSearch(Article** arr, int size, int key) {
    int low = 0;
    int high = size - 1;

    while (low <= high && key >= arr[low]->authorsCount && key <= arr[high]->authorsCount) {
        if (low == high) {
            if (arr[low]->authorsCount == key) return low;
            return -1;
        }
        if (arr[low]->authorsCount == arr[high]->authorsCount) {
            if (arr[low]->authorsCount == key) return low;
            return -1;
        }
        double posDouble = (double)(key - arr[low]->authorsCount) / (arr[high]->authorsCount - arr[low]->authorsCount);
    }
    return -1;
}

// --- ПОШУК ЗА НАЗВОЮ (Для виконання загальної вимоги) ---
void searchByTitle(Article** arr, int size, const string& targetTitle) {
    bool found = false;
    cout << "\nРезультати пошуку за назвою '" << targetTitle << "':\n";
    for (int i = 0; i < size; i++) {
        // Шукаємо підрядок у назві (щоб не вводити повну назву ідеально точно)
        if (arr[i]->title.find(targetTitle) != string::npos) {
            cout << "- " << arr[i]->title << " (Авторів: " << arr[i]->authorsCount
                << ", Impact: " << arr[i]->impactFactor << ", Рік: " << arr[i]->year << ")\n";
            found = true;
        }
    }
    if (!found) cout << "Статей з такою назвою не знайдено.\n";
}

// --- 6. Вставка перед елементом ---
void insertBefore(Article**& arr, int& size, int& capacity, int index) {
    if (index < 0 || index >= size) { cout << "Невірний індекс!\n"; return; }
    if (size >= capacity) expandArray(arr, capacity);

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    Article* temp = new Article;
    cout << "Введіть нову статтю (вставка перед №" << index + 1 << "):" << endl;
    cout << "Назва: "; cin.ignore(); getline(cin, temp->title);
    cout << "Авторів: "; cin >> temp->authorsCount;
    cout << "Impact: "; cin >> temp->impactFactor;
    cout << "Рік: "; cin >> temp->year;

    arr[index] = temp;
    size++;
    printTable(arr, size);
}

// --- 7. Вставка після елемента ---
void insertAfter(Article**& arr, int& size, int& capacity, int index) {
    if (index < 0 || index >= size) { cout << "Невірний індекс!\n"; return; }
    if (size >= capacity) expandArray(arr, capacity);

    for (int i = size; i > index + 1; i--) {
        arr[i] = arr[i - 1];
    }

    Article* temp = new Article;
    cout << "Введіть нову статтю (вставка після №" << index + 1 << "):" << endl;
    cout << "Назва: "; cin.ignore(); getline(cin, temp->title);
    cout << "Авторів: "; cin >> temp->authorsCount;
    cout << "Impact: "; cin >> temp->impactFactor;
    cout << "Рік: "; cin >> temp->year;

    arr[index + 1] = temp;
    size++;
    printTable(arr, size);
}

// --- 8. Заміна елемента ---
void replaceElement(Article** arr, int size, int index) {
    if (index < 0 || index >= size) { cout << "Невірний індекс!\n"; return; }
    cout << "Редагування елемента №" << index + 1 << endl;
    cout << "Стара назва: " << arr[index]->title << endl;
    cout << "Нова назва: "; cin.ignore(); getline(cin, arr[index]->title);
    cout << "Нова к-сть авторів: "; cin >> arr[index]->authorsCount;
    cout << "Новий Impact: "; cin >> arr[index]->impactFactor;
    cout << "Новий рік: "; cin >> arr[index]->year;

    // Виправлено: тепер передаємо реальний розмір масиву
    printTable(arr, size);
}

// --- 9. Видалення елементів, починаючи від обраного ---
// Виправлено: тепер видаляє всі елементи від index до кінця
void deleteFromIndex(Article**& arr, int& size, int index) {
    if (index < 0 || index >= size) { cout << "Невірний індекс!\n"; return; }

    // Видаляємо всі елементи від обраного і до кінця
    for (int i = index; i < size; i++) {
        delete arr[i];
        arr[i] = nullptr;
    }

    size = index; // Новий розмір масиву обрізається до індексу
    cout << "Елементи починаючи з №" << index + 1 << " були видалені." << endl;
    printTable(arr, size);
}

// --- 10. Статистика в діапазоні (по Impact Factor) ---
void calculateStatistics(Article** arr, int size) {
    double minRange, maxRange;
    cout << "Введіть діапазон Impact Factor (від до): ";
    cin >> minRange >> maxRange;
    double maxVal = -1.0, minVal = 10000.0, sum = 0;
    int count = 0;
    bool found = false;
    for (int i = 0; i < size; i++) {
        double val = arr[i]->impactFactor;
        if (val >= minRange && val <= maxRange) {
            if (val > maxVal) maxVal = val;
            if (val < minVal) minVal = val;
            sum += val;
            count++;
            found = true;
        }
    }

    if (found) {
        cout << "У діапазоні [" << minRange << ", " << maxRange << "]:" << endl;
        cout << "Максимум: " << maxVal << endl;
        cout << "Мінімум: " << minVal << endl;
        cout << "Середнє: " << (sum / count) << endl;
    }
    else {
        cout << "Елементів у заданому діапазоні не знайдено." << endl;
    }
}