#pragma once

#include <algorithm>
#include <initializer_list>

namespace List_h {
    struct Link {
        Link(int v, Link *n = nullptr);

        void insert(Link *nn);

        int val;
        Link *next;
    };

    struct Slink_list {
        Slink_list();
        Slink_list(std::initializer_list<int> l);

        const Link *get_head() const;
        void push_back(Link *n);
        void push_back(int n);

        ~Slink_list();
     private:
        Link *head;
        Link *end;
    };

    struct Skip_node {
        Skip_node(int v, size_t levels);

        ~Skip_node();

        int val;
        size_t levels;
        Skip_node **next;
        Skip_node **prev;
    };

    struct Skip_list {
        // Max level of a skip list
        static constexpr size_t max_lvl = 32;

        Skip_list();

        const Skip_node *get_head() const;
        Skip_node &get_head();

        void push_back(int v);
        void push_back(Skip_node *n);

        void insert(int key, int new_val);

        bool search(int key);

        void display() const;

        ~Skip_list();
    private:
        void Skip_list::end_prepend(Skip_node *n, int lvl);

        Skip_node *head;
        Skip_node *end;
    };

    size_t random_lvl();
    void print_link(const Link *l);

} // List_h
