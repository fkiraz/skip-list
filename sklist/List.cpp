#include <iostream>
#include "List.h"

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

    Slink_list::Slink_list() : head{ nullptr }, cur_p{ head } {}

    Slink_list::Slink_list(std::initializer_list<int> l) {
        auto it = l.begin();

        head = new Link{ *it++ };
        cur_p = head;

        while (it != l.end()) {
            cur_p->insert(new Link{ *it });
            cur_p = cur_p->next;
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
            cur_p = head;
        }
        else {
            cur_p->insert(n);
            cur_p = cur_p->next;
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
        cur_p = nullptr;
    }

}
