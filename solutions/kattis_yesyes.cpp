#include <bits/stdc++.h>
using namespace std;
// cell state: 0 unknown, 1 black, 2 white
// Solve one line: s[1..L], runs v[1..k]. Returns true if anything changed.
static bool F[105][105],G[105][105];
bool solveLine(vector<int>&s,const vector<int>&v){
    int L=s.size()-1,k=v.size()-1;
    vector<int> wp(L+2,0); // prefix count of white cells
    for(int i=1;i<=L;i++)wp[i]=wp[i-1]+(s[i]==2);
    auto noWhite=[&](int a,int b){return wp[b]-wp[a-1]==0;};
    auto canW=[&](int i){return s[i]!=1;};
    for(int i=0;i<=L+2;i++)for(int j=0;j<=k+2;j++)F[i][j]=G[i][j]=false;
    // F[i][j]: cells 1..i can be filled with exactly runs 1..j
    F[0][0]=true;
    for(int i=1;i<=L;i++)for(int j=0;j<=k;j++){
        bool r=canW(i)&&F[i-1][j];
        if(!r&&j>=1){
            int a=i-v[j]+1;
            if(a>=1&&noWhite(a,i)){
                if(a==1)r=(j==1);
                else r=canW(a-1)&&F[a-2][j-1];
            }
        }
        F[i][j]=r;
    }
    // G[i][j]: cells i..L can be filled with exactly runs j..k
    G[L+1][k+1]=true;
    for(int i=L;i>=1;i--)for(int j=k+1;j>=1;j--){
        bool r=canW(i)&&G[i+1][j];
        if(!r&&j<=k){
            int b=i+v[j]-1;
            if(b<=L&&noWhite(i,b)){
                if(b==L)r=(j==k);
                else r=canW(b+1)&&G[b+2][j+1];
            }
        }
        G[i][j]=r;
    }
    vector<int> diff(L+2,0); vector<char> cw(L+2,0);
    for(int i=1;i<=L;i++){
        if(!canW(i))continue;
        for(int j=0;j<=k;j++)if(F[i-1][j]&&G[i+1][j+1]){cw[i]=1;break;}
    }
    for(int j=1;j<=k;j++)for(int a=1;a+v[j]-1<=L;a++){
        int b=a+v[j]-1;
        if(!noWhite(a,b))continue;
        bool l=(a==1)?(j==1):(canW(a-1)&&F[a-2][j-1]);
        if(!l)continue;
        bool r=(b==L)?(j==k):(canW(b+1)&&G[b+2][j+1]);
        if(!r)continue;
        diff[a]++;diff[b+1]--;
    }
    bool ch=false; int run=0;
    for(int i=1;i<=L;i++){
        run+=diff[i];
        if(s[i]!=0)continue;
        bool cb=run>0;
        if(cb&&!cw[i]){s[i]=1;ch=true;}
        else if(!cb&&cw[i]){s[i]=2;ch=true;}
    }
    return ch;
}
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<int>> rv(n),cv(m);
    for(int i=0;i<n;i++){int p;scanf("%d",&p);rv[i].assign(p+1,0);for(int j=1;j<=p;j++)scanf("%d",&rv[i][j]);
        // drop zero-length runs if any
        vector<int> t{0};for(int j=1;j<=p;j++)if(rv[i][j]>0)t.push_back(rv[i][j]);rv[i]=t;}
    for(int i=0;i<m;i++){int p;scanf("%d",&p);cv[i].assign(p+1,0);for(int j=1;j<=p;j++)scanf("%d",&cv[i][j]);
        vector<int> t{0};for(int j=1;j<=p;j++)if(cv[i][j]>0)t.push_back(cv[i][j]);cv[i]=t;}
    vector<vector<int>> g(n,vector<int>(m,0));
    deque<int> q; vector<char> inq(n+m,1);
    for(int i=0;i<n+m;i++)q.push_back(i);
    while(!q.empty()){
        int x=q.front();q.pop_front();inq[x]=0;
        if(x<n){
            vector<int> s(m+1,0);
            for(int j=0;j<m;j++)s[j+1]=g[x][j];
            if(solveLine(s,rv[x])){
                for(int j=0;j<m;j++)if(g[x][j]!=s[j+1]){g[x][j]=s[j+1];if(!inq[n+j]){inq[n+j]=1;q.push_back(n+j);}}
            }
        }else{
            int c=x-n;
            vector<int> s(n+1,0);
            for(int i=0;i<n;i++)s[i+1]=g[i][c];
            if(solveLine(s,cv[c])){
                for(int i=0;i<n;i++)if(g[i][c]!=s[i+1]){g[i][c]=s[i+1];if(!inq[i]){inq[i]=1;q.push_back(i);}}
            }
        }
    }
    for(int i=0;i<n;i++){
        string o(m,'?');
        for(int j=0;j<m;j++)o[j]=g[i][j]==1?'X':g[i][j]==2?'.':'?';
        puts(o.c_str());
    }
}
