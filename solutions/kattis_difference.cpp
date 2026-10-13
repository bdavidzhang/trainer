#include <bits/stdc++.h>
using namespace std;
int main(){
    long long r,m;cin>>r>>m;
    const long long LIM=200000001LL;
    vector<bool> used(LIM+1,false);
    vector<long long> A;A.push_back(r);
    if(r<=LIM)used[r]=true;
    if(m==r){puts("1");return 0;}
    long long d=1;
    for(int n=2;;n++){
        while(used[d])d++;
        long long x=A.back()+d;
        if(x<=LIM)used[x]=true;
        for(int j=(int)A.size()-1;j>=0;j--){long long df=x-A[j];if(df>LIM)break;used[df]=true;}
        A.push_back(x);
        if(used[m]){printf("%d\n",n);return 0;}
    }
}
