#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


string toString(vector<long long> v) {
    string ans = "{";
    for (long long i: v) {
        ans += to_string(i);
        ans += ", ";
    }
    return ans.substr(0, ans.size() - 2) + "}";
}

class ToSmallest {
private:
    static vector<long long> vectorize(long long n) {
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

    static long long numberize(vector<long long> v) {
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
    
    static vector<long long> sendBackward(long long n) {
        vector<long long> v = vectorize(n);
        cout << toString(v) << endl;
        vector<long long> v_unsorted = v;
        sort(begin(v), end(v));
        cout << toString(v) << endl;
        
        int takeFrom;
        int insertAt;
        
        for (int i = v.size() - 1; i >= 0; i--) {
            if (v[i] != v_unsorted[i]) {
                for (int j = 0; j < i; j++) {
                    if (v[i] == v_unsorted[j]) {
                        insertAt = i;
                        takeFrom = j;
                        j = v.size();
                        i = -1;
                    }
                }
            }
        }
        for (int i = takeFrom; i < insertAt; i++) {
            swap(v_unsorted[i], v_unsorted[i + 1]);
            cout << toString(v_unsorted) << endl;
        }
        vector<long long> ans = {numberize(v_unsorted), takeFrom, insertAt};
        return ans;
    }
    
    static vector<long long> sendForward(long long n) {
        vector<long long> v = vectorize(n);
        cout << toString(v) << endl;
        vector<long long> v_unsorted = v;
        sort(begin(v), end(v));
        cout << toString(v) << endl;
        
        int takeFrom;
        int insertAt;
        
        for (int i = 0; i < v.size(); i++) {
            if (v[i] != v_unsorted[i]) {
                for (int j = v.size() - 1; j >= i + 1; j--) {
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
            cout << toString(v_unsorted) << endl;
        }
        vector<long long> ans = {numberize(v_unsorted), takeFrom, insertAt};
        return ans;
    }

public:
    static vector<long long> smallest(long long n) {
        vector<long long> backward = sendBackward(n);
        vector<long long> forward = sendForward(n);
        if (backward[0] < forward[0]) return backward;
        else if (forward[0] < backward[0]) return forward;
        else if (forward[1] < backward[1]) return forward;
        else if (backward[1] < forward[1]) return backward;
        else return forward;
    }
};

int main() {
    ToSmallest t;
    cout << toString(t.smallest(187863002809)) << endl;
    cout << toString(t.smallest(261235)) << endl;
    cout << toString(t.smallest(209917)) << endl;
    cout << toString(t.smallest(285365)) << endl;
    cout << toString(t.smallest(269045)) << endl;
    cout << toString(t.smallest(296837)) << endl;
    cout << toString(t.smallest(1717466)) << endl;
    return 0;
}
