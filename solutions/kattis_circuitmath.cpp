#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<bool>v(26);for(int i=0;i<n;i++){char c;cin>>c;v[i]=c=='T';}
 vector<bool>st;string t;while(cin>>t){char c=t[0];
  if(c>='A'&&c<='Z')st.push_back(v[c-'A']);
  else if(c=='-'){bool a=st.back();st.back()=!a;}
  else{bool b=st.back();st.pop_back();bool a=st.back();st.back()=c=='*'?(a&&b):(a||b);}}
 puts(st.back()?"T":"F");}
