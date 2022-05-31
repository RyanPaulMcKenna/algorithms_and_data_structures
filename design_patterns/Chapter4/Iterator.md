# ITERATOR

**Iterator** is a behavioral design pattern that lets you traverse elements of a collection without exposing its underlying representation (list, stack, tree, etc.).

## :worried: Problem

Collections can be storied in lists, trees, stacks and many other structures.
Common to all of these is the need to access the elements of the collection.

*The same collection can be traversed in many different way; BFS, DFS, Random access, etc.*

Adding more and more traversal algorithms to the collection gradually blurs its primary responsibility. Which is efficient data storage.

## :smiley: Solution

The Iterator pattern suggests extracting the traveersal behaviour of a collection into a seperate object called an iterator.

### Structure

```c++

```