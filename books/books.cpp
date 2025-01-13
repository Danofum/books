#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

struct book {
    string name;
    string author;
    string publish;
    string year;
    string price;
};

int intCheck(int integer, int max) {
    while (cin.fail() || integer < 0 || integer > max) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ошибка, вы должны ввести целое неотрицательное число." << endl << "Введите число ещё раз: " << endl;
        cin >> integer;
    }
    return integer;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<book> books;
    string fileLocation = "E:\\books.txt";
    ifstream in(fileLocation);
    int choice;

    if (in.is_open()) {
        book tempBook;
        while (getline(in, tempBook.name, ';') && getline(in, tempBook.author, ';') && getline(in, tempBook.publish, ';') && getline(in, tempBook.year, ';') && getline(in, tempBook.price)) {

            books.push_back(tempBook);
        }
        in.close();
    }

    do {
        cout << "Меню:" << endl;
        cout << "1. Показать книги" << endl;
        cout << "2. Добавить новую книгу" << endl;
        cout << "3. Отсортировать по цене (от min до max)" << endl;
        cout << "4. Выход" << endl;

        cin >> choice;
        choice = intCheck(choice, 4);

        switch (choice) {
        case 1: {
            cout << "Книга \t \t Автор \t \t Издательство \t Год \t Стоимость" << endl;
            for (int i = 0; i < books.size(); i++) {
                cout << books[i].name << "\t \t " << books[i].author << "\t \t " << books[i].publish << "\t " << books[i].year << "\t " << books[i].price << endl;
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
                string minPrice = books[0].price;
                string maxPrice = books[0].price;

                for (int i = 1; i < books.size(); i++) {
                    if (books[i].price < minPrice) {
                        minPrice = books[i].price;
                    }
                    if (books[i].price > maxPrice) {
                        maxPrice = books[i].price;
                    }
                }

                cout << "Минимальная цена: " << minPrice << endl;
                cout << "Максимальная цена: " << maxPrice << endl;
            }
            break;
        }
        case 4: {
            cout << "Выход из программы." << endl;
            break;
        }
        default: {
            cout << "Неверный выбор!" << endl;
            break;
        }
        }
        

    } while (choice != 4);

    return 0;
}