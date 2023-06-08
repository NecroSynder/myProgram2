#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>


struct Node {
  std::vector<int> keys;
  std::vector<Node*> children;
  bool leaf;

  Node(bool is_leaf) : leaf(is_leaf) {}

  bool isFull() const {
    return keys.size() == 3;
  }
};

// Function to search for a key in the (2, 4) tree
bool search_operation(Node* node, int key) {
  if (node == nullptr)
    return false;

  int i = 0;
  while (i < node->keys.size() && key > node->keys[i])
    i++;

  if (i < node->keys.size() && node->keys[i] == key)
    return true;

  if (node->leaf)
    return false;

  return search_operation(node->children[i], key);
}

void split_child(Node* parent, int child_index) {
  Node* child = parent->children[child_index];
  Node* new_node = new Node(child->leaf);

  for (int i = 2; i < child->keys.size(); i++) {
    new_node->keys.push_back(child->keys[i]);
  }

  if (!child->leaf) {
    for (int i = 2; i < child->children.size(); i++) {
      new_node->children.push_back(child->children[i]);
    }
  }

  child->keys.resize(2);
  child->children.resize(3);

  parent->keys.insert(parent->keys.begin() + child_index, child->keys[1]);
  parent->children.insert(parent->children.begin() + child_index + 1, new_node);
}

void insert_operation(Node*& node, int key) {
  if (node == nullptr) {
    node = new Node(true);
    node->keys.push_back(key);
    return;
  }

  if (node->leaf) {
    node->keys.push_back(key);
    std::sort(node->keys.begin(), node->keys.end());

    if (node->isFull()) {
      // Split the leaf node if it is already full
      Node* new_node = new Node(true);

      for (int i = 2; i < node->keys.size(); i++) {
        new_node->keys.push_back(node->keys[i]);
      }

      node->keys.resize(2);

      new_node->leaf = true;
      node->leaf = true;

      node->children.push_back(new_node);
    }
  } else {
    int i = 0;
    while (i < node->keys.size() && key > node->keys[i])
      i++;

    insert_operation(node->children[i], key);

    if (node->children[i]->isFull()) {
      // Split the child node if it is already full
      split_child(node, i);
    }
  }
}

void print_tree_helper(Node* node, int depth) {
  if (node == nullptr) {
    return;
  }

  for (int i = 0; i < node->keys.size(); i++) {
    std::cout << std::string(depth * 2, ' ') << node->keys[i] << std::endl;
  }

  if (!node->leaf) {
    for (int i = 0; i < node->children.size(); i++) {
      print_tree_helper(node->children[i], depth + 1);
    }
  }
}

void print_tree(Node* root) {
  print_tree_helper(root, 0);
}

int main() {
  int num_values = 100000000; // Change this value to generate a different number of values

  // Generate random keys using the C++ random library
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 1000);

  std::vector<int> keys(num_values);
  for (int i = 0; i < num_values; i++) {
    keys[i] = dis(gen);
  }

  // Build the (2, 4) tree
  Node* root = nullptr;

  for (int key : keys) {
    // Perform the insert operation to build the tree
    insert_operation(root, key);
  }

  // Measure the runtime of the search operation in nanoseconds
  auto start = std::chrono::high_resolution_clock::now();

  for (int key : keys) {
    // Perform the search operation using the (2, 4) tree
    bool result = search_operation(root, key);
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Runtime in nanoseconds: " << duration.count() << " ns" << std::endl;

  // Print the tree structure
  // print_tree(root);

  return 0;
}
