#include <iostream>
#include <random>
#include "List.h"

// Prototypes
int coin_flip();

namespace List_h {
    Link::Link(int v, Link *n) : val{ v }, next{ n } {}

    void Link::insert(Link *nn)
    {
        if (!nn) {
            return;
        }

        Link *tmp = next;

        next = nn;
        nn->next = tmp;
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

    Slink_list::Slink_list() : head{ nullptr }, end{ head } {}

    Slink_list::Slink_list(std::initializer_list<int> l) {
        auto it = l.begin();

        head = new Link{ *it++ };
        end = head;

        while (it != l.end()) {
            end->insert(new Link{ *it });
            end = end->next;
            ++it;
        }
    }

    const Link *Slink_list::get_head() const
    {
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
            head = new Link{ n };
            end = head;
        }
        else {
            end->next = new Link{ n };
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
    
    Skip_list::Skip_list(std::initializer_list<int> l) {
        size_t level = 0;

        lvls[level] = new Slink_list;
        // fill zero level
        for (auto it = l.begin(); it != l.end(); ++it) {
            lvls[level]->push_back(*it);
        }
        
        // fill randomly levels [1 ... max_lvl)
        while (++level != max_lvl) {
            int pos = 0;
        }
    }



}

int coin_flip()
{   
    std::random_device rd;
    std::uniform_int_distribution<int> dist{ 0, 1 };

    return dist(rd);
}
