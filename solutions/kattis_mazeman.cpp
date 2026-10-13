#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; string line; getline(cin,line); sscanf(line.c_str(),"%d %d",&n,&m);
    vector<string> g(n);
    for(int i=0;i<n;i++){ getline(cin,g[i]); while(!g[i].empty()&&(g[i].back()=='\r'||g[i].back()=='\n'))g[i].pop_back(); if((int)g[i].size()<m)g[i].resize(m,' '); }
    vector<vector<int>> comp(n,vector<int>(m,-1));
    vector<int> dots; vector<char> ent;
    int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
    auto open=[&](int i,int j){return i>0&&j>0&&i<n-1&&j<m-1&&(g[i][j]==' '||g[i][j]=='.');};
    for(int i=1;i<n-1;i++)for(int j=1;j<m-1;j++) if(open(i,j)&&comp[i][j]<0){
        int c=dots.size(); dots.push_back(0); ent.push_back(0);
        vector<pair<int,int>> st{{i,j}}; comp[i][j]=c;
        while(!st.empty()){ auto [x,y]=st.back(); st.pop_back();
            if(g[x][y]=='.')dots[c]++;
            for(int d=0;d<4;d++){int a=x+dx[d],b=y+dy[d];
                if(a<0||b<0||a>=n||b>=m)continue;
                if(a==0||b==0||a==n-1||b==m-1){ if(g[a][b]>='A'&&g[a][b]<='W')ent[c]=1; continue; }
                if(open(a,b)&&comp[a][b]<0){comp[a][b]=c;st.push_back({a,b});}
            }
        }
    }
    int players=0,un=0;
    for(size_t c=0;c<dots.size();c++){ if(ent[c]){ if(dots[c])players++; } else un+=dots[c]; }
    printf("%d %d\n",players,un);
}
