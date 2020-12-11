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

// constructors

Bank::Bank() : id_(0) {};

Bank::Bank(int id) : id_(id) {}

Bank::~Bank() {
  this->client_accounts_.Empty();
}

// getters setters

int Bank::get_id() const {
  return id_;
}

// actions

// Reads in well-formatted transactions from an input text file
bool Bank::ReadTransactions(string filename) {
  ifstream inFile;
  inFile.open(filename);
  if (inFile.is_open()) {
    string line = "";
    while (!inFile.eof()) {
      getline(inFile, line);
      Transaction temp(line);
      transaction_list_.push(temp);
    }
    inFile.close();
  } else {
    cerr << "Fail to read transactions." << endl;
    return false;
  }
  return true;
}

// Processes all transactions in queue
void Bank::ProcessTransactions() {
  int size = transaction_list_.size();
  for (int i = 0; i < size; ++i) {
    Process(transaction_list_.front());
    transaction_list_.pop();
  }
  cout << "Transaction processing complete." << endl;
}

// Prints out summary of all Accounts in the Bank
void Bank::PrintSummary() const {
  cout << "Final Balances: " << endl;
  client_accounts_.Display();
}

// For testing. Adds 1 transaction to queue.
bool Bank::AddOneTransaction(Transaction transaction) {
  transaction_list_.push(transaction);
  return true;
}

// For testing. Prints out the transaction list.
void Bank::PrintTransactionList() {
  int size = transaction_list_.size();
  for (int i = 0; i < size; ++i) {
    transaction_list_.front().PrintTransaction();
    transaction_list_.pop();
    cout << endl;
  }
}

// private

void Bank::Process(Transaction transaction) {
  if (transaction.get_valid() == false) { // if transaction has invalid process
    cerr << "ERROR: Transaction \"" << transaction << "\" is not valid." <<
      " Terminating this transaction." << endl;
  } else {
    char type = transaction.get_type();

    // open account type O
    if (type == 'O') {
      Open(transaction);

    } else if (type == 'D') {
      Deposit(transaction);

      // withdraw type W
    } else if (type == 'W') {
      Withdraw(transaction);

      // transfer type T
    } else if (type == 'T') {
      if ((transaction.get_client_id() == transaction.get_to_client_id()) &&
          (transaction.get_fund_id() == transaction.get_to_fund_id())) {
        cerr << "ERROR: Transaction \"" << transaction << "\" is not valid. " <<
          " Cannot transfer from a fund to itself." << endl;
      } else {
        Transfer(transaction);
      }

      // history type T
    } else if (type == 'H') {
      PrintHistory(transaction);

      // NOT RECOGNIZED TYPE, FAIL
    } else {
      cerr << "ERROR: Transaction '" << transaction << "' is not valid." <<
        " Terminating this transaction." << endl;
    } // end char type logic
  } // end valid_ logic
}

// Dynamic memory allocation here
void Bank::Open(const Transaction& transaction) {

  // open dynamic memory
  Account* open =
    new Account(transaction.get_client_id(), transaction.get_client_name());

  // if fail, delete dynamic memory
  if (this->client_accounts_.Insert(open)) {
    return;
  } else {
    delete open;
    open = nullptr;
    cerr << "ERROR: Account " << transaction.get_client_id() <<
      " is already open." << " Transaction refused." << endl;
  }
}

void Bank::Deposit(const Transaction& transaction) {
  Account* current;

  // if account not found
  if (!(client_accounts_.Retrieve(transaction.get_client_id(), current))) {
    cerr << "ERROR: Account " << transaction.get_client_id() << " not found." <<
      " Deposit refused." << endl;

  // account found
  } else {
    current->ProcessTransaction(transaction, nullptr);
  }
}

void Bank::Withdraw(const Transaction& transaction) {
  Account* current;

  // if account not found
  if (!(client_accounts_.Retrieve(transaction.get_client_id(), current))) {
    cerr << "ERROR: Account " << transaction.get_client_id() << " not found." <<
      " Withdraw refused." << endl;

  // account found
  } else {
    current->ProcessTransaction(transaction, nullptr);
  }
}

void Bank::Transfer(const Transaction& transaction) {
  Account* from;
  Account* to;

  // if account not found
  if (!(client_accounts_.Retrieve(transaction.get_client_id(), from))) {
    cerr << "ERROR: Account " << transaction.get_client_id() << " not found." <<
      " Transfer refused." << endl;

  } else if (!(client_accounts_.Retrieve(transaction.get_to_client_id(), to))) {
    cerr << "ERROR: Account " << transaction.get_to_client_id() << " not found." <<
      " Transfer refused." << endl;

  // account found
  } else {
    from->ProcessTransaction(transaction, to);
  }
}

void Bank::PrintHistory(const Transaction& transaction) {
  Account* current;

  // if account not found
  if (!(client_accounts_.Retrieve(transaction.get_client_id(), current))) {
    cerr << "ERROR: Account " << transaction.get_client_id() << " not found." <<
      " Printing history failed." << endl;

    // account found
  } else {
    current->ProcessTransaction(transaction, nullptr);
  }
}