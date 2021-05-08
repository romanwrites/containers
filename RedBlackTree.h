#pragma once

#include "RbTreeIterator.h"
#include "Allocator.h"
#include "Compare.h"
#include "ReverseIterator.h"
#include "Functional.h"
#include "Algorithm.h"
#include "Compare.h"

#define PRINT_INT_TREE 1

namespace ft {

enum Uniqueness {
  UNIQUE = true,
  NOT_UNIQUE = false
};

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc = ft::Allocator<Val> >
class RbTree {
 public:
  typedef RbTreeNodeBase *base_ptr;
  typedef const RbTreeNodeBase *const_base_ptr;
  typedef RbTreeNode<Val> *link_type;
  typedef const RbTreeNode<Val> *const_link_type;
  typedef typename Alloc::template rebind<RbTreeNode<Val> >::other node_allocator_type;
  typedef typename Alloc::template rebind<RbTreeNodeBase>::other node_base_allocator_type;
  typedef Key key_type;
  typedef Val value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef Alloc allocator_type;
  typedef RbTreeNode<Val> Node;
  typedef Compare key_compare;
  typedef RbTreeIterator<Val> iterator;
  typedef RbTreeConstIterator<Val> const_iterator;
  typedef ReverseIterator<iterator> reverse_iterator;
  typedef ReverseIterator<const_iterator> const_reverse_iterator;

 private:
  Uniqueness isUniqueTree;
  key_compare comp;
  node_allocator_type nodeAllocator;
  allocator_type allocator;
  node_base_allocator_type baseAllocator;
  Node *root;
  Node *nil;
  size_type currentSize;

  bool isUnique() const {
    return isUniqueTree == UNIQUE;
  }

 public:

  explicit RbTree(Uniqueness uniqueTree = UNIQUE,
                  const key_compare &comp = key_compare(),
                  const allocator_type &alloc = allocator_type())
      : isUniqueTree(uniqueTree),
        comp(comp),
        nodeAllocator(alloc),
        allocator(alloc),
        baseAllocator(alloc),
        root(NULL),
        nil(NULL), // maybe call static method, but how to pass nodeAllocator
        currentSize(0) {
    nil = createNilNode();
    root = nil;
  }

  RbTree(const RbTree &x) {
    operator=(x);
  }

  RbTree &operator=(const RbTree &x) {
    if (this != &x) {
      clear();
      this->comp = x.comp;
      this->nodeAllocator = x.nodeAllocator;
      this->allocator = x.allocator;
      this->baseAllocator = x.baseAllocator;
      this->currentSize = 0;
      insert(x.begin(), x.end());
    }
    return *this;
  }

  ~RbTree() {
    clear();
    nodeAllocator.deallocate(nil, 1);
  }

 public:
  size_type count(const key_type &k) const {
    if (isUnique()) {
      if (find(k).node != nil) {
        return 1;
      }
      return 0;
    }

    size_type i = 0;
    for (auto it = begin(); it != end(); ++it) {
      if (KeyOfValue()(*it) == k) {
        ++i;
      }
    }
    return i;
  }

  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    while (first != last) {
      insert(*first);
      ++first;
    }
  }

  iterator insert(iterator position, const value_type &val) {
    (void) position;
    return insert(val).first;
  }

  std::pair<iterator, bool> insert(value_type val) {
    if (root == nil) {
      root = createNode(nil, val);
      return insertNilNodeWrapper(root);
    } else {
      Node *node = root;

      while (node != nil) {
        if (comp(KeyOfValue()(val), KeyOfValue()(node->value))) {
          if (node->left != nil) {
            node = reinterpret_cast<Node *>(node->left);
          } else {
            node->left = createNode(node, val);
            return insertNilNodeWrapper(node->left);
          }
        } else if (isUnique() && !comp(KeyOfValue()(node->value), KeyOfValue()(val))) {
          return std::make_pair(iterator(node, nil), false);
        } else {
          if (node->right != nil) {
            node = reinterpret_cast<Node *>(node->right);
          } else {
            node->right = createNode(node, val);
            return insertNilNodeWrapper(node->right);
          }
        }
      }
    }
    std::cout
        << "LOOK HERE!!!!!!!! HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        << std::endl;
    return std::make_pair(iterator(nil, nil), false);
  }

