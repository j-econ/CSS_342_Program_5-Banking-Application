/*
 * @file fund.cpp
 * implementation for fund class
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */

#include "fund.h"

// constructors

Fund::Fund()
    : fund_id_(-1), fund_name_("Default Fund") {}

Fund::Fund(int fund_id, string fund_name, Name fund_owner)
  : fund_id_(fund_id), fund_name_(fund_name), fund_owner_(fund_owner) {}

// getter setters

Money Fund::get_amount() const {
  return amount_;
}

string Fund::get_fund_name() const {
  return fund_name_;
}

int Fund::get_fund_id() const {
  return fund_id_;
}

void Fund::set_amount(const Money& input) {
  amount_.set_amount(input.get_amount());
}

// actions

void Fund::Deposit(const Money& deposit) {
  amount_ += deposit;
}

bool Fund::Withdraw(const Money& withdraw) {
  if (this->IsEnough(withdraw)) {
    amount_ -= withdraw;
    return true;
  } else {
    return false;
  }
}

void Fund::StoreTransaction(Transaction input) {
  history_.push_back(input);
}

void Fund::PrintHistory() const {
  cout << *this << endl;
  for (unsigned int i = 0; i < history_.size(); ++i) {
    cout << "  " << history_[i] << endl;
  }
}

// returns true if enough in fund to withdraw amount
bool Fund::IsEnough(const Money& amount) const {
  return (amount_ >= amount);
}

// operators

ostream& operator<<(ostream& out, const Fund& rhs) {
  out << rhs.fund_name_ << ": " << rhs.amount_;
  return out;
}