#include "StudentGrades.h"

// Реалізація методу fromCSV для StudentWithGrades
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

// Реалізація методу fromCSV для StudentWithAbsences
std::shared_ptr<StudentWithAbsences> StudentWithAbsences::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string name, unexcusedAbsencesStr, excusedAbsencesStr;
    int unexcusedAbsences, excusedAbsences;

    std::getline(ss, name, ',');
    std::getline(ss, unexcusedAbsencesStr, ',');
    std::getline(ss, excusedAbsencesStr, ',');

    unexcusedAbsences = std::stoi(unexcusedAbsencesStr);
    excusedAbsences = std::stoi(excusedAbsencesStr);
    return std::make_shared<StudentWithAbsences>(name, unexcusedAbsences, excusedAbsences);
}

void StudentContainer::addStudent(const std::shared_ptr<Student>& student) {
    if (currentIndex < students.size()) {
        students[currentIndex] = student;
        ++currentIndex;
    } else {
        std::cout << "Container is full!" << std::endl;
    }
}

void StudentContainer::readFromFile(const std::string filename) {
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
        // Додати логіку для визначення типу студента
        if (line.find("Grade") != std::string::npos) {
            addStudent(StudentWithGrades::fromCSV(line));
        } else {
            addStudent(StudentWithAbsences::fromCSV(line));
        }
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

void StudentContainer::updateAbsences(const std::string& name, int unexcusedAbsences, int excusedAbsences) {
    for (int i = 0; i < currentIndex; ++i) {
        auto studentWithAbsences = std::dynamic_pointer_cast<StudentWithAbsences>(students[i]);
        if (studentWithAbsences && studentWithAbsences->getName() == name) {
            studentWithAbsences->setUnexcusedAbsences(unexcusedAbsences);
            studentWithAbsences->setExcusedAbsences(excusedAbsences);
            return;
        }
    }
    std::cout << "Student not found!" << std::endl;
}