  void transplant(base_ptr treeWhereToPlace, base_ptr treeToPlace) {
    if (treeWhereToPlace->parent == nil) {  // u is root
      root = reinterpret_cast<Node *>(treeToPlace);
    } else if (treeWhereToPlace == treeWhereToPlace->parent->left) { // u is left child
      treeWhereToPlace->parent->left = treeToPlace;
    } else { // u is right child
      treeWhereToPlace->parent->right = treeToPlace;
    }

    treeToPlace->parent = treeWhereToPlace->parent;
  }

  bool empty() const {
    return currentSize == 0;
  }

  size_type size() const {
    return currentSize;
  }

  size_type max_size() const {
    // using my Allocator:
    return nodeAllocator.max_size();
  }

  allocator_type get_allocator() const {
    return allocator_type();
  }

  void erase(iterator position) {
    removeNode(reinterpret_cast<Node *>(position.node));
  }

  size_type erase(const key_type &k) {
    size_type i = 0;

    for (iterator it = find(k); it.node != nil; it = find(k)) {
      erase(it);
      i++;
    }

    return i;
  }

  void erase(iterator first, iterator last) {
    while (first != last) {
      iterator tmp = first;
      ++first;
      erase(tmp);
    }
  }

  // ITERATORS ----------------------------------------------------------------------
  const_iterator begin() const {
    return const_iterator(reinterpret_cast<Node *>(nil->left), nil);
  }

  iterator begin() {
    return iterator(reinterpret_cast<Node *>(nil->left), nil);
  }

  iterator end() {
    return iterator(reinterpret_cast<Node *>(nil), nil);
  }

  const_iterator end() const {
    return const_iterator(reinterpret_cast<Node *>(nil), nil);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  iterator findNode(const key_type &key) const {
    Node *node;

    for (node = root; node != nil && KeyOfValue()(node->value) != key;) {
      if (comp(key, KeyOfValue()(node->value))) {
        node = reinterpret_cast<Node *>(node->left);
      } else {
        node = reinterpret_cast<Node *>(node->right);
      }
    }

    return iterator(node, nil);
  }

  iterator find(const key_type &key) {
    return findNode(key);
  }

  const_iterator find(const key_type &k) const {
    return const_iterator(findNode(k));
  }

  void clear() {
    erase(begin(), end());
    root = nil;
    nil->left = nil;
    nil->right = nil;
  }

  key_compare key_comp() const {
    return comp;
  }

  iterator lower_bound(const key_type &k) {
    iterator it = begin();

    for (; it != end(); ++it) {
      if (!(comp(KeyOfValue()(*it), k))) {
        break;
      }
    }
    return it;
  }

  const_iterator lower_bound(const key_type &k) const {
    const_iterator it = begin();

    for (; it != end(); ++it) {
      if (!(comp(KeyOfValue()(*it), k))) {
        break;
      }
    }
    return it;
  }

  iterator upper_bound(const key_type &k) {
    iterator it = begin();

    for (; it != end(); ++it) {
      if (comp(k, KeyOfValue()(*it))) {
        break;
      }
    }
    return it;
  }

  const_iterator upper_bound(const key_type &k) const {
    const_iterator it = begin();

    for (; it != end(); ++it) {
      if (comp(k, KeyOfValue()(*it))) {
        break;
      }
    }
    return it;
  }

  std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
    return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
  }

  std::pair<iterator, iterator> equal_range(const key_type &k) {
    return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
  }

 private:

  Node *createNode(Node *parent, value_type val) {
    Node *node = nodeAllocator.allocate(1);

    // Constructing NODE BASE is needed because of inheritance
    // efficient method. calling only copy constructor
    baseAllocator.construct(node, *node);
    // inefficient method
    // nodeAllocator.construct(node, Node(val));

    allocator.construct(&(node->value), val);
    node->color = RED;
    node->left = nil;
    node->right = nil;
    node->parent = parent;

    return node;
  }

  Node *createNilNode() {
    Node *node = nodeAllocator.allocate(1);

    node->color = BLACK;
    node->left = node;
    node->right = node;
    node->parent = node;

    return node;
  }

  void destroyNode(Node *node) {
    nodeAllocator.destroy(node);
    nodeAllocator.deallocate(node, 1);
  }

