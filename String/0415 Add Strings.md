京东一面
```cpp
class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = num1.length() - 1, j = num2.length() - 1, carry = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || carry) {
            int a = i >= 0 ? num1[i] - '0' : 0;
            int b = j >= 0 ? num2[j] - '0' : 0;
            int tmp = a + b + carry;
            ans += tmp % 10 + '0';
            carry = tmp / 10;
            --i, --j;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```
