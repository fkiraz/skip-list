#pragma once

#include <random>
#include <algorithm>
#include <initializer_list>

namespace List_h
{
    inline int coin_flip() {
        std::random_device rd;
        std::uniform_int_distribution<int> dist{0, 1};

        return dist(rd);
    }

    // Node class for a linked list
    template <typename T>
    struct Link {
        Link(T v, Link *n = nullptr) : val{v}, next{n} {};

        // Inserting nn after current node
        void insert(Link *nn) {
            if (nn) {
                Link *tmp = next;

                next = nn;
                nn->next = tmp;
            }
        }

        T val;
        Link *next;
    };

    // Singly linked list class
    template <typename T>
    struct Slink_list {
        Slink_list() : head{nullptr}, end{head}, sz{0} {};
        // Create linked list by passing a list of values like {1,2,3} : 1 -> 2 -> 3
        Slink_list(std::initializer_list<T> l) : sz{0} {
            auto it = l.begin();

            head = new Link<T>{*it++};
            end = head;
            ++sz;

            while (it != l.end()) {
                end->insert(new Link<T>{*it});
                end = end->next;
                ++it;
                ++sz;
            }
        }

        const Link<T> *get_head() const {
            return head;
        }

        const Link<T> *get_end() const {
            return end;
        }

        const size_t size() const {
            return sz;
        }

        const Link<T> *find(const T& key) const {
            const Link<T> *x = head;

            if (head) {
                while (x != nullptr && x->val != key) {
                    x = x->next;
                }
            }

            return (x && x->val == key) ? x : nullptr;
        }

        void push_back(Link<T> *const n) {
            if (!n) {
                return;
            }

            if (!head) {
                head = n;
                end = head;
            }
            else {
                end->insert(n);
                end = end->next;
            }
        }
        void push_back(T n) {
            if (!head) {
                head = new Link<T>{n};
                end = head;
            }
            else {
                end->next = new Link<T>{n};
                end = end->next;
            }
        }

        ~Slink_list() {
            Link<T> *p = head;

            while (p) {
                Link<T> *tmp = p->next;

                delete p;

                p = tmp;
            }

            head = nullptr;
            end = nullptr;
        }
    private:
        Link<T> *head;
        Link<T> *end;
        size_t sz;
    };

    // Skip node class for Skip list algorithm
    // Each node has certain level and several pointers to neighbours
    //               here
    //         * <- <- | ->
    //            * <- * -> -> -> *
    //            * <-   -> *  ->
    //
    template <typename T>
    struct Skip_node {
        Skip_node(int k, T v, size_t levels) : key{k}, val{v}, levels{levels}, next{new Skip_node<T> *[levels]}, prev{new Skip_node<T> *[levels]} 
        {
            for (size_t i = 0; i < levels; ++i) {
                next[i] = nullptr;
                prev[i] = nullptr;
            }
        }

        ~Skip_node() {
            delete[] next;
            delete[] prev;
        }

        int key;
        T val;
        size_t levels;
        Skip_node<T> **next;
        Skip_node<T> **prev;
    };

    // Skip list class
    template <typename T>
    struct Skip_list {
        // Max level of a skip list
        static constexpr size_t max_lvl = 32;

        Skip_list() : head{new Skip_node<T>(std::numeric_limits<int>::min(), T{}, max_lvl)}, end{new Skip_node<T>(std::numeric_limits<int>::max(), T{}, max_lvl)} {
            for (size_t i = 0; i < max_lvl; ++i) {
                head->next[i] = end;
                end->prev[i] = head;
            }
        }

        const Skip_node<T> *get_head() const {
            return head;
        }

        Skip_node<T> &get_head() {
            return *head;
        }

        void insert(int key, T new_val) {
            Skip_node<T> *update[max_lvl];
            Skip_node<T> *x = head;

            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                while (x->next[i]->key < key) {
                    x = x->next[i];
                }

                update[i] = x;
            }

