#pragma once

enum RbTreeColor {
  RED = false,
  BLACK = true
};

class RbTreeNodeBase {
 public:
  typedef RbTreeNodeBase* base_ptr;
  typedef const RbTreeNodeBase* const_base_ptr;

  base_ptr parent;
  base_ptr left;
  base_ptr right;
  RbTreeColor color;

  // Constructors and Coplien --------------------------------------------------------
  RbTreeNodeBase() : parent(NULL), left(NULL), right(NULL), color(BLACK) {
  }

  RbTreeNodeBase(const RbTreeNodeBase &o)
      : parent(o.parent), left(o.left), right(o.right), color(o.color) {
  }
//
//  // Constructors and Coplien --------------------------------------------------------
//  RbTreeNodeBase() : color(BLACK), parent(NULL), left(NULL), right(NULL) {
//  }
//
//  RbTreeNodeBase(const RbTreeNodeBase &o)
//      : color(o.color), parent(o.parent), left(o.left), right(o.right) {
//  }

  virtual ~RbTreeNodeBase() {
  }

  RbTreeNodeBase &operator=(const RbTreeNodeBase &o) {
    this->color = o.color;
    this->left = o.left;
    this->right = o.right;
    this->parent = o.parent;

    return *this;
  }

  // Methods --------------------------------------------------------
  bool isRed() const {
    return this->color == RED;
  }

  // Static methods --------------------------------------------------------
  static base_ptr minimum(base_ptr x, const_base_ptr nil) {
    while (x->left != nil) {
      x = x->left;
    }
    return x;
  }

  static base_ptr maximum(base_ptr x, const_base_ptr nil) {
    while (x->right != nil) {
      x = x->right;
    }
    return x;
  }

  static base_ptr increment(base_ptr x, const_base_ptr nil) {
    if (x->parent == nil && x->left == nil && x->right == nil) {
      x = const_cast<base_ptr>(nil);
      return x;
    }
    if (x == nil) {
      x = nil->left;
      return x;
    }
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

  static const_base_ptr increment(const_base_ptr x, const_base_ptr nil) {
    if (x->parent == nil && x->left == nil && x->right == nil) {
      x = const_cast<base_ptr>(nil);
      return x;
    }
    if (x == nil) {
      x = nil->left;
      return x;
    }
    if (x->right != nil) {
      // find min of right subtree
      x = minimum(x->right, nil);
    } else if (x == nil->right) {
      x = x->right;
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

  static base_ptr decrement(base_ptr x, const_base_ptr nil) {
    if (x == nil) {
      x = nil->right;
      return x;
    }
    if (x->left != nil) {
      base_ptr y = x->left;
      y = maximum(y, nil);
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

  static const_base_ptr decrement(const_base_ptr x, const_base_ptr nil) {
    if (x == nil) {
      x = nil->right;
      return x;
    }
    if (x->left != nil) {
      base_ptr y = x->left;
      y = maximum(y, nil);
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

};

//	------------------------------------- RB TREE NODE -----------------------------------------
template<class T>
class RbTreeNode : public RbTreeNodeBase {

 public:
  typedef T value_type;
  typedef const T const_value_type;

  value_type value;

  value_type *val() {
    return &value;
  }
  const_value_type *val() const {
    return &value;
  }

  // Constructors --------------------------------------------------------
  RbTreeNode() : RbTreeNodeBase() {
  }

  RbTreeNode(const value_type &value) : RbTreeNodeBase(), value(value) {
  }

  RbTreeNode(const RbTreeNode &o) : RbTreeNodeBase(o), value(o.value) {
  }

  RbTreeNode &operator=(const RbTreeNode &o) {
    this->color = o.color;
    this->value = o.value;
    this->left = o.left;
    this->right = o.right;
    this->parent = o.parent;

    return *this;
  }

  virtual ~RbTreeNode() {
  }
};
