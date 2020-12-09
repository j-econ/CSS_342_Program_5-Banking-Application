/*
 * @file name.h
 * header file for name class which represents the first and last name of a person
 * 
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#pragma once

#include <string>
#include <iostream>

using namespace std;

class Name {
 public:
  // constructors
  Name();
  Name(string first_name, string last_name);
  Name(const Name& input);

  // getters-setters
  string get_first_name() const;
  string get_last_name() const;
  string get_name() const;
  void set_name(string first_name, string last_name);

  // overloads

  bool operator<(const Name& rhs) const;
  bool operator<=(const Name& rhs) const;
  bool operator>(const Name& rhs) const;
  bool operator>=(const Name& rhs) const;

  bool operator==(const Name& rhs) const;
  bool operator!=(const Name& rhs) const;

  Name& operator=(const Name& rhs);

  friend ostream& operator<<(ostream& out, const Name& rhs);
  friend istream& operator>>(istream& in, Name& rhs);

 private:
  string first_name_;
  string last_name_;
};