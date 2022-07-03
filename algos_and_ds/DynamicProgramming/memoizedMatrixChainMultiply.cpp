#include <iostream>
#include <limits>

#define SIZE 6


int LookupChain(int m[SIZE][SIZE], int p[SIZE+1], int i, int j)
{
    int q;
    if (m[i][j] < std::numeric_limits<int>::max())
    {
        return m[i][j];
    }
    if (i == j)
    {
        m[i][j] = 0;
    } else {
        for (int k = i; k <= j-1;k++)
        {
            q = LookupChain(m,p,i,k) + LookupChain(m,p,k+1,j) + p[i-1]*p[k]*p[j];
            if (q < m[i][j])
            {
                m[i][j] = q;
            }
        }
    }
    return m[i][j];
}

int MemoizedMatrixChain(int m[SIZE][SIZE],int p[SIZE+1])
{
    int n = SIZE;
    for (int i = 0; i <= n;i++)
    {
        for (int j = 0; j <= n; j++)
        {
            m[i][j] = std::numeric_limits<int>::max();
        }
    }
    return LookupChain(m,p,1,n);
}


int main()
{
    int m[SIZE][SIZE]; // costs.
    int p[SIZE+1] = {30,35,15,5,10,20,25}; // dimensions.
    int totalOptimalNoOfCalcs = MemoizedMatrixChain(m,p);

    std::cout << totalOptimalNoOfCalcs << std::endl;

    int x;
    std::cin >> x;
}