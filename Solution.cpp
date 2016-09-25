#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

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
    
    static bool isAscending(long long n) {
        vector<long long> v = vectorize(n);
        for (int i = 0; i < v.size() - 1; i++) {
            if (v[i] > v[i+1]) return false;
        }
        return true;
    }
    
    static vector<long long> sendBackward(long long n) {
        long long min = LONG_LONG_MAX;
        int best_from = 0;
        int best_to = 0;
        vector<long long> v = vectorize(n);
        
        for (int i = 0; i < v.size() - 1; i++) {
            vector<long long> toSwap = v;
            for (int j = i; j < v.size() - 1; j++) {
                swap(toSwap[j], toSwap[j+1]);
                long long this_swap = numberize(toSwap);
                if (this_swap < min) {
                    min = this_swap;
                    best_from = i;
                    best_to = j + 1;
                }
            }
        }
        
        vector<long long> ans = {min, best_from, best_to};
        return ans;
    }
    
    static vector<long long> sendForward(long long n) {
        long long min = LONG_LONG_MAX;
        int best_from = 0;
        int best_to = 0;
        vector<long long> v = vectorize(n);
        
        for (int i = v.size() - 1; i > 0; i--) {
            vector<long long> toSwap = v;
            for (int j = i; j > 0; j--) {
                swap(toSwap[j], toSwap[j-1]);
                long long this_swap = numberize(toSwap);
                if (this_swap < min) {
                    min = this_swap;
                    best_from = i;
                    best_to = j - 1;
                }
                else if (this_swap == min) {
                    if (i < best_from) {
                        best_from = i;
                        best_to = j - 1;
                    }
                    else if (i == best_from) {
                        if (j - 1 < best_to) {
                            best_to = j - 1;
                        }
                    }
                }
            }
        }
        
        vector<long long> ans = {min, best_from, best_to};
        return ans;
    }

public:
    static vector<long long> smallest(long long n) {
        if (isAscending(n)) {
            vector<long long> ans = {n, 0, 0};
            return ans;
        }
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
    cout << toString(t.smallest(1122346)) << endl;
    //~ cout << toString(t.smallest(261235)) << endl;
    //~ cout << toString(t.smallest(209917)) << endl;
    //~ cout << toString(t.smallest(285365)) << endl;
    //~ cout << toString(t.smallest(269045)) << endl;
    //~ cout << toString(t.smallest(296837)) << endl;
    //~ cout << toString(t.smallest(1717466)) << endl;
    return 0;
}
