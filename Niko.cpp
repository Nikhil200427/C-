#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    string course;
    int marks;

    void inputData() {
        cout << "\nEnter Roll No: ";
        cin >> rollNo;
        cin.ignore(); 

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Marks: ";
        cin >> marks;
        cin.ignore();
    }

    void displayData() {
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nCourse: " << course;
        cout << "\nMarks: " << marks << endl;
    }
};

void addStudent() {
    ofstream file("students.txt", ios::app);
    Student s;
    s.inputData();
    file <<s.rollNo << "|" << s.name << "|" << s.course << "|" <<s.marks << "\n";
    file.close();
    cout << "\n Student added successfully!\n";
}

void displayAll() {
    ifstream file("students.txt");
    Student s;
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line == "") continue;

        found = true;
        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        s.rollNo = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.course = line.substr(pos2 + 1, pos3 - pos2 - 1);
        s.marks = stoi(line.substr(pos3 + 1));

        s.displayData();
    }

    if (!found) cout << "\n No records found!\n";
    file.close();
}

void searchStudent() {
    ifstream file("students.txt");
    int roll;
    cout << "\nEnter Roll No to search: ";
    cin >> roll;
    cin.ignore();

    Student s;
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line == "") continue;

        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        s.rollNo = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.course = line.substr(pos2 + 1, pos3 - pos2 - 1);
        s.marks = stoi(line.substr(pos3 + 1));

        if (s.rollNo == roll) {
            cout << "\n Record found:\n";
            s.displayData();
            found = true;
            break;
        }
    }

    if (!found) cout << "\n No record found for Roll No " << roll << endl;
    file.close();
}

void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    int roll;
    cout << "\nEnter Roll No to delete: ";
    cin >> roll;
    cin.ignore();

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line == "") continue;

        int pos = line.find('|');
        int fileRoll = stoi(line.substr(0, pos));

        if (fileRoll != roll)
            temp << line << "\n";
        else
            found = true;
    }

    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\n Record deleted successfully!\n";
    else
        cout << "\n Record not found!\n";
}

void updateStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    int roll;
    cout << "\nEnter Roll No to update: ";
    cin >> roll;
    cin.ignore();

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line == "") continue;

        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        int fileRoll = stoi(line.substr(0, pos1));

        if (fileRoll == roll) {
            Student s;
            cout << "\nEnter new details:\n";
            s.inputData();
            temp << s.rollNo << "|" << s.name << "|" << s.course << "|" << s.marks << "\n";
            found = true;
        } else {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\n Record updated successfully!\n";
    else
        cout << "\n Record not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n====== STUDENT MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "\n Exiting program...\n"; break;
            default: cout << "\n Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
