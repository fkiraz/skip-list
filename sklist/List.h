#pragma once

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

        void insert(Skip_node *n);

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

        bool search(int key);

        void display() const;
    private:
        Skip_node *head;
        Skip_node *end;
    };

    void print_link(const Link *l);

} // List_h