            x = x->next[0];

            if (x->key == key) {
                x->val = new_val;
            }
            else {
                size_t new_lvl = random_lvl();
                Skip_node<T> *n = new Skip_node<T>{key, new_val, new_lvl};

                for (auto i = 0; i < new_lvl; ++i) {
                    n->next[i] = update[i]->next[i];
                    n->prev[i] = update[i];
                    update[i]->next[i]->prev[i] = n;
                    update[i]->next[i] = n;
                }
            }
        }

        void delete_node(int key) {
            Skip_node<T> *update[max_lvl];
            Skip_node<T> *x = head;

            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                while (x->next[i]->key < key) {
                    x = x->next[i];
                }
                update[i] = x;
            }

            x = x->next[0];

            if (x->key == key) {
                for (auto i = 0; i < max_lvl; ++i) {
                    if (update[i]->next[i] != x) {
                        break;
                    }
                    update[i]->next[i] = x->next[i];
                }

                delete x;
            }
        }

        // Delete all nodes from a list
        void clear() {
            Skip_node<T> *p = head->next[0];

            while (p != end) {
                Skip_node<T> *t = p->next[0];

                delete p;

                p = t;
            }
        }

        void push_back(int k, T v) {
            if (!search(k)) {
                size_t new_lvl = random_lvl();
                Skip_node<T> *n = new Skip_node<T>{k, v, new_lvl};

                end_prepend(n, new_lvl);
            }
        }

        void push_back(Skip_node<T> * n) {
            if (n) {
                if (!search(n->key)) {
                    size_t lvl = std::min(n->levels, max_lvl);

                    end_prepend(n, lvl);
                }
            }
        }

        void push_front(int k, T v) {
            if (!search(k)) {
                size_t new_lvl = random_lvl();
                Skip_node<T> *n = new Skip_node<T>{k, v, new_lvl};

                head_append(n, new_lvl);
            }
        }

        void push_front(Skip_node<T> * const n) {
            if (n) {
                if (!search(n->key)) {
                    size_t lvl = std::min(n->levels, max_lvl);

                    head_append(n, lvl);
                }
            }
        }

        bool search(int key) const {
            const Skip_node<T> *x = head;

            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                while (x->next[i]->key < key) {
                    x = x->next[i];
                }
            }

            return (x->next[0]->key == key) ? true : false;
        }

        void display() const {
            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                const Skip_node<T> *p = head;

                while (p) {
                    std::cout << p->key << " (" << p->val << ")";

                    if (p->next[i]) {
                        std::cout << " -> ";
                    }
                    p = p->next[i];
                }

                std::cout << std::endl;
            }
        }

        ~Skip_list() {
            clear();

            delete head;
            delete end;
        }
    private:
        void end_prepend(Skip_node<T> * const n, size_t lvl) {
            for (auto i = 0; i < lvl; ++i) {
                n->next[i] = end;
                n->prev[i] = end->prev[i];
                end->prev[i]->next[i] = n;
                end->prev[i] = n;
            }
        }

        void head_append(Skip_node<T> * const n, size_t lvl) {
            for (auto i = 0; i < lvl; ++i) {
                n->prev[i] = head;
                n->next[i] = head->next[i];
                head->next[i]->prev[i] = n;
                head->next[i] = n;
            }
        }

        // Generating random level for Skip Nodes
        size_t random_lvl() {
            size_t lvl = 1;

            while (lvl < max_lvl && coin_flip()) {
                ++lvl;
            }

            return lvl;
        }

        Skip_node<T> *head;
        Skip_node<T> *end;
    };

    // Printing whole skip list
    template <typename T>
    void print_link(const Slink_list<T>& l) {
        const Link<T> *p = l.get_head();

        while (p) {
            std::cout << p->val;
            if (p->next) {
                std::cout << " -> ";
            }

            p = p->next;
        }
        std::cout << std::endl;
    }
} // List_h
