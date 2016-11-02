// Given a string s of length n, the Z-Algorithm produces an array
// Z where Z[i] is the length of the longest substring starting from
// S[i] which is also a prefix of S.

#include <string>
#include <vector>

using namespace std;

void z_algo(const string &s, vector<int> &z) {
    int n = (int)s.length();
    int l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        if (i > r) {
            l = r = i;
            while (r < n && s[r - l] == s[r]) r++;
            z[i] = r - l; r--;
        } else {
            int k = i - l;
            if (z[k] < r - i + 1) z[i] = z[k];
            else {
                l = i;
                while (r < n && s[r - l] == s[r]) r++;
                z[i] = r - l; r--;
            }
        }
    }
}
