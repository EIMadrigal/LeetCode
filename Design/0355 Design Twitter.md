4 features total, `follow` and `unfollow` need to record each user's followings and delete very quickly. So `unordered_map<int, unordered_set<int>>` can be used. `postTweet` is nothing special, but we need a data structure to store each user's posted tweets. So it may be `unordered_map<int, something>` and `something` could be hashset, linked list, array or others. As for `getNewsFeed`, since it needs the 10 most recent tweets so we should record the time stamp for each tweets. It can be done in `postTweet` and stored together with twitter id. Moreover, the 10 tweets must come from user's followings and themself, we can put these tweets in a heap according to time stamp and pop each one until 10 entries.

```cpp
class Twitter {
private:
    unordered_map<int, unordered_set<int>> followings;
    unordered_map<int, vector<pair<int, int>>> tweets;  // timestamp, tweetId
    int timestamp = 0;

public:
    Twitter() {}
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].emplace_back(timestamp, tweetId);
        timestamp++;
    }
    
    vector<int> getNewsFeed(int userId) {
        priority_queue<pair<int, int>> pq;
        for (auto tweet : tweets[userId]) {
            pq.push(tweet);
        }
        for (auto following : followings[userId]) {
            for (auto tweet : tweets[following]) {
                pq.push(tweet);
            }
        }

        vector<int> res;
        int num = min(10, (int) pq.size());
        for (int i = 0; i < num; ++i) {
            int tweetId = pq.top().second; pq.pop();
            res.push_back(tweetId);
        }
        return res;
    }
    
    void follow(int followerId, int followeeId) {
        followings[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        followings[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
```

Actually we can use linked list to store tweets. When `getNewsFeed`, the newest tweets from every following will be in a heap and multi-way merge to choose the top 10.

```class Twitter {

    private Map<Integer, Set<Integer>> followings;
    private Map<Integer, Tweet> tweets;  // user -> head of linked list
    private int timestamp = 0;

    private class Tweet {
        private int tweetId;
        private int timestamp;
        private Tweet next;

        public Tweet(int tweetId, int timestamp) {
            this.tweetId = tweetId;
            this.timestamp = timestamp;
        }
    }

    public Twitter() {
        followings = new HashMap<>();
        tweets = new HashMap<>();
    }
    
    public void postTweet(int userId, int tweetId) {
        if (tweets.containsKey(userId)) {
            Tweet oldHead = tweets.get(userId);
            Tweet newHead = new Tweet(tweetId, timestamp);
            newHead.next = oldHead;
            tweets.put(userId, newHead);
        } else {
            tweets.put(userId, new Tweet(tweetId, timestamp));
        }
        timestamp++;
    }
    
    public List<Integer> getNewsFeed(int userId) {
        PriorityQueue<Tweet> maxHeap = new PriorityQueue<>((x, y) -> (y.timestamp - x.timestamp));
        if (tweets.containsKey(userId)) {
            maxHeap.offer(tweets.get(userId));
        }
        Set<Integer> following = followings.get(userId);
        if (following != null) {
            for (Integer id : following) {
                Tweet tweet = tweets.get(id);
                if (tweet != null) {
                    maxHeap.offer(tweet);
                }
            }
        }
        List<Integer> res = new ArrayList<>();
        for (int i = 0; i < 10 && !maxHeap.isEmpty(); ++i) {
            Tweet tweet = maxHeap.poll();
            res.add(tweet.tweetId);
            if (tweet.next != null) {
                maxHeap.offer(tweet.next);
            }
        }
        return res;
    }
    
    public void follow(int followerId, int followeeId) {
        Set<Integer> following = followings.get(followerId);
        if (following == null) {
            Set<Integer> init = new HashSet<>();
            init.add(followeeId);
            followings.put(followerId, init);
        } else {
            following.add(followeeId);
        }
    }
    
    public void unfollow(int followerId, int followeeId) {
        Set<Integer> following = followings.get(followerId);
        if (following == null) {
            return;
        }
        following.remove(followeeId);
    }
}

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * List<Integer> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */

```