  void leftRotate(base_ptr x) {
    base_ptr y = x->right;
    x->right = y->left;
    if (y->left != nil) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) { //x is root
      root = reinterpret_cast<Node *>(y);
    } else if (x == x->parent->left) { //x is left child
      x->parent->left = y;
    } else { //x is right child
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(base_ptr x) {
    base_ptr y = x->left;
    x->left = y->right;
    if (y->right != nil) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) { //x is root
      root = reinterpret_cast<Node *>(y);
    } else if (x == x->parent->right) { //x is left child
      x->parent->right = y;
    } else { //x is right child
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

//  https://www.codesdope.com/course/data-structures-red-black-trees-insertion/
  void insertionFixup(base_ptr z) {
    while (z->parent->isRed()) {
      if (z->parent == z->parent->parent->left) { //z.parent is the left child

        base_ptr y = z->parent->parent->right; //uncle of z

        if (y->isRed()) { //case 1
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else { //case2 or case3
          if (z == z->parent->right) { //case2
            z = z->parent; //marked z.parent as new z
            leftRotate(z);
          }
          //case3
          z->parent->color = BLACK; //made parent black
          z->parent->parent->color = RED; //made parent red
          rightRotate(z->parent->parent);
        }
      } else { //z.parent is the right child
        base_ptr y = z->parent->parent->left; //uncle of z

        if (y->isRed()) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent; //marked z.parent as new z
            rightRotate(z);
          }
          z->parent->color = BLACK; //made parent black
          z->parent->parent->color = RED; //made parent red
          leftRotate(z->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

//  https://www.codesdope.com/course/data-structures-red-black-trees-deletion/
  void deletionFixup(base_ptr x) {
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        base_ptr w = x->parent->right;
        if (w->isRed()) {
          w->color = BLACK;
          x->parent->color = RED;
          leftRotate(x->parent);
          w = x->parent->right;
        }
        if (!w->left->isRed() && !w->right->isRed()) {
          w->color = RED;
          x = x->parent;
        } else {
          if (!w->right->isRed()) {
            w->left->color = BLACK;
            w->color = RED;
            rightRotate(w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->right->color = BLACK;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        base_ptr w = x->parent->left;
        if (w->isRed()) {
          w->color = BLACK;
          x->parent->color = RED;
          rightRotate(x->parent);
          w = x->parent->left;
        }
        if (!w->right->isRed() && !w->left->isRed()) {
          w->color = RED;
          x = x->parent;
        } else {
          if (!w->left->isRed()) {
            w->right->color = BLACK;
            w->color = RED;
            leftRotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->left->color = BLACK;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = BLACK;
  }

  void fixNilLeftRightDelete(base_ptr nodeToDelete) {
    if (nodeToDelete == nil->left) {
      iterator it = begin();
      ++it;
      nil->left = it.node;
    }
    if (nodeToDelete == nil->right) {
      iterator it = iterator(nodeToDelete, nil);
      --it;
      nil->right = it.node;
    }
  }

  void removeNode(base_ptr nodeToDelete) {
    base_ptr y = nodeToDelete;
    base_ptr x;
    RbTreeColor yOriginalColor = y->color;

    fixNilLeftRightDelete(nodeToDelete);

    if (nodeToDelete->left == nil) {
      x = nodeToDelete->right;
      transplant(nodeToDelete, reinterpret_cast<Node *>(nodeToDelete->right));
    } else if (nodeToDelete->right == nil) {
      x = nodeToDelete->left;
      transplant(nodeToDelete, reinterpret_cast<Node *>(nodeToDelete->left));
    } else {
      y = RbTreeNodeBase::minimum(reinterpret_cast<base_ptr>(nodeToDelete->right),
                                  reinterpret_cast<const_base_ptr>(nil)); //minimum element in right subtree
      yOriginalColor = y->color;
      x = y->right;
      if (y->parent == nodeToDelete) {
        x->parent = y;
      } else {
        transplant(y, y->right);
        y->right = nodeToDelete->right;
        y->right->parent = y;
      }
      transplant(nodeToDelete, y);
      y->left = nodeToDelete->left;
      y->left->parent = y;
      y->color = nodeToDelete->color;
    }

    if (yOriginalColor == BLACK) {
      deletionFixup(x);
    }

    if (nodeToDelete != nil) {
      destroyNode(reinterpret_cast<Node *>(nodeToDelete));
    }
    currentSize--;
  }

  void fixNilLeftRightInsert(base_ptr node) {
    Node *nodeNode = reinterpret_cast<Node *>(node);
    Node *nilLeft = reinterpret_cast<Node *>(nil->left);
    Node *nilRight = reinterpret_cast<Node *>(nil->right);

    if (nil->left != nil &&
        (comp(KeyOfValue()(nodeNode->value), KeyOfValue()(nilLeft->value))
            || KeyOfValue()(nodeNode->value) == KeyOfValue()(nilLeft->value))) {
      if (!isUnique()) {
        nil->left = RbTreeNodeBase::minimum(root, nil);
      } else {
        nil->left = node;
      }
    }
    if (nil->left != nil &&
        (comp(KeyOfValue()(nilRight->value), KeyOfValue()(nodeNode->value))
            || KeyOfValue()(nilRight->value) == KeyOfValue()(nodeNode->value))) {
      if (!isUnique()) {
        nil->right = RbTreeNodeBase::maximum(root, nil);
      } else {
        nil->right = node;
      }
    }
  }

  std::pair<iterator, bool> insertNilNodeWrapper(base_ptr node) {
    fixNilLeftRightInsert(node);

    // root node case
    if (nil->left == nil) {
      nil->left = node;
    }
    if (nil->right == nil) {
      nil->right = node;
    }

    insertionFixup(node);

    currentSize++;
    return std::make_pair(iterator(node, nil), true);
  }

  friend bool operator==(const RbTree &x, const RbTree &y) {
    return x.size() == y.size()
        && ft::equal<iterator, iterator, ft::equal_to<value_type> >(x.begin(), x.end(), y.begin());
  }

  friend bool operator<(const RbTree &x, const RbTree &y) {
    return ft::lexicographical_compare<iterator, Compare>(x.begin(), x.end(),
                                                          y.begin(), y.end());
  }

  friend bool operator!=(const RbTree &x, const RbTree &y) { return !(x == y); }

  friend bool operator>(const RbTree &x, const RbTree &y) { return y < x; }

  friend bool operator<=(const RbTree &x, const RbTree &y) { return !(y < x); }

  friend bool operator>=(const RbTree &x, const RbTree &y) { return !(x < y); }

#if PRINT_INT_TREE
// -------------------------------------------- PRINT INTEGER TREE ------------------------------------
 private:
  void fillAppend(Node *tree,
                  bool isRight,
                  std::string &appendLeft,
                  std::string &appendRight) const {
    std::string valStr = std::to_string(KeyOfValue()(tree->value));

    if (isRight) {
      if (tree->parent != nil) {
        appendLeft += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendLeft += std::string(valStr.length(), ' ');
      }
      appendRight += std::string(valStr.length(), ' ');
    } else {
      appendLeft += std::string(valStr.length(), ' ');
      if (tree->parent != nil) {
        appendRight += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendRight += std::string(valStr.length(), ' ');
      }
    }
  }

  std::string print(Node *tree, std::string space, bool isRight) const {
    if (tree == nil) {
      return "";
    }
    if (tree->parent != nil && tree->parent->parent != nil) {
      space += " ";
    }
    std::string ret;

    std::string appendLeft;
    std::string appendRight;
    fillAppend(tree, isRight, appendLeft, appendRight);

    if (tree->right != nil) {
      ret += print(reinterpret_cast<Node *>(tree->right), space + appendRight, true);
    }

    ret += space;
    if (tree->parent != nil) {
      if (tree->parent->right == tree) {
        ret += "┌";
      } else {
        ret += "└";
      }
    }
    if (tree->isRed()) {
      ret += std::string(RED_BG_SET + std::to_string(KeyOfValue()(tree->value)) + RESET);
    } else {
      ret += std::string(BLACK_BG_SET + std::to_string(KeyOfValue()(tree->value)) + RESET);
    }

    if (tree->left != nil && tree->right != nil) {
      ret += "┤";
    } else if (tree->left == nil && tree->right != nil) {
      ret += "┘";
    } else if (tree->right == nil && tree->left != nil) {
      ret += "┐";
    }
    ret += "\n";

    if (tree->left != nil) {
      ret += print(reinterpret_cast<Node *>(tree->left), space + appendLeft, false);
    }
    return ret;
  }

 public:
  void printIntTree() const {
    if (root != NULL && root != nil) {
      std::cout << print(root, "", true);
    }
  }
#endif
};

}
