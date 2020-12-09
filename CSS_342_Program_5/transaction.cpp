/*
 * @file transactuin.cpp
 * implementation file for transaction class
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#include "transaction.h"

Transaction::Transaction()
    : original_transaction_("Empty Transaction"),
      type_('0'),
      client_name_(Name()),
      client_id_(-1),
      fund_id_(-1),
      to_client_id_(-1),
      to_fund_id_(-1),
      amount_(Money()) {}

Transaction::Transaction(string transaction_string)
  : original_transaction_(transaction_string) {
  SetTransaction();
}

Transaction::Transaction(const Transaction& input)
    : original_transaction_(input.get_original_transaction()),
      type_(input.get_type()),
      client_name_(input.get_client_name()),
      fund_id_(input.get_fund_id()),
      to_client_id_(input.get_to_client_id()),
      to_fund_id_(input.get_to_fund_id()),
      amount_(input.get_amount()) {}

string Transaction::get_original_transaction() const {
  return original_transaction_;
}

char Transaction::get_type() const {
  return type_;
}

Name Transaction::get_client_name() const {
  return client_name_;
}

int Transaction::get_client_id() const {
  return client_id_;
}

int Transaction::get_fund_id() const {
  return fund_id_;
}

int Transaction::get_to_client_id() const {
  return to_client_id_;
}

int Transaction::get_to_fund_id() const {
  return to_fund_id_;
}

Money Transaction::get_amount() const {
  return amount_;
}

// assumes well formatted transaction
void Transaction::set_original_transaction(string transaction) {
  original_transaction_ = transaction;
  SetTransaction();
}

void Transaction::set_type(char type) {
  type_ = type;
}

void Transaction::set_client_name(Name name) {
  client_name_ = name;
}

void Transaction::set_client_id(int client_id) {
  client_id_ = client_id;
}

void Transaction::set_fund_id(int fund_id) {
  fund_id_ = fund_id;
}

void Transaction::set_to_client_id(int to_client_id) {
  to_client_id_ = to_client_id;
}

void Transaction::set_to_fund_id(int to_fund_id) {
  to_fund_id_ = to_fund_id;
}

void Transaction::set_amount(const Money& amount) {
  amount_ = amount;
}

void Transaction::PrintTransaction() const {
  cout << "Original Transaction: " << original_transaction_ << endl;
  cout << "type_: " << type_ << endl;
  cout << "client_name_: " << client_name_ << endl;
  cout << "client_id_: " << client_id_ << endl;
  cout << "fund_id_: " << fund_id_ << endl;
  cout << "to_client_id_: " << to_client_id_ << endl;
  cout << "to_fund_id_: " << to_fund_id_ << endl;
  cout << "amount_: " << amount_ << endl;
}

// transaction parser stores values and original transaction string
void Transaction::SetTransaction() {
  istringstream o_t(original_transaction_);
  type_ = original_transaction_[0];
  string burn = ""; // use up one of o_t reads

  // open account type
  if (type_ == 'O') {
    string last = "";
    string first = "";
    o_t >> burn >> last >> first >> client_id_;
    client_name_ = Name(first, last);

    // defaults
    fund_id_ = -1;
    to_client_id_ = -1;
    to_fund_id_ = -1;
    amount_ = Money();

    // deposit type or withdraw type
  } else if ((type_ == 'D') || (type_ == 'W')) {
    int id = 0;
    int value = 0;
    o_t >> burn >> id >> value;
    fund_id_ = id % 10;
    id /= 10;
    client_id_ = id;
    amount_ = Money(value);

    // defaults
    client_name_ = Name();
    to_client_id_ = -1;
    to_fund_id_ = -1;

  // transaction type
  } else if (type_ == 'T') {
    int from = 0;
    int value = 0;
    int to = 0;
    o_t >> burn >> from >> value >> to;
    fund_id_ = from % 10;
    from /= 10;
    client_id_ = from;
    to_fund_id_ = to % 10;
    to /= 10;
    to_client_id_ = to;
    amount_ = Money(value);

    // defaults
    client_name_ = Name();

  // history type
  } else if (type_ == 'H') {
    o_t >> burn >> client_id_;

    // defaults
    client_name_ = Name();
    fund_id_ = -1;
    to_client_id_ = -1;
    to_fund_id_ = -1;
    amount_ = Money();

  // non recognized transaction defaults
  } else {
    cerr << "Transaction type '" << type_ << "' is not valid." << endl;
    client_name_ = Name();
    client_id_ = -1;
    fund_id_ = -1;
    to_client_id_ = -1;
    to_fund_id_ = -1;
    amount_ = Money();
  }
}

istream& operator>>(istream& in, Transaction& rhs) {
  in >> rhs.original_transaction_;
  rhs.SetTransaction();
  return in;
}

ostream& operator<<(ostream& out, const Transaction& rhs) {
  out << rhs.original_transaction_;
  return out;
}