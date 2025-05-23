#ifndef BSTREE_H
#define BSTREE_H

#include <memory>
#include <vector>
#include <utility>

// Узел дерева
template <typename Key, typename Value>
struct BSTNode {
    std::pair<const Key, Value> data;
    std::unique_ptr<BSTNode<Key, Value>> left;
    std::unique_ptr<BSTNode<Key, Value>> right;
    BSTNode<Key, Value>* parent;
    BSTNode<Key, Value>* prev;
    BSTNode<Key, Value>* next;

    BSTNode(const Key& key, const Value& value)
        : data(key, value), parent(nullptr), left(nullptr), right(nullptr), prev(nullptr), next(nullptr) {}
};

// Базовый BSTree: rawInsert + итераторы
template <typename Key, typename Value>
class BSTree {
protected:
    std::unique_ptr<BSTNode<Key, Value>> root;
    BSTNode<Key, Value>* headList = nullptr;
    BSTNode<Key, Value>* tailList = nullptr;

    // "Голая" вставка без обновления списка
    void rawInsert(const Key& key, const Value& value) {
        if (!root) {
            root = std::make_unique<BSTNode<Key, Value>>(key, value);
            return;
        }
        BSTNode<Key, Value>* cur = root.get();
        BSTNode<Key, Value>* parent = nullptr;
        while (cur) {
            parent = cur;
            if (key < cur->data.first)
                cur = cur->left.get();
            else if (key > cur->data.first)
                cur = cur->right.get();
            else {
                cur->data.second = value;
                return;
            }
        }
        auto node = std::make_unique<BSTNode<Key, Value>>(key, value);
        node->parent = parent;
        if (key < parent->data.first)
            parent->left = std::move(node);
        else
            parent->right = std::move(node);
    }

    // In-order обход для списка
    void inOrder(BSTNode<Key, Value>* node, std::vector<BSTNode<Key, Value>*>& vec) {
        if (!node) return;
        inOrder(node->left.get(), vec);
        vec.push_back(node);
        inOrder(node->right.get(), vec);
    }

    BSTNode<Key, Value>* findNode(BSTNode<Key, Value>* node, const Key& key) const {
        if (!node) return nullptr;
        if (key == node->data.first) return node;
        if (key < node->data.first) return findNode(node->left.get(), key);
        return findNode(node->right.get(), key);
    }

public:
    BSTree() = default;

    // Вставка с обновлением итераторов
    virtual void insert(const Key& key, const Value& value) {
        rawInsert(key, value);
        updateIteratorMetadata();
    }

    bool contains(const Key& key) const {
        return findNode(root.get(), key) != nullptr;
    }

    void updateIteratorMetadata() {
        std::vector<BSTNode<Key, Value>*> vec;
        inOrder(root.get(), vec);
        if (vec.empty()) {
            headList = tailList = nullptr;
        } else {
            headList = vec.front();
            tailList = vec.back();
            for (size_t i = 0; i < vec.size(); ++i) {
                vec[i]->prev = i ? vec[i-1] : nullptr;
                vec[i]->next = (i+1<vec.size()) ? vec[i+1] : nullptr;
            }
        }
    }

    // Доступ к корню дерева
    BSTNode<Key, Value>* getRoot() { return root.get(); }
    const BSTNode<Key, Value>* getRoot() const { return root.get(); }

    // Итератор по next
    class Iterator {
        BSTNode<Key, Value>* cur;
    public:
        explicit Iterator(BSTNode<Key, Value>* start) : cur(start) {}
        bool operator!=(const Iterator& o) const { return cur != o.cur; }
        Iterator& operator++() { if (cur) cur = cur->next; return *this; }
        const std::pair<const Key, Value>& operator*() const { return cur->data; }
        const std::pair<const Key, Value>* operator->() const { return &cur->data; }
    };

    Iterator begin() { return Iterator(headList); }
    Iterator end()   { return Iterator(nullptr); }
    const Iterator begin() const { return Iterator(headList); }
    const Iterator end()   const { return Iterator(nullptr); }
};

// BSTMap
template <typename Key, typename Value>
class BSTMap : public BSTree<Key, Value> {
public:
    using BSTree<Key, Value>::insert;  // bring base insert(key,val)
    using BSTree<Key, Value>::contains;
    using BSTree<Key, Value>::getRoot;

    Value& operator[](const Key& key) {
        auto n = this->findNode(this->root.get(), key);
        if (n) return n->data.second;
        this->insert(key, Value());
        n = this->findNode(this->root.get(), key);
        return n->data.second;
    }

    Value operator[](const Key& key) const {
        auto n = this->findNode(this->root.get(), key);
        return n ? n->data.second : Value();
    }

    void insert(const std::pair<const Key, Value>& p) {
        insert(p.first, p.second);
    }
};

// BSTSet
template <typename Key>
class BSTSet : public BSTMap<Key, char> {
public:
    using BSTMap<Key, char>::insert;
    using BSTMap<Key, char>::contains;
    using BSTMap<Key, char>::getRoot;

    void insert(const Key& key) {
        BSTMap<Key, char>::insert(key, '\0');
    }
};

#endif // BSTREE_H
