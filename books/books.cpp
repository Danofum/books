#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct book {
    string name;
    string author;
    string publish;
    string year;
    double price;
};

int intCheck(int num, int max) {
    while (cin.fail() || num < 0 || num > max) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ошибка! Введите число от 0 до " << max << ": ";
        cin >> num;
    }
    return num;
}

bool sortingPoPrice(const book& a, const book& b) {
    return a.price < b.price;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<book> books;
    string fileLocation = "E:\\books.txt";

    ifstream in(fileLocation);
    if (in.is_open()) {
        book tempBook;
        while (getline(in, tempBook.name, ';') && getline(in, tempBook.author, ';') && getline(in, tempBook.publish, ';') && getline(in, tempBook.year, ';') && in >> tempBook.price) {
            in.ignore();
            books.push_back(tempBook);
        }
        in.close();
    }
    else {
        cout << "Ошибка открытия файла!" << endl;
    }

    int choice;

    do {
        cout << "Меню:" << endl;
        cout << "1. Показать книги" << endl;
        cout << "2. Добавить новую книгу" << endl;
        cout << "3. Отсортировать по цене (от min до max)" << endl;
        cout << "4. Добавить книги из другого файла" << endl;
        cout << "5. Удалить книгу" << endl;
        cout << "6. Выход" << endl;

        cin >> choice;
        choice = intCheck(choice, 6);

        switch (choice) {
        case 1: {
            cout << "Книга \t \t Автор \t \t Издательство \t Год \t Стоимость" << endl;
            for (int i = 0; i < books.size(); i++) {
                cout << i + 1 << ". " << books[i].name << "\t \t " << books[i].author << "\t \t " << books[i].publish << "\t " << books[i].year << "\t " << books[i].price << endl;
            }
            break;
        }
        case 2: {
            book addBook;
            cout << "Введите название книги: " << endl;
            cin >> addBook.name;
            cout << "Введите имя автора: " << endl;
            cin >> addBook.author;
            cout << "Введите название издательства: " << endl;
            cin >> addBook.publish;
            cout << "Введите год: " << endl;
            cin >> addBook.year;
            cout << "Введите стоимость: " << endl;
            cin >> addBook.price;

            books.push_back(addBook);

            ofstream out(fileLocation, ios::app);
            if (out.is_open()) {
                out << addBook.name << ";" << addBook.author << ";" << addBook.publish << ";" << addBook.year << ";" << addBook.price << endl;
                out.close();
                cout << "Книга добавлена!" << endl;
            }
            else {
                cout << "Ошибка открытия файла!" << endl;
            }
            break;
        }
        case 3: {
            if (books.empty()) {
                cout << "Список книг пуст!" << endl;
            }
            else {
                sort(books.begin(), books.end(), sortingPoPrice);
                cout << "Книги отсортированы по цене (от min до max):" << endl;
                for (int i = 0; i < books.size(); i++) {
                    cout << i + 1 << ". " << books[i].name << "\t \t " << books[i].author << "\t \t " << books[i].publish << "\t " << books[i].year << "\t " << books[i].price << endl;
                }
            }
            break;
        }
        case 4: {
            string fileLocation2;
            cout << "Введите путь к файлу с книгами: ";
            cin >> fileLocation2;

            ifstream file2(fileLocation2);
            if (file2.is_open()) {
                book tempBook;
                while (getline(file2, tempBook.name, ';') && getline(file2, tempBook.author, ';') && getline(file2, tempBook.publish, ';') && getline(file2, tempBook.year, ';') && file2 >> tempBook.price) {
                    file2.ignore();
                    books.push_back(tempBook);
                }
                file2.close();

                ofstream out(fileLocation);
                if (out.is_open()) {
                    for (int i = 0; i < books.size(); i++) {
                        out << books[i].name << ";" << books[i].author << ";" << books[i].publish << ";" << books[i].year << ";" << books[i].price << endl;
                    }
                    out.close();
                    cout << "Книги из файла добавлены!" << endl;
                }
                else {
                    cout << "Ошибка открытия файла!" << endl;
                }
            }
            else {
                cout << "Ошибка открытия файла!" << endl;
            }
            break;
        }
        case 5: { 
            if (books.empty()) {
                cout << "Список книг пуст!" << endl;
            }
            else {
                cout << "Введите номер книги для удаления: ";
                int bookNumber;
                cin >> bookNumber;
                bookNumber = intCheck(bookNumber, books.size()); 

                if (bookNumber >= 1 && bookNumber <= books.size()) {
                    books.erase(books.begin() + bookNumber - 1); 

                    ofstream out(fileLocation);
                    if (out.is_open()) {
                        for (int i = 0; i < books.size(); i++) {
                            out << books[i].name << ";" << books[i].author << ";" << books[i].publish << ";" << books[i].year << ";" << books[i].price << endl;
                        }
                        out.close();
                        cout << "Книга удалена!" << endl;
                    }
                    else {
                        cout << "Ошибка открытия файла!" << endl;
                    }
                }
                else {
                    cout << "Неверный номер книги!" << endl;
                }
            }
            break;
        }
        case 6: {
            cout << "Выход из программы." << endl;
            break;
        }
        default: {
            cout << "Неверный выбор!" << endl;
            break;
        }
        }

    } while (choice != 6);

    return 0;
}