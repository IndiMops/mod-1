#include "StudentGrades.h"

int main() {
    StudentContainer container;

    container.addStudent(std::make_shared<StudentWithGrades>("Alice", 90, "SP-1"));
    container.addStudent(std::make_shared<StudentWithGrades>("Bob", 85, "SSB-1"));
    container.addStudent(std::make_shared<StudentWithAbsences>("Charlie"));

    container.writeToFile("students.csv");

    StudentContainer newContainer;
    newContainer.readFromFile("students.csv");
    newContainer.displayStudents();

    newContainer.updateAbsences("Charlie", 3, 2);
    newContainer.displayStudents();

    return 0;
}