#include <map>
#include <iostream>
using namespace std;


int main() {
    int n;
    cin >> n;
    map<string,int> data;
    for ( int i = 0; i<n; i++){
        string in;
        cin >> in;
        auto element = data.find(in);
        if (element!= data.end())
            element->second++;
        else
            data.emplace(in,1);
    }
    int q;
    cin >> q;
    for (int i = 0; i<q; i++){
        string in;
        cin >> in;
        auto f = data.find(in);
        int res = f==data.end() ? 0 : f->second;
        cout << res << endl;
    }
    return 0;
}
