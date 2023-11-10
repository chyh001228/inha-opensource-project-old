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

  Node(int val) : key(val), left_child(nullptr), right_child(nullptr), height(1) {}
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
  bool IsTreeEmpty() { return (size_ == 0) ? true : false; }

  // 트리에 들어 있는 노드 수 반환
  // input:
  // output: 트리에 있는 노드 수
  int GetTreeSize() { return size_; }

  // 입력받은 숫자를 키로 가지는 노드 찾기
  // input: 찾을 노드의 Key
  // output: 해당 숫자를 Key로 하는 노드의 Depth, 없으면 0
  int FindNode(int key_to_find) {
    Node *temp = root_;
    int depth = 0;
    // temp가 nullptr이 아니고 키 값이 다른 경우 계속 탐색
    // AVL Tree는 정렬되어 있기 때문에 Key 비교 후 이동할 자식 결정
    while (temp != nullptr) {
      if (temp->key == key_to_find) {
        return depth;
      } else {
        temp = (key_to_find < temp->key) ? temp->left_child : temp->right_child;
        depth += 1;
      }
    }
    return 0;
  }


  // 입력받은 숫자를 Key로 하는 노드를 트리에 삽입, 십압할 위치를 재귀적으로
  // 찾음
  // input: 삽입할 노드의 Key
  // output: 삽입한 노드의 Depth
  int InsertNode(int key_to_insert) {
    Node *inserted_node = nullptr;
    root_ = InsertNodeWithRecursion(root_, key_to_insert, inserted_node);
    size_ += 1;
    return GetDepthOfNode(inserted_node);
  }


  //int 유형을 중첩하여 Node 유형을 변환하는 방법입니다.
  //Input: 찾을 노드의 Key
  //Output: 결과는 cout을 통해 출력 가능하며 반환값은 없습니다.
  void GetMaximumNodeOfSubTree(int key_to_insert) {
    Node* temp = GetInputNode(key_to_insert);
    
    //제목에는 없지만, 그가 Node의 존재 여부를 판단할 수 있는 방법이 있어야 한다고 생각합니다.
    if (temp == nullptr) {
        cout << "Node not found." << endl;
        return;
    }

    while (temp->right_child != nullptr) {
        temp = temp->right_child;
    }
    cout << temp.key << " " << GetDepthOfNode(temp) << endl;

  }

  void GetMinimumNodeOfSubTree(int key_to_insert) {
    Node* temp = GetInputNode(key_to_insert);

    //위와 같다.
    if (temp == nullptr) {
        cout << "Node not found." << endl;
        return;
    }

    while (temp->left_child != nullptr) {
        temp = temp->left_child;
    }
    cout << temp.key << " " << GetDepthOfNode(temp) << endl;

  }


  // 입력받은 숫자를 Key로 하는 노드를 트리에서 삭제, 삭제할 위치를 재귀적으로
  // 찾음
  // input: 삭제할 노드의 Key
  // output: 삭제한 노드의 Depth
  int DeleteNode(int key_to_insert) {
    int depth = 0;
    root_ = DeleteNodeWithRecursion(root_, key_to_insert, depth);
    return depth;
  }


  // 트리에서 입력받은 Key보다 작은 노드의 수를 반환, 재귀적으로 탐색
  // 0인지 검사 후 +1 해야함
  // input: 재귀적으로 현재 위치를 가지고 있을 노드 포인터, rank를 찾을 노드의
  // Key output: 해당 노드의 rank, 노드가 없는 경우 0
  int GetRankOfKey(Node *node, int key_to_find_rank) {
    if (node == nullptr) {
      return 0;
    }

    // 현재 노드의 키가 더 큰 경우 그대로 왼쪽 자식 탐색
    if (key_to_find_rank <= node->key) {
      return GetRankOfKey(node->left_child, key_to_find_rank);
    }
    // 현재 노드의 키가 작은 경우 양쪽 자식 탐색
    else {
      return 1 + GetRankOfKey(node->left_child, key_to_find_rank) +
             GetRankOfKey(node->right_child, key_to_find_rank);
    }
  }


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

  //Node를 찾는 방법을 새로 정의합니다.
  //Input: 찾을 노드의 Key
  //Output: 찾을 노드
  Node* GetInputNode(int key_to_insert) {
    Node* temp = root_;
    int depth = 0;
    while (temp != nullptr) {
        if (temp->key == key_to_find) {
            return temp;
        }
        else {
            temp = (key_to_find < temp->key) ? temp->left_child : temp->right_child;
        }
    }
    return nullptr;
  }


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
  void UpdateHeightOfNode(Node *node) {
    if (node == nullptr) {
      return;
    }
    node->height = 1 + max(GetHeightOfNode(node->left_child),
                           GetHeightOfNode(node->right_child));
  }

  // 입력 받은 노드를 기준으로 좌측으로 회전
  // input: 회전할 기준 노드
  // output: 회전 이후 서브트리의 루트 노드
  Node *RotateLeft(Node *cur_root) {
    Node *next_root = cur_root->right_child;
    Node *next_right_subtree = next_root->left_child;

    next_root->left_child = cur_root;
    cur_root->right_child = next_right_subtree;

    UpdateHeightOfNode(cur_root);
    UpdateHeightOfNode(next_root);

    return next_root;
  }

  // 입력 받은 노드를 기준으로 우측으로 회전
  // input: 회전할 기준 노드
  // output: 회전 이후 서브트리의 루트 노드
  Node *RotateRight(Node *cur_root) {
    Node *next_root = cur_root->left_child;
    Node *next_left_subtree = next_root->right_child;

    next_root->right_child = cur_root;
    cur_root->left_child = next_left_subtree;

    UpdateHeightOfNode(cur_root);
    UpdateHeightOfNode(next_root);

    return next_root;
  }


  // BalanceFactor를 반환
  // input: BalanceFactor를 측정할 노드
  // output: BalanceFactor
  int GetBalanceFactor(Node *node) {
    if (node == nullptr) {
      return 0;
    }
    return GetHeightOfNode(node->left_child) -
           GetHeightOfNode(node->right_child);
  }


  // AVL 트리의 특성을 유지하기 위해서 다시 밸런싱
  // input: 리밸런싱할 서브트리의 루트 노드
  // output: 리밸런싱 이후 서브트리의 루트 노드
  Node *RebalanceTree(Node *node) {
    UpdateHeightOfNode(node);

    int balance_factor = GetBalanceFactor(node);

    if (balance_factor > 1) {
      if (GetBalanceFactor(node->left_child) < 0) {
        node->left_child = RotateLeft(node->left_child);
      }
      return RotateRight(node);
    }
    if (balance_factor < -1) {
      if (GetBalanceFactor(node->right_child) > 0) {
        node->right_child = RotateRight(node->right_child);
      }
      return RotateLeft(node);
    }

    return node;
  }


  // 입력받은 숫자를 Key로 하는 노드를 트리에 삽입, 재귀적으로 삽입할 위치 찾기
  // input: 현재 삽입 위치 포인터, 삽입할 삽입할 노드의 Key, 삽입할 위치의 Depth
  // output: 재귀를 돌면서 변화된 서브트리의 루트
  Node *InsertNodeWithRecursion(Node *node, int key_to_insert,
                                Node *&inserted_node) {
    // 받은 노드가 nullptr이면 그 자리에 삽입
    if (node == nullptr) {
      // 새로운 노드 생성, 해당 위치에 그대로 삽입
      inserted_node = new Node(key_to_insert);
      return inserted_node;
    }
    // 재귀적으로 삽입할 위치 탐색
    else if (node->key < key_to_insert) {
      node->right_child = InsertNodeWithRecursion(node->right_child,
                                                  key_to_insert, inserted_node);
    } else if (node->key > key_to_insert) {
      node->left_child = InsertNodeWithRecursion(node->left_child,
                                                 key_to_insert, inserted_node);
    }
    // 이미 동일한 키값을 가진 노드가 존재
    else {
      return node;
    }

    // 트리 리밸런싱 이후 서브트리의 루트 반환
    return RebalanceTree(node);
  }


  // 받은 키를 루트로 하는 서브트리에서 가장 작은 Key를 가지는 노드 찾기
  // input: 서브트리의 루트 노드
  // output: 서브트리에서 가장 작은 Key를 가진 노드
  Node *GetMinimumNodeFromSubTree(Node *node) {
    while (node->left_child != nullptr) {
      node = node->left_child;
    }
    return node;
  }


  // 입력받은 숫자를 Key로 하는 노드를 트리에서 삭제, 재귀적으로 삭제 위치 찾기
  // input: 현재 삭제 위치 포인터, 삭제할 노드의 Key
  // output: 재귀를 돌면서 변화된 서브트리의 루트
  Node *DeleteNodeWithRecursion(Node *node, int key_to_delete, int &depth) {
    // 삭제할 것이 없으면 그대로 nullptr 반환
    if (node == nullptr) {
      return node;
    }

    // 재귀적으로 삭제할 노드 찾기
    if (key_to_delete < node->key) {
      node->left_child =
          DeleteNodeWithRecursion(node->left_child, key_to_delete, depth);
      depth += 1;
    } else if (key_to_delete > node->key) {
      node->right_child =
          DeleteNodeWithRecursion(node->right_child, key_to_delete, depth);
      depth += 1;
    }
    // 삭제할 노드 찾은 경우
    else {
      // 자식이 하나이거나 없는 경우
      if (node->left_child == nullptr || node->right_child == nullptr) {
        // temp = 삭제할 노드의 자식 노드
        Node *temp = (node->left_child) ? node->left_child : node->right_child;

        // 자식이 없는 경우
        if (temp == nullptr) {
          temp = node;
          node = nullptr;
        }
        // 자식이 하나인 경우
        else {
          // 삭제할 노드 위치에 자식 노드를 붙임
          *node = *temp;
        }
        delete temp;
        size_ -= 1;
      }
      // 자식이 둘인 경우
      else {
        // 후계자 노드 찾기
        Node *temp = GetMinimumNodeFromSubTree(node->right_child);
        node->key = temp->key;
        node->right_child =
            DeleteNodeWithRecursion(node->right_child, temp->key, depth);
      }
    }

    // 자식이 없었던 경우 그대로 리턴
    if (node == nullptr) {
      return node;
    }

    // 자식이 있었다면 Height 갱신, 리밸런싱
    UpdateHeightOfNode(node);
    return RebalanceTree(node);
  }
};
