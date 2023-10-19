#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
using pss = pair<string, string>;

vector<pss> Scanner(string s){

    vector<pss> res;
    for(int i=0 ; i<s.size() ; i++){
        
        if(s[i] == ' ') continue;
        if(s[i] == '(') res.emplace_back("LPR", "");
        else if(s[i] == ')') res.emplace_back("RPR", "");
        else if(s[i] == '+' or s[i] == '-' or s[i] == '*' or s[i] == '/' or s[i] == '=') res.emplace_back("OP", s.substr(i, 1));
        else if((s[i] >= 'A' and s[i] <= 'Z') or (s[i] >= 'a' and s[i] <= 'z')){ 
            int tmp = i; 
            while(i<s.size() and ((s[i] >= 'A' and s[i] <= 'Z') or (s[i] >= 'a' and s[i] <= 'z'))) i++;
            res.emplace_back("ID", s.substr(tmp, i-tmp));
            i--;
        }
        else if(s[i] >= '1' and s[i] <= '9'){
            int tmp = i; 
            while(i<s.size() and s[i] >= '0' and s[i] <= '9') i++;
            res.emplace_back("NUM", s.substr(tmp, i-tmp));
            i--;
        }
        else if(s[i] == '0') 
            if(i+1 < s.size() and s[i+1] >= '0' and s[i+1] <= '9') return {{"-1", "-1"}};
            else res.emplace_back("NUM", "0");
        else return {{"-1", "-1"}};
    }
    return res;
}

int main(){

    string in;
    getline(cin, in);
    auto res = Scanner(in);
    if(res[0].ff == "-1") cout << "invalid input" << endl;
    else for(auto i:res) cout << i.ff << " " << i.ss << endl;

    return 0;
}