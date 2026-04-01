#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		int len = numbers.size();
		int left = 0;
		int right = len - 1;
		while (left < right) {
			int sum = numbers[left] + numbers[right];
			if (sum == target) {
				break;
			} else if (sum < target) {
				++left;
			} else {
				--right;
			}
		}
		vector<int> result = {left + 1, right + 1};
		return result;
	}
};

int main(void) {
	Solution x;
	vector<int> vec = {2, 7, 11, 15};

	vector<int> result = x.twoSum(vec, 9);
	printf("%d %d\n", result[0], result[1]);
}
