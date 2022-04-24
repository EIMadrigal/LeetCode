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

## 
