#include "StudentGrades.h"

int main() {
    StudentContainer container;

    container.addStudent(std::make_shared<StudentWithGrades>("Alice", 90, "SP-1"));
    container.addStudent(std::make_shared<StudentWithGrades>("Bob", 85, "SSB-1"));

    container.writeToFile("students.csv");

    StudentContainer newContainer;
    newContainer.readFromFile("students.csv");
    newContainer.displayStudents();

    return 0;
}
