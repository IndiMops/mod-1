#include "StudentGrades.h"

int main() {
    StudentContainer container;

    // Додавання студентів вручну
    container.addStudent(std::make_shared<StudentWithGrades>("John Doe", 85, "Math"));
    container.addStudent(std::make_shared<StudentWithAttendance>("Jane Smith", 90, "Science", 3));

    // Відображення студентів
    std::cout << "Students added manually:" << std::endl;
    container.displayStudents();

    // Запис студентів у файл
    container.writeToFile("students.csv");

    StudentContainer newContainer;
    newContainer.readFromFile("students.csv");

    // Відображення студентів, зчитаних з файлу
    std::cout << "\nStudents read from file:" << std::endl;
    newContainer.displayStudents();

    return 0;
}