/*
 * @file account.h
 * implementation file for account class
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#include "account.h"

// constructors

Account::Account()
  : client_id_(-0001), client_name_(Name()) {
  CreateFunds();
}

Account::Account(int client_id, Name client_name)
  : client_id_(client_id), client_name_(client_name) {
  CreateFunds();
}

Account::Account(const Account& input)
  : client_id_(input.get_client_id()),
  client_name_(input.get_client_name()),
  funds_(input.get_funds()) {}

Account::~Account() {
}

int Account::get_client_id() const {
  return client_id_;
}

Name Account::get_client_name() const {
  return client_name_;
}

vector<Fund> Account::get_funds() const {
  return this->funds_;
}

bool Account::set_client_id(int id) {
  client_id_ = id;
  return true;
}

bool Account::set_client_name(Name name) {
  client_name_ = name;
  return true;
}

// actions

bool Account::ProcessTransaction(const Transaction& transaction) {
  char type = transaction.get_type();
  if (type == 'D') {
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

void Account::PrintAllFundHistory() const {
  cout << "Transaction History for " << client_name_ << " by fund:" << endl;
  for (unsigned int i = 0; i < funds_.size(); ++i) {
    funds_[i].PrintHistory();
  }
  cout << "End of Transaction History for " << client_name_ << "." << endl;
}

// overloads

bool Account::operator<(const Account& rhs) const {
  return (client_id_ < rhs.get_client_id());
}

bool Account::operator>(const Account& rhs) const {
  return (client_id_ > rhs.get_client_id());
}

bool Account::operator==(const Account& rhs) const {
  return (client_id_ == rhs.get_client_id());
}

bool Account::operator!=(const Account& rhs) const {
  return !(*this == rhs);
}

void Account::operator=(const Account& rhs) {
  client_id_ = rhs.get_client_id();
  client_name_ = rhs.get_client_name();
  funds_ = rhs.get_funds();
}

void Account::CreateFunds() {
  funds_.push_back(Fund(0, "Money Market", client_name_));
  funds_.push_back(Fund(1, "Prime Money Market", client_name_));
  funds_.push_back(Fund(2, "Long-Term Bond", client_name_));
  funds_.push_back(Fund(3, "Short-Term Bond", client_name_));
  funds_.push_back(Fund(4, "500 Index Fund", client_name_));
  funds_.push_back(Fund(5, "Capital Value Fund", client_name_));
  funds_.push_back(Fund(6, "Growth Equity Fund", client_name_));
  funds_.push_back(Fund(7, "Growth Index Fund", client_name_));
  funds_.push_back(Fund(8, "Value Fund", client_name_));
  funds_.push_back(Fund(9, "Value Stock Index", client_name_));
}

void Account::Deposit(const Transaction& transaction) {
  funds_[transaction.get_fund_id()].Deposit(transaction.get_amount());
  funds_[transaction.get_fund_id()].StoreTransaction(transaction);
}

bool Account::Withdraw(Transaction transaction) {
  
  // non linked withdrawal
  if ((transaction.get_type() != '0') &&
      (transaction.get_type() != '1') &&
      (transaction.get_type() != '2') &&
      (transaction.get_type() != '3')) {

    // non linked not enough funds
    if (transaction.get_amount() >
        funds_[transaction.get_fund_id()].get_amount()) {
      transaction.set_original_transaction(
        transaction.get_original_transaction() + "(Failed)");
      funds_[transaction.get_fund_id()].StoreTransaction(transaction);
      return false;

    // non linked enough
    } else {
      funds_[transaction.get_fund_id()].Withdraw(transaction.get_amount());
      funds_[transaction.get_fund_id()].StoreTransaction(transaction);
      return true;
    }

  // linked withdrawal
  } else {

    // linked not enough funds
    if (transaction.get_amount() >
        funds_[transaction.get_fund_id()].get_amount()) {

      // linked fund logic

      // fund 0
      if (transaction.get_fund_id() == 0) {
        if (funds_[0].get_amount() + funds_[1].get_amount() <
            transaction.get_amount()) { // not enough in both
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;
        } else { // enough in both, split transaction

          // first transaction
          string new_transaction_first = "W " + to_string(client_id_) +
            "0" + " " + to_string((funds_[0].get_amount()).Money::get_amount());
          Transaction new_first(new_transaction_first);
          funds_[0].Withdraw(new_first.get_amount());
          funds_[0].StoreTransaction(new_first);

          // second transaction
          Money remainder = transaction.get_amount() - funds_[0].get_amount();
          string new_transaction_second = "W " + to_string(client_id_) +
            "1" + " " + to_string(remainder.Money::get_amount());
          Transaction new_second(new_transaction_second);
          funds_[1].Withdraw(new_second.get_amount());
          funds_[1].StoreTransaction(new_second);
          return true;
        }

        // fund 1
      } else if (transaction.get_fund_id() == 1) {
        if (funds_[1].get_amount() + funds_[0].get_amount() <
            transaction.get_amount()) { // not enough in both
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;
        } else { // enough in both

          // first transaction
          string new_transaction_first = "W " + to_string(client_id_) +
            "1" + " " + to_string((funds_[1].get_amount()).Money::get_amount());
          Transaction new_first(new_transaction_first);
          funds_[1].Withdraw(new_first.get_amount());
          funds_[1].StoreTransaction(new_first);

          // second transaction
          Money remainder = transaction.get_amount() - funds_[1].get_amount();
          string new_transaction_second = "W " + to_string(client_id_) +
            "0" + " " + to_string(remainder.Money::get_amount());
          Transaction new_second(new_transaction_second);
          funds_[0].Withdraw(new_second.get_amount());
          funds_[0].StoreTransaction(new_second);
          return true;
        }

        // fund 2
      } else if (transaction.get_fund_id() == 2) {
        if (funds_[2].get_amount() + funds_[3].get_amount() <
            transaction.get_amount()) { // not enough in both
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;
        } else { // enough in both

          // first transaction
          string new_transaction_first = "W " + to_string(client_id_) +
            "2" + " " + to_string((funds_[2].get_amount()).Money::get_amount());
          Transaction new_first(new_transaction_first);
          funds_[2].Withdraw(new_first.get_amount());
          funds_[2].StoreTransaction(new_first);

          // second transaction
          Money remainder = transaction.get_amount() - funds_[2].get_amount();
          string new_transaction_second = "W " + to_string(client_id_) +
            "3" + " " + to_string(remainder.Money::get_amount());
          Transaction new_second(new_transaction_second);
          funds_[3].Withdraw(new_second.get_amount());
          funds_[3].StoreTransaction(new_second);
          return true;
        }

        // fund 3
      } else {
        if (funds_[3].get_amount() + funds_[2].get_amount() <
            transaction.get_amount()) { // not enough in both
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;
        } else { // enough in both

          // first transaction
          string new_transaction_first = "W " + to_string(client_id_) +
            "3" + " " + to_string((funds_[3].get_amount()).Money::get_amount());
          Transaction new_first(new_transaction_first);
          funds_[3].Withdraw(new_first.get_amount());
          funds_[3].StoreTransaction(new_first);

          // second transaction
          Money remainder = transaction.get_amount() - funds_[3].get_amount();
          string new_transaction_second = "W " + to_string(client_id_) +
            "3" + " " + to_string(remainder.Money::get_amount());
          Transaction new_second(new_transaction_second);
          funds_[3].Withdraw(new_second.get_amount());
          funds_[3].StoreTransaction(new_second);
          return true;
        }
      }

    // linked enough
    } else {
      funds_[transaction.get_fund_id()].Withdraw(transaction.get_amount());
      funds_[transaction.get_fund_id()].StoreTransaction(transaction);
      return true;
    }
  }
}

bool Account::Transfer(Transaction transaction) {
  return false;
}

void Account::PrintHistory(const Transaction& transaction) {}

ostream& operator<<(ostream& out, Account rhs) {
  out << rhs.get_client_name() << " Account ID: " << rhs.get_client_id() <<
    endl;
  for (unsigned int i = 0; i < rhs.funds_.size(); ++i) {
    out << "  " << rhs.funds_[i] << endl;
  }
  return out;
}