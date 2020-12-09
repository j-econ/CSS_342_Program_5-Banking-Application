/*
 * @file bank.cpp
 * implementation for bank class
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#include "bank.h"

Bank::Bank() : id_(0) {};

Bank::Bank(int id) : id_(id) {}

Bank::~Bank() {}

int Bank::get_id() {
  return 0;
}

bool Bank::ReadTransactions(string filename) {
  ifstream inFile;
  inFile.open(filename);
  if (inFile.is_open()) {
    string line = "";
    while (!inFile.eof()) {
      getline(inFile, line);
      transaction_list_.push(Transaction(line));
    }
    inFile.close();
  } else {
    cerr << "Fail to read transactions." << endl;
    return false;
  }
  return true;
}

void Bank::ProcessTransactions() {
  int size = transaction_list_.size();
  for (int i = 0; i < size; ++i) {
    Process(transaction_list_.front());
    transaction_list_.pop();
  }
  cout << "Processing Complete." << endl;
  PrintSummary();
}

void Bank::PrintSummary() const {}

bool Bank::AddOneTransaction(Transaction transaction) {
  transaction_list_.push(transaction);
  return true;
}

void Bank::PrintTransactionList() {
  int size = transaction_list_.size();
  for (int i = 0; i < size; ++i) {
    transaction_list_.front().PrintTransaction();
    transaction_list_.pop();
    cout << endl;
  }
}

bool Bank::Process(Transaction transaction) {
  char type = transaction.get_type();
  if (type == 'O') {
    return true;
  } else if (type == 'D') {
    Deposit(transaction);
    return true;
  } else if (type == 'W') {
    if (Withdraw(transaction)) {
      return true;
    } else {
      return false;
    }
  } else if (type == 'T') {
    if (Transfer(transaction)) {
      return true;
    } else {
      return false;
    }
  } else {
    PrintHistory(transaction);
    return true;
  }
}

// todo: cout to cerr
// dynamic memory here
bool Bank::Open(const Transaction& transaction) {

  // open dynamic memory
  Account* open =
    new Account(transaction.get_client_id(), transaction.get_client_name());

  // if fail, delete dynamic memory
  if (client_accounts_.Insert(open)) {
    return true;
  } else {
    delete open;
    open = nullptr;
    cerr << "Account " << transaction.get_client_id() << " is already open." <<
      "Transaction refused." << endl;
  }
}

void Bank::Deposit(const Transaction& transaction) {}

bool Bank::Withdraw(const Transaction& transaction) {
  return false;
}

bool Bank::Transfer(const Transaction& transaction) {
  return false;
}

void Bank::PrintHistory(const Transaction& transaction) {}