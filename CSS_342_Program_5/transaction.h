/*
 * @file transaction.h
 * header file for transaction class which represents one instance of a transaction that
 * can be processed at the bank.
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#pragma once

#include <iostream>
#include <sstream>

#include "name.h"
#include "money.h"

using namespace std;

class Transaction {
 public:
  // constructors
  Transaction();
  Transaction(string transaction_string);
  Transaction(const Transaction& input);

  // getters-setters
  string get_original_transaction() const;
  char get_type() const;
  Name get_client_name() const;
  int get_client_id() const;
  int get_fund_id() const;
  int get_to_client_id() const;
  int get_to_fund_id() const;
  Money get_amount() const;
  bool get_valid() const;

  void set_original_transaction(string transaction);

  // testing
  void set_type(char type);
  void set_client_name(Name name);
  void set_client_id(int client_id);
  void set_fund_id(int fund_id);
  void set_to_client_id(int to_client_id);
  void set_to_fund_id(int to_fund_id);
  void set_amount(const Money& amount);
  void set_valid(bool isValid);

  // testing
  void PrintTransaction() const;

  // overloads
  friend istream& operator>>(istream& in, Transaction& rhs);
  friend ostream& operator<<(ostream& out, const Transaction& rhs);

 private:
  void SetTransaction();

  string original_transaction_;
  char type_;
  Name client_name_;
  int client_id_;
  int fund_id_;
  int to_client_id_;
  int to_fund_id_;
  Money amount_;
  bool valid_;
};