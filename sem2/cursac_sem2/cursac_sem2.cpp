#include <Windows.h>
#include "student.h"

int main() {
    // Установка кодировки консоли для корректного отображения русских символов
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "RUS");

    StudentStream stream;
    int choice;

    do {
        // Главное меню
        cout << "\nМеню:\n"
            << "1. Добавить студента\n"
            << "2. Удалить студента\n"
            << "3. Отобразить всех студентов\n"
            << "4. Редактировать данные студента\n"
            << "5. Сохранить данные в файл\n"
            << "6. Загрузить данные из файла\n"
            << "7. Показать процент стипендий по группам\n"
            << "8. Группировать студентов по группам\n"
            << "0. Выход\n"
            << "Выберите опцию: ";
        cin >> choice;

        // Обработка выбора пользователя
        switch (choice) {
        case 1: // Добавление студента
            stream.addStudentInteractively();
            break;
        case 2: { // Удаление студента
            cin.ignore();
            string fullName;
            cout << "Введите ФИО студента для удаления: ";
            getline(cin, fullName);
            stream.removeStudent(fullName);
            break;
        }
        case 3: // Отображение всех студентов
            stream.displayAllStudents();
            break;
        case 4: { // Редактирование данных студента
            cin.ignore();
            string fullName;
            cout << "Введите ФИО студента для редактирования: ";
            getline(cin, fullName);
            stream.editStudent(fullName);
            break;
        }
        case 5: { // Сохранение данных в файл
            string filename;
            cout << "Введите имя файла для сохранения: ";
            cin >> filename;
            stream.saveToFile(filename);
            break;
        }
        case 6: { // Загрузка данных из файла
            string filename;
            cout << "Введите имя файла для загрузки: ";
            cin >> filename;
            stream.loadFromFile(filename);
            break;
        }
        case 7: // Процент стипендий по группам
            stream.displayGroupPercentageScholarship();
            break;
        case 8: // Группировка студентов
            stream.groupStudentsByGroup();
            break;
        case 0: // Сообщение о выходе
            cout << "Выход.\n";
            break;
        default: // Обработка неверного выбора
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}