#include "journal.h"

using namespace std;

size_t MyJournal::loadFromFile(ifstream &ifs) {
  size_t i = 1;
  for(; !ifs.eof(); ++i) {
    MyAbonent abonent;
    ifs >> abonent;
    push_back(abonent);
  }
  return i-1;
}

size_t MyJournal::findByName(const string &name, const string &suname,
                             size_t pos/*=0*/) {
  for(size_t i = pos; i < size(); ++i) {
    const MyAbonent &a = at(i);
    if(a.m_name == name && a.m_suname == suname)
      return i;
  }
  return (size_t)-1;
}

size_t MyJournal::FindByPhone(const std::string &phoneNumber, size_t pos/*=0*/) {
  for(size_t i = pos; i < size(); ++i) {
    const MyAbonent &a = at(i);
    if(a.m_phoneNumber == phoneNumber)
      return i;
  }
  return (size_t)-1;
}

const MyJournal& MyJournal::operator >>(std::ostream &os) const {
  for(size_t i = 0; i < size(); ++i) {
    const MyAbonent &abonent = at(i);
    cout << "_______________________________________" << endl;
    cout << "Abonent " << i+1 << endl;
    cout << abonent << endl;
  }
  return *this;
}