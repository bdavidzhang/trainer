#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;cin>>n>>k;vector<int> st;string s;
 for(int i=0;i<k;i++){cin>>s;if(s=="undo"){int m;cin>>m;while(m--&&!st.empty())st.pop_back();}else st.push_back(stoi(s));}
 long long p=0;for(int x:st)p+=x;p=((p%n)+n)%n;cout<<p<<endl;}
