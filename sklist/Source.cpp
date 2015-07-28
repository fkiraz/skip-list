#include <vector>
#include <initializer_list>
#include <algorithm>
#include <random>
#include <iostream>
#include <ctime>
#include "List.h"

using namespace std;
using namespace List_h;

void foo() {
    Skip_list ll;

    for (auto i = -50; i < 50000; ++i) {
        ll.push_back(i);
    }

    ll.display();
}

int main() {
    constexpr int border = 8000000;
    Skip_list sl;
    Slink_list sll;    

    for (auto i = 0; i < border; ++i) {
        sl.push_back(i);
        sll.push_back(i);
    }

    int val;

    std::cout << "Please enter a number to search: ";
    while (std::cin >> val) {

        clock_t t;

        t = clock();

        /*if (sl.search(val)) {
            std::cout << val << " was found" << std::endl;
        }
        else {
            std::cout << val << " was not found" << std::endl;
        }*/

        bool vt = sl.search(val);

        t = clock() - t;

        std::cout << "Search in the skip list took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC << " seconds).\n";

        t = clock();

        const Link *p = sll.find(val);

        t = clock() - t;

        std::cout << "Search in the singly linked list took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC << " seconds).\n";

        if (vt) {
            std::cout << "Value " << p->val << " was found\n";
        }
    }

    return 0;
}