/*
 * @file money.h
 * header file for money class which represents an amount of money only in whole dollars
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#pragma once

#include <iostream>

using namespace std;

class Money {
 public:
  // constructors
  Money();
  Money(int amount);
  Money(const Money& input);

  // getters-setters
  int get_amount() const;
  bool set_amount(int amount);

  // operator overloads

  Money operator+(const Money& rhs) const;
  Money& operator+=(const Money& rhs);

  Money operator-(const Money& rhs) const;
  Money& operator-=(const Money& rhs);

  Money operator-() const;

  bool operator<(const Money& rhs) const;
  bool operator<=(const Money& rhs) const;
  bool operator>(const Money& rhs) const;
  bool operator>=(const Money& rhs) const;

  bool operator==(const Money& rhs) const;
  bool operator!=(const Money& rhs) const;

  Money& operator=(const Money& rhs);

  friend ostream& operator<<(ostream& out, const Money& rhs);
  friend istream& operator>>(istream& in, Money& rhs);

 private:
  int amount_; 
};