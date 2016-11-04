// Runs Manacher's algorithm to compute the longest palindrome
// in a string in linear time.

#include <string>
#include <vector>

using namespace std;

string preprocess(string &s) {
    int n = (int)s.length();
    if (n == 0) return "^$";
    string ret = "^";
    for (int i = 0; i < n; i++) {
        ret += "#" + s.substr(i, 1);
    }
    ret += "#$";
    return ret;
}

string longestPalindrome(string &s) {
    string T = preprocess(s);
    int n = (int)T.length();
    vector<int> P(n, 0);
    int c = 0, r = 0;
    for (int i = 1; i < n - 1; i++) {
        int i_mirror = 2 * c - i;

        P[i] = (r > i) ? min(r - i, P[i_mirror]) : 0;

        // Attempt to expand palindrome centered at i
        while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
            P[i]++;

        // If palindrome cenetered at i expands past r,
        // adjust center based on expanded palindrome.
        if (i + P[i] > r) {
            c = i;
            r = i + P[i];
        }
    }

    // Find the maximum element in P.
    int maxlen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (P[i] > maxlen) {
            maxlen = P[i];
            centerIndex = i;
        }
    }
    return s.substr((centerIndex - 1 - maxlen) / 2, maxlen);
}

int main() {
    return 0;
}