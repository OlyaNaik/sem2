#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

/// <summary>
/// Класс, представляющий информацию о студенте.
/// </summary>
class Student {
public:
    /// <summary>
    /// ФИО студента.
    /// </summary>
    string fullName;

    /// <summary>
    /// Номер группы студента.
    /// </summary>
    string groupNumber;

    /// <summary>
    /// Список оценок студента.
    /// </summary>
    vector<int> grades;

    /// <summary>
    /// Стипендия студента.
    /// </summary>
    double scholarship = 0.0;

    /// <summary>
    /// Дополнительная информация о студенте.
    /// </summary>
    string additionalInfo;
};

/// <summary>
/// Класс, управляющий списком студентов и предоставляющий функции для работы с ними.
/// </summary>
class StudentStream {
private:
    /// <summary>
    /// Вектор для хранения списка студентов.
    /// </summary>
    vector<Student> students;

public:
    /// <summary>
    /// Добавляет студента в список, вводя данные с клавиатуры.
    /// </summary>
    void addStudentInteractively();

    /// <summary>
    /// Удаляет студента по указанному ФИО.
    /// </summary>
    /// <param name="fullName">ФИО студента, которого нужно удалить.</param>
    void removeStudent(const string& fullName);

    /// <summary>
    /// Отображает всех студентов, находящихся в списке.
    /// </summary>
    void displayAllStudents() const;

    /// <summary>
    /// Сохраняет всех студентов в файл.
    /// </summary>
    /// <param name="filename">Имя файла для сохранения данных.</param>
    void saveToFile(const string& filename) const;

    /// <summary>
    /// Загружает студентов из файла.
    /// </summary>
    /// <param name="filename">Имя файла для загрузки данных.</param>
    void loadFromFile(const string& filename);

    /// <summary>
    /// Редактирует информацию о студенте по указанному ФИО.
    /// </summary>
    /// <param name="fullName">ФИО студента, да��ные которого нужно изменить.</param>
    void editStudent(const string& fullName);

    /// <summary>
    /// Отображает процент стипендий, распределённых по каждой группе.
    /// </summary>
    void displayGroupPercentageScholarship() const;

    /// <summary>
    /// Группирует студентов по номеру группы и отображает их.
    /// </summary>
    void groupStudentsByGroup() const;
};

/// <summary>
/// Добавляет студента в список, вводя данные с клавиатуры.
/// </summary>
void StudentStream::addStudentInteractively() {
    Student student;
    cout << "Введите данные о студенте:\n";

    cout << "ФИО: ";
    cin.ignore();
    getline(cin, student.fullName);

    cout << "Номер группы: ";
    getline(cin, student.groupNumber);

    cout << "Введите 5 оценок (через пробел): ";
    student.grades.clear();
    for (int i = 0; i < 5; ++i) {
        int grade;
        cin >> grade;
        student.grades.push_back(grade);
    }

    cout << "Введите размер стипендии: ";
    cin >> student.scholarship;

    cout << "Дополнительная информация: ";
    cin.ignore();
    getline(cin, student.additionalInfo);

    students.push_back(student);
    cout << "Студент добавлен.\n";
}

/// <summary>
/// Удаляет студента из списка по указанному ФИО.
/// </summary>
/// <param name="fullName">ФИО студента, которого нужно удалить.</param>
void StudentStream::removeStudent(const string& fullName) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].fullName == fullName) {
            students.erase(students.begin() + i);
            cout << "Студент удален.\n";
            return;
        }
    }
    cout << "Студент не найден.\n";
}

/// <summary>
/// Отображает информацию обо всех студентах.
/// </summary>
void StudentStream::displayAllStudents() const {
    if (students.empty()) {
        cout << "Список студентов пуст.\n";
        return;
    }

    size_t maxFullNameWidth = 5;
    for (const auto& student : students) {
        maxFullNameWidth = max(maxFullNameWidth, min(student.fullName.length(), size_t(44)));
    }

    const size_t groupColumnWidth = 10;
    const size_t gradesColumnWidth = 15;
    const size_t scholarshipColumnWidth = 10;
    const size_t infoColumnWidth = 25;

    const size_t totalWidth = maxFullNameWidth + groupColumnWidth +
        gradesColumnWidth + scholarshipColumnWidth +
        infoColumnWidth + 11;

    auto printTableBorder = [totalWidth]() { cout << "+" << string(totalWidth + 3, '-') << "+" << endl; };

    printTableBorder();
    cout << "| " << left << setw(maxFullNameWidth) << "ФИО"
        << " | " << setw(groupColumnWidth) << "Группа"
        << " | " << setw(gradesColumnWidth) << "Оценки"
        << " | " << setw(scholarshipColumnWidth) << "Стипендия"
        << " | " << setw(infoColumnWidth) << "Доп. информация"
        << " |\n";
    printTableBorder();

    for (const auto& student : students) {
        cout << "| " << left << setw(maxFullNameWidth) << student.fullName.substr(0, 44)
            << " | " << setw(groupColumnWidth) << student.groupNumber
            << " | ";

        string gradesStr;
        for (int grade : student.grades) {
            gradesStr += to_string(grade) + " ";
        }
        cout << left << setw(gradesColumnWidth) << gradesStr.substr(0, gradesColumnWidth - 1);

        cout << " | " << right << setw(scholarshipColumnWidth) << fixed << setprecision(2) << student.scholarship
            << " | " << left << setw(infoColumnWidth) << student.additionalInfo.substr(0, infoColumnWidth)
            << " |\n";
    }
    printTableBorder();
}

