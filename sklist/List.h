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

        ~Slink_list();
    private:
        Link *head;
        Link *cur_p;
    };

    void print_link(const Link *l);

} // List_h
