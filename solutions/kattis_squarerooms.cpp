#include <bits/stdc++.h>
using namespace std;
int n,m; char g[105][105]; int lab[105][105]; int pre[105][105];
int rooms=0;
int h[105]; unordered_set<unsigned long long> failed;
inline int cntT(int r1,int c1,int r2,int c2){ // inclusive
    return pre[r2+1][c2+1]-pre[r1][c2+1]-pre[r2+1][c1]+pre[r1][c1];
}
bool rec(int pos){
    while(pos<n*m){
        int r=pos/m,c=pos%m;
        if(g[r][c]!='#'&&lab[r][c]<0)break;
        pos++;
    }
    if(pos==n*m)return true;
    int r=pos/m,c=pos%m;
    // state = position + skyline of covered cells; memoize dead states
    unsigned long long key=pos+1;
    for(int j=0;j<m;j++){
        int e=max(h[j], j<c? r+1 : r);
        key=key*1000003ULL+e+7; key^=key>>29;
    }
    if(failed.count(key))return false;
    // determine max size by free cells
    int id=rooms;
    vector<int> cand;
    for(int s=1;r+s<=n&&c+s<=m;s++){
        bool ok=true;
        for(int k=0;k<s&&ok;k++){
            if(g[r+s-1][c+k]=='#'||lab[r+s-1][c+k]>=0)ok=false;
            if(g[r+k][c+s-1]=='#'||lab[r+k][c+s-1]>=0)ok=false;
        }
        if(!ok)break;
        int t=cntT(r,c,r+s-1,c+s-1);
        if(t>1)break;
        if(t==1)cand.push_back(s);
    }
    for(int s:cand){
        for(int i=r;i<r+s;i++)for(int j=c;j<c+s;j++)lab[i][j]=id;
        rooms++;
        int oldh[105];
        for(int j=c;j<c+s;j++){oldh[j-c]=h[j];h[j]=r+s;}
        if(rec(pos+s))return true;
        for(int j=c;j<c+s;j++)h[j]=oldh[j-c];
        rooms--;
        for(int i=r;i<r+s;i++)for(int j=c;j<c+s;j++)lab[i][j]=-1;
    }
    failed.insert(key);
    return false;
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)scanf("%s",g[i]);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        lab[i][j]=-1;
        pre[i+1][j+1]=pre[i][j+1]+pre[i+1][j]-pre[i][j]+(g[i][j]=='$');
    }
    if(!rec(0)){puts("elgnatcer");return 0;}
    for(int i=0;i<n;i++){
        string s;
        for(int j=0;j<m;j++){
            if(g[i][j]=='#')s+='#';
            else {int l=lab[i][j]; s+=(l<26?char('A'+l):char('a'+l-26));}
        }
        puts(s.c_str());
    }
}
