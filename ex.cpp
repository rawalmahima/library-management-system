#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s_username;
    string var;
    var = "19CVE1001.txt";
    ifstream inu(var);
    getline(inu, s_username);
    s_username += ",id3-book3";
    ofstream out(var);
    out << s_username;
    return 0;
}