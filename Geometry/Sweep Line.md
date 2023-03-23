## LintCode 391 数飞机
```java
/**
 * Definition of Interval:
 * public class Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this.start = start;
 *         this.end = end;
 *     }
 * }
 */

public class Solution {
    /**
     * @param airplanes: An interval array
     * @return: Count of airplanes are in the sky.
     */
    public int countOfAirplanes(List<Interval> airplanes) {
        // write your code here
        List<Point> list = new ArrayList<>(airplanes.size() * 2);
        for (Interval airplane : airplanes) {
            list.add(new Point(airplane.start, 1));
            list.add(new Point(airplane.end, 0));
        }
        Collections.sort(list, (Point p1, Point p2) -> {
            if (p1.x == p2.x) return p1.y - p2.y;
            return p1.x - p2.x;
        });
        int res = 0, cur = 0;
        for (Point p : list) {
            if (p.y == 0) cur--;
            else cur++;
            res = Math.max(res, cur);
        }
        return res;
    }
}
```

## 252 Meeting Rooms
```java
public class Solution {
    public boolean canAttendMeetings(Interval[] intervals) {
        Arrays.sort(intervals, (a, b) -> a.start - b.start);
        for (int i = 0; i < intervals.length - 1; ++i) {
            if (intervals[i + 1].start < intervals[i].end) return false;
        }
        return true;
    }
}
```

## 253 Meeting Rooms II
```java
public class Solution {
    public int minMeetingRooms(int[][] intervals) {
        List<int[]> list = new ArrayList<>();
        for (int[] interval : intervals) {
            list.add(new int[]{interval[0], 1});
            list.add(new int[]{interval[1], -1});
        }
        list.sort((a, b) -> a[0] == b[0] ? a[1] - b[1] : a[0] - b[0]);
        int res = 0, cnt = 0;
        for (int[] point : list) {
            cnt += point[1];
            res = Math.max(res, cnt);
        }
        return res;
    }
}

public class Solution {
    public int minMeetingRooms(int[][] intervals) {
        if (intervals.length <= 1) return intervals.length;
        Arrays.sort(intervals, (a, b) -> a[0] - b[0]);
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> a[1] - b[1]);
        heap.offer(intervals[0]);
        for (int i = 1; i < intervals.length; ++i) {
            int[] prev = heap.poll();
            if (intervals[i][0] < prev[1]) heap.offer(intervals[i]);
            else prev[1] = intervals[i][1];
            heap.offer(prev);
        }
        return heap.size();
    }
}

public class Solution {
    public int minMeetingRooms(int[][] intervals) {
        int[] starts = new int[intervals.length], ends = new int[intervals.length];
        for (int i = 0; i < intervals.length; ++i) {
            starts[i] = intervals[i][0];
            ends[i] = intervals[i][1];
        }
        Arrays.sort(starts);
        Arrays.sort(ends);
        int res = 0, end = 0;
        for (int i = 0; i < starts.length; ++i) {
            if (starts[i] < ends[end]) res++;
            else end++;
        }
        return res;
    }
}
```

## 
