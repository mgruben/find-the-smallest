#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Debugging helper function
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
    /**
     * Given a long long int n, return as a vector
     * e.g. vectorize(1234) -> {1,2,3,4}
     */
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
    
    /**
     * Given a vector v, return as a long long int
     * e.g. numberize({1,2,3,4}) -> 1234
     */
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
    
    /**
     * Returns true if the given long long int
     * cannot be made smaller.
     * Returns false otherwise
     * e.g. isAscending(1123345567789) -> true
     * e.g. isAscending(91) -> false
     */
    static bool isAscending(long long n) {
        vector<long long> v = vectorize(n);
        for (int i = 0; i < v.size() - 1; i++) {
            if (v[i] > v[i+1]) return false;
        }
        return true;
    }
    
    /**
     * Naively calculates the best swap from an earlier
     * position to a later position.
     * 
     * Since the algorithm ascends insertion points first,
     * then removal points, there is no explicit tie-breaking,
     * because the first lowest solution found is the best,
     * in accordance with the problem statement's
     * i, j preferences.
     */
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
    
    /**
     * Naively calculates the best swap from a later
     * position to an earlier position.
     * 
     * Ties are broken first with preference for a lower
     * removal point, and then with preference for a lower
     * insertion point.  This is in accordance with the
     * problem statement's i, j preferences.
     */
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
                
                // Tie-breaking
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
    /**
     * Given a positive number n, returns the smallest possible
     * single-digit-move number that can result, along with the
     * index i from which moved digit came, and index j at which
     * the moved digit was inserted.
     * 
     * e.g. smallest(261235) -> {126235, 2, 0}
     * e.g. smallest(1000000) -> {1, 0, 6}
     */
    static vector<long long> smallest(long long n) {
        
        // Check if number is already the smallest
        if (isAscending(n)) {
            vector<long long> ans = {n, 0, 0};
            return ans;
        }
        
        /**
         * Naively moving digits backward obtains a different
         * best answer than does naively moving digits forward.
         * 
         * Accordingly, do both, then break ties.
         */
        vector<long long> backward = sendBackward(n);
        vector<long long> forward = sendForward(n);
        
        // If one number is smaller than another
        if (forward[0] < backward[0]) return forward;
        else if (backward[0] < forward[0]) return backward;
        
        /**
         * If the numbers are the same, but one result has
         * a lower removal point than does the other.
         */
        else if (forward[1] < backward[1]) return forward;
        else if (backward[1] < forward[1]) return backward;
        
        /**
         * If the removal points are the same, but one result has
         * a lower insertion point than does the other.
         */
        else if (forward[2] < backward[2]) return forward;
        else if (backward[2] < forward[2]) return backward;
        
        // If results are the same, arbitrarily return one of them
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
