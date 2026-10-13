#include <bits/stdc++.h>
using namespace std;
int P,N;
int T[1005],F[1005]; char S[1005];
long long ans[1005];
int main(){
    scanf("%d %d",&P,&N);
    for(int i=0;i<N;i++) scanf("%d %d %c",&T[i],&F[i],&S[i]);
    for(int side=0;side<2;side++){
        char ch=side?'L':'R';
        vector<long long> A(P,0),B(P,0); // 0 = free, else end time
        vector<deque<int>> q(P);
        auto process=[&](long long lim){
            while(true){
                long long m=LLONG_MAX;
                for(int l=0;l<P;l++){ if(A[l]) m=min(m,A[l]); if(B[l]) m=min(m,B[l]); }
                if(m==LLONG_MAX||m>lim) break;
                for(int l=0;l<P;l++){ if(A[l]==m) A[l]=0; if(B[l]==m) B[l]=0; }
                for(int l=0;l<P;l++){
                    while(!A[l]&&!q[l].empty()){
                        int car=q[l].front(); q[l].pop_front();
                        ans[car]=m+F[car];
                        if(!B[l]) B[l]=ans[car]; else A[l]=ans[car];
                    }
                }
            }
        };
        for(int i=0;i<N;i++) if(S[i]==ch){
            process(T[i]);
            int open=-1;
            for(int l=0;l<P;l++) if(!A[l]){open=l;break;}
            if(open>=0){
                ans[i]=T[i]+F[i];
                if(!B[open]) B[open]=ans[i]; else A[open]=ans[i];
            } else {
                int bl=0;
                for(int l=1;l<P;l++) if(q[l].size()<q[bl].size()) bl=l;
                q[bl].push_back(i);
            }
        }
        process(LLONG_MAX-1);
    }
    for(int i=0;i<N;i++) printf("%lld\n",ans[i]);
}
