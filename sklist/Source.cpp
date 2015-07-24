#include <iostream>
#include "List.h"

using namespace std;
using namespace List_h;

int main() {
    Slink_list sl{ 1, 2, 3, 4, 5 };
    Slink_list tl;

    const Link *list = sl.get_head();

    print_link(tl.get_head());

    sl.push_back(nullptr);
    tl.push_back(new Link{ 120 });

    print_link(list);
    print_link(tl.get_head());

    return 0;
}