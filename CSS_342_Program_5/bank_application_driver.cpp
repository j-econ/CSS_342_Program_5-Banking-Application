/*
 * @bank_application_driver.cpp
 * driver for banking application
 *
 * @author Joseph Lan
 * @date 08 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */

#include <iostream>
#include <string>

#include "bank.h"
#include "bs_tree.h"
#include "transaction.h"
#include "account.h"
#include "fund.h"
#include "name.h"
#include "money.h"

using namespace std;

// Testing methods for application classes
void BankTest(string filename);
void BSTreeTest();
void AccountTest();
void FundTest();
void TransactionTest();
void NameTest();
void MoneyTest();

int main() {

  string filename = "";
  filename = "BankTransIn.txt";

  Bank bank_342(342);
  bank_342.ReadTransactions(filename);
  bank_342.ProcessTransactions();
  cout << endl;
  bank_342.PrintSummary();

  //Testing methods here
  //cout << boolalpha << endl;
  //BankTest(filename);
  //BSTreeTest();
  //AccountTest();
  //FundTest();
  //TransactionTest();
  //NameTest();
  //MoneyTest();
  return 0;
}

void BankTest(string filename) {
  cout << "BANK CLASS TESTING BEGIN-----------------------------------" << endl;
  cout << endl;

  Bank bank_342(342);
  bank_342.ReadTransactions(filename);
  bank_342.ProcessTransactions();
  cout << endl;
  bank_342.PrintSummary();

  cout << endl;
  cout << "-------------------------------------BANK CLASS TESTING END" << endl;
  cout << endl;
}

void BSTreeTest() {
  cout << "BSTree CLASS TESTING BEGIN---------------------------------" << endl;
  cout << endl;

  cout << "Make Accounts" << endl;
  Account dave1420(1420, Name("Dave", "Braile"));
  Account john1124(1124, Name("John", "Ifan"));
  Account brian4192(4192, Name("Brian", "Jav"));
  Account steve1942(1942, Name("Steve", "Paj"));
  Account amber5831(5831, Name("Amber", "Cheerio"));
  Account emily4928(4928, Name("Emily", "Bae"));
  Account jessica4256(4256, Name("Jessica", "Fjei"));
  Account blair8829(8829, Name("Blair", "Emaf"));
  Account fiona6427(6427, Name("Fiona", "Soi"));
  Account yvi7891(7891, Name("Yvi", "Fre"));
  Account grace1239(1239, Name("Grace", "Ches"));
  Account esther6466(6466, Name("Esther", "Mem"));
  Account heather5858(5858, Name("Heather", "Dac"));
  Account rich1001(1001, Name("Rich", "Rich"));
  cout << "All accounts made" << endl;
  cout << endl;

  // insertion
  BSTree accounts;
  cout << "Inserting accounts" << endl;
  accounts.Insert(&dave1420);
  accounts.Insert(&john1124);
  accounts.Insert(&brian4192);
  accounts.Insert(&steve1942);
  accounts.Insert(&amber5831);
  accounts.Insert(&emily4928);
  accounts.Insert(&jessica4256);
  accounts.Insert(&blair8829);
  accounts.Insert(&fiona6427);
  accounts.Insert(&yvi7891);
  accounts.Insert(&grace1239);
  accounts.Insert(&esther6466);
  accounts.Insert(&heather5858);
  accounts.Insert(&rich1001);
  cout << "All accounts inserted" << endl;
  cout << endl;

  // add existing
  cout << "add existing 1239" << endl;
  Account duplicate1239(1239, Name("dupe", "dupe"));
  cout << "insert dupe: " << accounts.Insert(&duplicate1239) << endl;
  cout << endl;

  // display
  cout << "Displaying accounts" << endl;
  accounts.Display();
  cout << "All account displayed" << endl;
  cout << endl;

  // retrieve test
  Account* retrieve;
  cout << "retrieve true/false: " << accounts.Retrieve(1239, retrieve) << endl;
  cout << "retrieve: " << retrieve << endl;
  cout << "retrieve: " << endl;
  cout << *retrieve << endl;
  cout << endl;

  cout << "retrieve 1049" << endl;
  cout << "retrieve true/false: " << accounts.Retrieve(1049, retrieve) << endl;
  cout << endl;

  //Empty test
  cout << "Is empty: " << accounts.isEmpty() << endl;
  cout << "Empty accounts." << endl;
  accounts.Empty();
  cout << "Is empty: " << accounts.isEmpty() << endl;
  accounts.Display();

  cout << endl;
  cout << "-----------------------------------BSTree CLASS TESTING END" << endl;
  cout << endl;
}