/// <summary>
/// Сохраняет список студентов в указанный файл.
/// </summary>
/// <param name="filename">Имя файла для сохранения данных.</param>
void StudentStream::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи.\n";
        return;
    }

    for (const auto& student : students) {
        outFile << student.fullName << "\n"
            << student.groupNumber << "\n"
            << student.grades.size() << "\n";
        for (int grade : student.grades) {
            outFile << grade << " ";
        }
        outFile << "\n" << student.scholarship << "\n"
            << student.additionalInfo << "\n";
    }
    cout << "Данные сохранены в файл.\n";
}

/// <summary>
/// Загружает список студентов из указанного файла.
/// </summary>
/// <param name="filename">Имя файла для загрузки данных.</param>
void StudentStream::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Не удалось открыть файл для чтения.\n";
        return;
    }

    students.clear();

    string fullName, groupNumber, additionalInfo;
    int gradesCount;
    double scholarship;
    while (getline(inFile, fullName)) {
        getline(inFile, groupNumber);
        inFile >> gradesCount;

        vector<int> grades(gradesCount);
        for (int i = 0; i < gradesCount; ++i) {
            inFile >> grades[i];
        }

        inFile >> scholarship;
        inFile.ignore();
        getline(inFile, additionalInfo);

        students.push_back({ fullName, groupNumber, grades, scholarship, additionalInfo });
    }
    cout << "Данные загружены из файла.\n";
}

/// <summary>
/// Редактирует данные студента по указанному ФИО.
/// </summary>
/// <param name="fullName">ФИО студента, чьи данные нужно изменить.</param>
void StudentStream::editStudent(const string& fullName) {
    for (auto& student : students) {
        if (student.fullName == fullName) {
            cout << "Введите новые данные для студента:\n";

            /// <summary>
            /// Ввод новой информации: ФИО, номер группы, оценки, стипендию и дополнительную информацию.
            /// </summary>
            cout << "ФИО: ";
            cin.ignore();
            getline(cin, student.fullName);

            cout << "Группа: ";
            getline(cin, student.groupNumber);

            cout << "Оценки (5 чисел через пробел): ";
            student.grades.clear();
            for (int i = 0; i < 5; ++i) {
                int grade;
                cin >> grade;
                student.grades.push_back(grade);
            }

            cout << "Стипендия: ";
            cin >> student.scholarship;

            cout << "Доп. информация: ";
            cin.ignore();
            getline(cin, student.additionalInfo);

            cout << "Данные обновле��ы.\n";
            return;
        }
    }
    cout << "Студент не найден.\n";
}

/// <summary>
/// Расчитывает процент стипендии для каждой группы студентов и выводит его.
/// </summary>
void StudentStream::displayGroupPercentageScholarship() const {
    /// <summary>
    /// Карта для хранения общей суммы стипендий по каждой группе.
    /// </summary>
    map<string, double> groupScholarshipSum;

    /// <summary>
    /// Общая сумма стипендий для всех студентов.
    /// </summary>
    double totalScholarship = 0;

    for (const auto& student : students) {
        groupScholarshipSum[student.groupNumber] += student.scholarship;
        totalScholarship += student.scholarship;
    }

    /// <summary>
    /// Вывод процента стипендий для каждой группы.
    /// </summary>
    cout << fixed << setprecision(2);
    for (const auto& group : groupScholarshipSum) {
        double percentage = (group.second / totalScholarship) * 100;
        cout << "Группа: " << group.first << " - Процент стипендии: " << percentage << "%\n";
    }
}

/// <summary>
/// Группирует студентов по их номерам групп и отображает их списком.
/// </summary>
void StudentStream::groupStudentsByGroup() const {
    /// <summary>
    /// Проверка наличия студентов в списке.
    /// Если список пуст, выводится сообщение.
    /// </summary>
    if (students.empty()) {
        cout << "Список студентов пуст.\n";
        return;
    }

    /// <summary>
    /// Карта для группировки студентов, где ключ — номер группы, а значение — вектор студентов этой группы.
    /// </summary>
    map<string, vector<Student>> groups;

    for (const auto& student : students) {
        groups[student.groupNumber].push_back(student);
    }

    const size_t fullNameWidth = 25;
    const size_t gradesWidth = 15;
    const size_t scholarshipWidth = 10;
    const size_t infoWidth = 20;
    const size_t totalWidth = fullNameWidth + gradesWidth + scholarshipWidth + infoWidth + 12;

    /// <summary>
    /// Вспомогательная функция для вывода горизонтальной линии для таблиц.
    /// </summary>
    auto printHorizontalLine = [totalWidth]() {
        cout << "+" << string(totalWidth - 1, '-') << "+" << endl;
        };

    for (const auto& group : groups) {
        string groupNumber = group.first;

        cout << "Группа: " << groupNumber << "\n";
        printHorizontalLine();
        cout << "| " << setw(fullNameWidth) << left << "ФИО"
            << " | " << setw(gradesWidth) << "Оценки"
            << " | " << setw(scholarshipWidth) << "Стипендия"
            << " | " << setw(infoWidth) << left << "Доп. информация"
            << " |\n";
        printHorizontalLine();

        for (const auto& student : group.second) {
            /// <summary>
            /// Форматирование оценки и дополнительной информации с учетом длины таблицы.
            /// </summary>
            string gradesStr;
            for (int grade : student.grades) {
                gradesStr += to_string(grade) + " ";
            }
            cout << "| " << setw(fullNameWidth) << left << student.fullName.substr(0, fullNameWidth)
                << " | " << setw(gradesWidth) << gradesStr.substr(0, gradesWidth - 1)
                << " | " << setw(scholarshipWidth) << fixed << setprecision(2) << student.scholarship
                << " | " << setw(infoWidth) << left << student.additionalInfo.substr(0, infoWidth)
                << " |\n";
        }
        printHorizontalLine();
        cout << "\n";
    }
}