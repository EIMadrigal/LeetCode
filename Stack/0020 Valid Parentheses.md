```cpp
// 遇到左括号压栈，遇到右括号判断其与栈顶的左括号是否匹配，若匹配，弹出
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;    
    
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            } else {
                if (st.empty()) {
                    return false;
                } else if (c == ')' && st.top() != '(') {
                    return false;
                } else if (c == ']' && st.top() != '[') {
                    return false;
                } else if (c == '}' && st.top() != '{') {
                    return false;
                } else {
                    st.pop();
                }
            }
        }
        
        return st.empty();
    }
};
```

```python
class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        dic = {')':'(', ']':'[', '}':'{'}
        for c in s:
            if c in dic.values():
                stack.append(c)
            elif c in dic.keys():
                if len(stack) == 0 or stack.pop() != dic[c]:
                    return False
        return stack == []
```
