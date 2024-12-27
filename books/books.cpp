#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Book {
    string name;
    string author;
    string publishing;
    string year;
    string cost;
};

int getInputInt(int min, int max) {
    setlocale(LC_ALL, "RU");
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка. Введите число от " << min << " до " << max << ": ";
        } else {
            return input;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    string fileLocation = "E:/books.txt";  // Путь к файлу
    vector<Book> books;
    ifstream inFile(fileLocation);
    
    if (!inFile.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 1;
    }

    // Загрузка данных из файла
    Book book;
    while (inFile >> book.name >> book.author >> book.publishing >> book.year >> book.cost) {
        books.push_back(book);
    }
    inFile.close();

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Показать книги\n";
        cout << "2. Добавить новую книгу\n";
        cout << "3. Удалить книгу\n";
        cout << "4. Добавить книги из другого файла\n";
        cout << "5. Фильтрация по цене\n";
        cout << "6. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Название \t Автор \t Издательство \t Год \t Цена" << endl;
                for (const auto& book : books) {
                    cout << book.name << " \t " << book.author << " \t " << book.publishing << " \t " << book.year << " \t " << book.cost << endl;
                }
                break;
            }
            case 2: {
                Book newBook;
                cout << "Введите название книги: ";
                cin.ignore();
                getline(cin, newBook.name);
                cout << "Введите имя автора: ";
                getline(cin, newBook.author);
                cout << "Введите издательство: ";
                getline(cin, newBook.publishing);
                cout << "Введите год издания: ";
                getline(cin, newBook.year);
                cout << "Введите цену книги: ";
                getline(cin, newBook.cost);

                books.push_back(newBook);
                
                // Добавляем книгу в файл
                ofstream outFile(fileLocation, ios::app);
                if (!outFile.is_open()) {
                    cout << "Не удалось открыть файл для добавления!" << endl;
                    return 1;
                }
                outFile << newBook.name << " " << newBook.author << " " << newBook.publishing << " " << newBook.year << " " << newBook.cost << endl;
                outFile.close();
                break;
            }
            case 3: {
                int index;
                cout << "Введите номер книги для удаления (от 0 до " << books.size() - 1 << "): ";
                cin >> index;

                if (index >= 0 && index < books.size()) {
                    books.erase(books.begin() + index);
                    cout << "Книга удалена!" << endl;

                    // Перезаписываем файл с новыми данными
                    ofstream outFile(fileLocation);
                    if (!outFile.is_open()) {
                        cout << "Не удалось открыть файл для перезаписи!" << endl;
                        return 1;
                    }
                    for (const auto& book : books) {
                        outFile << book.name << " " << book.author << " " << book.publishing << " " << book.year << " " << book.cost << endl;
                    }
                    outFile.close();
                } else {
                    cout << "Некорректный индекс!" << endl;
                }
                break;
            }
            case 4: {
                string anotherFile;
                cout << "Введите путь к файлу для добавления данных: ";
                cin >> anotherFile;

                ifstream inFile(anotherFile);
                if (!inFile.is_open()) {
                    cout << "Не удалось открыть файл для добавления!" << endl;
                    break;
                }

                while (inFile >> book.name >> book.author >> book.publishing >> book.year >> book.cost) {
                    books.push_back(book);
                }
                inFile.close();

                // Перезаписываем файл с новыми данными
                ofstream outFile(fileLocation);
                if (!outFile.is_open()) {
                    cout << "Не удалось открыть файл для перезаписи!" << endl;
                    return 1;
                }
                for (const auto& book : books) {
                    outFile << book.name << " " << book.author << " " << book.publishing << " " << book.year << " " << book.cost << endl;
                }
                outFile.close();
                break;
            }
            case 5: {
                double minPrice, maxPrice;
                cout << "Введите минимальную цену: ";
                cin >> minPrice;
                cout << "Введите максимальную цену: ";
                cin >> maxPrice;

                cout << "Книги в пределах диапазона цен (" << minPrice << " - " << maxPrice << "):" << endl;
                cout << "Название \t Автор \t Издательство \t Год \t Цена" << endl;
                for (const auto& book : books) {
                    double cost = stod(book.cost);  // Преобразуем строку в число
                    if (cost >= minPrice && cost <= maxPrice) {
                        cout << book.name << " \t " << book.author << " \t " << book.publishing << " \t " << book.year << " \t " << book.cost << endl;
                    }
                }
                break;
            }
            case 6:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
