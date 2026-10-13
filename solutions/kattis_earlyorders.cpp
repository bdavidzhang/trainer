#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<int> x(n),last(k+1,-1); for(int i=0;i<n;i++){scanf("%d",&x[i]);last[x[i]]=i;}
    vector<int> st; vector<char> in(k+1,0);
    for(int i=0;i<n;i++){
        int v=x[i]; if(in[v]) continue;
        while(!st.empty()&&st.back()>v&&last[st.back()]>i){in[st.back()]=0;st.pop_back();}
        st.push_back(v); in[v]=1;
    }
    for(size_t i=0;i<st.size();i++) printf("%d%c",st[i],i+1<st.size()?' ':'\n');
}
