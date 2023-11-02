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

int main() {

    ios::sync_with_stdio(0), cin.tie(0);
    string a;
    while (getline(cin, a)) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] == '(')
                cout << "LPR\n";
            else if (a[i] == ')')
                cout << "RPR\n";
            else if (a[i] == '+')
                cout << "PLUS\n";
            else if (a[i] == '-')
                cout << "MINUS\n";
            else if (a[i] == '*')
                cout << "MUL\n";
            else if (a[i] == '/')
                cout << "DIV\n";
            else if (a[i] == '0')
                cout << "NUM 0\n";
            else if (int(a[i]) >= int('1') and int(a[i]) <= int('9')) {
                cout << "NUM ";
                do {
                    cout << a[i];
                    i++;
                } while (int(a[i]) >= int('0') and int(a[i]) <= int('9'));
                i--;
                cout << "\n";
            }
        }
    }

    return 0;
}