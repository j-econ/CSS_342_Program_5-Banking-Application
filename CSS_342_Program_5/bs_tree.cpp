/*
 * @file bs_tree.cpp
 * implementation file for bs_tree class
 *
 * @author Joseph Lan
 * @date 06 December 2020
 * CSS 342 B Fall 2020
 * Prof. Dimpsey
 */
#include "bs_tree.h"

// constructors

BSTree::BSTree() : root_(nullptr) {}

BSTree::~BSTree() {
  this->Empty();
}

// actions

bool BSTree::Insert(Account* open) {

  // create the new node to be inserted with input data
  Node* insert = new Node{ open, nullptr, nullptr };
  Node* current = this->root_;
  Node* previous = nullptr; // hold the precursor

  // base cases - empty tree
  if (this->root_ == nullptr) {
    this->root_ = insert;
    return true;
  }

  // traverse until either acct id matches, or reaches a nullptr node
  while (current != nullptr) {

    // if account id already exists
    // delete dynamic memory for node, dynamic memory for open is released in calling
    if (insert->pAcct->get_client_id() == current->pAcct->get_client_id()) {
      delete insert;
      insert = nullptr;
      return false;
    }

    previous = current; // update precursor before moving current

    // if less than client id, go left
    if (insert->pAcct->get_client_id() < current->pAcct->get_client_id()) {
      current = current->left;
    } else {
      current = current->right;
    }
  } // current is nullptr here

  // current is nullptr, previous is where we came from
  if (insert->pAcct->get_client_id() < previous->pAcct->get_client_id()) {
    previous->left = insert;
  } else {
    previous->right = insert;
  }
  return true;
}

bool BSTree::Retrieve(const int& account_id, Account*& account_found) const {
  if (root_ == nullptr) { // base case, tree is empty
    return false;
  }

  Node* current = root_;

  while (current != nullptr) {
    // if current account matches
    if (current->pAcct->get_client_id() == account_id) {
      account_found = current->pAcct;
      return true;
    } else {

      // if not match, go left or right
      if (account_id < current->pAcct->get_client_id()) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
  } // current == nullptr here
  return false;
}

// recursive display, facade function
void BSTree::Display() const {
  if (this->root_ == nullptr) {
    cout << "No accounts." << endl;
    return;
  }
  DisplayHelper(root_);
}

// recursive empty, facade function
void BSTree::Empty() {
  if (this->root_ == nullptr) { // base case, already empty.
    return;
  }
  EmptyHelper(this->root_);
  this->root_ = nullptr;
}

bool BSTree::isEmpty() const {
  if (this->root_ == nullptr) {
    return true;
  } else {
    return false;
  }
}

// private

void BSTree::DisplayHelper(Node* current) const {
  if (current == nullptr) { // do nothing
    return;
  }

  DisplayHelper(current->left);
  cout << *(current->pAcct) << endl;
  DisplayHelper(current->right);
}

void BSTree::EmptyHelper(Node* current) {
  if (current == nullptr) { // do nothing
    return;
  }
  EmptyHelper(current->left);
  EmptyHelper(current->right);
  delete current;
  current = nullptr;
}