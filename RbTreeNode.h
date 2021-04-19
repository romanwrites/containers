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
  base_ptr parent;
  base_ptr left;
  base_ptr right;

  // Constructors and Coplien --------------------------------------------------------
  RbTreeNodeBase() : color(RbTreeColor::BLACK), parent(nullptr), left(nullptr), right(nullptr) {}

  RbTreeNodeBase(const RbTreeNodeBase &o)
      : color(o.color), parent(o.parent), left(o.left), right(o.right) {}

  virtual ~RbTreeNodeBase() {}

  RbTreeNodeBase &operator=(const RbTreeNodeBase &o) {
    this->color = o.color;
    this->left = o.left;
    this->right = o.right;
    this->parent = o.parent;

    return *this;
  }

  // Methods --------------------------------------------------------
  bool isRed() const {
    return this->color == RbTreeColor::RED;
  }

  // Static methods --------------------------------------------------------
  static base_ptr minimum(base_ptr x, const_base_ptr nil) {
    while (x->left != nil) {
      x = x->left;
    }
    return x;
  }

//  static const_base_ptr minimum(const_base_ptr x) {
//    while (x->left != NULL) {
//      x = x->left;
//    }
//    return x;
//  }

  static base_ptr maximum(base_ptr x, const_base_ptr nil) {
    while (x->right != nil) {
      x = x->right;
    }
    return x;
  }

//  static const_base_ptr maximum(const_base_ptr x, ) {
//    while (x->right != nil) {
//      x = x->right;
//    }
//    return x;
//  }

  static base_ptr increment(base_ptr x, const_base_ptr nil) throw() {
    if (x->right != nil) {
      // find min of right subtree
      x = minimum(x->right, nil);
    } else {
      base_ptr y = x->parent;
      while (x == y->right) {
        x = y;
        y = y->parent;
      }
      if (x->right != y) {
        x = y;
      }
    }
    return x;
  }

//  base_ptr increment(base_ptr x) throw() {
//    return local_increment(x);
//  }
//
//  const_base_ptr increment(const_base_ptr x) throw() {
//    return local_increment(const_cast<base_ptr >(x));
//  }

  static base_ptr decrement(base_ptr x, const_base_ptr nil) throw() {
//    if (x->isRed() && x->parent->parent == x) {
//      x = x->right;
//    } // todo wtf?
//    else if (x->left != nil) {
    if (x->left != nil) {
      base_ptr y = x->left;
      y = maximum(y, nil);
//      while (y->right != nil) {
//        y = y->right;
//      }
      x = y;
    } else {
      base_ptr y = x->parent;
      while (x == y->left) {
        x = y;
        y = y->parent;
      }
      x = y;
    }
    return x;
  }

//  base_ptr decrement(base_ptr x) throw() {
//    return local_decrement(x);
//  }
//
//  const_base_ptr decrement(const_base_ptr x) throw() {
//    return local_decrement(const_cast<base_ptr>(x));
//  }

};

//	------------------------------------- RB TREE NODE -----------------------------------------
template<class T>
class RbTreeNode : public RbTreeNodeBase {

 public:
  typedef T value_type;

  value_type value;

  // Constructors --------------------------------------------------------
  RbTreeNode() : RbTreeNodeBase(), value(NULL) {}

  RbTreeNode(const value_type &value) : RbTreeNodeBase(), value(value) {}

  RbTreeNode(const RbTreeNode &o) : RbTreeNodeBase(o), value(o.value) {}

  RbTreeNode &operator=(const RbTreeNode &o) {
    this->color = o.color;
    this->value = o.value;
    this->left = o.left;
    this->right = o.right;
    this->parent = o.parent;

    return *this;
  }

  virtual ~RbTreeNode() {}
};
