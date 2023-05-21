#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class GradeBook {
public: 
  static const int students = 10;
  static const int tests = 3;
private:
  string courseName;
  int grades[students][tests];
public:
  GradeBook(string, const int[][tests]);

  void setCourseName(string);
  string getCourseName();
  void displayMessage();
  void processgrades();
  int getMinimum();
  int getMaximum();
  double getAverage(const int[], const int);
  void outputBarChart();
  void outputGrades();
};

GradeBook::GradeBook(string name, const int gradesArray[][tests]) {
  setCourseName(name);
  for (int grade = 0; grade < students; ++grade)
    for (int test = 0; test < tests; ++test)
      grades[grade][test] = gradesArray[grade][test];
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
  cout << "\nLowest grade is " << getMinimum() << "\nHighest grade is " << getMaximum() << endl;
  outputBarChart();
}

int GradeBook::getMinimum() {
  int lowGrade = 100;
  for (int grade = 0; grade < students; ++grade) {
    for (int test = 0; test < tests; ++test)
      if (grades[grade][test] < lowGrade) 
        lowGrade = grades[grade][test];
  }
  return lowGrade;
}

int GradeBook::getMaximum() {
  int highGrade = 100;
  for (int grade = 0; grade < students; ++grade) {
    for (int test = 0; test < tests; ++test)
      if (grades[grade][test] > highGrade) 
        highGrade = grades[grade][test];
  }
  return highGrade;
}

double GradeBook::getAverage(const int setOfGrades[], const int grades) {
  int total = 0;
  for (int grade = 0; grade < tests; ++grade) {
    total += setOfGrades[grade];
  }
  return static_cast<double>(total) / grades;
}

void GradeBook::outputBarChart() {
  cout << "\nGrade distribution: " << endl;
  const int frequencySize = 11;
  int frequency[frequencySize] = {};
  for (int i = 0; i < students; ++i) {
    for (int test = 0; test < tests; ++test)
     frequency[grades[i][test] / students]++;
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

void GradeBook::outputGrades()
{
  cout<<"\nThe grades are:\n\n";
  cout<<"            ";
  for ( int test = 0; test< tests; test++)
    cout<<"Test "<< test + 1 <<"  ";
    
  cout<<"Average"<< endl;
  for(int student = 0; student < students; student++)
  {
    cout<<"Student "<< setw(2) <<student + 1;
    for(int test = 0; test < tests; test++)
      cout << setw(8) << grades[student][test];
    double average = getAverage(grades[student], tests);
    cout << setw(9) << setprecision(2) << fixed << average << endl;
  }
}

int main() {
  int gradesArray[ GradeBook::students ][ GradeBook::tests ] =
    {{87,96,70},
    { 68,87,90},
    { 94,100,90},
    { 100,81,82},
    {83,65,85},
    { 78,87,65},
    {85,75,83},
    { 91,94,100},
    {76,72,84},
    { 87,93,73}};
  GradeBook myGradeBook("CS203 Introduction to C++ Programming", gradesArray);
  myGradeBook.displayMessage();
  myGradeBook.processgrades();
  return 0;
}