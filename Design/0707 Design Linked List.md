```python
# 1 use singly linked list
class Node:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class MyLinkedList:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.dummy = Node()
        self.cnt = 0

    def get(self, index: int) -> int:
        """
        Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        """
        if 0 <= index < self.cnt:
            cur = self.dummy
            for _ in range(index + 1):
                cur = cur.next
            return cur.val
        return -1

    def addAtHead(self, val: int) -> None:
        """
        Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
        """
        self.addAtIndex(0, val)

    def addAtTail(self, val: int) -> None:
        """
        Append a node of value val to the last element of the linked list.
        """
        self.addAtIndex(self.cnt, val)

    def addAtIndex(self, index: int, val: int) -> None:
        """
        Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
        """
        if index < 0:
            index = 0
        elif index > self.cnt:
            return
        node = Node(val)
        cur = self.dummy
        for _ in range(index):
            cur = cur.next
        node.next = cur.next
        cur.next = node
        self.cnt += 1

    def deleteAtIndex(self, index: int) -> None:
        """
        Delete the index-th node in the linked list, if the index is valid.
        """
        if 0 <= index < self.cnt:
            cur = self.dummy
            for _ in range(index):
                cur = cur.next
            cur.next = cur.next.next
            self.cnt -= 1


# Your MyLinkedList object will be instantiated and called as such:
# obj = MyLinkedList()
# param_1 = obj.get(index)
# obj.addAtHead(val)
# obj.addAtTail(val)
# obj.addAtIndex(index,val)
# obj.deleteAtIndex(index)


# 2 use doubly linked list
class Node:
    def __init__(self, val=0, next=None, prev=None):
        self.val = val
        self.next, self.prev = next, prev

class MyLinkedList:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.dummy_head, self.dummy_tail = Node(), Node()
        self.dummy_head.next, self.dummy_tail.prev = self.dummy_tail, self.dummy_head
        self.cnt = 0

    def get(self, index: int) -> int:
        """
        Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        """
        if 0 <= index < self.cnt:
            if index < self.cnt // 2:
                cur = self.dummy_head
                for _ in range(index + 1):
                    cur = cur.next
            else:
                cur = self.dummy_tail
                for _ in range(self.cnt - index):
                    cur = cur.prev
            return cur.val
        return -1

    def addAtHead(self, val: int) -> None:
        """
        Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
        """
        self.addAtIndex(0, val)

    def addAtTail(self, val: int) -> None:
        """
        Append a node of value val to the last element of the linked list.
        """
        self.addAtIndex(self.cnt, val)

    def addAtIndex(self, index: int, val: int) -> None:
        """
        Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
        """
        if index < 0:
            index = 0
        elif index > self.cnt:
            return
        node = Node(val)
        if index < self.cnt // 2:
            cur = self.dummy_head
            for _ in range(index):
                cur = cur.next
            node.next = cur.next
            cur.next = node
            node.next.prev = node
            node.prev = cur
        else:
            cur = self.dummy_tail
            for _ in range(self.cnt - index):
                cur = cur.prev
            node.prev = cur.prev
            cur.prev = node
            node.prev.next = node
            node.next = cur
        self.cnt += 1

    def deleteAtIndex(self, index: int) -> None:
        """
        Delete the index-th node in the linked list, if the index is valid.
        """
        if 0 <= index < self.cnt:
            if index < self.cnt // 2:
                cur = self.dummy_head
                for _ in range(index):
                    cur = cur.next
                cur.next = cur.next.next
                cur.next.prev = cur
            else:
                cur = self.dummy_tail
                for _ in range(self.cnt - index - 1):
                    cur = cur.prev
                cur.prev = cur.prev.prev
                cur.prev.next = cur
            self.cnt -= 1
```
