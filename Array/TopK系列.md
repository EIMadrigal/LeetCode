## 215 数组中的第K个最大元素
```cpp
// quick select O(n) O(1)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int l = 0, r = nums.size() - 1, target = nums.size() - k;
        while (l < r) {
            int pivotPos = partition(nums, l, r);
            if (pivotPos == target) {
                return nums[pivotPos];
            }
            if (pivotPos < target) {
                l = pivotPos + 1;
            }
            else {
                r = pivotPos - 1;
            }
        }
        return nums[l];
    }
private:
    int partition(vector<int>& nums, int l, int r) {
        srand(time(nullptr));
        int idx = l + rand() % (r - l + 1);
        swap(nums[idx], nums[r]);
        int smallIdx = l - 1;
        for (int i = l; i < r; ++i) {
            if (nums[i] < nums[r]) {
                swap(nums[i], nums[++smallIdx]);
            }
        }
        swap(nums[r], nums[++smallIdx]);
        return smallIdx;
    }
};

// min heap O(nlogk) O(k)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap(nums.begin(), nums.begin() + k);
        for (int i = k; i < nums.size(); ++i) {
            if (nums[i] > heap.top()) {
                heap.pop();
                heap.push(nums[i]);
            }
        }
        return heap.top();
    }
};
```
