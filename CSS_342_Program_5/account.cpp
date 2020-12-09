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

void Account::ProcessTransaction(
  const Transaction& transaction, Account* to_account) {
  char type = transaction.get_type();

  //deposit
  if (type == 'D') {
    Deposit(transaction);

    // withdraw
  } else if (type == 'W') {
    if (!(Withdraw(transaction))) {
      cerr << "ERROR: Not enough funds to withdraw " <<
        transaction.get_amount() << " from " << client_name_ << " " <<
        funds_[transaction.get_fund_id()].get_fund_name() << "." << endl;
    }

    // transfer
  } else if (type == 'T') {
    if (!(Transfer(transaction, to_account))) {
      cerr << "ERROR: Not enough funds to transfer " <<
        transaction.get_amount() << " from " << client_name_ << " " <<
        funds_[transaction.get_fund_id()].get_fund_name() << "." << endl;
    }

    // print history
  } else {
    if (transaction.get_fund_id() < 0) { // print all
      PrintAllFundHistory();
    } else { // print just one fund
      PrintHistory(transaction);
    }
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

//private

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
  int fund_id = transaction.get_fund_id(); // simplification
  Money amount = transaction.get_amount();

  // non linked withdrawal
  if ((fund_id != 0) && (fund_id != 1) && (fund_id != 2) && (fund_id != 3)) {

    // non linked not enough
    if (amount > funds_[fund_id].get_amount()) {
      transaction.set_original_transaction(
        transaction.get_original_transaction() + "(Failed)");
      funds_[transaction.get_fund_id()].StoreTransaction(transaction);
      return false;

    // non linked enough
    } else {
      funds_[fund_id].Withdraw(transaction.get_amount());
      funds_[fund_id].StoreTransaction(transaction);
      return true;
    }

  // linked withdrawal
  } else {

    // linked not enough funds
    if (amount > funds_[fund_id].get_amount()) {

      // fund 0
      if (fund_id == 0) {

        // not enough in both combined
        if (funds_[0].get_amount() + funds_[1].get_amount() < amount) {
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;

          // enough in both combined
        } else {

          Money remainder = amount - funds_[0].get_amount();

          // first transaction
          string new_transaction_first = "W " +
            to_string(transaction.get_client_id()) +
            "0" +
            " " +
            to_string( (funds_[0].get_amount()).Money::get_amount());
          Transaction new_first(new_transaction_first);
          funds_[0].Withdraw(new_first.get_amount());
          funds_[0].StoreTransaction(new_first);

          // second transaction
          string new_transaction_second = "W " + to_string(client_id_) +
            "1" + " " + to_string(remainder.Money::get_amount());
          Transaction new_second(new_transaction_second);
          funds_[1].Withdraw(new_second.get_amount());
          funds_[1].StoreTransaction(new_second);
          return true;
        }

        // fund 1
      } else if (fund_id == 1) {

        // not enough in both combined
        if (funds_[1].get_amount() + funds_[0].get_amount() < amount) {
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;

          // enough in both combined
        } else {

          Money remainder = amount - funds_[1].get_amount();

          // first transaction
          string new_transaction_first = "W " +
            to_string(transaction.get_client_id()) +
            "1" +
            " " +
            to_string((funds_[1].get_amount()).Money::get_amount());
          Transaction new_first(new_transaction_first);
          funds_[1].Withdraw(new_first.get_amount());
          funds_[1].StoreTransaction(new_first);

          // second transaction
          string new_transaction_second = "W " + to_string(client_id_) +
            "0" + " " + to_string(remainder.Money::get_amount());
          Transaction new_second(new_transaction_second);
          funds_[0].Withdraw(new_second.get_amount());
          funds_[0].StoreTransaction(new_second);
          return true;
        }

        // fund 2
      } else if (fund_id == 2) {

        // not enough in both combined
        if (funds_[2].get_amount() + funds_[3].get_amount() < amount) {
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;

          // enough in both combined
        } else {

          Money remainder = amount - funds_[2].get_amount();

          // first transaction
          string new_transaction_first = "W " +
            to_string(transaction.get_client_id()) +
            "2" +
            " " +
            to_string((funds_[2].get_amount()).Money::get_amount());
          Transaction new_first(new_transaction_first);
          funds_[2].Withdraw(new_first.get_amount());
          funds_[2].StoreTransaction(new_first);

          // second transaction
          string new_transaction_second = "W " + to_string(client_id_) +
            "3" + " " + to_string(remainder.Money::get_amount());
          Transaction new_second(new_transaction_second);
          funds_[3].Withdraw(new_second.get_amount());
          funds_[3].StoreTransaction(new_second);
          return true;
        }

        // fund 3
      } else {

        // not enough in both combined
        if (funds_[3].get_amount() + funds_[2].get_amount() < amount) {
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;

          // enough in both combined
        } else {

          Money remainder = amount - funds_[3].get_amount();

          // first transaction
          string new_transaction_first = "W " +
            to_string(transaction.get_client_id()) +
            "3" +
            " " +
            to_string((funds_[3].get_amount()).Money::get_amount());
          Transaction new_first(new_transaction_first);
          funds_[3].Withdraw(new_first.get_amount());
          funds_[3].StoreTransaction(new_first);

          // second transaction
          string new_transaction_second = "W " + to_string(client_id_) +
            "2" + " " + to_string(remainder.Money::get_amount());
          Transaction new_second(new_transaction_second);
          funds_[2].Withdraw(new_second.get_amount());
          funds_[2].StoreTransaction(new_second);
          return true;
        }
      }

    // linked enough
    } else {
      funds_[fund_id].Withdraw(transaction.get_amount());
      funds_[fund_id].StoreTransaction(transaction);
      return true;
    }
  }
}

bool Account::Transfer(Transaction transaction, Account* to_account) {
  int fund_id = transaction.get_fund_id(); // simplify
  int to_fund_id = transaction.get_to_fund_id();
  Money amount = transaction.get_amount();

  // non linked withdrawal
  if ((fund_id != 0) && (fund_id != 1) && (fund_id != 2) && (fund_id != 3)) {

    // non linked not enough funds
    if (amount > funds_[fund_id].get_amount()) {
      transaction.set_original_transaction(
        transaction.get_original_transaction() + "(Failed)");
      funds_[transaction.get_fund_id()].StoreTransaction(transaction);
      return false;

      // non linked enough
    } else {

      // withdraw from here
      funds_[fund_id].Withdraw(amount);
      funds_[fund_id].StoreTransaction(transaction);
      
      // deposit to here
      to_account->funds_[to_fund_id].Deposit(amount);
      to_account->funds_[to_fund_id].StoreTransaction(transaction);

      return true;
    }
  } else {

    // linked not enough funds
    if (amount > funds_[fund_id].get_amount()) {

      // fund 0
      if (fund_id == 0) {

        // not enough in both combined
        if (funds_[0].get_amount() + funds_[1].get_amount() < amount) {
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;

          // enough in both combined
        } else {

          Money remainder = amount - funds_[0].get_amount();

          // first transaction
          string new_transaction_first = "T " +
            to_string(transaction.get_client_id()) +
            "0" +
            " " +
            to_string((funds_[0].get_amount()).Money::get_amount()) +
            to_string(transaction.get_to_client_id()) +
            to_string(transaction.get_to_fund_id());
          Transaction new_first(new_transaction_first);
          funds_[0].Withdraw(new_first.get_amount());
          funds_[0].StoreTransaction(new_first);

          // second transaction
          string new_transaction_second = "T " +
            to_string(client_id_) +
            "1" +
            " " +
            to_string(remainder.Money::get_amount()) +
            to_string(transaction.get_client_id()) +
            to_string(transaction.get_to_fund_id());
          Transaction new_second(new_transaction_second);
          funds_[1].Withdraw(new_second.get_amount());
          funds_[1].StoreTransaction(new_second);

          to_account->funds_[transaction.get_to_fund_id()].Deposit(
            new_first.get_amount());
          to_account->funds_[transaction.get_to_fund_id()].StoreTransaction(
            new_first);
          to_account->funds_[transaction.get_to_fund_id()].Deposit(
            new_second.get_amount());
          to_account->funds_[transaction.get_to_fund_id()].StoreTransaction(
            new_second);

          return true;
        }

        // fund 1
      } else if (fund_id == 1) {

        // not enough in both combined
        if (funds_[1].get_amount() + funds_[0].get_amount() < amount) {
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;

          // enough in both combined
        } else {

          Money remainder = amount - funds_[1].get_amount();

          // first transaction
          string new_transaction_first = "T " +
            to_string(transaction.get_client_id()) +
            "1" +
            " " +
            to_string((funds_[1].get_amount()).Money::get_amount()) +
            to_string(transaction.get_to_client_id()) +
            to_string(transaction.get_to_fund_id());
          Transaction new_first(new_transaction_first);
          funds_[1].Withdraw(new_first.get_amount());
          funds_[1].StoreTransaction(new_first);

          // second transaction
          string new_transaction_second = "T " +
            to_string(client_id_) +
            "0" +
            " " +
            to_string(remainder.Money::get_amount()) +
            to_string(transaction.get_client_id()) +
            to_string(transaction.get_to_fund_id());
          Transaction new_second(new_transaction_second);
          funds_[0].Withdraw(new_second.get_amount());
          funds_[0].StoreTransaction(new_second);

          to_account->funds_[transaction.get_to_fund_id()].Deposit(
            new_first.get_amount());
          to_account->funds_[transaction.get_to_fund_id()].StoreTransaction(
            new_first);
          to_account->funds_[transaction.get_to_fund_id()].Deposit(
            new_second.get_amount());
          to_account->funds_[transaction.get_to_fund_id()].StoreTransaction(
            new_second);

          return true;
        }

        // fund 2
      } else if (fund_id == 2) {

        // not enough in both combined
        if (funds_[2].get_amount() + funds_[3].get_amount() < amount) {
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;

          // enough in both combined
        } else {

          Money remainder = amount - funds_[2].get_amount();

          // first transaction
          string new_transaction_first = "T " +
            to_string(transaction.get_client_id()) +
            "2" +
            " " +
            to_string((funds_[2].get_amount()).Money::get_amount()) +
            to_string(transaction.get_to_client_id()) +
            to_string(transaction.get_to_fund_id());
          Transaction new_first(new_transaction_first);
          funds_[2].Withdraw(new_first.get_amount());
          funds_[2].StoreTransaction(new_first);

          // second transaction
          string new_transaction_second = "T " +
            to_string(client_id_) +
            "3" +
            " " +
            to_string(remainder.Money::get_amount()) +
            to_string(transaction.get_client_id()) +
            to_string(transaction.get_to_fund_id());
          Transaction new_second(new_transaction_second);
          funds_[3].Withdraw(new_second.get_amount());
          funds_[3].StoreTransaction(new_second);

          to_account->funds_[transaction.get_to_fund_id()].Deposit(
            new_first.get_amount());
          to_account->funds_[transaction.get_to_fund_id()].StoreTransaction(
            new_first);
          to_account->funds_[transaction.get_to_fund_id()].Deposit(
            new_second.get_amount());
          to_account->funds_[transaction.get_to_fund_id()].StoreTransaction(
            new_second);

          return true;
        }

        // fund 3
      } else {

        // not enough in both combined
        if (funds_[3].get_amount() + funds_[2].get_amount() < amount) {
          transaction.set_original_transaction(
            transaction.get_original_transaction() + "(Failed)");
          funds_[transaction.get_fund_id()].StoreTransaction(transaction);
          return false;

          // enough in both combined
        } else {

          Money remainder = amount - funds_[3].get_amount();

          // first transaction
          string new_transaction_first = "T " +
            to_string(transaction.get_client_id()) +
            "3" +
            " " +
            to_string((funds_[3].get_amount()).Money::get_amount()) +
            to_string(transaction.get_to_client_id()) +
            to_string(transaction.get_to_fund_id());
          Transaction new_first(new_transaction_first);
          funds_[3].Withdraw(new_first.get_amount());
          funds_[3].StoreTransaction(new_first);

          // second transaction
          string new_transaction_second = "T " +
            to_string(client_id_) +
            "2" +
            " " +
            to_string(remainder.Money::get_amount()) +
            to_string(transaction.get_client_id()) +
            to_string(transaction.get_to_fund_id());
          Transaction new_second(new_transaction_second);
          funds_[2].Withdraw(new_second.get_amount());
          funds_[2].StoreTransaction(new_second);

          to_account->funds_[transaction.get_to_fund_id()].Deposit(
            new_first.get_amount());
          to_account->funds_[transaction.get_to_fund_id()].StoreTransaction(
            new_first);
          to_account->funds_[transaction.get_to_fund_id()].Deposit(
            new_second.get_amount());
          to_account->funds_[transaction.get_to_fund_id()].StoreTransaction(
            new_second);

          return true;
        }
      }

      // linked enough
    } else {

      // withdraw from here
      funds_[fund_id].Withdraw(amount);
      funds_[fund_id].StoreTransaction(transaction);

      // deposit to here
      to_account->funds_[to_fund_id].Deposit(amount);
      to_account->funds_[to_fund_id].StoreTransaction(transaction);
    }
  }
}

void Account::PrintHistory(const Transaction& transaction) {
  cout << "Transaction History for " << get_client_name() << " ";
  funds_[transaction.get_fund_id()].PrintHistory();
}


ostream& operator<<(ostream& out, Account rhs) {
  out << rhs.get_client_name() << " Account ID: " << rhs.get_client_id() <<
    endl;
  for (unsigned int i = 0; i < rhs.funds_.size(); ++i) {
    out << "  " << rhs.funds_[i] << endl;
  }
  return out;
}