//  still bugs here sob;

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.size() > nums2.size()) {
			swap(nums1, nums2);
		} // nums1 is now always shorter than nums2
		int len1 = nums1.size();
		int len2 = nums2.size();
		auto get1 = [nums1, len1] (int i) {return (i >= len1) ? 1e9 : nums1[i];};
		auto get2 = [nums2, len2] (int i) {return (i >= len2) ? 1e9 : nums2[i];};
		auto valid = [&] (int a_i, int b_i) {return get1(a_i + 1) >= get2(b_i) && get2(b_i + 1) >= get1(a_i);};
		int k = (len1 + len2) / 2;
		int imin = 0;
		int imax = len1 - 1;
		auto calci = [imin, imax] () {return (imin + imax) / 2;};
		int i = calci();
		auto calcj = [i, k] () {return k - 2 - i;};
		int j = calcj();
		while (!valid(i, j) && imin <= imax) {
			if (get1(i + 1) < get2(j)) imax = (imin + imax) / 2 - 1;
			else if (get2(j + 1) < get1(i)) imin = (imin + imax) / 2 + 1;
			i = calci();
			j = calcj();
		}
		if ((len1 + len2) & 1) return max(get1(i), get2(j));
		else return (max(get1(i + 1), get2(j + 1)) + min(get1(i + 1), get2(j + 1))) / 2.0;
	}
};

int main(void) {
	vector<int> vec1 = {1, 2, 3};
	vector<int> vec2 = {4, 5, 6};
	Solution x;
	cout << x.findMedianSortedArrays(vec1, vec2) << endl;
}
