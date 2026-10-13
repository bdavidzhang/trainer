#include <bits/stdc++.h>
using namespace std;
// Blocks of three: 3i is always present (index 2i+1), exactly one of 3i+1 / 3i+2 is present
// (index 2i+2), 100000 = 3*33333+1 is the last element. The first guess inside a block's
// pair is declared a miss, which fixes the other one as present.
int main(){
    const int B=33333; // blocks 0..B-1, then 99999, 100000
    int k=2*B+2;
    printf("%d\n",k); fflush(stdout);
    vector<int> miss(B,0); // 0 undecided, 1 => 3i+1 missing, 2 => 3i+2 missing
    int x;
    while(scanf("%d",&x)==1){
        if(x==-1){
            string out;
            for(int i=0;i<B;i++){
                out+=to_string(3*i)+"\n";
                int m=miss[i]==1?3*i+2:3*i+1;
                out+=to_string(m)+"\n";
            }
            out+="99999\n100000\n";
            fputs(out.c_str(),stdout); fflush(stdout);
            return 0;
        }
        int ans;
        if(x==100000) ans=k;
        else if(x%3==0) ans=2*(x/3)+1;
        else{
            int b=x/3, w=x%3;
            if(miss[b]==0){miss[b]=w; ans=-1;}
            else if(miss[b]==w) ans=-1;
            else ans=2*b+2;
        }
        printf("%d\n",ans); fflush(stdout);
    }
    return 0;
}
