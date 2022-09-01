京东一面没做出来。。。我是傻逼
```cpp
暴力
class Solution {
public:
    int trap(vector<int>& height) {
        // 每个格子储水取决于左边最大值和右边最大值
        int ans = 0;
        for (int i = 1; i < height.size() - 1; ++i) {
            int max_left = 0, max_right = 0;
            for (int j = i; j >= 0; --j) {
                max_left = max(max_left, height[j]);
            }
            for (int j = i; j < height.size(); ++j) {
                max_right = max(max_right, height[j]);
            }
            ans += min(max_left, max_right) - height[i];
        }
        return ans;
    }
};


提前计算每个格子左边的最大值和右边的最大值
class Solution {
public:
    int trap(vector<int>& height) {
        const int n = height.size();
        int ans = 0, maxLeft = 0, maxRight = 0;
        vector<int> left(n, 0);
        vector<int> right(n, 0);
        for(int i = 0;i < n;++i) {
            if(height[i] > maxLeft) {
                maxLeft = height[i];
            }
            left[i] = maxLeft;
        }
        
        for(int i = n - 1;i >= 0;--i) {
            if(height[i] > maxRight) {
                maxRight = height[i];
            }
            right[i] = maxRight;
        }
        
        for(int i = 0;i < n;++i) {
            int curWater = min(left[i], right[i]) - height[i];
            ans += curWater;
        }
        
        return ans;
    }
};


单调栈
# 找右侧第一个比nums[i]大的作为右墙，左墙就是弹出当前元素cur后的栈顶元素
# 遇到右墙就清算其和左墙间所有的蓄水面积，i必然比cur大但是不一定比s.top()大所以取min
# 注意底部宽度不是i - cur而是i - s.top() - 1，比如[4,2,0,3,2,5]的最后一个宽度是4而非2

class Solution:
    def trap(self, height: List[int]) -> int:
        ans = 0
        stack = []
        for i, h in enumerate(height):
            while stack and h > height[stack[-1]]:
                cur_idx = stack.pop()
                if not stack:  # cur没有左墙
                    break
                
                width = i - stack[-1] - 1
                heigh = min(h, height[stack[-1]]) - height[cur_idx]
                ans += width * heigh
            stack.append(i)
        return ans


双指针
max_left和max_right哪个小就可以结算哪边的水量, 相等时结算任意一边均可
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2)
            return 0;
        int ans = 0;
        int i = 1, j = n - 2;
        int max_left = height[0], max_right = height[n - 1];
        while (i <= j) {
            if (max_left < max_right) {
                if (max_left - height[i] > 0) {
                    ans += max_left - height[i]; 
                }
                max_left = max(max_left, height[i]);
                i++;
            } else {
                if (max_right - height[j] > 0) {
                    ans += max_right - height[j];
                }
                max_right = max(max_right, height[j]);
                j--;
            }
        }
        return ans;
    }
};
```
