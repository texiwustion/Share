#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Person {
    int id;
    string name;
    int iq;

    bool operator < (const Person& p) const {
        // 比较函数，根据姓名进行排序
        return name < p.name;
    }
};

void generateRandomData(int count, string fileName) {
    ofstream outFile(fileName);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> idDist(1, 1000);
    std::uniform_int_distribution<int> iqDist(60, 150);

    outFile << setw(7) << setfill(' ') << left << "Name" << '\t'
            << setw(5) << setfill(' ') << left << "ID" << '\t'
            << setw(5) << setfill(' ') << left << "IQ" << endl;
    for (int i = 0; i < count; i++) {
        Person p;
        p.id = idDist(gen);
        p.iq = iqDist(gen);

        char name[5];
        for (int j = 0; j < 4; j++) {
            name[j] = 'a' + rand() % 26;
        }
        name[4] = '\0';
        p.name = name;
        outFile << setw(7) << setfill(' ') << left << p.name << '\t'
                << setw(5) << setfill(' ') << left << p.id << '\t'
                << setw(5) << setfill(' ') << left << p.iq << endl;
    }

    outFile.close();
}

void sortData(vector<Person>& persons) {
    int option;
    cout << "use number to choose how to sort:\n1. Name\n2. ID\n3. IQ\n";
    cin >> option;

    switch (option) {
        case 1:
            sort(persons.begin(), persons.end());  // 根据姓名排序
            break;
        case 2:
            sort(persons.begin(), persons.end(), [](const Person& p1, const Person& p2) {  // 等效于 lambda表达式
                return p1.id < p2.id;
            });
            break;
        case 3:
            sort(persons.begin(), persons.end(), [](const Person& p1, const Person& p2) {  // 等效于 lambda表达式
                return p1.iq < p2.iq;
            });
            break;
        default:
            cout << "invalid option!\n";
            break;
    }
}

void outputData(vector<Person>& persons, string fileName) {
    ofstream outFile(fileName);
    if (outFile.is_open()) {
        outFile << setw(7) << setfill(' ') << left << "Name" << '\t'
                << setw(5) << setfill(' ') << left << "ID" << '\t'
                << setw(5) << setfill(' ') << left << "IQ" << endl;
        for (Person& p : persons) {
            outFile << setw(7) << setfill(' ') << left << p.name << '\t'
                    << setw(5) << setfill(' ') << left << p.id << '\t'
                    << setw(5) << setfill(' ') << left << p.iq << endl;
        }
        outFile.close();
        cout << "output succeed!\n";
    } else {
        cout << "file cannot open!\n";
    }
}

int main() 
{
  // generateRandomData(100, "data.txt");

  vector<Person> persons;
  ifstream inFile("data.txt");
  if (inFile.is_open()) {
      string line;
      getline(inFile, line); //跳过第一行
      while (getline(inFile, line)) {
          Person p;
          char buf[20];
          sscanf(line.c_str(), "%s\t%d\t%d", buf, &p.id, &p.iq);
          p.name = buf;
          persons.push_back(p);
      }
      inFile.close();
  }

  sortData(persons);
  outputData(persons, "data_out.txt");
  return 0;
}