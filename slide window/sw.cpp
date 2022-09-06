#include<iostream>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<stdlib.h>
#include"SlideWindow.h"

using namespace std;

int lengthOfLongestSonstring(string s) {
	int n = s.length();
	unordered_set<char> uset;
	int right = 0;
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			uset.erase(s[i - 1]);
		}

		while (right < n && !uset.count(s[right])) {
			uset.insert(s[i]);
			++right;
		}
		ret = max(ret, (int)uset.size());
	}
	return ret;
}


vector<vector<int>>& floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
	const int dx[4] = { 1,0,0,-1 };
	const int dy[4] = { 0,1,-1,0 };

	if (image[sr][sc] == newColor) return image;
	int n = image.size(), m = image[0].size();
	int CurrCol = image[sr][sc];
	queue<pair<int, int>> que;

	que.emplace(sr, sc);
	image[sr][sc] = newColor;

	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int mx = x + dx[i], my = y + dy[i];
			while (mx >= 0 && mx < n && my >= 0 && my < m && image[mx][my] == CurrCol) {
				que.emplace(mx, my);
				image[mx][my] = newColor;
			}
		}
	}
	return image;
}

int dfs(vector<vector<int>>& grid, int x, int y) {
	if (x < 0 || x == grid.size() || y < 0 || y == grid[0].size()|| grid[x][y] == 0) return 0;
	const int dx[4] = { 1,0,0,-1 };
	const int dy[4] = { 0,1,-1,0 };

	grid[x][y] = 0;
	
	int ans = 1;
	
	for (int i = 0; i < 4; i++) {
		int mx = x + dx[i], my = y + dy[i];
		ans += dfs(grid, mx, my);
	}

	return ans;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
	int col = grid.size(), row = grid[0].size();
	int ans = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			ans = max(ans, dfs(grid, i, j));
		}
	}
	return ans;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
	if (root1 == nullptr) return root2;
	if (root2 == nullptr) return root1;

	TreeNode* merge = new TreeNode(root1->val + root2->val);
	auto q = queue<TreeNode*>();
	auto q1 = queue<TreeNode*>();
	auto q2 = queue<TreeNode*>();

	q.emplace(merge);
	q1.emplace(root1);
	q2.emplace(root2);

	while (!q1.empty() && q2.empty()) {
		auto node = q.front(), node1 = q1.front(), node2 = q2.front();
		auto left1 = node1->left, left2 = node2->left, right1 = node1->right, right2 = node2->right;
		q.pop();
		q1.pop();
		q2.pop();

		if (left1 != nullptr || left2 != nullptr) {
			if (left1 != nullptr && left2 != nullptr) {
				TreeNode* left = new TreeNode(left1->val + left2->val);
				node->left = left;
				q.emplace(left);
				q1.emplace(left1);
				q2.emplace(left2);
			}
			else if (node1->left != nullptr && node2->left == nullptr) {
				node->left = left1;
			}
			else if (node1->left == nullptr && node2->left != nullptr) {
				node->left = left2;
			}

			if (node1->right != nullptr && node2->right != nullptr) {
				auto right = new TreeNode(right1->val + right2->val);
				node->right = right;
				q.emplace(right);
				q1.emplace(right1);
				q2.emplace(right2);
			}
			else if (node1->right != nullptr && node2->right == nullptr) {
				node->right = right1;
			}
			else if (node1->right == nullptr && node2->right != nullptr) {
				node->right = right2;
			}
		}
	}
	return merge;
}

int main() {
	string str = "#_";
	int num3 = 1 ^ 3 ^ 4;
	cout << num3 << endl;
	MaxWindow maxw;
	vector<int> nums({ 1,3,-1,-3,5,3,6,7 });
	vector<int> ans = maxw.maxSlidingWindow(nums, 3);

	MinWindow window;
	string src = "abc";
	string t = "bc";
	int pos = src.find_first_of("X");
	
	string win = window.minWindow(src, t);
	const int num = 5;
	int tmp = num;
	string s = "abcabcbb";
	int len = lengthOfLongestSonstring(s);
	cout << s.substr(1,2) << endl;

	vector<vector<int>> grid = { {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 }, { 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0 }, { 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 } };

	int k = maxAreaOfIsland(grid);
	cout << k << endl;
	return 0;
}