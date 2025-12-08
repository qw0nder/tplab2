#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H

#include "STUDENT.h"

class StudentDatabase {
private:
    STUDENT** students;  // массив указателей на студентов
    int size;           // текущее количество студентов
    int capacity;       // вместимость массива

    void resize();      // увеличение размера массива
    void clear();       // очистка пам€ти

public:
    //  онструкторы
    StudentDatabase();
    StudentDatabase(const StudentDatabase& other);

    // ƒеструктор
    ~StudentDatabase();

    // ќператор присваивани€
    StudentDatabase& operator=(const StudentDatabase& other);

    // ќсновные методы
    void addStudent(const STUDENT& student);
    void addStudentAtPosition(const STUDENT& student, int position);
    void removeStudent(int index);
    void editStudent(int index);

    // Ќовый метод дл€ добавлени€ оценок
    void addGradesToStudent(int index);

    // ћетоды работы с данными
    void displayAll() const;
    void displayExcellentStudents() const; // только отличники
    void sortByAverageGrade(); // сортировка по среднему баллу

    // ¬спомогательные методы
    int getSize() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif