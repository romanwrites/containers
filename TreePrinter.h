#pragma once

namespace ft {

class TreePrinter {

 private:
  class Node {
   public:
    int value;
    Node *parent;
    Node *left;
    Node *right;
    RedBlackTreeColor color;
    Node() {}


    Node(int const value) : value(value), parent(nullptr), left(nullptr), right(nullptr), color(RedBlackTreeColor::RED) {}
  };

  Node *root;

  void fillAppend(Node *tree,
                  bool isRight,
                  std::string &appendLeft,
                  std::string &appendRight) const {
    std::string valStr = std::string(std::to_string(tree->value));

    if (isRight) {
      if (tree->parent != nullptr) {
        appendLeft += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendLeft += std::string(valStr.length(), ' ');
      }
      appendRight += std::string(valStr.length(), ' ');
    } else {
      appendLeft += std::string(valStr.length(), ' ');
      if (tree->parent != nullptr) {
        appendRight += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendRight += std::string(valStr.length(), ' ');
      }
    }
  }

  std::string print(Node *tree, std::string space, bool isRight) const {
    if (tree == nullptr) {
      return "";
    }
    if (tree->parent != nullptr && tree->parent->parent != nullptr) {
      space += " ";
    }
    std::string ret;

    std::string appendLeft;
    std::string appendRight;
    fillAppend(tree, isRight, appendLeft, appendRight);

    if (tree->right != nullptr) {
      ret += print(tree->right, space + appendRight, true);
    }

    ret += space;
    if (tree->parent != nullptr) {
      if (tree->parent->right == tree) {
        ret += "┌";
      } else {
        ret += "└";
      }
    }
    if (tree->color == RedBlackTreeColor::RED) {
      ret += std::string(RED_BG_SET + std::to_string(tree->value) + RESET);
    } else {
      ret += std::string(BLACK_BG_SET + std::to_string(tree->value) + RESET);
    }

    if (tree->left != nullptr && tree->right != nullptr) {
      ret += "┤";
    } else if (tree->left == nullptr && tree->right != nullptr) {
      ret += "┘";
    } else if (tree->right == nullptr && tree->left != nullptr) {
      ret += "┐";
    }
    ret += "\n";

    if (tree->left != nullptr) {
      ret += print(tree->left, space + appendLeft, false);
    }
    return ret;
  }

  Node *addRecursive(Node *tree, int value) {
    if (tree == nullptr) {
      return new Node(value);
    }

    if (value < tree->value) {
      tree->right = addRecursive(tree->right, value);
      tree->right->parent = tree;
    } else if (value > tree->value) {
      tree->left = addRecursive(tree->left, value);
      tree->left->parent = tree;
    } else {
      return tree;
    }

    return tree;
  }

 public:
  void printTree() const {
    if (root != nullptr) {
      std::cout << print(root, "", true);
    }
  }

  void add(int i) {
    root = addRecursive(root, i);
  }

  TreePrinter() : root(nullptr){}

};
}
