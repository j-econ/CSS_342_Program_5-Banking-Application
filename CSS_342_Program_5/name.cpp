/*
 * @file name.cpp
 * implementation for name class
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#include "name.h"

// constructors

Name::Name() : first_name_("Default"), last_name_("Default") {};

Name::Name(string first_name, string last_name)
    : first_name_(first_name), last_name_(last_name) {}

Name::Name(const Name& input)
  : first_name_(input.get_first_name()), last_name_(input.get_last_name()) {}

// getters - setters

string Name::get_first_name() const { return first_name_; }

string Name::get_last_name() const { return last_name_; }

string Name::get_name() const {
  return (first_name_ + " " + last_name_);
}

void Name::set_name(string first_name, string last_name) {
  first_name_ = first_name;
  last_name_ = last_name;
}

// operator overloads
// all relational operators compare alphabetically by last name then first name

bool Name::operator<(const Name& rhs) const {
  if (this->last_name_ < rhs.get_last_name()) {
    return true;
  } else if (this->last_name_ == rhs.get_last_name()) {
    if (this->first_name_ < rhs.get_first_name()) {
      return true;
    }
  }
  return false;
}

bool Name::operator<=(const Name& rhs) const {
  bool equal = ((this->last_name_ == rhs.get_last_name()) &&
                (this->first_name_ == rhs.get_first_name()));
  return ((*this < rhs) || (*this == rhs));
}

bool Name::operator>(const Name& rhs) const {
  if (this->last_name_ > rhs.get_last_name()) {
    return true;
  } else if (this->last_name_ == rhs.get_last_name()) {
    if (this->first_name_ > rhs.get_first_name()) {
      return true;
    }
  }
  return false;
}

bool Name::operator>=(const Name& rhs) const {
  return ((*this > rhs) || (*this == rhs));
}

bool Name::operator==(const Name& rhs) const {
  return ((this->last_name_ == rhs.get_last_name()) &&
          (this->first_name_ == rhs.get_first_name()));
}

bool Name::operator!=(const Name& rhs) const {
  return !(*this == rhs);
}

Name& Name::operator=(const Name& rhs) {
  if (*this == rhs) { return *this; } // base case same Name

  this->first_name_ = rhs.get_first_name();
  this->last_name_ = rhs.get_last_name();
  return *this;
}

ostream& operator<<(ostream& out, const Name& rhs) {
  out << rhs.get_first_name() << ' ' << rhs.get_last_name();
  return out;
}

// takes input of 2 strings in the order last_name, first_name sets rhs to input values.
istream& operator>>(istream& in, Name& rhs) {
  in >> rhs.last_name_ >> rhs.first_name_;
  return in;
}