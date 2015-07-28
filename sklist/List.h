#pragma once

#include <algorithm>
#include <initializer_list>

namespace List_h
{
    // Node class for a linked list
    struct Link {
        Link(int v, Link *n = nullptr);

        // Inserting nn after current node
        void insert(Link *nn);

        int val;
        Link *next;
    };

    // Singly linked list class
    struct Slink_list {
        Slink_list();
        // Create linked list by passing a list of values like {1,2,3} : 1 -> 2 -> 3
        Slink_list(std::initializer_list<int> l);

        const Link *get_head() const;
        const Link *find(int key) const;
        void push_back(Link *n);
        void push_back(int n);

        ~Slink_list();
    private:
        Link *head;
        Link *end;
    };

    // Skip node class for Skip list algorithm
    // Each node has certain level and several pointers to neighbours
    //               here
    //         * <- <- | ->
    //            * <- * -> -> -> *
    //            * <-   -> *  ->
    //
    struct Skip_node {
        Skip_node(int v, size_t levels);

        ~Skip_node();

        int val;
        size_t levels;
        Skip_node **next;
        Skip_node **prev;
    };

    // Skip list class
    struct Skip_list {
        // Max level of a skip list
        static constexpr size_t max_lvl = 32;

        Skip_list();

        const Skip_node *get_head() const;
        Skip_node &get_head();

        void push_back(int v);
        void push_back(Skip_node *const n);

        void push_front(int v);
        void push_front(Skip_node * const n);

        void insert(int key, int new_val);
        void delete_node(int key);

        bool search(int key);

        void display() const;

        ~Skip_list();
    private:
        // Deleting all nodes from a list
        void clear();
        void end_prepend(Skip_node * const n, size_t lvl);
        void head_append(Skip_node * const n, size_t lvl);

        Skip_node *head;
        Skip_node *end;
    };

    // Generating random level for Skip Nodes
    size_t random_lvl();
    // Printing whole skip list
    void print_link(const Slink_list& l);
} // List_h
