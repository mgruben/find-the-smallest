#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> vectorize(long long n) {
    vector<long long> rev_ans;
    while (n) {
        rev_ans.push_back(n % 10);
        n /= 10;
    }
    vector<long long> ans;
    while (!rev_ans.empty()) {
        ans.push_back(rev_ans.back());
        rev_ans.pop_back();
    }
    return ans;
}

long long numberize(vector<long long> v) {
    vector<long long> rev_v;
    while (!v.empty()) {
        rev_v.push_back(v.back());
        v.pop_back();
    }
    long long ans = 0;
    while (!rev_v.empty()) {
        ans *= 10;
        ans += rev_v.back();
        rev_v.pop_back();
    }
    return ans;
}

string toString(vector<long long> v) {
    string ans = "{";
    for (int i: v) {
        ans += to_string(i);
        ans += ", ";
    }
    return ans.substr(0, ans.size() - 2) + "}";
}

class toSmallest {
public:
    static vector<long long> sendBackward(long long n) {
        vector<long long> ans;
        
        return ans;
    }
    
    static vector<long long> sendForward(long long n){
        vector<long long> ans;
        return ans;
    }
    static vector<long long> smallest(long long n);
};

int main() {
    cout << numberize(vectorize(261235)) << endl;
    //~ ToSmallest t;
    //~ t.smallest(261235);
    return 0;
}
