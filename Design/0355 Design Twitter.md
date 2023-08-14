4 features total, `follow` and `unfollow` need to record each user's followings and delete very quickly. So `unordered_map<int, unordered_set<int>>` can be used. `postTweet` is nothing special, but we need a data structure to store each user's posted tweets. So it may be `unordered_map<int, something>` and `something` could be hashset, linked list, array or others. As for `getNewsFeed`, since it needs the 10 most recent tweets so we should record the time stamp for each tweets. It can be done in `postTweet` and stored together with twitter id. Moreover, the 10 tweets must come from user's followings, we can put all tweets in a heap according to time stamp and pop each to check if the userid meets conditions until 10 entries.

```cpp

```


```java

```
