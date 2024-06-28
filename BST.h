#pragma once
#ifndef _BST_HPP_
#define _BST_HPP_
#include <iostream>
#include <queue>
#include <functional>
#include <string>

namespace dby
{
    enum class bst_traverse
    {
        pre_order,
        in_order,
        post_order,
        level_order
    };

    template <class T>
    class BST
    {
        struct Node
        {
            T value;
            Node* left;
            Node* right;
            Node(T value, Node* left = nullptr, Node* right = nullptr) : value(value), left(left), right(right) { }
            ~Node() { }
        };

        Node* root;
        std::function<bool(T, T)> compare;
        std::function<bool(T, T)> equals;

    public:
        BST()
        {
            this->root = nullptr;
            this->compare = [](T a, T b) { return a.first < b.first; };
            this->equals = [](T a, T b) { return a.first == b.first; };
        }

        BST(std::function<bool(T, T)> compare, std::function<bool(T, T)> equals)
        {
            this->root = nullptr;
            this->compare = compare;
            this->equals = equals;
        }

        ~BST()
        {
            this->_destroy_tree(this->root);
        }

        void traverse_descending(std::function<void(T)> doThis)
        {
            this->_in_order_desc(this->root, doThis);
        }

        /* CAPACITY METHODS */

        std::size_t height()
        {
            std::size_t h = this->_height(this->root);
            return h - (h != 0);
        }

        std::size_t count_nodes()
        {
            return this->_count_nodes(this->root);
        }

        /* ACCESS METHODS */

        T* lowest_element()
        {
            if (this->root == nullptr)
            {
                return nullptr;
            }

            Node* it = this->root;

            while (it->left != nullptr)
            {
                it = it->left;
            }

            return &it->value;
        }

        T* highest_element()
        {
            if (this->root == nullptr)
            {
                return nullptr;
            }

            Node* it = this->root;

            while (it->right != nullptr)
            {
                it = it->right;
            }

            return &it->value;
        }

        T* find(int key)
        {
            Node* result = this->_find(root, key);
            return result ? &result->value : nullptr;
        }

        /* MODIFIER METHODS */

        void insert(T value)
        {
            if (this->root == nullptr)
            {
                this->root = new Node(value);
                return;
            }
            this->_insert(this->root, value);
        }

        bool remove(int key)
        {
            return this->_remove(this->root, key);
        }

        void destroy_tree()
        {
            this->_destroy_tree(this->root);
        }

        /* DECLARATIVE METHODS */

        void traverse(bst_traverse type, std::function<void(T)> doThis)
        {
            switch (type)
            {
            case bst_traverse::pre_order: this->_pre_order(this->root, doThis); break;
            case bst_traverse::in_order: this->_in_order(this->root, doThis); break;
            case bst_traverse::post_order: this->_post_order(this->root, doThis); break;
            case bst_traverse::level_order: this->_level_order(this->root, doThis);
            }
        }

        std::size_t count_if(std::function<bool(T)> condition)
        {
            return this->_count_if(root, condition);
        }

        bool search(int key)
        {
            return this->_search(root, key);
        }

    private:
        std::size_t _height(Node* node)
        {
            if (node == nullptr)
            {
                return 0;
            }

            return max(this->_height(node->left), this->_height(node->right)) + 1;
        }

        void _in_order_desc(Node* node, std::function<void(T)>& doThis)
        {
            if (node == nullptr)
            {
                return;
            }

            this->_in_order_desc(node->right, doThis);
            doThis(node->value);
            this->_in_order_desc(node->left, doThis);
        }

        bool _remove(Node*& node, int key)
        {
            if (node == nullptr)
            {
                return false;
            }

            if (key < node->value.first)
            {
                return this->_remove(node->left, key);
            }

            if (key > node->value.first)
            {
                return this->_remove(node->right, key);
            }

            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
                return true;
            }

            if (node->left == nullptr)
            {
                Node* tmp = node;
                node = node->right;
                delete tmp;
                return true;
            }

            if (node->right == nullptr)
            {
                Node* tmp = node;
                node = node->left;
                delete tmp;
                return true;
            }

            Node* next = this->_successor(node);
            node->value = next->value;
            return this->_remove(root->right, next->value.first);
        }

        Node* _successor(Node* node)
        {
            Node* current = node->right;
            while (current && current->left)
            {
                current = current->left;
            }
            return current;
        }

        bool _search(Node* node, int key)
        {
            if (node == nullptr)
            {
                return false;
            }

            if (node->value.first == key)
            {
                return true;
            }

            if (key < node->value.first)
            {
                return this->_search(node->left, key);
            }

            return this->_search(node->right, key);
        }

        std::size_t _count_nodes(Node* node)
        {
            if (node == nullptr)
            {
                return 0;
            }

            return 1 + this->_count_nodes(node->left) + this->_count_nodes(node->right);
        }

        std::size_t _count_if(Node* node, std::function<bool(T)>& condition)
        {
            if (node == nullptr)
            {
                return 0;
            }

            return condition(node->value) + this->_count_if(node->left, condition) + this->_count_if(node->right, condition);
        }

        void _destroy_tree(Node* node)
        {
            if (node == nullptr)
            {
                return;
            }
            this->_destroy_tree(node->left);
            this->_destroy_tree(node->right);
            delete node;
        }

        Node* _find(Node* node, int key)
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            if (node->value.first == key)
            {
                return node;
            }

            if (key < node->value.first)
            {
                return this->_find(node->left, key);
            }

            return this->_find(node->right, key);
        }

        void _insert(Node* node, T value)
        {
            if (this->equals(value, node->value))
            {
                return;
            }

            if (this->compare(value, node->value))
            {
                if (node->left == nullptr)
                {
                    node->left = new Node(value);
                    return;
                }
                this->_insert(node->left, value);
            }
            else
            {
                if (node->right == nullptr)
                {
                    node->right = new Node(value);
                    return;
                }
                this->_insert(node->right, value);
            }
        }

        void _pre_order(Node* node, std::function<void(T)>& doThis)
        {
            if (node == nullptr)
            {
                return;
            }

            doThis(node->value);
            this->_pre_order(node->left, doThis);
            this->_pre_order(node->right, doThis);
        }

        void _in_order(Node* node, std::function<void(T)>& doThis)
        {
            if (node == nullptr)
            {
                return;
            }

            this->_in_order(node->left, doThis);
            doThis(node->value);
            this->_in_order(node->right, doThis);
        }

        void _post_order(Node* node, std::function<void(T)>& doThis)
        {
            if (node == nullptr)
            {
                return;
            }

            this->_post_order(node->left, doThis);
            this->_post_order(node->right, doThis);
            doThis(node->value);
        }

        void _level_order(Node* node, std::function<void(T)>& doThis)
        {
            if (node == nullptr)
            {
                return;
            }

            std::queue<Node*> q;
            q.push(node);

            while (!q.empty())
            {
                Node* otherNode = q.front();
                doThis(otherNode->value);
                q.pop();

                if (otherNode->left != nullptr)
                {
                    q.push(otherNode->left);
                }

                if (otherNode->right != nullptr)
                {
                    q.push(otherNode->right);
                }
            }
        }
    };
}

#endif