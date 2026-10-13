#include <bits/stdc++.h>
using namespace std;
int main(){string d="0123456789ACDEFHJKLMNPRTVWX";map<char,char> fix={{'B','8'},{'G','C'},{'I','1'},{'O','0'},{'Q','0'},{'S','5'},{'U','V'},{'Y','V'},{'Z','2'}};
    int w[8]={2,4,5,7,8,10,11,13};
    int P;scanf("%d",&P);while(P--){int K;char s[64];scanf("%d %s",&K,s);
        int v[9];for(int i=0;i<9;i++){char ch=s[i];if(fix.count(ch))ch=fix[ch];v[i]=d.find(ch);}
        long long chk=0,val=0;for(int i=0;i<8;i++){chk+=w[i]*v[i];val=val*27+v[i];}
        if(chk%27!=v[8])printf("%d Invalid\n",K);else printf("%d %lld\n",K,val);}}
