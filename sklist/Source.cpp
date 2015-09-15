#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include "List.h"

using namespace std;
using namespace List_h;

void foo() {
    Skip_list<int> ll;

    for (auto i = -50; i < 50000; ++i) {
        ll.push_back(i, i);
    }

    ll.display();
}

int main() {
    constexpr int border = 8000000;
    Skip_list<int> sl;
    Slink_list<int> sll;    

    for (auto i = 0; i < border; ++i) {
        sl.push_back(i, i);
        sll.push_back(i);
    }

    int val;

    std::cout << "Please enter a number to search: ";
    while (std::cin >> val) {

        clock_t t;

        t = clock();

        bool vt = sl.search(val);

        t = clock() - t;

        std::cout << "Search in the skip list took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC << " seconds).\n";

        t = clock();

        const Link<int> *p = sll.find(val);

        t = clock() - t;

        std::cout << "Search in the singly linked list took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC << " seconds).\n";

        if (vt) {
            std::cout << "Value " << p->val << " was found\n";
        }
    }

    return 0;
}