#ifndef STUDENTGRADES_H
#define STUDENTGRADES_H

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// Abstract base class for a student
class Student {
public:
    virtual ~Student() = default;
    virtual void display() const = 0; // Pure virtual function to display student information
    virtual std::string getDataForFile() const = 0; // Pure virtual function to get student data for file
};

// Concrete class for a student with grades
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

    static std::shared_ptr<StudentWithGrades> fromCSV(const std::string& csvLine); // Static function to create StudentWithGrades object from CSV line
};

// Concrete class for a student with attendance
class StudentWithAttendance : public Student {
private:
    std::string name;
    int grade;
    std::string className;
    int missedClasses;

public:
    StudentWithAttendance(const std::string& name, int grade, const std::string& className, int missedClasses)
        : name(name), grade(grade), className(className), missedClasses(missedClasses) {}
    
    void display() const override {
        std::cout << "Student: " << name << ", Grade: " << grade << ", Class: " << className << ", Missed Classes: " << missedClasses << std::endl;
    }
    
    std::string getDataForFile() const override {
        return name + "," + std::to_string(grade) + "," + className + "," + std::to_string(missedClasses);
    }

    static std::shared_ptr<StudentWithAttendance> fromCSV(const std::string& csvLine); // Static function to create StudentWithAttendance object from CSV line
};


class StudentContainer {
private:
    std::array<std::shared_ptr<Student>, 10> students; // Array to store shared pointers to Student objects
    int currentIndex = 0; // Index to keep track of the current position in the array

public:
    void addStudent(const std::shared_ptr<Student>& student); // Function to add a student to the container
    void readFromFile(const std::string& filename); // Function to read student data from a file
    void writeToFile(const std::string& filename); // Function to write student data to a file
    void displayStudents() const; // Function to display all the students in the container
};

#endif // STUDENTGRADES_H