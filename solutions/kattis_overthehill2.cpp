#include <bits/stdc++.h>
using namespace std;
const int M=37;
int val(char c){ if(c>='A'&&c<='Z')return c-'A'; if(c>='0'&&c<='9')return 26+c-'0'; return 36; }
int inv(int a){ for(int i=1;i<M;i++)if(a*i%M==1)return i; return 0; }
int main(){
    string l; getline(cin,l); int n=atoi(l.c_str());
    string P,C; getline(cin,P); getline(cin,C);
    auto strip=[](string&s){ while(!s.empty()&&(s.back()=='\r'||s.back()=='\n'))s.pop_back(); };
    strip(P);strip(C);
    size_t len=max(P.size(),C.size()); len=(len+n-1)/n*n;
    P.resize(len,' ');C.resize(len,' ');
    int R=len/n;
    // rows: [p_i (n) | c_i (n)]
    vector<vector<int>> a(R,vector<int>(2*n));
    for(int i=0;i<R;i++)for(int j=0;j<n;j++){a[i][j]=val(P[i*n+j]);a[i][n+j]=val(C[i*n+j]);}
    int rank=0; vector<int> piv;
    for(int col=0;col<n&&rank<R;col++){
        int s=-1; for(int i=rank;i<R;i++)if(a[i][col]){s=i;break;}
        if(s<0)continue;
        swap(a[s],a[rank]); int iv=inv(a[rank][col]);
        for(int j=0;j<2*n;j++)a[rank][j]=a[rank][j]*iv%M;
        for(int i=0;i<R;i++)if(i!=rank&&a[i][col]){ int f=a[i][col]; for(int j=0;j<2*n;j++)a[i][j]=((a[i][j]-f*a[rank][j])%M+M)%M; }
        piv.push_back(col); rank++;
    }
    for(int i=rank;i<R;i++)for(int j=n;j<2*n;j++)if(a[i][j]){puts("No solution");return 0;}
    if(rank<n){puts("Too many solutions");return 0;}
    // row i of reduced: unknown column i => K[r][i]=a[i][n+r]
    for(int r=0;r<n;r++){ for(int j=0;j<n;j++){ if(j)putchar(' '); printf("%d",a[j][n+r]); } putchar('\n'); }
}
