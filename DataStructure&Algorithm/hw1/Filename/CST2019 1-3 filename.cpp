// author - Xiao YijiA
// edit distance -- programming 
#include<cstdio>
int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    char *a = new char[n + 1];
    char *b = new char[m + 1];
    scanf("%s", a);
    scanf("%s", b);
    // a is vertical, b in horizontal
    // if we draw the process, the original figure should be a lenth(a) * lenth(b) table, 
    int hori[2][m + 1] = {{0}};
    for(int i = 0; i <= m; i++){
        hori[0][i] = i;
        // Here I consulted small TA (Yang Yaoliang), originally I initialized the hori[1][i] to 0, but that will prevent array from updating
        // The small TA indicated that the hori[1]'s initialization is wrong
        hori[1][i] = 1000;
    }
    for(int i = 1; i <= n; i++){
        // cur is the current array we use
        // old is the line above the current array
        // these two lines are updated alternatively, to avoid frequent mod2(it takes unnecessary time)， we i % 2 here and store them
        int cur = i % 2;
        int old = (i + 1) % 2;
        hori[cur][0] = i;
        
        // we define the bounds for loop here, to make 'for' loop looks clearer
        int lower = (1 > i - k ? 1 : i - k);
        int upper = (m < i + k ? m : i + k);
        
        // First I used a 2-dim array to test algorithm, memory will boost; then I saw a MOOC from Pku, I learned to use Compressed arrays
        // So then I just used 1 array, but some information will lost(a[i - 1][j - 1])
        // then I consulted small TA Du Junyi, he indicated that I use 2 arrays altenatively to avoid information missing
        for(int j = lower; j <= upper; j++){
            // if the letter is the same, we can just omit them, so the value stays the same 
            if(a[i] == b[j]){
                hori[cur][j] = hori[old][j - 1];
                continue;
            }
            // if not, we need to use dynamic planning to update.
            else{
                hori[cur][j] = hori[cur][j - 1] < hori[old][j] ? hori[cur][j - 1] + 1 : hori[old][j] + 1;
            }
        }
    }
    // print the last line's last value 
    printf("%d", hori[n % 2][m] > k ? -1 : hori[n % 2][m]);
    return 0;
}