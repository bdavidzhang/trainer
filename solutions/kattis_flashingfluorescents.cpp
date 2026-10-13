#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; cin>>s; int n=s.size();
    int target=0; for(int i=0;i<n;i++) if(s[i]=='0') target|=1<<i;
    vector<char> cur(1<<n,0),nxt; cur[0]=1;
    for(int t=0;;t++){
        if(cur[target]){ printf("%d\n",t); return 0; }
        int L=t+1; // new available press with reach L
        nxt=cur;
        for(int i=0;i<n;i++){
            int e=min(n,i+L); int iv=((1<<e)-1)^((1<<i)-1);
            for(int mk=0;mk<(1<<n);mk++) if(cur[mk]) nxt[mk^iv]=1;
        }
        cur.swap(nxt);
    }
}
