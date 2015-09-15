#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{		
	TEST_CLASS(Link_test) {
	public:
		
		TEST_METHOD(Test_Constructor)
		{
            constexpr int var = 10;
            List_h::Link<int> l{var};
            Assert::IsNotNull(&l);
            Assert::AreEqual(var, l.val);
		}

        TEST_METHOD(Test_Insert) {
            constexpr int var_1 = 10;
            constexpr int var_2 = 20;
            List_h::Link<int> l_1{var_1};
            l_1.insert(new List_h::Link<int>{var_2});

            Assert::IsNotNull(l_1.next);
            Assert::AreEqual(var_2, l_1.next->val);
        }

        TEST_METHOD(Test_Copy) {
            constexpr int var = 50;
            List_h::Link<int> *l_1 = new List_h::Link<int>{var};
            List_h::Link<int> l_2 = *l_1;

            delete l_1;
            l_1 = nullptr;

            Assert::AreEqual(var, l_2.val);
        }
	};

    TEST_CLASS(Slink_Test) {
    public:
        TEST_METHOD(Test_Default_Constructor) {
            List_h::Slink_list<int> sl;

            Assert::IsNull(sl.get_head());
        }

        TEST_METHOD(Test_Init_Constructor) {
            constexpr size_t sz = 5;
            List_h::Slink_list<int> sl{1, 2, 3, 4, 5};
            
            Assert::AreEqual(sz, sl.size());
        }

        TEST_METHOD(Test_Find_Exist) {
            const std::string search_w1{"Line"};
            const std::string search_w2{"ln"};
            List_h::Slink_list<std::string> sl{"hello", "world", "line", "Line", "ln"};

            const List_h::Link<std::string> *p1 = sl.find(search_w1);
            const List_h::Link<std::string> *p2 = sl.find(search_w2);

            Assert::AreEqual(p1->val, search_w1);
            Assert::AreEqual(p2->val, search_w2);
        }

        TEST_METHOD(Test_Find_Null) {
            constexpr int val = 10;
            List_h::Slink_list<int> sl{1, 2, 3};

            const List_h::Link<int> *p1 = sl.find(val);

            Assert::IsNull(p1);
        }
    };
}