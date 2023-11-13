#include "library_code.h"

// 정적 변수 초기화
bool Set::destructorCalled = false; 

Set::~Set() {
    // 동적으로 할당된 메모리 해제
    for (auto ptr : allocated_memory_) {
        delete ptr;
    }
    // 소멸자가 호출되었음을 표시
    destructorCalled = true;

}

void Set::AllocateMemory() {
    // 예시로 int 메모리 할당
    int* new_memory = new int(42); 
    allocated_memory_.push_back(new_memory);
}
