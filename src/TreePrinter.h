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
    RbTreeColor color;
    Node() {}


    Node(int const value) : value(value), parent(NULL), left(NULL), right(NULL), color(RED) {}
  };

  Node *root;

  void fillAppend(Node *tree,
                  bool isRight,
                  std::string &appendLeft,
                  std::string &appendRight) const {
    std::string valStr = std::string(std::to_string(tree->value));

    if (isRight) {
      if (tree->parent != NULL) {
        appendLeft += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendLeft += std::string(valStr.length(), ' ');
      }
      appendRight += std::string(valStr.length(), ' ');
    } else {
      appendLeft += std::string(valStr.length(), ' ');
      if (tree->parent != NULL) {
        appendRight += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendRight += std::string(valStr.length(), ' ');
      }
    }
  }

  std::string print(Node *tree, std::string space, bool isRight) const {
    if (tree == NULL) {
      return "";
    }
    if (tree->parent != NULL && tree->parent->parent != NULL) {
      space += " ";
    }
    std::string ret;

    std::string appendLeft;
    std::string appendRight;
    fillAppend(tree, isRight, appendLeft, appendRight);

    if (tree->right != NULL) {
      ret += print(tree->right, space + appendRight, true);
    }

    ret += space;
    if (tree->parent != NULL) {
      if (tree->parent->right == tree) {
        ret += "┌";
      } else {
        ret += "└";
      }
    }
    if (tree->color == RED) {
      ret += std::string(RED_BG_SET + std::to_string(tree->value) + RESET);
    } else {
      ret += std::string(BLACK_BG_SET + std::to_string(tree->value) + RESET);
    }

    if (tree->left != NULL && tree->right != NULL) {
      ret += "┤";
    } else if (tree->left == NULL && tree->right != NULL) {
      ret += "┘";
    } else if (tree->right == NULL && tree->left != NULL) {
      ret += "┐";
    }
    ret += "\n";

    if (tree->left != NULL) {
      ret += print(tree->left, space + appendLeft, false);
    }
    return ret;
  }

  Node *addRecursive(Node *tree, int value) {
    if (tree == NULL) {
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
    if (root != NULL) {
      std::cout << print(root, "", true);
    }
  }

  void add(int i) {
    root = addRecursive(root, i);
  }

  TreePrinter() : root(NULL){}

};
}
