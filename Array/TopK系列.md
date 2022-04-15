## 215 数组中的第K个最大元素
```cpp
// partition
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int l = 0, r = nums.size() - 1;
	    while (true) {
		    int pivotPos = partition(nums, l, r);
		    if (k - 1 == pivotPos)
			    return nums[pivotPos];
		    if (k - 1 < pivotPos)
                r = pivotPos - 1;
		    else
			    l = pivotPos + 1;
	    }  
    }
private:
    int partition(vector<int>& nums, int low, int high) {
        int pivot = nums[low];
        
        while(low < high) {
            while(low < high && nums[high] <= pivot)
                --high;
            nums[low] = nums[high];
            while(low < high && nums[low] >= pivot)
                ++low;
            nums[high] = nums[low];
        }
        nums[low] = pivot;
        return low;
    }
};

// priority_queue
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q(nums.begin(), nums.end());
        while(--k)
            q.pop();
        return q.top();
    }
};
```
