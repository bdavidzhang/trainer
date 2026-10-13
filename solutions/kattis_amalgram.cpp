#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string a,b; cin>>a>>b; int ca[26]={0},cb[26]={0};
    for(char c:a)ca[c-'a']++; for(char c:b)cb[c-'a']++;
    string r; for(int i=0;i<26;i++) r.append(max(ca[i],cb[i]),char('a'+i));
    cout<<r<<"\n";
}
