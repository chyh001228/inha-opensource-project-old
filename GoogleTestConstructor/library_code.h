#ifndef LIBRARY_CODE_H
#define LIBRARY_CODE_H

// 여기에 Node 구조체와 Set 클래스 정의 포함
struct Node {
    // Node 구조체 멤버들
};

class Set {
public:
    Set(); // 생성자
    ~Set(); // 소멸자

    Node *GetRootOfTree();

private:
    Node *root_;
    int size_;
};

#endif // LIBRARY_CODE_H
