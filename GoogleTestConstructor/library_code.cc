#include "library_code.h"

// Set 클래스의 생성자 구현
Set::Set() : root_(nullptr), size_(0) {
}

// Set 클래스의 소멸자 구현
Set::~Set() {
}

Node *Set::GetRootOfTree() {
    return root_;
}
