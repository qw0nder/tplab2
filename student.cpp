#include "STUDENT.h"
#include <stdexcept>
#include <iomanip>
#include <limits>

// Конструктор без параметров
STUDENT::STUDENT() : fullName("Unknown"), groupNumber("Unknown"),
grades(nullptr), gradesCount(0), gradesCapacity(0) {
    std::cout << "STUDENT: Default constructor called for " << fullName << std::endl;
}

// Конструктор с параметрами
STUDENT::STUDENT(const std::string& name, const std::string& group, int* gradesArray, int count)
    : fullName(name), groupNumber(group), grades(nullptr), gradesCount(0), gradesCapacity(0) {

    std::cout << "STUDENT: Parameterized constructor called for " << fullName << std::endl;

    if (count > 0 && gradesArray != nullptr) {
        setGrades(gradesArray, count);
    }
}

// Конструктор копирования
STUDENT::STUDENT(const STUDENT& other)
    : fullName(other.fullName), groupNumber(other.groupNumber),
    grades(nullptr), gradesCount(0), gradesCapacity(0) {

    std::cout << "STUDENT: Copy constructor called for " << fullName << std::endl;
    copyGrades(other);
}

// Деструктор
STUDENT::~STUDENT() {
    std::cout << "STUDENT: Destructor called for " << fullName << std::endl;
    clearGrades();
}

// Оператор присваивания
STUDENT& STUDENT::operator=(const STUDENT& other) {
    std::cout << "STUDENT: Assignment operator called for " << fullName << std::endl;

    if (this != &other) {
        fullName = other.fullName;
        groupNumber = other.groupNumber;
        clearGrades();
        copyGrades(other);
    }
    return *this;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const STUDENT& student) {
    os << "Student: " << student.fullName << std::endl;
    os << "Group: " << student.groupNumber << std::endl;
    os << "Grades (" << student.gradesCount << "): ";
    if (student.grades != nullptr && student.gradesCount > 0) {
        for (int i = 0; i < student.gradesCount; ++i) {
            os << student.grades[i];
            if (i < student.gradesCount - 1) os << ", ";
        }
        os << std::endl;
        os << "Average grade: " << std::fixed << std::setprecision(2) << student.getAverageGrade();
    }
    else {
        os << "No grades";
    }
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, STUDENT& student) {
    std::cout << "Enter student's full name (surname and initials): ";
    std::getline(is, student.fullName);

    std::cout << "Enter group number: ";
    std::getline(is, student.groupNumber);

    student.clearGrades();

    // Спрашиваем, хочет ли пользователь ввести оценки сейчас
    char choice;
    std::cout << "Do you want to enter grades now? (y/n): ";
    is >> choice;
    is.ignore();

    if (choice == 'y' || choice == 'Y') {
        student.addMultipleGrades();
    }

    return is;
}

// Set методы
void STUDENT::setFullName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
    fullName = name;
}

void STUDENT::setGroupNumber(const std::string& group) {
    if (group.empty()) {
        throw std::invalid_argument("Group number cannot be empty");
    }
    groupNumber = group;
}

void STUDENT::setGrades(int* gradesArray, int count) {
    clearGrades();
    if (count > 0 && gradesArray != nullptr) {
        gradesCapacity = (count < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : count * 2;
        grades = new int[gradesCapacity];
        gradesCount = 0;

        for (int i = 0; i < count; ++i) {
            addGrade(gradesArray[i]);
        }
    }
}

// Get методы
std::string STUDENT::getFullName() const {
    return fullName;
}

std::string STUDENT::getGroupNumber() const {
    return groupNumber;
}

int* STUDENT::getGrades() const {
    return grades;
}

int STUDENT::getGradesCount() const {
    return gradesCount;
}

// Вычисление среднего балла
double STUDENT::getAverageGrade() const {
    if (grades == nullptr || gradesCount == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < gradesCount; ++i) {
        sum += grades[i];
    }
    return sum / gradesCount;
}

// Проверка, что только оценки 4 и 5
bool STUDENT::hasOnlyGoodGrades() const {
    if (grades == nullptr || gradesCount == 0) {
        return false;
    }

    for (int i = 0; i < gradesCount; ++i) {
        if (grades[i] < 4) {
            return false;
        }
    }
    return true;
}

// Добавление одной оценки
void STUDENT::addGrade(int grade) {
    if (grade < 2 || grade > 5) {
        throw std::invalid_argument("Grade must be between 2 and 5");
    }

    if (gradesCount >= gradesCapacity) {
        resizeGrades();
    }

    grades[gradesCount++] = grade;
    std::cout << "Grade " << grade << " added to student " << fullName << std::endl;
}

// Добавление нескольких оценок
void STUDENT::addMultipleGrades() {
    std::cout << "Adding grades for student: " << fullName << std::endl;
    std::cout << "Current grades: ";
    displayGrades();

    int count;
    std::cout << "How many grades do you want to add? ";
    std::cin >> count;

    if (count <= 0) {
        std::cout << "No grades to add." << std::endl;
        return;
    }

    std::cout << "Enter " << count << " grades (2-5): ";
    for (int i = 0; i < count; ++i) {
        int grade;
        std::cin >> grade;
        try {
            addGrade(grade);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Invalid grade: " << e.what() << ". Please enter a valid grade: ";
            --i; // Повторяем ввод для этого индекса
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cin.ignore();
}

// Увеличение размера массива оценок
void STUDENT::resizeGrades() {
    if (gradesCapacity == 0) {
        gradesCapacity = DEFAULT_CAPACITY;
    }
    else {
        gradesCapacity *= 2;
    }

    int* newGrades = new int[gradesCapacity];
    for (int i = 0; i < gradesCount; ++i) {
        newGrades[i] = grades[i];
    }

    delete[] grades;
    grades = newGrades;
}

// Очистка массива оценок
void STUDENT::clearGrades() {
    if (grades != nullptr) {
        delete[] grades;
        grades = nullptr;
    }
    gradesCount = 0;
    gradesCapacity = 0;
}

// Копирование оценок
void STUDENT::copyGrades(const STUDENT& other) {
    if (other.grades != nullptr && other.gradesCount > 0) {
        gradesCapacity = other.gradesCapacity;
        grades = new int[gradesCapacity];
        gradesCount = other.gradesCount;
        for (int i = 0; i < gradesCount; ++i) {
            grades[i] = other.grades[i];
        }
    }
}

// Вывод оценок
void STUDENT::displayGrades() const {
    if (grades == nullptr || gradesCount == 0) {
        std::cout << "No grades" << std::endl;
        return;
    }

    for (int i = 0; i < gradesCount; ++i) {
        std::cout << grades[i];
        if (i < gradesCount - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}