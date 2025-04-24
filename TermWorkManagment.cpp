#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Student {
    int rollNumber;
    string name;
    float attendance;
    float unitTest;
    float achievements;
    float mockPractical;
    float totalScore;

    Student()
        : rollNumber(0), name(""), attendance(0), unitTest(0),
          achievements(0), mockPractical(0), totalScore(0) {}

    Student(int r, string n, float att, float ut, float ach, float mp)
        : rollNumber(r), name(n), attendance(att), unitTest(ut),
          achievements(ach), mockPractical(mp) {
        totalScore = (att * 0.2) + (ut * 0.4) + (ach * 0.1) + (mp * 0.3);
    }
};

// Custom comparator for priority_queue
struct CompareStudents {
    bool operator()(const Student& s1, const Student& s2) {
        return s1.totalScore < s2.totalScore; 
    }
};

vector<Student> students;
unordered_map<int, Student> studentMap;
priority_queue<Student, vector<Student>, CompareStudents> ranking;

void addStudent() {
    int rollNumber;
    string name;
    float attendance, unitTest, achievements, mockPractical;

    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Attendance (out of 100): ";
    cin >> attendance;
    cout << "Enter Unit Test Score (out of 100): ";
    cin >> unitTest;
    cout << "Enter Achievements (out of 10): ";
    cin >> achievements;
    cout << "Enter Mock Practical Score (out of 50): ";
    cin >> mockPractical;

    Student newStudent(rollNumber, name, attendance, unitTest, achievements, mockPractical);
    students.push_back(newStudent);
    studentMap[rollNumber] = newStudent;
    ranking.push(newStudent);

    cout << "Student added successfully!\n";
}

void displayAllStudents() {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    cout << setw(10) << "RollNo" << setw(20) << "Name" 
         << setw(10) << "Attend" << setw(10) << "UnitTest" 
         << setw(10) << "Achieve" << setw(10) << "MockPr" 
         << setw(10) << "Total" << endl;
    cout << string(70, '-') << endl;

    for (const auto& student : students) {
        cout << setw(10) << student.rollNumber << setw(20) << student.name
             << setw(10) << student.attendance << setw(10) << student.unitTest
             << setw(10) << student.achievements << setw(10) << student.mockPractical
             << setw(10) << student.totalScore << endl;
    }
}

void searchStudent() {
    int rollNumber;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumber;
    cin.ignore(); // To ignore the leftover newline character

    if (studentMap.find(rollNumber) != studentMap.end()) {
        const Student& student = studentMap[rollNumber];
        cout << "Student Found:\n";
        cout << "Name: " << student.name << "\nAttendance: " << student.attendance
             << "\nUnit Test: " << student.unitTest << "\nAchievements: " << student.achievements
             << "\nMock Practical: " << student.mockPractical << "\nTotal Score: " << student.totalScore << endl;
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found.\n";
    }
}


void rankStudents() {
    if (ranking.empty()) {
        cout << "No students to rank.\n";
        return;
    }

    priority_queue<Student, vector<Student>, CompareStudents> tempRanking = ranking;
    int rank = 1;

    cout << "Top Students by Rank:\n";
    while (!tempRanking.empty() && rank <= 3) {
        const Student& top = tempRanking.top();
        cout << "Rank " << rank++ << ": " << top.name 
             << " with Total Score: " << top.totalScore << endl;
        tempRanking.pop();
    }
}

int main() {
    int choice;

    do {
        cout << "\nAutomated Term Work Assessment System\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Rank Students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: rankStudents(); break;
            case 5: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