void AccountTest() {
  cout << "ACCOUNT CLASS TESTING BEGIN--------------------------------" << endl;
  cout << endl;

  // constructor
  cout << "CONSTRUCTOR" << endl;
  Account defaulter;
  cout << "default: " << defaulter << endl;

  Transaction jcash("O Cash Johnny 1001");
  Account cash(jcash.get_client_id(), jcash.get_client_name());
  cout << "Transaction jcash: " << jcash << endl;
  cout << "Account cash: " << endl;
  cout << cash << endl;

  Account cash2(cash);
  cout << "copy constr cash2(cash): " << endl;
  cout << cash2;
  cout << endl;

  // get-set
  cout << "GET/SET" << endl;
  cout << "cash id: " << cash.get_client_id() << endl;
  cout << "cash client: " << cash.get_client_name() << endl;
  cout << endl;

  cash2.set_client_id(1005);
  cash2.set_client_name(Name("No", "Cash"));
  cout << "set cash2 to 1005, No Cash: " << endl << cash2;
  cout << endl;

  cout << cash;
  cout << endl;
  Transaction cashtrans1("D 10010 542");
  Transaction cashtrans2("D 10011 1542");
  Transaction cashtrans3("D 10012 5442");
  Transaction cashtrans4("D 10013 7540");
  Transaction cashtrans5("D 10017 5442");
  Transaction cashtrans6("D 10016 7542");
  Transaction cashtrans7("D 10011 1500");
  Transaction cashtrans8("D 10012 5000");
  Transaction cashtrans9("D 10013 7000");
  Transaction cashtrans10("D 10017 6543");
  Transaction cashtrans11("D 10016 7576");
  Transaction cashtrans12("W 10017 1000");
  Transaction cashtrans13("W 10016 65");
  Transaction cashtrans14("W 10010 72");
  Transaction cashtrans15("T 10017 54 10015");
  Transaction cashtrans16("W 10017 20000");
  Transaction cashtrans17("H 1001");
  // depos
  cash.ProcessTransaction(cashtrans1,nullptr);
  cash.ProcessTransaction(cashtrans2, nullptr);
  cash.ProcessTransaction(cashtrans3, nullptr);
  cash.ProcessTransaction(cashtrans4, nullptr);
  cash.ProcessTransaction(cashtrans5, nullptr);
  cash.ProcessTransaction(cashtrans6, nullptr);
  cash.ProcessTransaction(cashtrans7, nullptr);
  cash.ProcessTransaction(cashtrans8, nullptr);
  cash.ProcessTransaction(cashtrans9, nullptr);
  cash.ProcessTransaction(cashtrans10, nullptr);
  cash.ProcessTransaction(cashtrans11, nullptr);
  // withdraws
  cash.ProcessTransaction(cashtrans11, nullptr);
  cash.ProcessTransaction(cashtrans12, nullptr);
  cash.ProcessTransaction(cashtrans13, nullptr);
  cash.ProcessTransaction(cashtrans14, nullptr);
  // transfer
  cash.ProcessTransaction(cashtrans15, nullptr);
  // finish
  cash.ProcessTransaction(cashtrans16, nullptr);
  cash.ProcessTransaction(cashtrans17, nullptr);



  cout << cash << endl;
  cash.PrintAllFundHistory();

  cout << endl;
  cout << "----------------------------------ACCOUNT CLASS TESTING END" << endl;
  cout << endl;
}

