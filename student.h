#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class STUDENT {
private:
    std::string fullName;     // фамилия и инициалы
    std::string groupNumber;  // номер группы
    int* grades;              // массив оценок
    int gradesCount;          // текущее количество оценок
    int gradesCapacity;       // вместимость массива оценок
    static const int DEFAULT_CAPACITY = 5;

    void resizeGrades();      // увеличение размера массива оценок

public:
    // Конструкторы
    STUDENT();
    STUDENT(const std::string& name, const std::string& group, int* gradesArray, int count);
    STUDENT(const STUDENT& other);

    // Деструктор
    ~STUDENT();

    // Перегрузка операторов
    STUDENT& operator=(const STUDENT& other);
    friend std::ostream& operator<<(std::ostream& os, const STUDENT& student);
    friend std::istream& operator>>(std::istream& is, STUDENT& student);

    // Set методы
    void setFullName(const std::string& name);
    void setGroupNumber(const std::string& group);
    void setGrades(int* gradesArray, int count);

    // Get методы
    std::string getFullName() const;
    std::string getGroupNumber() const;
    int* getGrades() const;
    int getGradesCount() const;

    // Методы для работы с оценками
    double getAverageGrade() const;
    bool hasOnlyGoodGrades() const; // только оценки 4 и 5

    // Новые методы для добавления оценок
    void addGrade(int grade);
    void addMultipleGrades();

    // Методы для работы с памятью
    void clearGrades();
    void copyGrades(const STUDENT& other);

    // Вспомогательные методы
    void displayGrades() const;
};

#endif