class Solution {
	public:
		// 19:29
		vector<vector<char>> grid;
		bool contains = false;
		void rec(int x, int y, string word) {
			if (word.size() == 0) {
				contains = true;
				return;
			}
			char c = ' ';
			if (x - 1 >= 0 && grid[x - 1][y] == word[0] && !contains) {
				c = grid[x - 1][y];
				grid[x - 1][y] = ' ';
				rec(x - 1, y, word.substr(1));
				grid[x - 1][y] = c;
			}
			if (y - 1 >= 0 && grid[x][y - 1] == word[0] && !contains) {
				c = grid[x][y - 1];
				grid[x][y - 1] = ' ';
				rec(x, y - 1, word.substr(1));
				grid[x][y - 1] = c;
			}
			if (x + 1 < grid.size() && grid[x + 1][y] == word[0] && !contains) {
				c = grid[x + 1][y];
				grid[x + 1][y] = ' ';
				rec(x + 1, y, word.substr(1));
				grid[x + 1][y] = c;
			}
			if (y + 1 < grid[0].size() && grid[x][y + 1] == word[0] && !contains) {
				c = grid[x][y + 1];
				grid[x][y + 1] = ' ';
				rec(x, y + 1, word.substr(1));
				grid[x][y + 1] = c;
			}
		}
		bool exist(vector<vector<char>>& board, string word) {
			int n = board.size();
			int m = board[0].size();
			grid.resize(n, vector<char>(m));
			bool word0 = false;
			if (word.size() == 0) {
				return true;
			}
			vector<pair<int, int>> f;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					grid[i][j] = board[i][j];
					if (board[i][j] == word[0]) {
						f.push_back(make_pair(i, j));
						word0 = true;
					}
				}
			}
			if (word.size() == 1) {
				if (word0) {
					return true;
				} else {
					return false;
				}
			}
			for (pair<int, int> p : f) {
				char c = grid[p.first][p.second];
				grid[p.first][p.second] = ' ';
				rec(p.first, p.second, word.substr(1));
				grid[p.first][p.second] = c;
				if (contains) {
					break;
				}
			}
			return contains;
		}
};