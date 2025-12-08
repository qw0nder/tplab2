#include "StudentDatabase.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>

// Конструктор без параметров
StudentDatabase::StudentDatabase() : students(nullptr), size(0), capacity(0) {
    std::cout << "StudentDatabase: Default constructor called" << std::endl;
}

// Конструктор копирования
StudentDatabase::StudentDatabase(const StudentDatabase& other) : size(other.size), capacity(other.capacity) {
    std::cout << "StudentDatabase: Copy constructor called" << std::endl;
    students = new STUDENT * [capacity];
    for (int i = 0; i < size; ++i) {
        students[i] = new STUDENT(*other.students[i]);
    }
}

// Деструктор
StudentDatabase::~StudentDatabase() {
    std::cout << "StudentDatabase: Destructor called" << std::endl;
    clear();
}

// Оператор присваивания
StudentDatabase& StudentDatabase::operator=(const StudentDatabase& other) {
    std::cout << "StudentDatabase: Assignment operator called" << std::endl;

    if (this != &other) {
        clear();
        size = other.size;
        capacity = other.capacity;
        students = new STUDENT * [capacity];
        for (int i = 0; i < size; ++i) {
            students[i] = new STUDENT(*other.students[i]);
        }
    }
    return *this;
}

// Добавление студента в конец
void StudentDatabase::addStudent(const STUDENT& student) {
    addStudentAtPosition(student, size);
}

// Добавление студента на определенную позицию
void StudentDatabase::addStudentAtPosition(const STUDENT& student, int position) {
    if (position < 0 || position > size) {
        throw std::out_of_range("Invalid position for adding student");
    }

    if (size >= capacity) {
        resize();
    }

    // Сдвигаем элементы вправо
    for (int i = size; i > position; --i) {
        students[i] = students[i - 1];
    }

    // Добавляем нового студента
    students[position] = new STUDENT(student);
    ++size;

    std::cout << "Student added at position " << position << std::endl;
}

// Удаление студента
void StudentDatabase::removeStudent(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index: student not found");
    }

    std::cout << "Removing student: " << students[index]->getFullName() << std::endl;
    delete students[index];

    // Сдвигаем элементы влево
    for (int i = index; i < size - 1; ++i) {
        students[i] = students[i + 1];
    }

    --size;
    std::cout << "Student removed successfully" << std::endl;
}

// Редактирование студента
void StudentDatabase::editStudent(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index: student not found");
    }

    std::cout << "Editing student: " << students[index]->getFullName() << std::endl;

    STUDENT temp;
    try {
        std::cin >> temp;
        *students[index] = temp;
        std::cout << "Student edited successfully" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error editing student: " << e.what() << std::endl;
    }
}

// Добавление оценок студенту
void StudentDatabase::addGradesToStudent(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index: student not found");
    }

    try {
        students[index]->addMultipleGrades();
        std::cout << "Grades added successfully to student: "
            << students[index]->getFullName() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error adding grades: " << e.what() << std::endl;
    }
}

// Вывод всех студентов
void StudentDatabase::displayAll() const {
    if (size == 0) {
        std::cout << "Database is empty" << std::endl;
        return;
    }

    std::cout << "\n=== ALL STUDENTS ===" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "\nStudent #" << (i + 1) << ":" << std::endl;
        std::cout << *students[i] << std::endl;
        std::cout << "-------------------" << std::endl;
    }
}

// Вывод студентов с оценками 4 и 5
void StudentDatabase::displayExcellentStudents() const {
    bool found = false;

    std::cout << "\n=== STUDENTS WITH GRADES 4 AND 5 ===" << std::endl;
    for (int i = 0; i < size; ++i) {
        if (students[i]->hasOnlyGoodGrades()) {
            found = true;
            std::cout << "Name: " << students[i]->getFullName() << std::endl;
            std::cout << "Group: " << students[i]->getGroupNumber() << std::endl;
            std::cout << "Grades: ";
            students[i]->displayGrades();
            std::cout << "Average grade: " << students[i]->getAverageGrade() << std::endl;
            std::cout << "-------------------" << std::endl;
        }
    }

    if (!found) {
        std::cout << "No students with only grades 4 and 5 found." << std::endl;
    }
}

// Сортировка по возрастанию среднего балла
void StudentDatabase::sortByAverageGrade() {
    if (size <= 1) return;

    // Простая сортировка пузырьком
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (students[j]->getAverageGrade() > students[j + 1]->getAverageGrade()) {
                // Меняем местами указатели
                STUDENT* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    std::cout << "Students sorted by average grade (ascending)" << std::endl;
}

// Получение количества студентов
int StudentDatabase::getSize() const {
    return size;
}

// Сохранение в файл
void StudentDatabase::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }

    file << size << "\n";
    for (int i = 0; i < size; ++i) {
        file << students[i]->getFullName() << "\n";
        file << students[i]->getGroupNumber() << "\n";

        int gradesCount = students[i]->getGradesCount();
        int* grades = students[i]->getGrades();

        file << gradesCount << "\n";
        if (grades != nullptr && gradesCount > 0) {
            for (int j = 0; j < gradesCount; ++j) {
                file << grades[j] << " ";
            }
        }
        file << "\n";
    }

    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}

// Загрузка из файла
void StudentDatabase::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }

    clear();

    int fileSize;
    file >> fileSize;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // пропускаем всю строку

    for (int i = 0; i < fileSize; ++i) {
        std::string name, group;
        int gradesCount;

        // Читаем имя (может быть пустой строкой из-за предыдущих пробелов)
        while (std::getline(file, name) && name.empty()) {
            // Пропускаем пустые строки
        }

        std::getline(file, group);
        file >> gradesCount;

        int* grades = nullptr;
        if (gradesCount > 0) {
            grades = new int[gradesCount];
            for (int j = 0; j < gradesCount; ++j) {
                file >> grades[j];
            }
        }

        // Пропускаем все символы до конца строки
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        STUDENT student(name, group, grades, gradesCount);
        addStudent(student);

        if (grades != nullptr) {
            delete[] grades;
        }
    }

    file.close();
    std::cout << "Data loaded from " << filename << std::endl;
}

// Увеличение размера массива
void StudentDatabase::resize() {
    capacity = (capacity == 0) ? 2 : capacity * 2;
    STUDENT** newArray = new STUDENT * [capacity];

    for (int i = 0; i < size; ++i) {
        newArray[i] = students[i];
    }

    delete[] students;
    students = newArray;
}

// Очистка памяти
void StudentDatabase::clear() {
    for (int i = 0; i < size; ++i) {
        delete students[i];
    }
    delete[] students;
    students = nullptr;
    size = 0;
    capacity = 0;
}