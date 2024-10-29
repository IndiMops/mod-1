#include "StudentGrades.h"

// Function to create a StudentWithGrades object from a CSV line
std::shared_ptr<StudentWithGrades> StudentWithGrades::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string name, className, gradeStr;
    int grade;

    // Extract name, grade, and class name from the CSV line
    std::getline(ss, name, ',');
    std::getline(ss, gradeStr, ',');
    std::getline(ss, className, ',');

    // Convert grade from string to integer
    grade = std::stoi(gradeStr);

    // Create and return a shared pointer to a StudentWithGrades object
    return std::make_shared<StudentWithGrades>(name, grade, className);
}

// Function to create a StudentWithAttendance object from a CSV line
std::shared_ptr<StudentWithAttendance> StudentWithAttendance::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string name, className, gradeStr, missedClassesStr;
    int grade, missedClasses;

    // Extract name, grade, class name, and missed classes from the CSV line
    std::getline(ss, name, ',');
    std::getline(ss, gradeStr, ',');
    std::getline(ss, className, ',');
    std::getline(ss, missedClassesStr, ',');

    // Convert grade and missed classes from string to integer
    grade = std::stoi(gradeStr);
    missedClasses = std::stoi(missedClassesStr);

    // Create and return a shared pointer to a StudentWithAttendance object
    return std::make_shared<StudentWithAttendance>(name, grade, className, missedClasses);
}

// Function to add a student to the container
void StudentContainer::addStudent(const std::shared_ptr<Student>& student) {
    if (currentIndex < students.size()) {
        // Add the student to the container if there is space
        students[currentIndex] = student;
        ++currentIndex;
    } else {
        // Print an error message if the container is full
        std::cout << "Container is full!" << std::endl;
    }
}

// Function to read student data from a file
void StudentContainer::readFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        // Print an error message if the file cannot be opened
        std::cerr << "Error opening file for reading" << std::endl;
        return;
    }

    std::string line;

    if (std::getline(infile, line)) {
        // Skip the first line (header) of the file
    }

    while (std::getline(infile, line)) {
        if (line.find(",") != std::string::npos) {
            // If the line contains a comma, create a StudentWithGrades object
            addStudent(StudentWithGrades::fromCSV(line));
        } else {
            // If the line does not contain a comma, create a StudentWithAttendance object
            addStudent(StudentWithAttendance::fromCSV(line));
        }
    }
}

// Function to write student data to a file
void StudentContainer::writeToFile(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        // Print an error message if the file cannot be opened
        std::cerr << "Error opening file for writing" << std::endl;
        return;
    }

    // Write the header to the file
    outfile << "Name,Grade,ClassName,MissedClasses" << std::endl;

    // Write each student's data to the file
    for (int i = 0; i < currentIndex; ++i) {
        outfile << students[i]->getDataForFile() << std::endl;
    }
}

// Function to display all students in the container
void StudentContainer::displayStudents() const {
    for (int i = 0; i < currentIndex; ++i) {
        // Call the display function for each student
        students[i]->display();
    }
}