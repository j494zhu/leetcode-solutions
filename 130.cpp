#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
class Solution {
private:
	vector<pair<int, int>> vec = {};
	bool touch_edge = false;
	int m = 0;
	int n = 0;
	bool in_bound(int x, int y) {
		return x >= 0 && y >= 0 && x < m && y < n;
	}
	void dfs(int x, int y, vector<vector<char>>& board) {
		if (!in_bound(x, y) || board[x][y] != 'O') {
			return;
		}
		if (board[x][y] == 'O') {
			vec.push_back(make_pair(x, y));
			board[x][y] = 'o';
			if (x == 0 || y == 0 || x == m - 1 || y == n - 1) {
				touch_edge = true;
			}
		}
		dfs(x - 1, y, board);
		dfs(x + 1, y, board);
		dfs(x, y - 1, board);
		dfs(x, y + 1, board);
		return;
	}
	void geto(int x, int y, vector<vector<char>>& board) {
		vec= {};
		touch_edge = false;
		m = board.size();
		n = board[0].size();
		dfs(x, y, board);
		if (touch_edge) {
			for (pair<int, int> p : vec) {
				board[p.first][p.second] = 'O';
			}
		} else {
			for (pair<int, int> p : vec) {
				board[p.first][p.second] = 'X';
			}
		}
		return;
	}
public:
	void solve(vector<vector<char>>& board) {
		int m = board.size();
		if (m == 0) return;
		int n = board[0].size();
		
		vector<pair<int, int>> veco;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] == 'X') continue;
				geto(i, j, board);
			}
		}
	}
};
int main(void) {
	
}
