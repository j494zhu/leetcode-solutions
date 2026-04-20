#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
	void gameOfLife(vector<vector<int>>& board) {
		int m = board.size();
		int n = board[0].size();
		// since m, n <25, we can just loop through
		// every single cell
		// if the size of the grid is larger, 
		// consider using vector to store grids that
		// will be potentially updated each time
		
		auto is_valid_grid = [&](int x, int y) -> bool {
			return 0 <= x && x <m && 0 <= y && y < n;
		};
		const vector<int> x_shift = {1, 1, 1, 0, 0, -1, -1, -1};
		const vector<int> y_shift = {1, 0, -1, 1, -1, 1, 0, -1};
		auto count_live = [&](int x, int y) -> int {
			const int n = (int)x_shift.size();
			int cnt = 0;
			for (int i = 0; i < n; i++) {
				int nx = x + x_shift[i];
				int ny = y + y_shift[i];
				if (is_valid_grid(nx, ny) && board[nx][ny] == 1) {
					++cnt;
				}
			}
			return cnt;
		};
		vector<int> tmp(m * n);
		int ind = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				int live_neighbors = count_live(i, j);
				if (board[i][j] == 0) {
					if (live_neighbors == 3) {
						tmp[ind] = 1;
					} else {
						tmp[ind] = 0;
					}
				} else {
					if (2 <= live_neighbors && live_neighbors <= 3) {
						tmp[ind] = 1;
					} else {
						tmp[ind] = 0;
					}
				}
				++ind;
			}
		}
		ind = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				board[i][j] = tmp[ind];
				++ind;
			}
		}
		
	}
};