/*
 * @file
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "transaction.h"
#include "fund.h"
#include "name.h"

using namespace std;

class Account {
 public:
  // constructors
  Account();
  Account(int client_id, Name client_name);
  Account(const Account& input);
  ~Account();

  // getters-setters
  int get_client_id() const;
  Name get_client_name() const;
  vector<Fund> get_funds() const;

  bool set_client_id(int id);
  bool set_client_name(Name name);

  // actions
  bool ProcessTransaction(const Transaction& transaction);
  void PrintAllFundHistory() const;

  // operator overload
  bool operator<(const Account& rhs) const;
  bool operator>(const Account& rhs) const;

  bool operator==(const Account& rhs) const;
  bool operator!=(const Account& rhs) const;

  void operator=(const Account& rhs);

  friend ostream& operator<<(ostream& out, Account rhs);

 private:
  void CreateFunds();
  void Deposit(const Transaction& transaction);
  bool Withdraw(Transaction transaction);
  bool Transfer(Transaction transaction);
  void PrintHistory(const Transaction& transaction);

  int client_id_;
  Name client_name_;
  vector<Fund> funds_;
};