#include <bits/stdc++.h>
using namespace std;
int main(){
    string c,s;cin>>c>>s;string o;
    if(c=="E"){
        for(size_t i=0;i<s.size();){size_t j=i;while(j<s.size()&&s[j]==s[i])j++;o+=s[i];o+=to_string(j-i);i=j;}
    }else for(size_t i=0;i+1<s.size();i+=2)o+=string(s[i+1]-'0',s[i]);
    cout<<o<<"\n";
}