void FundTest() {
  cout << "FUND CLASS TESTING BEGIN-----------------------------------" << endl;
  cout << endl;

  // constructor
  cout << "CONSTRUCTOR" << endl;
  Fund default_test;
  cout << "default: " << default_test << endl;
  Fund tester1(2, "Prime Money Market", Name("David", "Bradley"));
  cout << "tester1 2,primemoneymarket,davidbradley: " << tester1 << endl;

  //getter setters
  cout << "getter setter" << endl;
  tester1.set_amount(Money(50));
  cout << "set to 50 bucks, getter: " << tester1.get_amount() << endl;
  cout << "fund name: " << tester1.get_fund_name() << endl;
  cout << "fund_id: " << tester1.get_fund_id() << endl;
  cout << endl;

  //actions
  cout << "ACTIONS" << endl;
  cout << tester1 << endl;
  tester1.Deposit(Money(500));
  cout << "deposit 500 into tester1, tester1: " << tester1 << endl;
  tester1.Withdraw(Money(300));
  cout << "withdraw 300 from tester1, tester1: " << tester1 << endl;
  tester1.Withdraw(Money(500));
  cout << "withdraw 500 from tester1, tester1: " << tester1 << endl;
  cout << endl;

  Transaction depotenk("D 10022 10000");
  Transaction withdraw5k("W 10022 5000");
  cout << "depofive: " << depotenk << endl;
  cout << "withdraw5k: " << withdraw5k << endl;
  tester1.Deposit(Money(10000));
  tester1.StoreTransaction(depotenk);
  tester1.Withdraw(Money(5000));
  tester1.StoreTransaction(withdraw5k);
  cout << tester1 << endl;
  tester1.PrintHistory();

  cout << endl;
  cout << "-------------------------------------FUND CLASS TESTING END" << endl;
  cout << endl;
}

void TransactionTest() {
  cout << "TRANSACTION CLASS TESTING BEGIN----------------------------" << endl;
  cout << endl;

  // constructors
  cout << "constructors" << endl;
  Transaction default_test;
  cout << "default: " << default_test << endl;
  default_test.PrintTransaction();
  cout << endl;
  Transaction johnny("O Cash Johnny 1001");
  cout << "testing O constr, O Cash Johnny 1001: " << johnny << endl;
  johnny.PrintTransaction();
  cout << endl;
  Transaction deposit_johnny("D 10010 542");
  cout << "testing D constr, D 10010 542: " << deposit_johnny << endl;
  deposit_johnny.PrintTransaction();
  cout << endl;
  Transaction withdraw_johnny("W 10016 65");
  cout << "testing W constr, W 10016 65: " << withdraw_johnny << endl;
  withdraw_johnny.PrintTransaction();
  cout << endl;
  Transaction transfer_johnny("T 10016 20 10010");
  cout << "testing T constr, T 10016 20 10010: " << transfer_johnny << endl;
  transfer_johnny.PrintTransaction();
  cout << endl;
  Transaction history_johnny("H 1001");
  cout << "testing H constr, H 1001: " << history_johnny << endl;
  history_johnny.PrintTransaction();
  cout << endl;

  // getters-setter
  cout << "johnny: " << endl;
  johnny.PrintTransaction();
  cout << "get_original_transaction(): " << johnny.get_original_transaction() <<
    endl;
  cout << "get_type(): " << johnny.get_type() << endl;
  cout << "get_client_name(): " << johnny.get_client_name() << endl;
  cout << "get_client_id(): " << johnny.get_client_id() << endl;
  cout << "get_fund_id(): " << johnny.get_fund_id() << endl;
  cout << "get_to_client_id: " << johnny.get_to_client_id() << endl;
  cout << "get_to_fund_id: " << johnny.get_to_fund_id() << endl;
  cout << "get_amount(): " << johnny.get_amount() << endl;
  cout << "setting johnny to A, Bob Saggot, 1412, 5, 8881, 4, 102" << endl;
  johnny.set_type('A');
  johnny.set_client_name(Name("Bob", "Saggot"));
  johnny.set_client_id(1412);
  johnny.set_fund_id(5);
  johnny.set_to_client_id(8881);
  johnny.set_to_fund_id(4);
  johnny.set_amount(Money(102));
  cout << "new johnny: " << endl;
  johnny.PrintTransaction();
  cout << endl;

  cout << "setting johnny to new transaction, W 10010 72" << endl;
  johnny.set_original_transaction("W 10010 72");
  johnny.PrintTransaction();

  cout << "------------------------------TRANSACTION CLASS TESTING END" << endl;
  cout << endl;
}

