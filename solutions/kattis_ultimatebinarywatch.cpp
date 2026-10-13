#include <bits/stdc++.h>
using namespace std;
int main(){ string t; cin>>t;
    for(int b=3;b>=0;b--){ string r="         "; int pos[4]={0,2,6,8};
        for(int i=0;i<4;i++) r[pos[i]]=((t[i]-'0')>>b&1)?'*':'.';
        cout<<r<<"\n"; } }
