#include <bits/stdc++.h>
using namespace std;
int main(){
    const char* t[26]={"@","8","(","|)","3","#","6","[-]","|","_|","|<","1","[]\\/[]","[]\\[]","0","|D","(,)","|Z","$","']['","|_|","\\/","\\/\\/","}{","`/","2"};
    // one line of text; scraped samples may carry a leading blank line, so skip empty lines
    string s, ln;
    while(getline(cin,ln)){ if(!ln.empty() && ln!="\r"){ s=ln; break; } }
    string o;
    for(char c:s){
        if(c=='\r') continue;
        if(isalpha((unsigned char)c)) o+=t[tolower(c)-'a']; else o+=c;
    }
    cout<<o<<"\n";
}
