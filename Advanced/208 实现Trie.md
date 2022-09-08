```cpp
// vector
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() : root(new trieNode()) {}
    
    ~Trie() {
        if(root)
            delete root;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        trieNode* node = root;
        for(const char c : word) {
            if(!node->children[c - 'a'])
                node->children[c - 'a'] = new trieNode();
            node = node->children[c - 'a'];
        }
        node->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        const trieNode* node = find(word);
        return node && node->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }
private:
    struct trieNode {
        trieNode() : children(26, nullptr), isWord(false) {}
        
        ~trieNode() {
            for(auto child : children)
                if(child)
                    delete child;
        }
        
        vector<trieNode*> children;
        bool isWord;
    };
    
    const trieNode* find(string word) {
        const trieNode* node = root;
        for(const char c : word) {
            node = node->children[c - 'a'];
            if(!node)
                return nullptr;
        }
        return node;
    }
    
    trieNode* root;
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
    Trie() : root(new trieNode()) {}
    
    ~Trie() {
        if(root)
            delete root;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        trieNode* node = root;
        for(const char c : word) {
            auto p = node->children.emplace(c, nullptr);
            if(p.second)  // insert successfully
                p.first->second = new trieNode();  // key does not exist yet, replace nullptr with trieNode
            node = p.first->second;
        }
        node->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        const trieNode* node = find(word);
        return node && node->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }
private:
    struct trieNode {
        trieNode() : isWord(false) {}
        
        ~trieNode() {
            for(auto p : children)
                if(p.second)
                    delete p.second;
        }
        
        unordered_map<char, trieNode*> children;
        bool isWord;
    };
    
    const trieNode* find(string word) {
		const trieNode* node = root;
		for (const char c : word) {
			auto it = node->children.find(c);
			if (it == node->children.end())
				return nullptr;
			else
				node = it->second;
		}
		return node;
	}
    
    trieNode* root;
};
```

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
