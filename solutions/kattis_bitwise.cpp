#include <bits/stdc++.h>
using namespace std;
int n,k; vector<int> a;
bool check(int mask){
    // candidate starts: r+1 where r=0 or prefix OR (masked) from 0 changes at r
    int cur=0;
    for(int r=0;r<n;r++){
        int nw=cur|(a[r]&mask);
        if(r==0||nw!=cur){
            cur=nw;
            int s=r+1, cnt=0, o=0;
            for(int i=s;i<s+n;i++){
                o|=a[i];
                if((o&mask)==mask){cnt++;o=0; if(cnt>=k) return true;}
            }
        }
        if(cur==mask && r>0) { /* no more changes possible */ break; }
    }
    return false;
}
int main(){
    scanf("%d %d",&n,&k); a.resize(2*n+1);
    for(int i=0;i<n;i++){scanf("%d",&a[i]);a[i+n]=a[i];}
    a[2*n]=a[0];
    int ans=0;
    for(int b=29;b>=0;b--) if(check(ans|(1<<b))) ans|=1<<b;
    printf("%d\n",ans);
}
