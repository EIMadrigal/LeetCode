```cpp
// start from top right corner, O(m + n)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty())
            return false;
        const int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = n - 1;
        while (i < m && j >= 0) {
            if (target == matrix[i][j])
                return true;
            if (target > matrix[i][j])
                ++i;
            else
                --j;
        }
        return false;
    }
};
```
