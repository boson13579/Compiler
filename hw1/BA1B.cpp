#include <bits/stdc++.h>

using namespace std;
#ifdef LOCAL
template <class... T>
void dbg(T... x) {
    char e{};
    ((cerr << e << x, e = ' '), ...);
}
#define debug(x...) dbg("(", #x, ") = ", x, '\n')
#else
#define debug(...) ((void)0)
#endif
#define ff first
#define ss second
vector<string> Token;
vector<string> Origin;
int idx;
set<string> month = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
vector<int> day;

void Scanner(string s) {
    for (int i = 0; i < s.size(); i++) {
 
        // tmp block
        bool tmpid = i + 9 < s.size();
        if (tmpid) {
            for (int t = i + 1; t <= i + 9 and tmpid; t++) {
                if (s[t] < '0' or s[t] > '9') {
                    tmpid = false;
                }
            }
        }

        bool tmphon = i + 8 < s.size();
        if (i + 8 < s.size())
            for (int t = i + 1; t <= i + 8 and tmphon; t++)
                if (s[t] < '0' or s[t] > '9') tmphon = false;

        bool tmpyear = i + 3 < s.size();
        if (i + 3 < s.size())
            for (int t = i + 1; t <= i + 3 and tmpyear; t++)
                if (s[t] < '0' or s[t] > '9') tmpyear = false;

        bool tmpday = false;
        string nowday = "";
        for (int t = 0; t < day.size() and !tmpday; t++) {
            int len = to_string(day[t]).size();
            if (i + len - 1 >= s.size()) continue;
            if ((s.substr(i, len) == to_string(day[t])) and (i + len == s.size() or (s[i + len] < '0' or s[i + len] > '9'))) tmpday = true, nowday = to_string(day[t]);
        }

        bool tmpnat = i + 2 < s.size();
        if (i + 2 < s.size())
            for (int t = i; t <= i + 2; t++)
                if (s[t] < '0' or s[t] > '9') tmpnat = false;

        // main scanner block
        if (s[i] == ' ') continue;
        if (s[i] == '(')
            Token.push_back("LBR"), Origin.push_back(s.substr(i, 1));
        else if (s[i] == ')')
            Token.push_back("RBR"), Origin.push_back(s.substr(i, 1));
        else if (s[i] == '+')
            Token.push_back("PLUS"), Origin.push_back(s.substr(i, 1));
        else if (s[i] == '.')
            Token.push_back("DOT"), Origin.push_back(s.substr(i, 1));
        else if (s[i] == '/')
            Token.push_back("SLASH"), Origin.push_back(s.substr(i, 1));

        else if (i + 2 < s.size() and month.find(s.substr(i, 3)) != month.end())
            Token.push_back("MONTH"), Origin.push_back(s.substr(i, 3)), i += 2;

        else if (s[i] >= 'A' and s[i] <= 'Z' and tmpid)
            Token.push_back("ID"),Origin.push_back(s.substr(i, 10)), i += 9;
            
        else if (s[i] == '9' and tmphon)
            Token.push_back("PHONENUM"), Origin.push_back(s.substr(i, 9)), i += 8;

        else if (tmpyear and (s[i] == '1' or s[i] == '2'))
            Token.push_back("YEAR"), Origin.push_back(s.substr(i, 4)), i += 3;
        else if (tmpnat)
            Token.push_back("NATIONNUM"), Origin.push_back(s.substr(i, 3)), i += 2;
        else if (tmpday)
            Token.push_back("DAY"), Origin.push_back(nowday), i += nowday.size() - 1;

        else {
            Token = {"-1"};
            return;
        }
    }
}

bool Proc();
bool Stmt();
bool phone();
bool date();

int main() {
    // init

    for (int i = 1; i <= 31; i++) day.emplace_back(i);
    reverse(day.begin(), day.end());
    // for(auto i:day) debug(i);
    idx = 0;
    Token.clear();
    Origin.clear();

    string input;
    getline(cin, input);

    Scanner(input);
    // for (int i = 0; i < Token.size(); i++)
    //     debug("debug", Token[i], Origin[i]);
    if (Token[0] != "-1" and Proc() and idx == Token.size())
        for (int i = 0; i < Token.size(); i++)
            cout << Origin[i] << " " << Token[i] << '\n';
    else
        cout << "Invalid input\n";

    return 0;
}

bool Proc() {
    return Stmt();
}
bool Stmt() {
    if (Token[idx++] == "ID")
        return true;
    else idx--;
    if (Token[idx] == "PLUS")
        return phone();
    else
        return date();
}

bool phone() {
    if (Token[idx++] != "PLUS") return false;
    if (Token[idx++] != "LBR") return false;
    if (Token[idx++] != "NATIONNUM") return false;
    if (Token[idx++] != "RBR") return false;
    if (Token[idx++] != "PHONENUM") return false;
    return true;
}

bool date() {
    if (Token[idx] == "YEAR") {
        if (Token[idx++] != "YEAR") return false;
        if (Token[idx++] != "SLASH") return false;
        if (Token[idx++] != "MONTH") return false;
        if (Token[idx++] != "SLASH") return false;
        if (Token[idx++] != "DAY") return false;
        return true;
    } else if (Token[idx] == "MONTH") {
        if (Token[idx++] != "MONTH") return false;
        if (Token[idx++] != "DOT") return false;
        if (Token[idx++] != "DAY") return false;
        if (Token[idx++] != "DOT") return false;
        if (Token[idx++] != "YEAR") return false;
        return true;

    } else
        return false;
}
