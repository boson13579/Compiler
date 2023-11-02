#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
using pss = pair<string, string>;

vector<pss> Scanner(string s) {
    vector<pss> res;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') continue;
        else if(i + 1 < s.size() and s.substr(i,2) == "if") res.emplace_back("KEYWORD", s.substr(i, 2)), i+=1;
        else if(i + 3 < s.size() and s.substr(i,4) == "else") res.emplace_back("KEYWORD", s.substr(i, 4)), i+=3;
        else if(i + 4 < s.size() and s.substr(i,5) == "while") res.emplace_back("KEYWORD", s.substr(i, 5)), i+=4;
        else if (s[i] == '+' or s[i] == '-' or s[i] == '*' or s[i] == '/' or s[i] == '=' or s[i] == '(' or \
                 s[i] == ')' or s[i] == '{' or s[i] == '}' or s[i] == '<' or s[i] == '>' or s[i] == ';')
            res.emplace_back("SYMBOL", s.substr(i, 1));
        else if ((s[i] >= 'A' and s[i] <= 'Z') or (s[i] >= 'a' and s[i] <= 'z')) {
            int tmp = i;
            while (i < s.size() and ((s[i] >= 'A' and s[i] <= 'Z') or (s[i] >= 'a' and s[i] <= 'z') or \ 
                                     (s[i] >= '0' and s[i] <= '9')) ) i++;
            res.emplace_back("IDENTIFIER", s.substr(tmp, i - tmp));
            i--;
        } else if (s[i] >= '1' and s[i] <= '9') {
            int tmp = i;
            while (i < s.size() and s[i] >= '0' and s[i] <= '9') i++;
            res.emplace_back("NUM", s.substr(tmp, i - tmp));
            i--;
        } else if (s[i] == '0')
            if (i + 1 < s.size() and s[i + 1] >= '0' and s[i + 1] <= '9')
                return {{"-1", "-1"}};
            else
                res.emplace_back("NUM", "0");
        else res.emplace_back("Invalid", "");
    }
    return res;
}

int main() {
    string in, tmp;
    while(getline(cin, tmp)) in += tmp;
    auto res = Scanner(in);
    if (res[0].ff == "-1")
        cout << "Invalid" << endl;
    else
        for (auto i : res) {
            if(i.ff != "Invalid") 
                cout << i.ff << " \"" << i.ss  << "\""<< endl;
            else
                cout << i.ff << endl;

        }

    return 0;
}