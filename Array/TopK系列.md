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

## 347 前K个高频元素
```python
维护k个元素的小顶堆 O(nlgk) O(n)
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        cnt = collections.Counter(nums)
        heap = []
        for key, val in cnt.items():
            if len(heap) < k:
                heapq.heappush(heap, (val, key))
            else:
                if val > heap[0][0]:
                    heapq.heapreplace(heap, (val, key))
        return [item[1] for item in heap]


# 基于快排partition O(n) O(n)
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        cnt = list(collections.Counter(nums).items())
        
        def qsort(low, high, k):
            if low >= high:
                return
            
            pivot_idx = random.randint(low, high)
            cnt[pivot_idx], cnt[low] = cnt[low], cnt[pivot_idx]
            smaller_idx = low
            for i in range(low + 1, high + 1):
                if cnt[i][1] >= cnt[low][1]:
                    smaller_idx += 1
                    cnt[smaller_idx], cnt[i] = cnt[i], cnt[smaller_idx]
            cnt[smaller_idx], cnt[low] = cnt[low], cnt[smaller_idx]
            if smaller_idx == k - 1:
                return
            elif smaller_idx > k - 1:
                qsort(low, smaller_idx - 1, k)
            else:
                qsort(smaller_idx + 1, high, k - (smaller_idx - low + 1))

        qsort(0, len(cnt) - 1, k)
        return [item[0] for item in cnt[:k]]
        
        
# 桶排序：对于每种可能的频率1-n创建list O(n) O(n)
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        buckets = [[] for _ in range(1 + len(nums))]
        cnt = collections.Counter(nums)
        for num, freq in cnt.items():
            buckets[freq].append(num)
        flat = list(itertools.chain(*buckets))
        return flat[::-1][:k]
```
