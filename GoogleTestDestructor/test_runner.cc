#include "library_code.h"
#include <gtest/gtest.h>



TEST(SetTest, Destructor) {
    {
        Set* mySet = new Set();
        // 동적 메모리 할당
        mySet->AllocateMemory(); 
        // 소멸자 호출하여 메모리 해제 확인
        delete mySet;
    }
    // 소멸자 호출 여부 확인
    ASSERT_TRUE(Set::destructorCalled);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
