#include <bits/stdc++.h>
using namespace std;
map<char, vector<string>> mp;
map<char, set<char>> ans;

set<char> first(char A) {
    if (!ans[A].empty()) return ans[A];

    bool emp = false;
    set<char> ret;

    for (auto s : mp[A]) {
        bool tmpemp = true;
        for (auto c : s) {
            if (!isupper(c)) {
                ret.insert(c);
                if (c != ';') tmpemp = false;
                break;
            } else {
                auto tmp = first(c);
                ret.insert(tmp.begin(), tmp.end());
                if (tmp.find(';') == tmp.end()) {
                    tmpemp = false;
                    break;
                }
            }
        }
        emp |= tmpemp;
    }
    if (!emp and ret.find(';') != ret.end()) ret.erase(';');
    return ret;
}

int main() {
    string s;
    while (getline(cin, s) and s != "END_OF_GRAMMAR") {
        char A = s[0];
        stringstream ss(s.substr(2));
        while (getline(ss, s, '|')) {
            mp[A].push_back(s);
        }
    }
    for (auto tmp : mp) {
        if (ans[tmp.first].empty()) {
            ans[tmp.first] = first(tmp.first);
        }
    }

    for (auto tmp : ans) {
        cout << tmp.first << " ";
        for (auto c : tmp.second) {
            cout << c;
        }
        cout << "\n";
    }

    cout << "END_OF_FIRST\n";
}