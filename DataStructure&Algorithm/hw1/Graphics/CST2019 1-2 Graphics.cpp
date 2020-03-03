// author - Xiao Yijia
#include<cstdio>
#include<stdlib.h>
// store a point in XOY plane
struct Point
{
    int x, y;
    // construction function
    Point(int _x = 0, int _y = 0){x = _x; y = _y;}
};

// ToLeft method is learned from MOOC and CSDN
inline bool ToLeft(Point p, Point q, Point s){
    // to avoid overflow, we need to cast int to long long here
    long long px = p.x; long long py = p.y;
    long long qx = q.x; long long qy = q.y;
    long long sx = s.x; long long sy = s.y;
    return px * qy - py* qx + qx * sy - qy * sx + sx * py - sy * px <= 0;
}

// to use 'qsort' function, we need to define a compare function, the definition below can be found in documentation
inline int cmp(const void * a, const void * b) {return ( *(int*)a - *(int*)b );}

int main(){
    int n, m;
    scanf("%d", &n);
    // 'xs' is used for storing the x-axis value of the n points on x axis
    // 'ys' is used for storing the y-axis value of the n points on y axis
    int *xs = new int[n];
    int *ys = new int[n];
    for(int i = 0;  i < n; i++)
        scanf("%d", &xs[i]);
    for(int i = 0;  i < n; i++)
        scanf("%d", &ys[i]);
    
    // sort the xs and ys, then we can match elements in 'xs' and 'ys' based on index 
    qsort(xs, n, sizeof(int), cmp);
    qsort(ys, n, sizeof(int), cmp);
    
    scanf("%d", &m);
    int x, y;
    // (x, y) is coordinate of the line : (0, 0) to (x, y)
    while (m--){
        scanf("%d %d", &x, &y);
        int lo = 0, hi = n - 1, mid = (lo + hi) >> 1;
        // we need to use binary search, because if we use linear search, time will exceed limit. 
        // Considering the n lines are sorted, we can use bin search to reduce it to log(n)
        // Begin Bin Search: find the LastSmaller value
        while (lo <= hi){
            mid = (lo + hi) >> 1;
            // Here ToLeft is just like '<' in int, it is the result of comparison
            if(!ToLeft(Point(xs[mid], 0), Point(0, ys[mid]), Point(x, y)))
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        printf("%d\n", hi + 1);
    }
    return 0;
}