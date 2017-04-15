// Knuth-Morris-Pratt Algorithm for searching a substring s
// inside another string w (of length k). Returns the 0-based
// index of the first match (k if no match is found).
//
// Running Time: O(k)

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

void precompute_kmp(string &w, VI &t) {
    t = VI((int)w.length());
    int i = 2, j = 0;
    t[0] = -1; t[1] = 0;

    while (i < (int)w.length()) {
        if (w[i-1] == w[j]) { t[i] = j + 1; i++, j++; }
        else if (j > 0) j = t[j];
        else { t[i] = 0; i++; }
    }
}

int KMP(string &s, string &w) {
    int m = 0, i = 0;
    VI t;

    precompute_kmp(w, t);
    while (m + i < (int)s.length()) {
        if (w[i] == s[m + i]) {
            i++;
            if (i == (int)w.length()) return m;
        } else {
            m += (i - t[i]);
            if (i > 0) i = t[i];
        }
    }
    return (int)s.length();
}

int main()
{
  string a = (string) "The example above illustrates the general technique for assembling "+
    "the table with a minimum of fuss. The principle is that of the overall search: "+
    "most of the work was already done in getting to the current position, so very "+
    "little needs to be done in leaving it. The only minor complication is that the "+
    "logic which is correct late in the string erroneously gives non-proper "+
    "substrings at the beginning. This necessitates some initialization code.";
  
  string b = "table";
  
  int p = KMP(a, b);
  cout << p << ": " << a.substr(p, b.length()) << " " << b << endl;
}
