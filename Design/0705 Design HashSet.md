```cpp

```

seperate chaining
```java
class MyHashSet {
    private static final int BUCKETS = 1009;
    private LinkedList[] data;

    public MyHashSet() {
        data = new LinkedList[BUCKETS];
        for (int i = 0; i < BUCKETS; ++i) {
            data[i] = new LinkedList<Integer>();
        }
    }
    
    public void add(int key) {
        int h = hash(key);
        Iterator<Integer> iterator = data[h].iterator();
        while (iterator.hasNext()) {
            Integer elem = iterator.next();
            if (elem == key) {
                return;
            }
        }
        data[h].offerLast(key);
    }
    
    public void remove(int key) {
        int h = hash(key);
        Iterator<Integer> iterator = data[h].iterator();
        while (iterator.hasNext()) {
            Integer elem = iterator.next();
            if (elem == key) {
                data[h].remove(elem);
                return;
            }
        }
    }
    
    public boolean contains(int key) {
        int h = hash(key);
        Iterator<Integer> iterator = data[h].iterator();
        while (iterator.hasNext()) {
            Integer elem = iterator.next();
            if (elem == key) {
                return true;
            }
        }
        return false;
    }

    private static int hash(int key) {
        return key % BUCKETS;
    }
}

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet obj = new MyHashSet();
 * obj.add(key);
 * obj.remove(key);
 * boolean param_3 = obj.contains(key);
 */
```
