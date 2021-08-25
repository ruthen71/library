// 回文判定
// verified
// ABC 159 B - String Palindrome
// https://atcoder.jp/contests/abc159/submissions/17871564

#include <iostream>
using namespace std;

bool is_palindrome(string s){
    string t(s.rbegin(),s.rend());
    return s == t;
}

int main() {
    string s; cin >> s;
    int n = s.size();
    string ans = (is_palindrome(s) && is_palindrome(s.substr(0, (n-1)/2)) && is_palindrome(s.substr((n+1)/2)))? "Yes" : "No";
    cout << ans << endl;
    return 0;
}
