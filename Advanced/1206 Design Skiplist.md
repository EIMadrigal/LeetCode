```cpp
class Skiplist {
private:
    struct Node {
        int val;
        vector<Node *> level;

        Node(int v, int sz=32) : val(v), level(sz, nullptr) {}
    };

    Node *head, *tail;
    int level;
    
    // 在level[0]找到小于target的最大节点
    Node *find(int target) {
        Node *p = head;
        for (int i = level - 1; i >= 0; --i) {
            while (p->level[i] && p->level[i]->val < target) {
                p = p->level[i];
            }
        }
        p = p->level[0];
        return p;
    }

    int randomLevel() {
        int lv = 1;
        while (rand() % 4 == 1 && lv < 32) {
            lv++;
        }
        return lv;
    }
    
public:
    Skiplist() {
        head = new Node(INT_MIN);
        tail = new Node(INT_MAX, 0);

        for (int i = 0; i < 32; ++i) {
            head->level[i] = tail;
        }

        level = 0;
    }

    bool search(int target) {
        Node *p = find(target);
        return p->val == target;
    }
    
    void add(int num) {
        Node *p = head;
        vector<Node *> prev(32, nullptr);
        for (int i = level - 1; i >= 0; --i) {
            while (p->level[i] && p->level[i]->val < num) {
                p = p->level[i];
            }
            prev[i] = p;
        }

        int lv = randomLevel();
        if (lv > level) {
            ++level;
            lv = level;
            prev[level - 1] = head;
        }

        Node *newNode = new Node(num, lv);
        for (int i = lv - 1; i >= 0; --i) {  // from lv - 1 not level - 1 if lv < level
            p = prev[i];
            newNode->level[i] = p->level[i];
            p->level[i] = newNode;
        }
    }
    
    bool erase(int num) {
        Node *p = head;
        vector<Node *> prev(32, nullptr);
        for (int i = level - 1; i >= 0; --i) {
            while (p->level[i] && p->level[i]->val < num) {
                p = p->level[i];
            }
            prev[i] = p;
        }
        p = p->level[0];
        if (p->val != num) {
            return false;
        }
        for (int i = 0; i < level; ++i) {
            if (prev[i]->level[i] != p) break;
            prev[i]->level[i] = p->level[i];
        }
        delete p; 
        while (level > 0 && head->level[level - 1] == tail) {
            --level;
        }
        return true;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */
```
