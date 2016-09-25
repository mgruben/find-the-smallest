# find-the-smallest
Find the smallest number resulting from a single digit move

Given a positive number `n`, from which any single digit can be removed and replaced elsewhere, find the smallest number which would result from one such move.

In the event that the same number could be obtained by more than one move:
* Prefer a smaller removal index over a larger removal index, then
* Prefer a smaller insertion index over a larger insertion index.

For example:
```
smallest(261235) --> [126235, 2, 0]
smallest(209917) --> [29917, 0, 1]
```

This project was completed for [CodeWars - Find the smallest](https://www.codewars.com/kata/find-the-smallest).

I recommend that this code should only be viewed _after_ you've completed your own implementation.  
If you're super stuck, take a break, take a walk, and it will come to you; good luck.
