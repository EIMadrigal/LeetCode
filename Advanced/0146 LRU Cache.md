```cpp
class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {}
    
    int get(int key) {
        const auto it = m.find(key);
        if(it == m.cend())
            return -1;
        
        // move the key-value pair to the front of the list
        l.splice(l.begin(), l, it->second);
        
        return it->second->second;
    }
    
    void put(int key, int value) {
        const auto it = m.find(key);
        
        // key exists
        if(it != m.cend()) {
            it->second->second = value;   // update the value
            l.splice(l.begin(), l, it->second);
            return;
        }
        
        // capacity is reached, remove the oldest entry
        if(l.size() == capacity_) {
            m.erase(l.back().first);  // why we need the key in the pair
            l.pop_back();
        }
        
        l.emplace_front(key, value);
        m[key] = l.begin();
    }
private:
    int capacity_;
    unordered_map<int, list<pair<int, int>>::iterator> m;
    list<pair<int, int>> l;
};
```

```cpp
class LRUCache {
public:

    struct Node {
        int key, val;
        Node *prev, *next;
        Node() : key(-1), val(-1), prev(nullptr), next(nullptr) {}
        Node(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {}
    };

    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(), tail = new Node();
        head->next = tail, tail->prev = head;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if (it == m.end()) {
            return -1;
        }
        Node* node = it->second;
        del(node);
        insert(node);
        return node->val;
    }
    
    void put(int key, int value) {
        auto it = m.find(key);
        if (it == m.end()) {
            if (m.size() == capacity) {
                Node* r = tail->prev;
                m.erase(r->key);
                del(r);
                delete r;
            }
            Node* node = new Node(key, value);
            insert(node);
            m[key] = node;
        }
        else {
            Node* node = it->second;
            node->val = value;
            del(node);
            insert(node);
        }
    }

    // get也要删除, 因此不能用tail
    void del(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insert(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next = node;
        node->next->prev = node;
    }

    int capacity;
    unordered_map<int, Node*> m;
    Node *head, *tail;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

```python
class Node:
    def __init__(self, key, val):
        self.key, self.val = key, val
        self.prev = self.next = None

class LRUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.map = {}
        self.old, self.new = Node(0, 0), Node(0, 0)
        self.new.next, self.old.prev = self.old, self.new
        
    def get(self, key: int) -> int:
        if key not in self.map:
            return -1
        node = self.map[key]
        self._delete(node)
        self._add(node)
        return node.val

    def put(self, key: int, value: int) -> None:
        if key in self.map:
            self._delete(self.map[key])
        node = Node(key, value)
        self._add(node)
        self.map[key] = node
        if len(self.map) > self.capacity:
            oldest = self.old.prev
            self._delete(oldest)
            del self.map[oldest.key]
    
    def _delete(self, node):
        prev, nxt = node.prev, node.next
        prev.next, nxt.prev = nxt, prev
    
    def _add(self, node):
        nxt = self.new.next
        nxt.prev = self.new.next = node
        node.prev, node.next = self.new, nxt


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
```