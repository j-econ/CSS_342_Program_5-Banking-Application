/*
 * @file fund.h
 * header file for fund class which represents a single fund within a bank account
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "money.h"
#include "transaction.h"
#include "name.h"

using namespace std;

class Fund {
 public:
  // constructors
  Fund();
  Fund(int fund_id, string fund_name, Name fund_owner);

  // getters-setters
  Money get_amount() const;
  string get_fund_name() const;
  int get_fund_id() const;

  void set_amount(const Money& input);

  // actions
  void Deposit(const Money& deposit);
  bool Withdraw(const Money& withdraw);
  void StoreTransaction(Transaction input);
  void PrintHistory() const;

  // overloads
  friend ostream& operator<<(ostream& out, const Fund& rhs);

 private:
  bool IsEnough(const Money& amount) const;

  int fund_id_;
  string fund_name_;
  Name fund_owner_;
  Money amount_;
  vector<Transaction> history_;
};