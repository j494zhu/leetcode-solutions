#include<set>
using namespace std;
class MedianFinder {
private:
	multiset<int> st;
	multiset<int>::iterator it;
	int left, right;
public:
	MedianFinder() {
		it = st.begin();
		left = 0;
		right = 0;
	}
	
	void addNum(int num) {
		st.insert(num);
		if (st.size() == 1) {
			it = st.begin(); 
		} else {
			if (num >= (*it)) ++right;
			else ++left;
			if (left > right) {
				--it;
				--left;
				++right;
			} else if (right > left + 1) {
				++it;
				--right;
				++left;
			}
		}
	}
	
	double findMedian() {
		if (st.size() & 1) return *it;
		auto it2 = next(it);
		return ((*it) + *(it2)) / 2.0;
	}
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
