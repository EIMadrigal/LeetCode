## 0208 Implement Trie (Prefix Tree)

Trie作为一种树型的数据结构，适合用来store/retrieve字符串的集合，典型的应用包括autocomplete、spellchecker等。

时间复杂度分为：

1. build阶段为$O(n)$，$n$为所有字符串的长度之和。
2. search阶段为$O(k)$，$k$为待查找的字符串长度。



### C++

```cpp
// vector
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() : root(new TrieNode()) {}
    ~Trie() {
        if (root)
            delete root;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* node = root;
        for (const char c : word) {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* node = root;
        for (const char c : word) {
            node = node->children[c - 'a'];
            if (!node)
                return false;
        }
        return node && node->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (const char c : prefix) {
            node = node->children[c - 'a'];
            if (!node)
                return false;
        }
        return node != nullptr;
    }
private:
    struct TrieNode {
        TrieNode() : children(26, nullptr), isWord(false) {}
        ~TrieNode() {
            for (auto child : children)
                if (child)
                    delete child;
        }
        
        vector<TrieNode*> children;
        bool isWord;
    };
    
    TrieNode* root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```
 
```cpp
// hashmap
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() : root(new TrieNode()) {}
    ~Trie() {
        if (root)
            delete root;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* node = root;
        for (const char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* node = root;
        for (const char c : word) {
            if (!node->children.count(c)) return false;
            node = node->children[c];
        }
        return node->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (const char c : prefix) {
            if (!node->children.count(c)) return false;
            node = node->children[c];
        }
        return true;
    }
private:
    struct TrieNode {
        TrieNode() : isWord(false) {}
        ~TrieNode() {
            for (auto p : children)
                if (p.second)
                    delete p.second;
        }
        
        unordered_map<char, TrieNode*> children;
        bool isWord;
    };
    
    TrieNode* root;
};
```


### Python

```python
class TrieNode:
    def __init__(self):
        self.children = {}
        self.endOfWord = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        cur = self.root
        for c in word:
            if c not in cur.children:
                cur.children[c] = TrieNode()
            cur = cur.children[c]
        cur.endOfWord = True

    def search(self, word: str) -> bool:
        cur = self.root
        for c in word:
            if c not in cur.children:
                return False
            cur = cur.children[c]
        return cur.endOfWord
            
    # because of this func we cannot use hashmap to do insert and search
    def startsWith(self, prefix: str) -> bool:
        cur = self.root
        for c in prefix:
            if c not in cur.children:
                return False
            cur = cur.children[c]
        return True


# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)
```


### Java


