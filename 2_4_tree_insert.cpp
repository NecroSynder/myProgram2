#include <chrono>
#include <iostream>
#include <random>
#include <vector>

// Define the (2, 4) tree structure here
class TwoFourTree {
private:
  struct Node {
    std::vector<int> keys;
    std::vector<int> values;
    std::vector<Node *> children;
    bool leaf;

    Node(bool isLeaf) : leaf(isLeaf) {}

    // Helper function to find the appropriate child index for the given key
    int findKeyIndex(int key) {
      std::vector<int>::size_type index = 0;
      while (index < keys.size() && keys[index] < key) {
        index++;
      }
      return static_cast<int>(index);
    }
  };

  Node *root;

public:
  TwoFourTree() : root(nullptr) {}

  void insert(int key, int value) {
    if (root == nullptr) {
      root = new Node(true);
      root->keys.push_back(key);
      root->values.push_back(value);
    } else {
      Node *current = root;
      while (!current->leaf) {
        int childIndex = current->findKeyIndex(key);
        current = current->children[childIndex];
      }

      current->keys.push_back(key);
      current->values.push_back(value);
      // Sort keys and values within the leaf node
      int n = current->keys.size();
      for (int i = n - 1; i > 0; i--) {
        if (current->keys[i] < current->keys[i - 1]) {
          std::swap(current->keys[i], current->keys[i - 1]);
          std::swap(current->values[i], current->values[i - 1]);
        } else {
          break;
        }
      }

      // Split the leaf node if it has more than 4 keys
      if (n > 4) {
        splitLeaf(current);
      }
    }
  }

private:
  void splitLeaf(Node *node) {
    Node *newNode = new Node(true);
    int midIndex = node->keys.size() / 2;
    int midKey = node->keys[midIndex];

    // Move keys and values after the middle index to the new node
    for (std::vector<int>::size_type i = midIndex; i < node->keys.size(); i++) {
      newNode->keys.push_back(node->keys[i]);
      newNode->values.push_back(node->values[i]);
    }

    // Erase keys and values after the middle index from the original node
    node->keys.erase(node->keys.begin() + midIndex, node->keys.end());
    node->values.erase(node->values.begin() + midIndex, node->values.end());

    // Insert the new key and new node to the parent
    Node *parent = findParent(node);
    if (parent == nullptr) {
      // If the node is the root, create a new root and set the split nodes as
      // children
      root = new Node(false);
      root->keys.push_back(midKey);
      root->children.push_back(node);
      root->children.push_back(newNode);
    } else {
      int childIndex = parent->findKeyIndex(midKey);
      parent->keys.insert(parent->keys.begin() + childIndex, midKey);
      parent->children.insert(parent->children.begin() + childIndex + 1,
                              newNode);
    }
  }

  Node *findParent(Node *node) { return findParentHelper(root, node); }

  Node *findParentHelper(Node *current, Node *child) {
    if (current == nullptr)
      return nullptr;
    for (Node *c : current->children) {
      if (c == child)
        return current;
      Node *parent = findParentHelper(c, child);
      if (parent != nullptr)
        return parent;
    }
    return nullptr;
  }
};

int main() {
  // Create a (2, 4) tree instance
  TwoFourTree tree;

  // Generate a fixed number of values (1000 in this case)
  int numKeys = 500;

  // Generate random keys and values
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> keyDist(1, 100);
  std::uniform_int_distribution<int> valueDist(1, 1000);

  for (int i = 0; i < numKeys; i++) {
    int key = keyDist(gen);
    int value = valueDist(gen);
    tree.insert(key, value);
  }

  // Measure the time before and after the insertion
  auto start = std::chrono::steady_clock::now();

  // Insert another key-value pair
  int key = keyDist(gen);
  int value = valueDist(gen);
  tree.insert(key, value);

  auto end = std::chrono::steady_clock::now();

  // Calculate the elapsed time in nanoseconds
  auto duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  std::cout << "Elapsed time: " << duration.count() << " nanoseconds" << std::endl;

  return 0;
}