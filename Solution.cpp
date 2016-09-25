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

class ToSmallest {
public:
    static vector<long long> sendBackward(long long n) {
        vector<long long> v = vectorize(n);
        
        int takeFrom = 0;
        int insertAt = 0;
        int i = 0;
        
        while (i+1 < v.size() && v[i+1] < v[i]) {
            swap(v[i], v[i+1]);
            insertAt++;
            i++;
        }

        vector<long long> ans = {numberize(v), takeFrom, insertAt};
        return ans;
    }
    
    static vector<long long> sendForward(long long n) {
        vector<long long> v = vectorize(n);
        vector<long long> v_unsorted = v;
        sort(begin(v), end(v));
        
        int takeFrom;
        int insertAt;
        
        for (int i = 0; i < v.size(); i++) {
            if (v[i] != v_unsorted[i]) {
                for (int j = i + 1; j < v.size(); j++) {
                    if (v[i] == v_unsorted[j]) {
                        insertAt = i;
                        takeFrom = j;
                        i = j = v.size();
                    }
                }
            }
        }
        for (int i = takeFrom; i > insertAt; i--) {
            swap(v_unsorted[i], v_unsorted[i - 1]);
        }
        vector<long long> ans = {numberize(v_unsorted), takeFrom, insertAt};
        return ans;
    }
    static vector<long long> smallest(long long n);
};

int main() {
    ToSmallest t;
    cout << toString(t.sendForward(261235)) << endl;
    cout << toString(t.sendBackward(209917)) << endl;
    cout << toString(t.sendForward(285365)) << endl;
    cout << toString(t.sendForward(269045)) << endl;
    cout << toString(t.sendForward(296837)) << endl;
    cout << toString(t.sendBackward(1000000)) << endl;

    return 0;
}
