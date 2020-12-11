/*
 * @file bs_tree.h
 * header file for bs_tree class which is a binary tree that stores bank accounts
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#pragma once

#include "account.h"

using namespace std;

// tree design from assignment + helper methods
class BSTree {
 public:
  // constructors
  BSTree();
  ~BSTree();

  // getters-setters
  // no getters-setters by assignment instructions

  // actions
  bool Insert(Account* account_in);
  bool Retrieve(const int& account_id, Account*& account_found) const;
  void Display() const;
  void Empty();
  bool isEmpty() const;

 private:
  struct Node {
    // initializers for c++11 compatibility
    Node(Account* acct_in, Node* left_in, Node* right_in)
      : pAcct(acct_in), left(right_in), right(right_in) {}

    // default
    Node() : pAcct(nullptr), left(nullptr), right(nullptr) {}

    Account* pAcct;
    Node* left;
    Node* right;
  };
  void DisplayHelper(Node* root) const;
  void EmptyHelper(Node* root);
  Node* root_;
};