void NameTest() {
  cout << "NAME--- CLASS TESTING BEGIN--------------------------------" << endl;
  cout << endl;

  // CONSTRUCTORS
  cout << "CONSTRUCTORS" << endl;
  Name plain;
  cout << "default name: " << plain << endl;
  Name joseph("Joseph", "Lan");
  cout << "joseph(Joseph,Lan): " << joseph << endl;
  Name joseph2(joseph);
  cout << "joseph copy const joseph2(joseph): " << joseph2 << endl;
  cout << endl;

  // get-set
  cout << "GET/SET" << endl;
  plain.set_name("Rob", "Dimpsey");
  cout << "plain.set_name(Rob,Dimpsey): " << plain.get_name() << endl;
  cout << "plain.get_first_name(): " << plain.get_first_name() << endl;
  cout << "plain.get_last_name(): " << plain.get_last_name() << endl;
  cout << endl;

  // overloads
  cout << "OVERLOADS" << endl;
  cout << "relational is lastname, first name comparison" << endl;
  Name blake("Blake", "Shelton");
  cout << "blake(Blake,Shelton): " << blake << endl;
  cout << "joseph < blake: " << (joseph < blake) << endl;
  cout << "joseph <= blake: " << (joseph <= blake) << endl;
  cout << "joseph > blake: " << (joseph > blake) << endl;
  cout << "joseph >= blake: " << (joseph >= blake) << endl;
  cout << "joseph == blake: " << (joseph == blake) << endl;
  cout << "joseph !- blake: " << (joseph != blake) << endl;
  cout << "joseph == joseph2" << (joseph == joseph) << endl;
  cout << "&joseph, &joseph2: " << &joseph << ", " << &joseph2 << endl;
  plain = joseph;
  cout << "plain = joseph, plain: " << plain << endl;
  cout << "&joseph, &plain: " << &joseph << ", " << &plain << endl;

  cout << endl;
  cout << "-------------------------------------NAME CLASS TESTING END" << endl;
  cout << endl;
}

void MoneyTest() {
  cout << "MONEY CLASS TESTING BEGIN----------------------------------" << endl;
  cout << endl;

  // constructors
  cout << "CONSTRUCTORS" << endl;
  Money zero;
  cout << "default money: " << zero << endl;
  Money minus5(-5);
  cout << "minus(-5): " << minus5 << endl;
  Money ten(10);
  cout << "Money ten(10): " << ten << endl;
  Money twenty(20);
  cout << "Money twenty(20): " << twenty << endl;
  Money twenty2(twenty);
  cout << "copy const twenty2(twenty): " << twenty2 << endl;
  cout << "Money twenty(20): " << twenty << endl;
  cout << endl;

  // operators
  cout << "OPERATORS + GET/SET" << endl;
  cout << "ten + twenty: " << ten + twenty << endl;
  cout << "ten - twenty: " << ten - twenty << endl;
  cout << "ten: " << ten << endl;
  cout << "twenty: " << twenty << endl;
  cout << "ten += twenty: " << (ten += twenty) << endl;
  cout << "ten: " << ten << endl;
  cout << "twenty: " << twenty << endl;
  cout << "set ten to 10" << endl;
  ten.set_amount(10);
  cout << "getter ten: " << ten.get_amount() << endl;
  cout << "ten < twenty: " << (ten < twenty) << endl;
  cout << "ten <= twenty: " << (ten <= twenty) << endl;
  cout << "ten > twenty: " << (ten > twenty) << endl;
  cout << "ten >= twenty: " << (ten >= twenty) << endl;
  cout << "ten == twenty: " << (ten == twenty) << endl;
  cout << "ten != twenty: " << (ten != twenty) << endl;
  cout << "twenty == twenty2: " << (twenty == twenty2) << endl;
  cout << "twenty != twenty2: " << (twenty != twenty2) << endl;
  cout << "twenty < twenty2: " << (twenty < twenty2) << endl;
  cout << "twenty <= twenty2: " << (twenty <= twenty2) << endl;
  cout << "twenty > twenty2: " << (twenty > twenty2) << endl;
  cout << "twenty >= twenty2: " << (twenty >= twenty2) << endl;
  cout << "-twenty: " << -twenty << endl;
  cout << "-minus5: " << -minus5 << endl;
  twenty2 = ten;
  cout << "twenty2 = ten, twenty2: " << twenty2 << endl;

  cout << endl;
  cout << "------------------------------------MONEY CLASS TESTING END" << endl;
  cout << endl;
}