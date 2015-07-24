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

    struct Skip_list {
        // Max level of a skip list
        static constexpr size_t max_lvl = 32;

        Skip_list(std::initializer_list<int> l);
    private:
        Slink_list *lvls[max_lvl];

    };

    void print_link(const Link *l);

} // List_h
