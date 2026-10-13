#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n,m,a,c,x; cin>>n>>m>>a>>c>>x;
    vector<long long> v(n);
    for(int i=0;i<n;i++){ x=((a%m)*(x%m)+c)%m; v[i]=x; }
    // iterative stack: (lo,hi,minV,maxV)
    struct St{int lo,hi;long long mn,mx;};
    vector<St> st; st.push_back({0,(int)n-1,-1,LLONG_MAX});
    long long cnt=0;
    while(!st.empty()){
        St s=st.back();st.pop_back();
        if(s.lo>s.hi)continue;
        int mid=(s.lo+s.hi)/2;
        if(v[mid]>s.mn&&v[mid]<s.mx)cnt++;
        st.push_back({s.lo,mid-1,s.mn,min(s.mx,v[mid])});
        st.push_back({mid+1,s.hi,max(s.mn,v[mid]),s.mx});
    }
    cout<<cnt<<endl;
}
