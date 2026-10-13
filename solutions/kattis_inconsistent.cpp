#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll N,M;cin>>N>>M;
    // N-1 categories: X = 1/1, Y = (d-1)/d. One category: X = (floor(B/q)+1)/B, Y = 1/q, B=M-N+1.
    ll B=M-N+1;ll bestq=-1,bestg=LLONG_MIN;
    for(ll q=2;q<=M-2*(N-1);q++){ll g=M-2*N+2-q-B/q;if(g>bestg){bestg=g;bestq=q;}}
    ll q=bestq;
    ll rest=M-q; // distribute over N-1 categories, each >=2
    string out;
    for(ll i=0;i<N-1;i++){ll d=(i==N-2)?rest:2;rest-=d;
        out+="1 1 "+to_string(d-1)+" "+to_string(d)+"\n";}
    out+=to_string(B/q+1)+" "+to_string(B)+" 1 "+to_string(q)+"\n";
    fputs(out.c_str(),stdout);
}
