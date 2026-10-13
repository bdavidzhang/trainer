#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; cin>>s; int h=s.size()/2;
    string a=s.substr(0,h),b=s.substr(h);
    auto rot=[](string&t){int r=0;for(char c:t)r+=c-'A';for(char&c:t)c='A'+(c-'A'+r)%26;};
    rot(a);rot(b);
    for(int i=0;i<h;i++)a[i]='A'+(a[i]-'A'+b[i]-'A')%26;
    cout<<a<<"\n";
}
