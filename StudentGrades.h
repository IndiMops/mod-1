#ifndef STUDENTGRADES_H
#define STUDENTGRADES_H

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// Базовий клас для студентів
class Student {
public:
    virtual ~Student() = default;
    virtual void display() const = 0;
    virtual std::string getDataForFile() const = 0;
};

// Похідний клас для студентів з оцінками
class StudentWithGrades : public Student {
private:
    std::string name;
    int grade;
    std::string className;

public:
    StudentWithGrades(const std::string& name, int grade, const std::string& className)
        : name(name), grade(grade), className(className) {}
    
    void display() const override {
        std::cout << "Student: " << name << ", Grade: " << grade << ", Class: " << className << std::endl;
    }
    
    std::string getDataForFile() const override {
        return name + "," + std::to_string(grade) + "," + className;
    }

    static std::shared_ptr<StudentWithGrades> fromCSV(const std::string& csvLine);
};

// Контейнер для студентів
class StudentContainer {
private:
    std::array<std::shared_ptr<Student>, 10> students;
    int currentIndex = 0;

public:
    void addStudent(const std::shared_ptr<Student>& student);
    void readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename);
    void displayStudents() const;
};

#endif // STUDENTGRADES_H
