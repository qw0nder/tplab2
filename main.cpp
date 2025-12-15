#include "StudentDatabase.h"
#include <iostream>
#include <limits>
#include <cstdlib>

void showMenu() {
    std::cout << "\n=== STUDENT DATABASE MANAGEMENT SYSTEM ===" << std::endl;
    std::cout << "1. Add new student" << std::endl;
    std::cout << "2. Add student at specific position" << std::endl;
    std::cout << "3. Remove student" << std::endl;
    std::cout << "4. Edit student (full edit)" << std::endl;
    std::cout << "5. Add grades to student" << std::endl;
    std::cout << "6. Display all students" << std::endl;
    std::cout << "7. Display students with grades 4 and 5" << std::endl;
    std::cout << "8. Sort students by average grade" << std::endl;
    std::cout << "9. Save database to file" << std::endl;
    std::cout << "10. Load database from file" << std::endl;
    std::cout << "11. Show number of students" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

void addStudent(StudentDatabase& db) {
    STUDENT student;
    try {
        std::cin >> student;
        db.addStudent(student);
        std::cout << "Student added successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error adding student: " << e.what() << std::endl;
    }
}

void addStudentAtPosition(StudentDatabase& db) {
    if (db.getSize() == 0) {
        std::cout << "Database is empty. Adding as first student." << std::endl;
        addStudent(db);
        return;
    }

    int position;
    std::cout << "Enter position (0-" << db.getSize() << "): ";
    std::cin >> position;
    std::cin.ignore();

    STUDENT student;
    try {
        std::cin >> student;
        db.addStudentAtPosition(student, position);
        std::cout << "Student added at position " << position << " successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error adding student: " << e.what() << std::endl;
    }
}

void removeStudent(StudentDatabase& db) {
    if (db.getSize() == 0) {
        std::cout << "Database is empty!" << std::endl;
        return;
    }

    int index;
    std::cout << "Enter student number to remove (1-" << db.getSize() << "): ";
    std::cin >> index;
    std::cin.ignore();

    try {
        db.removeStudent(index - 1);
    }
    catch (const std::exception& e) {
        std::cout << "Error removing student: " << e.what() << std::endl;
    }
}

void editStudent(StudentDatabase& db) {
    if (db.getSize() == 0) {
        std::cout << "Database is empty!" << std::endl;
        return;
    }

    int index;
    std::cout << "Enter student number to edit (1-" << db.getSize() << "): ";
    std::cin >> index;
    std::cin.ignore();

    try {
        db.editStudent(index - 1);
    }
    catch (const std::exception& e) {
        std::cout << "Error editing student: " << e.what() << std::endl;
    }
}

void addGradesToStudent(StudentDatabase& db) {
    if (db.getSize() == 0) {
        std::cout << "Database is empty!" << std::endl;
        return;
    }

    int index;
    std::cout << "Enter student number to add grades to (1-" << db.getSize() << "): ";
    std::cin >> index;
    std::cin.ignore();

    try {
        db.addGradesToStudent(index - 1);
    }
    catch (const std::exception& e) {
        std::cout << "Error adding grades: " << e.what() << std::endl;
    }
}

void saveToFile(StudentDatabase& db) {
    std::string filename;
    std::cout << "Enter filename to save: ";
    std::getline(std::cin, filename);

    try {
        db.saveToFile(filename);
    }
    catch (const std::exception& e) {
        std::cout << "Error saving to file: " << e.what() << std::endl;
    }
}

void loadFromFile(StudentDatabase& db) {
    std::string filename;
    std::cout << "Enter filename to load: ";
    std::getline(std::cin, filename);

    try {
        db.loadFromFile(filename);
    }
    catch (const std::exception& e) {
        std::cout << "Error loading from file: " << e.what() << std::endl;
    }
}

int main() {
    StudentDatabase db;
    int choice;

    // Пример создания нескольких студентов для тестирования
    int grades1[] = { 5, 5, 4, 5 };
    int grades2[] = { 3, 4, 3, 5 };
    int grades3[] = { 4, 4, 4, 4, 5 };

    try {
        STUDENT s1("Ivanov I.I.", "CS-101", grades1, 4);
        STUDENT s2("Petrov P.P.", "CS-102", grades2, 4);
        STUDENT s3("Sidorov S.S.", "CS-103", grades3, 5);

        db.addStudent(s1);
        db.addStudent(s2);
        db.addStudent(s3);
    }
    catch (const std::exception& e) {
        // Игнорируем ошибки в демонстрационных данных
    }

    std::cout << "Welcome to Student Database Management System!" << std::endl;
    std::cout << "Loaded " << db.getSize() << " demo students." << std::endl;

    do {
        try {
            showMenu();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1:
                addStudent(db);
                break;
            case 2:
                addStudentAtPosition(db);
                break;
            case 3:
                removeStudent(db);
                break;
            case 4:
                editStudent(db);
                break;
            case 5:
                addGradesToStudent(db);
                break;
            case 6:
                db.displayAll();
                break;
            case 7:
                db.displayExcellentStudents();
                break;
            case 8:
                db.sortByAverageGrade();
                db.displayAll();
                break;
            case 9:
                saveToFile(db);
                break;
            case 10:
                loadFromFile(db);
                break;
            case 11:
                std::cout << "Number of students: " << db.getSize() << std::endl;
                break;
            case 0:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option! Please try again." << std::endl;
                break;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);

    return 0;
}