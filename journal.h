#pragma once

#include <vector>
#include <fstream>

#include "abonent.h"
#include "myvector.h"

//class MyJournal: public std::vector<MyAbonent> {
class MyJournal: public MyVector<MyAbonent> {
public:
  size_t loadFromFile(std::ifstream &filestream);
  size_t findByName(const std::string &name,
                    const std::string &suname,
                    size_t startpos = 0);
  size_t FindByPhone(const std::string &phoneNumber, size_t startpos = 0);

  const MyJournal& operator >>(std::ostream &os) const;
};

inline std::ostream& operator << (std::ostream &os, const MyJournal &journal) {
  journal >> os;
  return os;
}
