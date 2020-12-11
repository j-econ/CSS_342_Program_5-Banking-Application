/*
 * @file money.cpp
 * implementation for money class
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */

#include "money.h"

Money::Money() : amount_(0) {}

Money::Money(int amount) : amount_(amount) {}

Money::Money(const Money& input) : amount_(input.get_amount()) {}

int Money::get_amount() const {
  return amount_;
}

bool Money::set_amount(int amount) {
  amount_ = amount;
  return true;
}

Money Money::operator+(const Money& rhs) const {
  Money result = *this;
  result += rhs;
  return result;
}

Money& Money::operator+=(const Money& rhs) {
  amount_ += rhs.get_amount();
  return *this;
}

Money Money::operator-(const Money& rhs) const {
  Money result = *this;
  result -= rhs;
  return result;
}

Money& Money::operator-=(const Money& rhs) {
  amount_ -= rhs.get_amount();
  return *this;
}

Money Money::operator-() const {
  return -(this->get_amount());
}

bool Money::operator<(const Money& rhs) const {
  return (amount_ < rhs.get_amount());
}

bool Money::operator<=(const Money& rhs) const {
  return ((*this < rhs) || (*this == rhs));
}

bool Money::operator>(const Money& rhs) const {
  return (amount_ > rhs.get_amount());
}

bool Money::operator>=(const Money& rhs) const {
  return ((*this > rhs) || (*this == rhs));
}

bool Money::operator==(const Money& rhs) const {
  return (amount_ == rhs.get_amount());
}

bool Money::operator!=(const Money& rhs) const {
  return !(*this == rhs);
}

Money& Money::operator=(const Money& rhs) {
  if (*this == rhs) { return *this; } // base case same obj

  this->amount_ = rhs.get_amount();
  return *this;
}

ostream& operator<<(ostream& out, const Money& rhs) {
  out << "$" << rhs.get_amount();
  return out;
}

// takes in an integer which rhs amount is set to if above 0
istream& operator>>(istream& in, Money& rhs) {
  int value = 0;
  in >> value;
  if (value > 0) {
    rhs.set_amount(value);
  }
  return in;
}
