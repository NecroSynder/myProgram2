
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Node {
public:
  int data;
  Node *left;
  Node *right;

  Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

Node *newNode(int data) {
  Node *node = new Node(data);
  return node;
}

Node *insert(Node *node, int data) {
  if (node == nullptr) {
    return newNode(data);
  }
  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  }
  return node;
}

bool search(Node *node, int data) {
  if (node == nullptr) {
    return false;
  }
  if (data < node->data) {
    return search(node->left, data);
  } else if (data > node->data) {
    return search(node->right, data);
  }
  return true;
}

Node *minValueNode(Node *node) {
  while (node && node->left != nullptr) {
    node = node->left;
  }
  return node;
}

Node *deleteNode(Node *root, int data) {
  if (root == nullptr) {
    return root;
  }
  if (data < root->data) {
    root->left = deleteNode(root->left, data);
  } else if (data > root->data) {
    root->right = deleteNode(root->right, data);
  } else {
    if (root->left == nullptr) {
      Node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      Node *temp = root->left;
      delete root;
      return temp;
    } else {
      Node *temp = minValueNode(root->right);
      root->data = temp->data;
      root->right = deleteNode(root->right, temp->data);
    }
  }
  return root;
}

int main() {
  srand(time(nullptr));
  Node *root = nullptr;
  int n = 100;

  for (int i = 0; i < n; ++i) {
    root = insert(root, rand() % 100);
  }

  // Measure the runtime of the insert operation
  auto start_insert = std::chrono::high_resolution_clock::now();
  root = insert(root, rand() % 100);
  auto end_insert = std::chrono::high_resolution_clock::now();
  auto duration_insert = std::chrono::duration_cast<std::chrono::nanoseconds>(
      end_insert - start_insert);
  std::cout << "Runtime of insert: " << duration_insert.count()
            << " nanoseconds" << std::endl;

  // Measure the runtime of the search operation
  auto start_search = std::chrono::high_resolution_clock::now();
  search(root, rand() % 100);
  auto end_search = std::chrono::high_resolution_clock::now();
  auto duration_search = std::chrono::duration_cast<std::chrono::nanoseconds>(
      end_search - start_search);
  std::cout << "Runtime of search: " << duration_search.count()
            << " nanoseconds" << std::endl;

  // Measure the runtime of the delete operation
  auto start_delete = std::chrono::high_resolution_clock::now();
  root = deleteNode(root, rand() % 100);
  auto end_delete = std::chrono::high_resolution_clock::now();
  auto duration_delete = std::chrono::duration_cast<std::chrono::nanoseconds>(
      end_delete - start_delete);
  std::cout << "Runtime of delete: " << duration_delete.count()
            << " nanoseconds" << std::endl;

//   auto start_combined = std::chrono::high_resolution_clock::now();
//   for (int i = 0; i < n; ++i) {
//     root = insert(root, rand() % 100);
//     search(root, rand() % 100);
//     root = deleteNode(root, rand() % 100);
//   }
//   auto end_combined = std::chrono::high_resolution_clock::now();
//   auto duration_combined = std::chrono::duration_cast<std::chrono::nanoseconds>(
//       end_combined - start_combined);
//   std::cout << "Combined runtime of insert, search, and delete: "
//             << duration_combined.count() << " nanoseconds" << std::endl;

  return 0;
}
