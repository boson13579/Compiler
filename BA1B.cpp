#include <bits/stdc++.h>
using namespace std;
vector<string> Token;
vector<char> Origin;
int idx;
void Scanner(string s) {
    for (auto i : s) {
        if (i == ' ') continue;
        if (i == '(')
            Token.push_back("leftParen"), Origin.push_back(i);
        else if (i == ')')
            Token.push_back("rightParen"), Origin.push_back(i);
        else if (i >= '0' and i <= '9')
            Token.push_back("num"), Origin.push_back(i);
        else if (i >= 'a' and i <= 'z')
            Token.push_back("funcName"), Origin.push_back(i);
        else if (i >= 'A' and i <= 'Z')
            Token.push_back("className"), Origin.push_back(i);
    }
}

bool Proc();
bool Stmt();
bool Class();
bool Func();
bool Args();
bool Arg();

int main() {
    string input;
    getline(cin, input);

    Scanner(input);
    if (Proc() and idx == Token.size())
        for (int i = 0; i < Token.size(); i++)
            cout << Token[i] << " " << Origin[i] << '\n';
    else
        cout << "invalid input\n";

    return 0;
}

bool Proc() {
    return Stmt();
}
bool Stmt() {
    if (Token[idx] == "className")
        return Class();
    else if (Token[idx] == "leftParen")
        return Func();
    else
        return false;
}
bool Class() {
    if (idx + 2 >= Token.size()) return false;
    if (Token[idx++] != "className") return false;
    if (Token[idx++] != "leftParen") return false;
    if (Token[idx++] != "rightParen") return false;
    return Args();
};
bool Func() {
    if (idx + 2 >= Token.size()) return false;
    if (Token[idx++] != "leftParen") return false;
    if (Token[idx++] != "funcName") return false;
    Args();
    if (idx >= Token.size() or Token[idx++] != "rightParen") return false;
    return true;
};
bool Args() {
    if (idx == Token.size()) return true;
    int tmp = idx;
    if (!Arg()) {
        idx = tmp;
        return true;
    }
    return Args();
}
bool Arg() {
    if (Token[idx++] != "num") {
        idx--;
        return Func();
    }
    return true;
}