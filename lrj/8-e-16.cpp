#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>

using namespace std;

const int maxn = 5000 + 5;

int T, n;
int a[maxn], b[maxn], maxm[maxn][maxn];
vector< int > vec[maxn];

void to_start(int *x){
    for(int i = 0; i < n; ++i){
        maxm[i][i] = x[i];
        int temp = x[i];
        for(int j = i + 1; j < n; ++j){
            if(x[j] > temp){
                maxm[i][j] = x[j];
                temp = x[j];
            }
            else maxm[i][j] = maxm[i][j-1];
        }
    }
    for(int i = 0; i < n; ++i){
        vec[i].clear();
        for(int j = i + 1; j < n; ++j)
            if(x[j] > x[i]) vec[i].push_back(x[j]);
        sort(vec[i].begin(),vec[i].end());
    }
}

bool judge(int *x){
    to_start(x);
    for(int i = 0; i < n; ++i){
        for(int j = i + 2; j < n; ++j) if(x[j] < x[i])
            if(maxm[i][j-1] > x[i]){
                int pos = lower_bound(vec[j].begin(), vec[j].end(), x[i]) - vec[j].begin();
                if(pos != vec[j].size())
                    if(vec[j][pos] < maxm[i][j-1])
                        return true;
            }
    }
    return false;
}


int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i = 0; i < n; ++i){
            scanf("%d", &a[i]);
            b[n-1-i] = a[i];
        }
        //这种变换并不总是对的。需要结合对换具体考虑。
        if(judge(a) || judge(b)) printf("YES\n"); 
        else printf("NO\n");
    }
    return 0;
}
