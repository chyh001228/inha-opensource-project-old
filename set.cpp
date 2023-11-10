/*
MIT License

Copyright (c) 2023 Kim Ji-Soo(김지수), Lee Seok-Hyeon(이석현), Lee Jun-Young(이준용), Cheng Yihe(정역하)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


// Key와 좌우 자식을 가진 AVL Tree의 기본 노드 구조체 정의
// key: 32bit integer
struct Node {
  int key;
  Node *parent;
  Node *left_child;
  Node *right_child;
  int height;

  Node(int val) 
      : key(val), left_child(nullptr), right_child(nullptr), height(1) {}
};

class Set {
 public:
  Set() : root_(nullptr), size_(0) {}
  ~Set() {}


  // 트리의 루트 노드 반환
  Node *GetRootOfTree() { return root_; }

  // 트리에 노드가 없는 지 확인
  // input:
  // output: 노드가 있으면 true, 없으면 false
  bool IsTreeEmpty() { return size_ == 0 ? true : false; }

  // 트리에 들어 있는 노드 수 반환
  // input:
  // output: 트리에 있는 노드 수
  int GetTreeSize() { return size_; }

  // 입력받은 숫자를 키로 가지는 노드 찾기
  // input: 찾을 노드의 Key
  // output: 해당 숫자를 Key로 하는 노드의 Depth, 없으면 0
  int FindNode(int key_to_find);


  // 입력받은 숫자를 Key로 하는 노드를 트리에 삽입, 십압할 위치를 재귀적으로 찾음
  // input: 삽입할 노드의 Key
  // output: 삽입한 노드의 Depth
  int InsertNode(int key_to_insert);


  // 입력받은 노드를 루트로 하는 서브트리에서 가장 작은 Key를 가지는 노드 찾기
  // input: 서브트리의 루트 노드
  // output: 서브트리에서 가장 작은 Key를 가진 노드
  Node *GetMinimumNodeOfSubTree(Node *node);

  // 받은 키를 루트로 하는 서브트리에서 가장 큰 Key를 가지는 노드 찾기
  // input: 서브트리의 루트 노드
  // output: 서브트리에서 가장 큰 Key를 가진 노드
  Node *GetMaximumNodeOfSubTree(Node *node);


  // 입력받은 숫자를 Key로 하는 노드를 트리에서 삭제, 삭제할 위치를 재귀적으로 찾음
  // input: 삭제할 노드의 Key
  // output: 삭제한 노드의 Depth
  int DeleteNode(int key_to_insert);


  // 트리에서 입력받은 Key보다 작은 노드의 수를 반환, 재귀적으로 탐색
  // 0인지 검사 후 +1 해야함
  // input: 재귀적으로 현재 위치를 가지고 있을 노드 포인터, rank를 찾을 노드의
  // Key output: 해당 노드의 rank, 노드가 없는 경우 0
  int GetRankOfKey(Node *node, int key_to_find_rank);


  // 디버깅용 Inorder 출력
  // input: 서브트리의 Root
  // ouput:
  void display(Node *node) {
    if (node == nullptr) return;

    display(node->left_child);
    cout << node->key << " ";
    display(node->right_child);
  };


 private:
  Node *root_;
  int size_;


  // 노드의 Depth 반환
  // input: Depth를 알아낼 노드
  // output: 해당 노드의 Depth
  int GetDepthOfNode(Node *node) {
    int depth = 0;
    Node *temp = root_;
    while (temp != nullptr && temp->key != node->key) {
      temp = (node->key < temp->key) ? temp->left_child : temp->right_child;
      depth += 1;
    }
    return depth;
  }

  // 노드의 Height 반환
  // input: Height를 알아낼 노드
  // output: 해당 노드의 Height
  int GetHeightOfNode(Node *node) {
    if (node == nullptr) {
      return 0;
    }
    return node->height;
  }

  // 노드의 Height 갱신
  // input: Height를 갱신할 노드
  // output:
  void UpdateHeightOfNode(Node *node);

  // 입력 받은 노드를 기준으로 좌측으로 회전
  // input: 회전할 기준 노드
  // output: 회전 이후 서브트리의 루트 노드
  Node* RotateLeft(Node *cur_root);

  // 입력 받은 노드를 기준으로 우측으로 회전
  // input: 회전할 기준 노드
  // output: 회전 이후 서브트리의 루트 노드
  Node *RotateRight(Node *cur_root);


  // BalanceFactor를 반환
  // input: BalanceFactor를 측정할 노드
  // output: BalanceFactor
  int GetBalanceFactor(Node* node);
  

  // AVL 트리의 특성을 유지하기 위해서 다시 밸런싱
  // input: 리밸런싱할 서브트리의 루트 노드
  // output: 리밸런싱 이후 서브트리의 루트 노드
  Node *RebalanceTree(Node *node);

  // 입력받은 숫자를 Key로 하는 노드를 트리에 삽입, 재귀적으로 삽입할 위치 찾기
  // input: 현재 삽입 위치 포인터, 삽입할 삽입할 노드의 Key, 삽입할 위치의 Depth
  // output: 재귀를 돌면서 변화된 서브트리의 루트
  Node *InsertNodeWithRecursion(Node *node, int key_to_insert, Node*& inserted_node);


  // 입력받은 숫자를 Key로 하는 노드를 트리에서 삭제, 재귀적으로 삭제 위치 찾기
  // input: 현재 삭제 위치 포인터, 삭제할 노드의 Key
  // output: 재귀를 돌면서 변화된 서브트리의 루트
  Node* DeleteNodeWithRecursion(Node *node, int key_to_delete, int& depth);
};
