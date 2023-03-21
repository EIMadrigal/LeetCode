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
