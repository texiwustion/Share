#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class GradeBook {
public: 
  static const int students = 10;
private:
  string courseName;
  int grades[students];
public:
  GradeBook(string, const int[]);

  void setCourseName(string);
  string getCourseName();
  void displayMessage();
  void processgrades();
  int getMinimum();
  int getMaximum();
  double getAverage();
  void outputBarChart();
  void outputGrades();
};

GradeBook::GradeBook(string name, const int gradesArray[]) {
  setCourseName(name);
  for (int grade = 0; grade < students; ++grade)
    grades[grade] = gradesArray[grade];
}

void GradeBook::setCourseName(string name) {
  courseName = name;
}

string GradeBook::getCourseName() {
  return courseName;
}

void GradeBook::displayMessage() {
  cout << "Welcome to the grade book for\n" << getCourseName() << "!" << endl;
}

void GradeBook::processgrades() {
  outputGrades();
  cout << "\nClass average is " << setprecision(2) << fixed << getAverage() << "\nLowest grade is " << getMinimum() << "\nHighest grade is " << getMaximum() << endl;
  outputBarChart();
}

int GradeBook::getMinimum() {
  int lowGrade = 100;
  for (int grade = 0; grade < students; ++grade) {
    if (grades[grade] < lowGrade) 
      lowGrade = grades[grade];
  }
  return lowGrade;
}

int GradeBook::getMaximum() {
  int highGrade = 100;
  for (int grade = 0; grade < students; ++grade) {
    if (grades[grade] > highGrade) 
      highGrade = grades[grade];
  }
  return highGrade;
}

double GradeBook::getAverage() {
  int total = 0;
  for (int grade = 0; grade < students; ++grade) {
    total += grades[grade];
  }
  return static_cast<double>(total) / students;
}

void GradeBook::outputBarChart() {
  cout << "\nGrade distribution: " << endl;
  const int frequencySize = 11;
  int frequency[frequencySize] = {};
  for (int i = 0; i < students; ++i) {
    frequency[grades[i] / students]++;
  }
  for (int j = 0; j < frequencySize; ++j) {
    if (j == 0) 
      cout << "  0-9: ";
    else if (j == 10) 
      cout << "  100: ";
    else 
      cout << j * 10 << "-" << (j * 10) + 9 << ": ";
    for (int k = 0; k < frequency[j]; ++k) 
      cout << "*";
    cout << endl;
  }
}

void GradeBook::outputGrades() {
  cout << "\nThe grades are:\n\n";
  for (int student = 0; student < students; student++)
    cout << "Student " << setw(2) << student + 1 << ": " << setw(3) << grades[student] << endl;
}
int main() {
  int gradesArray[GradeBook::students] = {87, 68, 94, 100, 83, 78, 85, 91, 76, 87};
  GradeBook myGradeBook("CS203 Introduction to C++ Programming", gradesArray);
  myGradeBook.displayMessage();
  myGradeBook.processgrades();
  return 0;
}