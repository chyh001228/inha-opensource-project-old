#include "library_code.h"
#include <gtest/gtest.h>

// 생성자 테스트
TEST(SetTest, Constructor) {
    Set mySet; 

    //root가 nullptr인지 확인
    EXPECT_EQ(mySet.GetRootOfTree(), nullptr);
}

// 메인 함수
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
