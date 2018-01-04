#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

class MyBirthday {
  friend class MyAbonent;
protected:
  int m_day;
  int m_month;
  int m_year;

public:
  MyBirthday(int day = 0, int month = 0, int year = 0);
  operator bool();
  MyBirthday& operator =(const MyBirthday &other);
};

class MyAddress {
  friend class MyAbonent;
protected:
  std::string   m_town;      //город
  std::string   m_street;    //улица
  std::string   m_building;  //Дом
  std::string   m_flat;      //Квартира

public:
  operator bool();
  MyAddress& operator =(const MyAddress &other);
};

class MyAbonent {
  friend class MyJournal;
protected:
  std::string   m_name;
  std::string   m_suname;
  std::string   m_phoneNumber;
  MyBirthday    m_bithday;
  MyAddress     m_address;

public:
  operator bool();
  MyAbonent& operator <<(std::string &str);
  MyAbonent& operator <<(std::ifstream &ifs);
  const MyAbonent& operator >>(std::ostream &os) const;

  MyAbonent& operator =(const MyAbonent& other);

protected:
  bool parse(const std::string &str, size_t &pos, size_t &len) const;
  bool parseStr(const std::string &src, std::string &dest,
                size_t &pos, size_t &len) const;
  bool parseInt(const std::string &src, int &dst,
                size_t &pos, size_t &len) const;
};

inline std::ifstream& operator >> (std::ifstream &ifs, MyAbonent &abonent) {
  abonent << ifs;
  return ifs;
}

inline std::ostream& operator << (std::ostream &os, const MyAbonent &abonent) {
  abonent >> os;
  return os;
}
