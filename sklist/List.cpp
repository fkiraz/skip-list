#include <iostream>
#include <random>
#include "List.h"

// Prototypes
int coin_flip();

namespace List_h
{
    Link::Link(int v, Link *n) : val{v}, next{n} {}

    void Link::insert(Link *nn) {
        if (nn) {
            Link *tmp = next;

            next = nn;
            nn->next = tmp;
        }
    }

    Slink_list::Slink_list() : head{nullptr}, end{head} {}

    Slink_list::Slink_list(std::initializer_list<int> l) {
        auto it = l.begin();

        head = new Link{*it++};
        end = head;

        while (it != l.end()) {
            end->insert(new Link{*it});
            end = end->next;
            ++it;
        }
    }

    const Link *Slink_list::get_head() const {
        return head;
    }

    void Slink_list::push_back(Link * n) {
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

    void Slink_list::push_back(int n) {
        if (!head) {
            head = new Link{n};
            end = head;
        }
        else {
            end->next = new Link{n};
            end = end->next;
        }
    }

    Slink_list::~Slink_list() {
        Link *p = head;

        while (p) {
            Link *tmp = p->next;

            delete p;

            p = tmp;
        }

        head = nullptr;
        end = nullptr;
    }

    Skip_node::Skip_node(int v, size_t levels) : val{v}, levels{levels}, next{new Skip_node *[levels]}, prev{new Skip_node *[levels]} {
        for (size_t i = 0; i < levels; ++i) {
            next[i] = nullptr;
            prev[i] = nullptr;
        }
    }

    void Skip_node::insert(Skip_node *n) {
        if (n) {
            for (size_t i = 0; i < n->levels; ++i) {
                if (next[i]) {
                    n->next[i] = next[i];
                    next[i]->prev[i] = n;
                }

                n->prev[i] = this;
                next[i] = n;
            }
        }
    }

    Skip_node::~Skip_node() {
        delete[] next;
        delete[] prev;
    }

    Skip_list::Skip_list() : head{new Skip_node(std::numeric_limits<int>::min(), max_lvl)}, end{new Skip_node(std::numeric_limits<int>::max(), max_lvl)} {
        for (size_t i = 0; i < max_lvl; ++i) {
            head->next[i] = end;
            end->prev[i] = head;
        }
    }

    const Skip_node *Skip_list::get_head() const {
        return head;
    }

    Skip_node &Skip_list::get_head() {
        return *head;
    }

    void Skip_list::insert(int key, int new_val) {
        Skip_node *update[max_lvl];
        Skip_node *x = head;

        for (auto i = max_lvl - 1; i != static_cast<size_t> (-1); --i) {
            while (x->next[i]->val < key) {
                x = x->next[i];
            }

            update[i] = x;
        }

        x = x->next[0];

        if (x->val == key) {
            x->val = new_val;
        }
        else {
            size_t new_lvl = random_lvl();
            Skip_node *n = new Skip_node{new_val, new_lvl};

            for (auto i = 0; i < new_lvl; ++i) {
                n->next[i] = update[i]->next[i];
                n->prev[i] = update[i];
                update[i]->next[i]->prev[i] = n;
                update[i]->next[i] = n;
            }
        }
    }

    void Skip_list::push_back(int v) {
        if (!search(v)) {
            size_t new_lvl = random_lvl();
            Skip_node *n = new Skip_node{v, new_lvl};

            for (auto i = 0; i < new_lvl; ++i) {
                n->next[i] = end;
                n->prev[i] = end->prev[i];
                end->prev[i]->next[i] = n;
                end->prev[i] = n;
            }
        }
    }

    bool Skip_list::search(int key) {
        const Skip_node *x = head;

        for (auto i = max_lvl - 1; i != static_cast<size_t> (-1); --i) {
            while (x->next[i]->val < key) {
                x = x->next[i];
            }
        }

        return (x->next[0]->val == key) ? true : false;
    }

    void Skip_list::display() const {
        for (auto i = max_lvl - 1; i != static_cast<size_t> (-1); --i) {
            const Skip_node *p = head;

            while (p) {
                std::cout << p->val;

                if (p->next[i]) {
                    std::cout << " -> ";
                }
                p = p->next[i];
            }

            std::cout << std::endl;
        }
    }

    Skip_list::~Skip_list() {
        delete head;
        delete end;
    }

    size_t random_lvl() {
        size_t lvl = 1;

        while (lvl < Skip_list::max_lvl && coin_flip()) {
            ++lvl;
        }

        return lvl;
    }

    void print_link(const Link *l) {
        const Link *p = l;

        while (p) {
            std::cout << p->val;
            if (p->next) {
                std::cout << " -> ";
            }

            p = p->next;
        }
        std::cout << std::endl;
    }
}

int coin_flip() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist{0, 1};

    return dist(rd);
}