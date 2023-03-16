#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

class Student {
public:
  string name;
  string course;
  int id;

public:
  Student(string n, string c, int i) : name(n), course(c), id(i) {}
  string getName() { return name; }
  string getCourse() { return course; }
  int getId() { return id; }
};

class StudentList {
public:
  map<int, Student *> students;

public:
  void addStudent(Student *s) { students[s->getId()] = s; }
  void deleteStudent(int id) { students.erase(id); }
  void editStudent(int id, Student *s) { students[id] = s; }
  void showList(bool loadedFromFile = true) {
    if (!loadedFromFile) {
      cout << "\nAll Students:\n";
    } else {
      cout << "\nLoaded Students:\n";
    }
    for (auto const &[id, student] : students) {
      cout << "Name: " << student->getName()
           << " | Course: " << student->getCourse() << " | ID: " << id << endl;
    }
  }
  Student *searchByName(string name) {
    for (auto const &[id, student] : students) {
      if (student->getName() == name) {
        return student;
      }
    }
    return nullptr;
  }
  Student *searchByCourse(string course) {
    for (auto const &[id, student] : students) {
      if (student->getCourse() == course) {
        return student;
      }
    }
    return nullptr;
  }
  Student *searchById(int id) {
    auto it = students.find(id);
    if (it == students.end()) {
      return nullptr;
    }
    return it->second;
  }
  void loadFromFile() {

    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    ifstream fin(fileName);
    if (fin.is_open()) {
      string line;
      while (getline(fin, line)) {
        int id;
        string name, course;
        stringstream ss(line);
        ss >> id; // remove leading whitespace
        ss.ignore(1, ','); // ignore the comma separator
        getline(ss, name, ',');
        getline(ss, course);
        // remove newline character at the end of the strings
        if (!name.empty() && name.back() == '\r') {
          name.pop_back();
        }
        if (!course.empty() && course.back() == '\r') {
          course.pop_back();
        }
        Student *s = new Student(name, course, id);
        addStudent(s);
      }
      fin.close();
      cout << "Data loaded from file.\n";
    } else {
      cout << "File not found, starting with an empty list.\n";
    }
  }

  void saveToFile() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    ofstream fout(fileName);
    if (fout.is_open()) {
      for (auto const &[id, student] : students) {
        fout << student->getId() << "," << student->getName() << ","
             << student->getCourse() << endl;
      }
      fout.close();
      cout << "Data saved to file.\n";
    } else {
      cout << "Unable to save data to file.\n";
    }
  }
};

int main() {
  StudentList list;
  int choice;
  int Choice;
  cout << "Do you have a File to load? (1: "
          "Yes, "
          "2: No): ";
  cin >> Choice;
  if (Choice == 1) {
    list.loadFromFile();
    list.showList(true); // display the loaded students
  }
  do {
    cout << "\n\n1. Add student\n";
    cout << "2. Delete student\n";
    cout << "3. Edit student\n";
    cout << "4. Show list\n";
    cout << "5. Search by name\n";
    cout << "6. Search by course\n";
    cout << "7. Search by ID\n";
    cout << "8. Load from File\n";
    cout << "9. Save to file\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 1: {
      string name, course;
      int id;
      cout << "Enter student name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter course name: ";
      cin >> course;
      cout << "Enter ID: ";
      cin >> id;
      Student *s = new Student(name, course, id);
      list.addStudent(s);
      cout << "Student added.\n";
      break;
    }
    case 2: {
      int id;
      cout << "Enter student ID to delete: ";
      cin >> id;
      list.deleteStudent(id);
      cout << "Student deleted.\n";
      break;
    }
    case 3: {
      int id;
      cout << "Enter student ID to edit: ";
      cin >> id;
      Student *s = list.searchById(id);
      if (s != nullptr) {
        string name, course;
        cout << "Enter new name: ";
        cin >> name;
        cout << "Enter new course: ";
        cin >> course;
        s->name = name;
        s->course = course;
        list.editStudent(id, s);
        cout << "Student edited.\n";
      } else {
        cout << "Student not found.\n";
      }
      break;
    }
    case 4:
      list.showList(); // display all students
      break;
    case 5: {
      string name;
      cout << "Enter student name to search: ";
      cin.ignore();
      getline(cin, name);
      Student *s = list.searchByName(name);
      if (s != nullptr) {
        cout << "Name: " << s->getName() << " | Course: " << s->getCourse()
             << " | ID: " << s->getId() << endl;
      } else {
        cout << "Student not found.\n";
      }
      break;
    }
    case 6: {
      string course;
      cout << "Enter course to search: ";
      cin >> course;
      Student *s = list.searchByCourse(course);
      if (s != nullptr) {
        cout << "Name: " << s->getName() << " | Course: " << s->getCourse()
             << " | ID: " << s->getId() << endl;
      } else {
        cout << "Student not found.\n";
      }
      break;
    }
    case 7: {
      int id;
      cout << "Enter ID to search: ";
      cin >> id;
      Student *s = list.searchById(id);
      if (s != nullptr) {
        cout << "Name: " << s->getName() << " | Course: " << s->getCourse()
             << " | ID: " << s->getId() << endl;
      } else {
        cout << "Student not found.\n";
      }
      break;
    }
    case 8: {
      list.loadFromFile();
      break;
    }
    case 9: 
      list.saveToFile();
      break;
    case 10:
      int saveChoice;
      cout << "Do you want to save the data to file again before exiting? (1: "
              "Yes, "
              "2: No): ";
      cin >> saveChoice;
      if (saveChoice == 1) {
        list.saveToFile();
      }
      cout << "Goodbye!\n";
      exit(0);
    }
  } while (choice != 9);
  return 0;
}
