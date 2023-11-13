#include "library_code.h"
#include <gtest/gtest.h>

// 소멸자 테스트
TEST(SetTest, Destructor) {
    Set* mySet = new Set();
    mySet->AllocateMemory(); // 동적 메모리 할당
    delete mySet; // 소멸자 호출하여 메모리 해제 확인
}

// 메인 함수
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
