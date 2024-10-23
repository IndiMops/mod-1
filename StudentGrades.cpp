#include "StudentGrades.h"

// Реалізація методу fromCSV
std::shared_ptr<StudentWithGrades> StudentWithGrades::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string name, className, gradeStr;
    int grade;

    std::getline(ss, name, ',');
    std::getline(ss, gradeStr, ',');
    std::getline(ss, className, ',');

    grade = std::stoi(gradeStr);
    return std::make_shared<StudentWithGrades>(name, grade, className);
}

void StudentContainer::addStudent(const std::shared_ptr<Student>& student) {
    if (currentIndex < students.size()) {
        students[currentIndex] = student;
        ++currentIndex;
    } else {
        std::cout << "Container is full!" << std::endl;
    }
}

void StudentContainer::readFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error opening file for reading" << std::endl;
        return;
    }

    std::string line;

    // Пропустити перший рядок із заголовком
    if (std::getline(infile, line)) {
        // Це заголовок, просто пропускаємо його
    }

    // Зчитуємо дані
    while (std::getline(infile, line)) {
        addStudent(StudentWithGrades::fromCSV(line));
    }
}

void StudentContainer::writeToFile(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error opening file for writing" << std::endl;
        return;
    }

    // Записати заголовок
    outfile << "Name,Grade,ClassName" << std::endl;

    // Записати дані студентів
    for (int i = 0; i < currentIndex; ++i) {
        outfile << students[i]->getDataForFile() << std::endl;
    }
}

void StudentContainer::displayStudents() const {
    for (int i = 0; i < currentIndex; ++i) {
        students[i]->display();
    }
}
