## 146 LRU Cache

### C++

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
            it->second->second = value;  // update the value
            l.splice(l.begin(), l, it->second);
        } else {
             // capacity is reached, remove the oldest entry
            if(l.size() == capacity_) {
                m.erase(l.back().first);  // why we need the key in the pair
                l.pop_back();
            }
            l.emplace_front(key, value);
            m[key] = l.begin();
        }
    }

private:
    int capacity_;
    unordered_map<int, list<pair<int, int>>::iterator> m;  // key -> node iterator
    list<pair<int, int>> l;  // list node stores (key, val) pair
};
```

```cpp
class LRUCache {
private:
    struct ListNode {
        int key, val;
        ListNode* prev, *next;
        ListNode() : key(0), val(0), prev(nullptr), next(nullptr) {}
        ListNode(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {}
    };

    int capacity_;
    ListNode *head_, *tail_;
    unordered_map<int, ListNode*> map_;

public:
    LRUCache(int capacity) : capacity_(capacity) {
        head_ = new ListNode();
        tail_ = new ListNode();
        head_->next = tail_;
        tail_->prev = head_;
    }

    int get(int key) {
        if (map_.find(key) == map_.end()) {
            return -1;
        }
        ListNode* node = map_[key];
        _remove(node);
        _addHead(node);
        return node->val;
    }

    void put(int key, int value) {
        if (map_.find(key) != map_.end()) {
            ListNode* cur = map_[key];
            cur->val = value;
            _remove(cur);
            _addHead(cur);
            return;
        }
        if (map_.size() == capacity_) {
            ListNode* removed = tail_->prev;
            _remove(removed);
            map_.erase(removed->key);
            delete removed;
        }
        ListNode *node = new ListNode(key, value);
        _addHead(node);
        map_[key] = node;   
    }

    void _remove(ListNode* cur) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
    }

    void _addHead(ListNode* cur) {
        cur->prev = head_;
        cur->next = head_->next;
        head_->next->prev = cur;
        head_->next = cur;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

### Python

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

### Java
