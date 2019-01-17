#include <bits/stdc++.h>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string text, arg;
    int cmd;
    stack<string> history;

    cin >> cmd;
    while (cin >> cmd) {
        switch (cmd) {
            case 1: // Append
                cin >> arg;
                history.push(text);
                text.append(arg);
                break;
            case 2: // Erase
                cin >> cmd;
                history.push(text);
                text.erase(text.length() - cmd);
                break;
            case 3: // Get
                cin >> cmd;
                cout << text[cmd - 1] << '\n';
                break;
            case 4: // Undo
                text = move(history.top());
                history.pop();
                break;
        }
    }
    return 0;
}
