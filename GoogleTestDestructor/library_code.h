#ifndef LIBRARY_CODE_H
#define LIBRARY_CODE_H

#include <vector>

class Set {
public:
    Set();
    ~Set();

    // 동적 메모리 할당을 위한 함수
    void AllocateMemory(); 

private:
    // 동적으로 할당된 메모리를 보관할 벡터
    std::vector<int*> allocated_memory_; 
};

#endif // LIBRARY_CODE_H