/*
1 $
2 A -> aBb --> first(b) -> follow(B) except ; and a can be ;
3.a A -> aB --> follow(A) -> follow(B)
3.b A -> aBb and b can be ; --> follow(A) -> follow(B)
*/
#include <bits/stdc++.h>
using namespace std;
map<char, vector<string>> mp;
map<char, set<char>> firstS, followS;

set<char> first(char A) {
    if (!firstS[A].empty()) return firstS[A];

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
                if (c == A) continue;
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

void Follow() {
    // 1.測資很爛，所以先把S的follow設成$
    auto s = mp['S'][0];
    if (s.back() == '$') followS['S'].insert('$');

    // 2.
    auto Findfirst = [&](char c) -> set<char> {
        if (isupper(c)) {
            auto ret = firstS[c];
            if (ret.find(';') != ret.end()) ret.erase(';');
            return ret;
        } else
            return set<char>{c};
    };

    for (auto [c, v] : mp) {
        for (auto s : v) {
            for (int i = s.size() - 1; i > 0; i--) {
                auto tmp = Findfirst(s[i]);
                int p = i - 1;
                while (p >= 0) {
                    if (isupper(s[p])) {
                        followS[s[p]].insert(tmp.begin(), tmp.end());
                        if (firstS[s[p]].find(';') == firstS[s[p]].end()) break;
                    } else
                        break;
                    p--;
                }
            }
        }
    }

    // 3.
    for (int t = 0; t < mp.size(); t++)
        for (auto [c, v] : mp) {
            for (auto s : v) {
                for (int i = s.size() - 1; i >= 0; i--) {
                    if (isupper(s[i])) {
                        followS[s[i]].insert(followS[c].begin(), followS[c].end());
                        if (firstS[s[i]].find(';') == firstS[s[i]].end()) break;
                    } else
                        break;
                }
            }
        }
}

int main() {
    string s;
    while (getline(cin, s) and s != "END_OF_GRAMMAR") {
        char A = s[0];
        stringstream ss(s.substr(2));
        while (getline(ss, s, '|')) mp[A].push_back(s);
    }
    for (auto tmp : mp)
        if (firstS[tmp.first].empty())
            firstS[tmp.first] = first(tmp.first);

    Follow();

    cout << "First set: \n";
    for (auto tmp : firstS) {
        cout << tmp.first << " ";
        for (auto c : tmp.second) cout << c;
        cout << "\n";
    }

    cout << "Follow set: \n";
    for (auto tmp : followS) {
        cout << tmp.first << " ";
        for (auto c : tmp.second) cout << c;
        cout << "\n";
    }
}
