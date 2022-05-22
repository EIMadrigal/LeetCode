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
```cpp

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
