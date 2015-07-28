#include <iostream>
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
    Skip_list sl;
    
    sl.push_back(3);
    sl.push_back(6);
    sl.push_back(7);
    sl.push_back(9);
    sl.push_back(12);
    sl.push_back(17);
    sl.push_back(19);
    sl.push_back(25);
    sl.push_back(26);

    sl.insert(40, 40);
    sl.push_front(1);

    sl.delete_node(1);
    sl.delete_node(17);

    sl.display();

    int val;

    std::cout << "Please enter a number to search: ";
    std::cin >> val;

    if (sl.search(val)) {
        std::cout << val << " was found" << std::endl;
    }
    else {
        std::cout << val << " was not found" << std::endl;
    }

    return 0;
}