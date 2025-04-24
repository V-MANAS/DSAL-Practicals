#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

enum PatientPriority {
    SERIOUS, NON_SERIOUS, GENERAL_CHECKUP
};

struct Patient {
    string name;
    PatientPriority priority;
};

struct ComparePatients {
    bool operator()(const Patient& p1, const Patient& p2) {
        return p1.priority < p2.priority;
    }
};

void displayPatient(const Patient& patient) {
    cout << "Name: " << patient.name << ", Priority: ";
    switch (patient.priority) {
        case SERIOUS: 
            cout << "Serious (Top Priority)" << endl;
            break;
        case NON_SERIOUS: 
            cout << "Non-Serious (Medium Priority)" << endl;
            break;
        case GENERAL_CHECKUP: 
            cout << "General Checkup (Least Priority)" << endl;
            break;
    }
}

int main() {
    priority_queue<Patient, vector<Patient>, ComparePatients> patientQueue;
    
    while (true) {
        cout << "<------------------------------------------->" << endl;
        cout << "Hospital Patient Queue Management System" << endl;
        cout << "1. Add Serious Patient" << endl;
        cout << "2. Add Non-Serious Patient" << endl;
        cout << "3. Add General Checkup Patient" << endl;
        cout << "4. Treat Next Patient" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Patient patient;
                patient.priority = SERIOUS;
                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, patient.name);
                patientQueue.push(patient);
                break;
            }
            case 2: {
                Patient patient;
                patient.priority = NON_SERIOUS;
                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, patient.name);
                patientQueue.push(patient);
                break;
            }
            case 3: {
                Patient patient;
                patient.priority = GENERAL_CHECKUP;
                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, patient.name);
                patientQueue.push(patient);
                break;
            }
            case 4:
                if (!patientQueue.empty()) {
                    Patient nextPatient = patientQueue.top();
                    patientQueue.pop();
                    displayPatient(nextPatient);
                } else {
                    cout << "No patients in the queue." << endl;
                }
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
