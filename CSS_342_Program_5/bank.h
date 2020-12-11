/*
 * @file bank.h
 * header file for bank class represents a bank with bank accounts.
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#pragma once

#include <iostream>
#include <queue>
#include <fstream>

#include "transaction.h"
#include "bs_tree.h"
#include "account.h"

using namespace std;

class Bank {
 public:
  // constructors
  Bank();
  Bank(int id);
  ~Bank();

  // getters-setters
  int get_id() const;

  // actions
  bool ReadTransactions(string filename);
  void ProcessTransactions(); // process all transactions in the queue
  void PrintSummary() const; // print summary of all accounts in the bank

  // for testing
  bool AddOneTransaction(Transaction transaction);
  void PrintTransactionList();

 private:
  // no const functions as all functions have the ability to store transaction
  void Process(Transaction transaction);
  void Open(const Transaction& transaction);
  void Deposit(const Transaction& transaction);
  void Withdraw(const Transaction& transaction);
  void Transfer(const Transaction& transaction);
  void PrintHistory(const Transaction& transaction);

  int id_;
  queue<Transaction> transaction_list_;
  BSTree client_accounts_;
};