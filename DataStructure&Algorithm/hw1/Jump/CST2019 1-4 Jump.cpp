// Author: Xiao Yijia
#include<cstdio>
#include<iostream>
using namespace std;
// the queue user-defined queue
// it can push elements to rear, and pop element from both sides
// The function of this queue is simplifying the search and keep the queue 'monotone increasing'
struct queue{
    int *a = nullptr;
    int head = 0, tail = 0;
    
    // initializing the queue
    queue(int n = 1000100){ a = new int[1000100];}
    
    // check if the queue is empty
    bool empty(){ return head - tail >= 0; }
    
    // return the front and back element of the queue
    int front(){
        return a[head];
    }
    int back(){
        return a[tail - 1];
    }
    
    // push a new element to rear
    void push(int n){ 
        a[tail] = n; 
        tail++;
    }

    // pop the first/last element from the queue
    void pop_head(){ head++; }
    void pop_tail(){ 
        if(!empty()) 
        tail--;
    }
};
struct grid{
    int l, r, t;
};
int main(){
    // read in data, and initialize the queue and f[](used for storing the min-time-cost)
    int n;
    scanf("%d", &n);
    queue q;
    long long *f = new long long [n + 1]();
    f[n] = 0;
    grid *a = new grid[n + 1];
    for(int i = 1; i < n;i++)
        scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].t);
    // at first, the n-th grid's range should be empty, setting left > right can satisfy
    a[n].l = n + 1;
    a[n].r = n;
    // initially, n is in the queue
    q.push(n);
    
    // the main body of the algorithm(Here Zhang Yunsheng taught how the task can be converted using queue)
    // begining from n-th element to 1-st element
    for(int i = n - 1; i >= 1; i--){
        // iterate from left_(i+1) to left_i, pop the tail-elements larger than the new-comer
        for(int l = a[i + 1].l - 1; l >= a[i].l; l--){
            while(!q.empty() && f[l] <= f[q.back()]){
                q.pop_tail();
            }
            // push the new one into queue
            q.push(l);
        }
        // similar to the left part, this time the right bound is moving
        // in left direction, so we need to pop the elements no longer in the [a[i].l, a[i].r]
        for(int r = a[i + 1].r; r > a[i].r; r--){
            if(q.front() == r) {
                q.pop_head();
            }
        }
        // update the time cost
        f[i] =f[q.front()] + a[i].t;
    }
    // DO REMEMBER!!! longlong should use lld!!!
    printf("%lld", f[1]);
    return 0;
}