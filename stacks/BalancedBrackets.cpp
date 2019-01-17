#include <bits/stdc++.h>
using namespace std;



int main() {
    map<char,char>paraBal;
    paraBal[')']='(';
    paraBal[']']='[';
    paraBal['}']='{';
    int t;
    cin >> t;
    while(t--)
        {
        string s;
        stack<char>st;
        cin >> s;
        int flag=0;
        for(int i=0;s[i]!='\0';i++)
            {
            if(s[i]=='(' || s[i]=='{' || s[i]=='[')
                st.push(s[i]);
            else{
                if(!st.empty() and paraBal[s[i]]==st.top())
                 st.pop();
                else
                {
                    flag=1;
                    break;
                }
            }
        }

        (!flag and st.empty()) ? cout << "YES" << endl : cout << "NO " << endl ;

    }
    return 0;
}
