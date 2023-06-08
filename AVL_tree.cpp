
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Node {
public:
  int data;
  Node *left;
  Node *right;
  int height;

  Node(int data) : data(data), left(nullptr), right(nullptr), height(1) {}
};

Node *newNode(int data) {
  Node *node = new Node(data);
  return node;
}

int height(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int getBalanceFactor(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return height(node->left) - height(node->right);
}

Node *leftRotation(Node *x) {
  if (x == nullptr || x->right == nullptr) {
    return x;
  }
  Node *y = x->right;
  Node *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;

  return y;
}

Node *rightRotation(Node *y) {
  if (y == nullptr || y->left == nullptr) {
    return y;
  }
  Node *x = y->left;
  Node *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = std::max(height(y->left), height(y->right)) + 1;
  x->height = std::max(height(x->left), height(x->right)) + 1;

  return x;
}

Node *insert(Node *node, int data) {
  if (node == nullptr) {
    node = newNode(data);
    return node;
  } else if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  }

  // Update height of the current node
  node->height = 1 + std::max(height(node->left), height(node->right));

  // Check balance factor and perform rotations if necessary
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (data < node->left->data) {
      return rightRotation(node);
    } else {
      node->left = leftRotation(node->left);
      return rightRotation(node);
    }
  } else if (balanceFactor < -1) {
    if (data > node->right->data) {
      return leftRotation(node);
    } else {
      node->right = rightRotation(node->right);
      return leftRotation(node);
    }
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

Node *findMinNode(Node *node) {
  Node *current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

Node *deleteNode(Node *node, int data) {
  if (node == nullptr) {
    return node;
  } else if (data < node->data) {
    node->left = deleteNode(node->left, data);
  } else if (data > node->data) {
    node->right = deleteNode(node->right, data);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      Node *temp = node->left ? node->left : node->right;
      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
        delete temp;
      }
    } else {
      Node *temp = findMinNode(node->right);
      node->data = temp->data;
      node->right = deleteNode(node->right, temp->data);
    }
  }

  if (node != nullptr) {
    node->height = 1 + std::max(height(node->left), height(node->right));

    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
      if (getBalanceFactor(node->left) >= 0) {
        return rightRotation(node);
      } else {
        node->left = leftRotation(node->left);
        return rightRotation(node);
      }
    } else if (balanceFactor < -1) {
      if (getBalanceFactor(node->right) <= 0) {
        return leftRotation(node);
      } else {
        node->right = rightRotation(node->right);
        return leftRotation(node);
      }
    }
  }

  return node;
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

  return 0;
}
