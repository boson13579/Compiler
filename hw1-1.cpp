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
typedef pair<string, string> pss;
typedef pair<bool, int> pbi;

void ERROR() {
    cout << "invalid input\n";
    exit(0);
}

vector<pss> Scanner(string a) {
    vector<pss> ret;
    for (int i = 0; i < a.size(); i++) {
                if (a[i] == '\n' or a[i] == ' ')
            continue;

        else if (a[i] == '(')
            ret.emplace_back("LBR", "(");

        else if (a[i] == ')')
            ret.emplace_back("RBR", ")");

        else if (a[i] == '.')
            ret.emplace_back("DOT", ".");

        else if (a[i] == '"') {
            int tmp = i;
            do i++;
            while (a[i] != '"' and i < a.size());
            if (a[i] == a.size() or a[i] != '"') ERROR();
            ret.emplace_back("STRLIT", a.substr(tmp, i + 1 - tmp));
        } else {
            int fi = i;
            int tmp = int(a[i]);
            if (!(
                    (tmp >= int('a') and tmp <= int('z')) or
                    (tmp >= int('A') and tmp <= int('Z')) or
                    (tmp == int('_')))) ERROR();

            while (i < a.size()) {
                if (a[i] == '.' or a[i] == '(' or a[i] == ')' or a[i] == '"') break;
                tmp = int(a[i]);
                if (!(
                        (tmp >= int('a') and tmp <= int('z')) or
                        (tmp >= int('A') and tmp <= int('Z')) or
                        (tmp >= int('0') and tmp <= int('9')) or
                        (tmp == int('_')))) ERROR();
                i++;
            }
            ret.emplace_back("ID", a.substr(fi, i - fi));
            i--;
        }
    }
    return ret;
}

// idx edx both include
pbi STMTS(vector<pss> &v, int idx, int edx);
pbi STMT(vector<pss> &v, int idx, int edx);

pbi PRIMARY_TAIL(vector<pss> &v, int idx, int edx) {
    debug("PRIMARY_TAIL", idx, edx);
    if (idx > edx) return pbi(true, edx);

    if (v[idx].ff == "DOT") {
        if (idx + 1 > edx) return pbi(false, edx);
        if (v[idx + 1].ff == "ID")
            return PRIMARY_TAIL(v, idx + 2, edx);
        else return pbi(false, edx);
    }
    if (v[idx].ff == "LBR") {
        int tmpi = idx, count = 1;
        while (count) {
            tmpi++;
            if (tmpi > edx) return pbi(false, edx);
            if (v[tmpi].ff == "LBR") count++;
            if (v[tmpi].ff == "RBR") count--;
        }
        pbi tmp = STMT(v, idx + 1, tmpi - 1);
        if (!tmp.ff) return pbi(false, edx);
        return PRIMARY_TAIL(v, tmpi + 1, edx);
    }

    /*Need check*/
    return pbi(true, v.size());
}

pbi PRIMARY(vector<pss> &v, int idx, int edx) {
    debug("PRIMARY", idx, edx);
    if (v[idx].ff != "ID") return pbi(false, edx);
    return PRIMARY_TAIL(v, idx + 1, edx);
}

pbi STMT(vector<pss> &v, int idx, int edx) {
    debug("STMT", idx, edx);
    if (idx >= edx) return pbi(true, edx);

    if (v[idx].ff == "STRLIT") return pbi(true, idx + 1);
    return PRIMARY(v, idx, edx);
}

pbi STMTS(vector<pss> &v, int idx, int edx) {
    debug("STMTS", idx, edx);
    if (idx >= edx) return pbi(true, edx);

    pbi tmp = STMT(v, idx, edx);
    if (!tmp.ff) return pbi(false, edx);
    tmp = STMTS(v, tmp.ss, edx);
    if (!tmp.ff) return pbi(false, edx);

    return pbi(true, tmp.ss + 1);
}
bool PRO(vector<pss> &v, int idx, int edx) {
    return STMTS(v, idx, edx).first;
}

int main() {
    string tmp, input;

    while (getline(cin, tmp)) input += tmp;

    vector<pss> ans = Scanner(input);
    for (int i = 0; i < ans.size(); i++)
        debug(i, ans[i].ff, ans[i].ss);
    if (PRO(ans, 0, ans.size() - 1))
        for (int i = 0; i < ans.size(); i++)
            cout << ans[i].ff << " " << ans[i].ss << '\n';
    else
        ERROR();

    return 0;
}