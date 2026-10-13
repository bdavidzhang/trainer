#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; string s; cin>>n>>k>>s;
    int f=0;
    for(int i=0;i<n;i++){
        if(i==0){ if(s[0]=='R') f++; }
        else if(s[i]==s[i-1]) f++;
    }
    cout<<max(0,k-f)<<"\n";
}
