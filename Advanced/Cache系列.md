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

## 460 LFU Cache

LFU和LRU的区别在于：优先删除访问频率最低的键值对，频率相同时优先删除LRU
删除操作的O(1)意味着要快速根据频率找到要删除的键值对，所以hashmap1存储freq -> doubly linked list
每个双向链表的组织和LRU一样，结点要存储(key, val, freq) 存储key是为了在hashmap2中删除对应的项，存储freq是为了get时更新访问频率并且移动到hashmap1合适的位置
get的O(1)需要hashmap2存储key -> 所有双向链表结点的映射

访问某项后其频率加一，如果删掉该项后当前min_freq的链表为空，意味着要更新min_freq，即接下来要干掉的是频率为min_freq的项

### C++

```cpp
class LFUCache {
public:
    LFUCache(int _capacity) {
        capacity = _capacity;
    }

    int get(int key) {
        if (capacity == 0) {
            return -1;
        }
        auto it = keyTable.find(key);
        if (it == keyTable.end()) {
            return -1;
        }
        list<Node>::iterator node = it->second;
        int val = node->val, freq = node->freq;
        freqTable[freq].erase(node);

        if (freqTable[freq].size() == 0) {
            freqTable.erase(freq);
            if (freq == minFreq)
                minFreq++;
        }
        // 更新访问频率
        freqTable[freq + 1].push_front(Node(key, val, freq + 1));
        keyTable[key] = freqTable[freq + 1].begin();
        return val;
    }

    void put(int key, int val) {
        if (capacity == 0) {
            return;
        }
        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            auto node = it->second;
            node->val = val;
            int freq = node->freq;
            freqTable[freq].erase(node);

            if (freqTable[freq].size() == 0) {
                freqTable.erase(freq);
                if (freq == minFreq)
                    minFreq++;
            }
            // 更新访问频率
            freqTable[freq + 1].push_front(Node(key, val, freq + 1));
            keyTable[key] = freqTable[freq + 1].begin();
        }
        else {  // 插入新项
            if (keyTable.size() == capacity) {  // 换出目前使用频率最低的项
                auto old = freqTable[minFreq].back();
                freqTable[minFreq].pop_back();  // 从链表中删除
                keyTable.erase(old.key);  // 从keyTable中删除
                if (freqTable[minFreq].size() == 0) {  // 从freqTable中删除
                    freqTable.erase(minFreq);
                }
            }
            freqTable[1].push_front(Node(key, val, 1));
            keyTable[key] = freqTable[1].begin();
            minFreq = 1;
        }
    }

    struct Node {
        int key, val, freq;
        Node(int _key, int _val, int _freq) : key(_key), val(_val), freq(_freq) {}
    };

    int capacity;
    int minFreq;  // 目前的最低频率(1或单调增加)
    unordered_map<int, list<Node>::iterator> keyTable;
    unordered_map<int, list<Node>> freqTable;
};
```

### Python

```python
class Node:
    def __init__(self, key, val):
        self.key, self.val = key, val
        self.prev = self.next = None
        self.freq = 0

def init_linked_list():
    new, old = Node(0, 0), Node(0, 0)
    new.next, old.prev = old, new
    return (new, old)
        
class LFUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.min_freq = 0
        self.key_map = {}
        self.freq_map = collections.defaultdict(init_linked_list)

    def get(self, key: int) -> int:
        if key not in self.key_map:
            return -1
        node = self.key_map[key]
        self._increase(node)
        return node.val

    def put(self, key: int, value: int) -> None:
        if self.capacity == 0:
            return None
        
        if key in self.key_map:
            node = self.key_map[key]
            node.val = value
        else:
            node = Node(key, value)
            self.key_map[key] = node
        
        if len(self.key_map) > self.capacity:
            new, old = self.freq_map[self.min_freq]
            oldest = old.prev
            self._delete(oldest)
            del self.key_map[oldest.key]
        self._increase(node)
    
    def _increase(self, node):
        node.freq += 1
        if node.freq > 1:
            self._delete(node)
        self._add(node.freq, node)
        if node.freq == 1:
            self.min_freq = 1
        elif node.freq - 1 == self.min_freq:
            new, old = self.freq_map[self.min_freq]
            if new.next is old:
                self.min_freq = node.freq

    def _add(self, freq, node):
        new, old = self.freq_map[freq]
        nxt = new.next
        nxt.prev = new.next = node
        node.prev, node.next = new, nxt
        
    def _delete(self, node):
        prev, nxt = node.prev, node.next
        prev.next, nxt.prev = nxt, prev
        

# Your LFUCache object will be instantiated and called as such:
# obj = LFUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
```
