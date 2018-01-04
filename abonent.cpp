#include "abonent.h"

#include <fstream>
#include <string.h>

using namespace std;

MyBirthday::MyBirthday(int day/*=0*/, int month/*=0*/, int year/*=0*/)
  : m_day(day), m_month(month), m_year(year)
{
}

MyBirthday::operator bool() {
  return (m_day > 0 && m_day <= 31
       && m_month > 0 && m_month <= 12);
}

MyBirthday& MyBirthday::operator =(const MyBirthday &b) {
  m_day = b.m_day;
  m_month = b.m_month;
  m_year = b.m_year;
  return *this;
}

MyAddress::operator bool() {
  return 0 != m_town.size()
      && 0 != m_street.size()
      && 0 != m_building.size()
      && 0 != m_flat.size();
}

MyAddress& MyAddress::operator =(const MyAddress &b) {
  m_town = b.m_town;
  m_street = b.m_street;
  m_building = b.m_building;
  m_flat = b.m_flat;
  return *this;
}

MyAbonent::operator bool() {
  return 0 != m_name.size()
      && 0 != m_suname.size()
      && 0 != m_phoneNumber.size()
      && m_bithday
      && m_address;
}

bool MyAbonent::parse(const std::string &str, size_t &pos, size_t &len) const {
  pos = str.find_first_not_of(" \t\v", pos);
  if(pos == str.npos)
    return false;
  len = str.find_first_of(",\n\0", pos);
  if(len == str.npos) {
    len = strlen(str.c_str() + pos);
    return len != 0;
  }
  len -= pos;
  return true;
}

bool MyAbonent::parseStr(const std::string &src, std::string &dst,
                         size_t &pos, size_t &len) const
{
  if(!parse(src, pos, len))
    return false;
  dst.assign(src, pos, len);
  pos += len + 1;
  return true;
}

bool MyAbonent::parseInt(const std::string &src, int &dst,
                         size_t &pos, size_t &len) const
{
  if(!parse(src, pos, len))
    return false;
  //dst = std::stoi(src.substr(pos, len), nullptr); //work only fo c++11
  dst = atoi(src.c_str() + pos);
  pos += len + 1;
  return true;
}

MyAbonent& MyAbonent::operator <<(string &str) {
  size_t pos = 0, len = 0;
  do {
    if(!parseStr(str, m_name, pos, len)) break;
    if(!parseStr(str, m_suname, pos, len)) break;
    if(!parseStr(str, m_phoneNumber, pos, len)) break;

    if(!parseInt(str, m_bithday.m_year, pos, len)) break;
    if(!parseInt(str, m_bithday.m_month, pos, len)) break;
    if(!parseInt(str, m_bithday.m_day, pos, len)) break;

    if(!parseStr(str, m_address.m_town, pos, len)) break;
    if(!parseStr(str, m_address.m_street, pos, len)) break;
    if(!parseStr(str, m_address.m_building, pos, len)) break;
    if(!parseStr(str, m_address.m_flat, pos, len)) break;
  } while(false);

  return *this;
}

MyAbonent& MyAbonent::operator <<(ifstream &ifs) {
  if(!ifs.eof()) {
    const int bufsize = 2048;
    char buf[bufsize];
    ifs.getline(buf, bufsize);
    string str(buf);
    *this << str;
  }
  return *this;
}

const MyAbonent& MyAbonent::operator >>(ostream &os) const {
  os << "Name: " << m_name << endl;
  os << "Suname: " << m_suname << endl;
  os << "Phone Number: " << m_phoneNumber << endl;
  os << "Birthday (d.m.y): ";
  os << m_bithday.m_day << ".";
  os << m_bithday.m_month << ".";
  os << m_bithday.m_year << endl;
  os << "Address" << endl;
  os << "Town: " << m_address.m_town << endl;
  os << "Street: " << m_address.m_street << endl;
  os << "Building: " << m_address.m_building << endl;
  os << "Flat: " << m_address.m_flat << endl;
  return *this;
}

MyAbonent& MyAbonent::operator =(const MyAbonent& b) {
  m_name = b.m_name;
  m_suname = b.m_suname;
  m_phoneNumber = b.m_phoneNumber;
  m_bithday = b.m_bithday;
  m_address = b.m_address;
  return *this;
}
