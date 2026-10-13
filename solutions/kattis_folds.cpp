#include <bits/stdc++.h>
using namespace std;
// Dragon curve: D(n) = (1+i)^m - i*D(2^m - n), where 2^(m-1) < n <= 2^m.
static string toDec(vector<long long> c){
    // value = sum c[k]*2^k, c may be negative
    auto norm=[&](vector<long long> v, vector<int>&bits)->bool{
        long long carry=0;bits.clear();
        for(size_t k=0;k<v.size();k++){
            long long d=v[k]+carry;
            long long b=((d%2)+2)%2;
            bits.push_back((int)b);
            carry=(d-b)/2;
        }
        return carry==0;
    };
    c.resize(c.size()+70,0);
    vector<int> bits;bool neg=false;
    if(!norm(c,bits)){neg=true;for(auto&x:c)x=-x;norm(c,bits);}
    vector<int> dec(1,0);
    for(int k=(int)bits.size()-1;k>=0;k--){
        int carry=bits[k];
        for(size_t i=0;i<dec.size();i++){int v=dec[i]*2+carry;dec[i]=v%10;carry=v/10;}
        if(carry)dec.push_back(carry);
    }
    string s;
    bool zero=dec.size()==1&&dec[0]==0;
    if(neg&&!zero)s+='-';
    for(int i=(int)dec.size()-1;i>=0;i--)s+=char('0'+dec[i]);
    return s;
}
int main(){
    string s;cin>>s;
    vector<int> dig;for(char ch:s)dig.push_back(ch-'0');
    vector<int> bits; // LSB first
    while(true){
        bool allz=true;for(int d:dig)if(d){allz=false;break;}
        if(allz)break;
        int rem=0;
        for(size_t i=0;i<dig.size();i++){int v=rem*10+dig[i];dig[i]=v/2;rem=v%2;}
        bits.push_back(rem);
    }
    vector<long long> cx(400,0),cy(400,0);
    int r=0;
    static const int ux[4]={1,0,-1,0},uy[4]={0,1,0,-1};
    static const int vx[4]={1,-1,-1,1},vy[4]={1,1,-1,-1};
    while(true){
        while(!bits.empty()&&bits.back()==0)bits.pop_back();
        if(bits.empty())break;
        int h=bits.size()-1;
        int cnt=0;for(int b:bits)cnt+=b;
        int m=(cnt==1)?h:h+1;
        int e=(r+m/2)%4;
        if(m%2==0){cx[m/2]+=ux[e];cy[m/2]+=uy[e];}
        else{cx[m/2]+=vx[e];cy[m/2]+=vy[e];}
        r=(r+3)%4;
        // n = 2^m - n
        vector<int> nb(m+1,0);
        int borrow=0;
        for(int k=0;k<=m;k++){
            int a=(k==m)?1:0;
            int b=(k<(int)bits.size())?bits[k]:0;
            int d=a-b-borrow;
            if(d<0){d+=2;borrow=1;}else borrow=0;
            nb[k]=d;
        }
        bits=nb;
    }
    cout<<toDec(cx)<<" "<<toDec(cy)<<"\n";
}
