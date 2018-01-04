#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

#include "abonent.h"
#include "journal.h"

using namespace std;

int main(int argc, char *argv[])
{
  const char filename[] = "abonents.txt";

  ifstream ifs(filename);
  if(!ifs.is_open()) {
    cout << "Error: fail on open file \"" << filename << "\"" << endl;
    return 1;
  }

  MyJournal journal;
  int num = journal.loadFromFile(ifs);

  ifs.close();

  cout << "The number of readed records: " << num << endl;

  cout << journal << endl;  //a something like AllShow();

  string name, suname;
  cout << endl << "--- Search example ---" << endl;
  cout << "Enter the abonent name: ";
  getline(cin, name);
  cout << "Enter the abonent sure name: ";
  getline(cin, suname);

  size_t n = journal.findByName(name, suname);
  cout << endl;
  if(n == (size_t)-1)
    cout << "Abonent not found" << endl;
  else {
    cout << "Founded abonent is number " << n+1 << ":" << endl;
    cout << journal[n] << endl;
  }

  cout << "Press [Enter] to exit" << endl;
  cin.ignore();
  return 0;
}