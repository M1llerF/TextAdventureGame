/**
 * @file: Event.h
 * @author: Justin P
 * @date: 2024-03-27
 */

#ifndef FLAG_H_INCLUDED
#define FLAG_H_INCLUDED

#include <string>

class Flag {
 public:
  Flag(std::string n) : value{false}, name{n} {}

  // Memory is handled by manager of flag pointer
  ~Flag() {}

  bool getValue() const { return value; }

  void setValue(bool v) {value = v; }

  std::string getName() const { return name; }

 private:
  bool value;
  std::string name;
};

#endif // FLAG_H_INCLUDED
