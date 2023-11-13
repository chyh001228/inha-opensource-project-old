#include "library_code.h"

Set::Set() {
}

Set::~Set() {
    // 동적으로 할당된 메모리 해제
    for (auto ptr : allocated_memory_) {
        delete ptr;
    }
}

// 임의로 동적 메모리를 할당
void Set::AllocateMemory() {
    // 예시로 int 메모리 할당
    int* new_memory = new int(42); 
    allocated_memory_.push_back(new_memory);
}
