#include <vector>
class Solution {
public:
    int countPrimes(int n) {
        int len = n;
        std::vector<bool> not_prime(len);
        for (int i = 2; i * i < len; i++) {
            if (!not_prime[i]) {
                for (int j = i * i; j < len; j += i) {
                    not_prime[j] = true;
                }
            }
        }
        int ans = 0;
        for (int i = 2; i < len; i++) {
            if (!not_prime[i]) ans++;
        }
        return ans;
    }
};