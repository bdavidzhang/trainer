#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,c,s,t; scanf("%d %d %d %d",&r,&c,&s,&t);
    vector<string> g(r);
    char buf[3105];
    for(int i=0;i<r;i++){ scanf("%3100s",buf); g[i]=buf; }
    vector<int> h(c,0),L(c),R(c),st,pre(c+1,0);
    vector<char> canon(c);
    long long ans=0;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++) h[j]= g[i][j]=='.' ? h[j]+1 : 0;
        if(i+1<r) for(int j=0;j<c;j++) pre[j+1]=pre[j]+(g[i+1][j]=='0');
        st.clear();
        for(int j=0;j<c;j++){
            while(!st.empty()&&h[st.back()]>h[j]) st.pop_back();
            // top has h<=h[j]
            if(!st.empty()&&h[st.back()]==h[j]){ canon[j]=0; L[j]=L[st.back()]; }
            else { canon[j]=1; L[j]= st.empty()?-1:st.back(); }
            st.push_back(j);
        }
        st.clear();
        for(int j=c-1;j>=0;j--){
            while(!st.empty()&&h[st.back()]>=h[j]) st.pop_back();
            R[j]= st.empty()?c:st.back();
            st.push_back(j);
        }
        for(int j=0;j<c;j++) if(canon[j]&&h[j]>0){
            int W=R[j]-L[j]-1,Hh=h[j];
            if(!((Hh>=s&&W>=t)||(Hh>=t&&W>=s))) continue;
            if(i+1<r && pre[R[j]]-pre[L[j]+1]==0) continue;
            ans++;
        }
    }
    printf("%lld\n",ans);
}
