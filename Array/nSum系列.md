## 1 两数之和
```python
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        records = {}
        for i, num in enumerate(nums):
            if target - num in records:
                return [records[target - num], i]
            records[num] = i
        return
```

## 167 两数之和 II - 输入有序数组
双指针一定会收敛到最优解[l,r]
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) {
            int s = numbers[l] + numbers[r];
            if (s == target) return {l + 1, r + 1};
            if (s < target) ++l;
            else --r;
        }
        return {-1, -1};
    }
};
```

## 170 Two Sum III - Data structure design

## 15 三数之和
```java
class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> ans = new ArrayList<>();
        for (int i = 0; i < nums.length - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int low = i + 1, high = nums.length - 1, sum = -nums[i];
            while (low < high) {
                if (nums[low] + nums[high] == sum) {
                    ans.add(Arrays.asList(nums[i], nums[low], nums[high]));
                    while (low < high && nums[low] == nums[low + 1])
                        ++low;
                    while (low < high && nums[high] == nums[high - 1])
                        --high;
                    ++low;
                    --high;
                } else if (nums[low] + nums[high] < sum) {
                    ++low;
                } else {
                    --high;
                }
            }
        }
        return ans;
    }
}
```

## 633 平方数之和
```cpp
class Solution {
public:
    bool judgeSquareSum(int c) {
        int l = 0, r = sqrt(c);
        while (l <= r) {
            if (l * l == c - r * r) return true;
            if (l * l < c - r * r) ++l;
            else --r;
        }
        return false;
    }
};
```

## 
