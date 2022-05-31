/*
        Union Find
    Is a data structure that keeps track of elements which
    are split into one or more disjoint sets. Its has two primary
    opeartions: find and union, getComponentSize, is_connected, countComponents
    all operations in: amortized(n)
    Construction: O(n)

    Find:
    given an element UnionFind will tell what group that
    element belongs to.

    Union:
    Merge two groups together.

    Kruskal's minimum spanning tree algorithm
    Amortized constant time O(1).

    Grid percolation

    Network connectivity

    Least common ancestor in trees

    Image processing
*/
#include <cassert>

class UnionFind 
{
    // The number of elements in this union find
    int _size;

    // Used to track size of each component.
    int *sz;

    // id[i] points to the parent of i, if id[i] = i then i is a root node
    int *id;

    int numComponents;

    UnionFind(int size)
    {
        assert(size > 0);

        _size = numComponents = size;
        sz = new int[_size];
        id = new int[_size];

        for (int i = 0; i < size; i++)
        {
            id[i] = i; // Link to itself (self root)
            sz[i] = 1; // Each component is orginally of size one
        }
    }

    // Find which component/set 'p' belongs to, takes amortized contant time.
    int find(int p) 
    {
        // Find the root of the component/set
        int root = p;
        while(root != id[root]) 
            root = id[root];

        // Compress the path leading back to the root.
        // Doing this operation is called "path compression"
        // and is what gives us amortized time complexity.
        while(p != root)
        {
            int next = id[p];
            id[p] = root;
            p = next;
        }
        return root;
    }

    // This is an alternative recursive formulation for the find method
    // int recursive_find(int p)
    // {
    //     if (p == id[p]) return p;
    //     return id[p] = recursive_find(id[p]);
    // }

    // Return whether or not the elements 'p' and 'q' are in
    // the same connected components/set.
    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    // Return the size of the components/set 'p' belongs to
    int componentSize(int p)
    {
        return sz[find(p)];
    }

    // Return the number of elements this UnionFind/Disjoint set
    int size() 
    {
        return _size;
    }

    // Returns the number of remaining components/sets.
    int components()
    {
        return numComponents;
    }

    // Unify the components/sets containing elements 'p' and 'q'
    void unify(int p, int q)
    {

        // The elements are already in the same group!
        if (connected(p,q)) return;

        int root1 = find(p);
        int root2 = find(q);

        // Merge smaller component/set into the larger one.
        if (sz[root1] < sz[root2])
        {
            sz[root2] += sz[root1];
            id[root1] = root2;
            sz[root1] = 0; 
        } else {
            sz[root1] += sz[root2];
            id[root2] = root1;
            sz[root2] = 0;
        }

        // Since the roots found are different we know that
        // the number of components/sets has decreased by one
        numComponents--;
    }
};

int main() 
{


}