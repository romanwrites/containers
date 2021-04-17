#pragma once

enum RbTreeColor {
  RED = false,
  BLACK = true
};

class RbTreeNodeBase {
 public:
  typedef RbTreeNodeBase* base_ptr;
  typedef const RbTreeNodeBase* const_base_ptr;

  RbTreeColor color;
  RbTreeNodeBase *parent;
  RbTreeNodeBase *left;
  RbTreeNodeBase *right;
};


//	------------------------------------- RB TREE NODE -----------------------------------------
template<class T>
class RbTreeNode : public RbTreeNodeBase{

 public:
  typedef T value_type;
  typedef RbTreeNodeBase* base_ptr;
  typedef const RbTreeNodeBase* const_base_ptr;

  value_type value;
  RbTreeColor color;
  RbTreeNode *parent;
  RbTreeNode *left;
  RbTreeNode *right;

  RbTreeNode() : color(RbTreeColor::BLACK), parent(nullptr), left(nullptr), right(nullptr) {}

  RbTreeNode(const value_type &value)
      : color(RbTreeColor::BLACK), value(value), left(nullptr), right(nullptr), parent(nullptr) {}

  RbTreeNode(const RbTreeNode &o)
      : color(o.color), value(o.value), left(o.left), right(o.right), parent(o.parent) {}

  RbTreeNode &operator=(const RbTreeNode &o) {
    color = o.color;
    value = o.value;
    left = o.left;
    right = o.right;
    parent = o.parent;
  }

  bool isRed() const {
    return color == RbTreeColor::RED;
  }

  virtual ~RbTreeNode() {}

  static base_ptr minimum(base_ptr x) {
    while (x->left != NULL) {
      x = x->left;
    }
    return x;
  }

  static const_base_ptr minimum(const_base_ptr x) {
    while (x->left != NULL) {
      x = x->left;
    }
    return x;
  }

  static base_ptr maximum(base_ptr x) {
    while (x->right != NULL) {
      x = x->right;
    }
    return x;
  }

  static const_base_ptr maximum(const_base_ptr x) {
    while (x->right != NULL) {
      x = x->right;
    }
    return x;
  }
};


