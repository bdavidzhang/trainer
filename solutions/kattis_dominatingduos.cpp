#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int> st;st.reserve(n);long long ans=0;for(int i=0;i<n;i++){int d;scanf("%d",&d);while(!st.empty()&&st.back()<d){st.pop_back();ans++;}if(!st.empty())ans++;st.push_back(d);}printf("%lld\n",ans);}
