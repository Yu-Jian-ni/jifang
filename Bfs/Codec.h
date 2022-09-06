#pragma once
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
#include<queue>
#include<unordered_set>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class Codec
{
public:
	string serialize(TreeNode* root) {
		if (root == nullptr) return "X";
		auto left = "(" + serialize(root->left) + ")";
		auto right = "(" + serialize(root->right) + ")";
		return left + to_string(root->val) + right;
	}

	inline int parseInt(const string& data, int& ptr) {
		int sgn = 1, x = 0;
		if (!isdigit(data[ptr])) {
			++ptr;
			sgn = -1;
		}
		while (isdigit(data[ptr])) {
			x = x * 10 + data[ptr] - '0';
			++ptr;
		}
		return x * sgn;
	}

	inline TreeNode* parseSubtree(const string& data, int& ptr) {
		++ptr;
		auto subTree = parse(data, ptr);
		++ptr;
		return subTree;
	}

	TreeNode* parse(const string& data, int& ptr) {
		if (data[ptr] == 'X') {
			++ptr;
			return nullptr;
		}
		auto node = new TreeNode(0);
		node->left = parseSubtree(data, ptr);
		node->val = parseInt(data, ptr);
		node->right = parseSubtree(data, ptr);

		return node;
	}

	TreeNode* deserialize(string data) {
		int ptr = 0;
		return parse(data, ptr);
	}
};

class Solution {
	vector<vector<int>> ans;
	
public:
	void dfs(bool choosePre, vector<int>& nums, vector<int> path, int cur) {
		if (cur == nums.size()) {
			ans.push_back(path);
			return;
		}

		dfs(false, nums, path, cur + 1);
		if (!choosePre && cur > 0 && nums[cur - 1] == nums[cur]) {
			return;
		}
		path.push_back(nums[cur]);
		dfs(true, nums, path, cur + 1);
		path.pop_back();
	}

	vector<vector<int>> subsetsWithDup(vector<int> &nums) {
		sort(nums.begin(), nums.end());
		vector<int> path;
		dfs(false, nums, path, 0);
		return ans;
	}

	string getPermutation(int n, int k) {
		string str;
		for (int i = 1; i <= n; i++) {
			str += to_string(i);
		}
		
		int i = 0;
		while (i < k - 1) {
			int left = n - 2, right = n - 1;
			while (str[left] > str[left + 1]) {
				--left;
			}
			while (str[right] < str[left]) {
				--right;
			}
			i++;
			swap(str[left], str[right]);
			sort(str.begin() + left + 1, str.end());
		}
		
		return str;
	}
};

class Permute {
	vector < vector<int>> ans;
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		int len = nums.size();
		if (len == 1) {
			ans.push_back(nums);
			return ans;
		}
		vector<int> path;
		vector<bool> used(len, false);
		dfs(nums, path, used, len);
		return ans;
	}

	void dfs(vector<int>& nums, vector<int>& path, vector<bool> used, int len) {
		if (path.size() == len) {
			ans.push_back(path);
			return;
		}

		for (int i = 0; i < len; i++) {
			if (used[i] || (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)) continue;
			else {
				path.push_back(nums[i]);
				used[i] = true;
				dfs(nums, path, used, len);
				used[i] = false;
				path.pop_back();
			}
		}
	}
};

class IpAddress {
	vector<string> ans;
	static constexpr int COUNT = 4;
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string> segs;
		dfs(s, segs, 0);
		return ans;
	}
	void dfs(string& s, vector<string>& segs, int start) {
		if (segs.size() == 4 && start == s.length()) {
			string tmp;
			for (int i = 0; i < 4; i++) {
				tmp += segs[i];
				if (i != 3) {
					tmp += '.';
				}
			}
			ans.push_back(move(tmp));
			return;
		}

		if ((segs.size() == 4 && start != s.length()) || (segs.size() != 4 && start == s.length())) return;

		string cur;
		for (size_t i = 0; i < 3; i++) {
			if (start + i >= s.length()) return;
			cur += s[start + i];
			if (cur.length() > 1 && cur[0] == '0') return;
			if (stoi(cur) <= 255) {
				segs.push_back(cur);
				dfs(s, segs, start + cur.length());
				segs.pop_back();
			}
			else {
				break;
			}
		}
	}
};

class MaxSubArray {
	struct Section {
		int lSum;
		int rSum;
		int sum;
		int mSum;
	};
public:
	Section merge(Section left, Section right) {
		int lSum = max(left.lSum, left.sum + right.lSum);
		int rSum = max(right.rSum, left.rSum + right.sum);
		int sum = left.sum + right.sum;
		int mSum = max(max(left.mSum, right.mSum), left.rSum + right.lSum);
		
		return { lSum, rSum, sum, mSum };
	}
	Section dfs(vector<int>& nums, int left, int right) {
		if (left == right) return { nums[left], nums[left], nums[left], nums[left] };
		int mid = (left + right) / 2;

		return merge(dfs(nums, left, mid), dfs(nums, mid + 1, right));
	}
	int maxSubArray(vector<int>& nums) {
		Section ans = dfs(nums, 0, nums.size() - 1);
		return ans.mSum;
	}
};

class Islands {
public:
	void dfs(vector<vector<char>>& grid, int i, int j, int row, int col) {
		if (i < 0 || j < 0 || i >= row || j >= col || grid[i][j] == '0') return;
		grid[i][j] = '0';
		dfs(grid, i - 1, j, row, col);
		dfs(grid, i + 1, j, row, col);
		dfs(grid, i, j - 1, row, col);
		dfs(grid, i, j + 1, row, col);
	}
	int numIslands(vector<vector<char>>& grid) {
		int row = grid.size();
		int col = grid[0].size();

		int cnt = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (grid[i][j] == '1') {
					++cnt;
					dfs(grid, i, j, row, col);
				}
			}
		}
		return cnt;
	}
};

class FinishCourse {
	vector<int> visited;
	vector<vector<int>> edges;
	bool ans = true;
public:
	void dfs(int i) {
		visited[i] = 1;
		for (int edge : edges[i]) {
			if (visited[edge] == 0) {
				dfs(edge);
				if (!ans) {
					return;
				}
			}
			else if (visited[edge] == 1) {
				ans = false;
				return;
			}
			visited[i] = 2;
		}
	}

	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		visited.resize(numCourses);
		edges.resize(numCourses);

		for (vector<int> pre : prerequisites) {
			edges[pre[1]].push_back(pre[0]);
		}
		for (int i = 0; i < numCourses; i++) {
			if (!visited[i]) {
				dfs(i);
			}
		}
		return ans;
	}
};

class NewCodec {
public:
	void dfs(TreeNode* root, string& ret) {
		if (root == nullptr) {
			ret += "null,";
			return;
		}
		ret += to_string(root->val) + ',';
		dfs(root->left, ret);
		dfs(root->right, ret);
	}
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (root == nullptr) return "";
		string ret;
		dfs(root, ret);
		return ret;
	}

	TreeNode* buildTree(queue<string>& que) {
		if (que.front() == "null") {
			que.pop();
			return nullptr;
		}
		int val = stoi(que.front());
		que.pop();
		TreeNode* root = new TreeNode(val);
		root->left = buildTree(que);
		root->right = buildTree(que);
		return root;
	}
	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.empty()) return nullptr;
		queue<string> que;
		string str;
		for (char c : data) {
			if (c == ',') {
				que.push(str);
				str.clear();
			}
			else {
				str += c;
			}
		}
		return buildTree(que);
	}
};

class RemoveParentheses {
	vector<string> res;
public:
	bool isValid(string& s) {
		int cnt = 0;
		for (char c : s) {
			if (c == '(') {
				++cnt;
			}
			else if (c == ')') {
				if (cnt == 0) return false;
				else {
					--cnt;
				}
			}
		}
		return cnt == 0;
	}
	void backTrack(string& s, int lremove, int rremove, int index) {
		if (lremove < 0 || rremove < 0) {
			return;
		}
		if (lremove == 0 && rremove == 0) {
			if (isValid(s)) {
				res.push_back(s);
			}
			return;
		}
		for (int i = 0; i < s.size(); i++) {
			if (i > 0 && s[i] == s[i - 1]) {
				continue;
			}
			if (s[i] == '(') {
				backTrack(s.erase(i ,1), lremove - 1, rremove, i + 1);
				s.insert(i, "(");
			}
			else if (s[i] == ')') {
				backTrack(s.erase(i, 1), lremove, rremove - 1, i + 1);
				s.insert(i, ")");
			}
		}
	}

	vector<string> removeInvalidParentheses(string s) {
		int lremove = 0;
		int rremove = 0;

		for (char c : s) {
			if (c == '(') {
				++lremove;
			}
			else if (c == ')') {
				if (lremove == 0) {
					++rremove;
				}
				else {
					--lremove;
				}
			}
		}
		backTrack(s, lremove, rremove, 0);
		return res;
	}
};

class RemoveInvalidParentheses {
public:
	template <typename Dtype>
	unsigned int __builtin_popcount(Dtype u) {
		u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
		u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
		u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
		u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
		u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
		return u;
	}

	bool checkValid(const string & str, int lmask, vector<int> & left, int rmask, vector<int> & right) {
		int pos1 = 0;
		int pos2 = 0;
		int cnt = 0;

		for (int i = 0; i < str.size(); i++) {
			if (pos1 < left.size() && i == left[pos1]) {
				if (!(lmask & (1 << pos1))) {
					cnt++;
				}
				pos1++;
			}
			else if (pos2 < right.size() && i == right[pos2]) {
				if (!(rmask & (1 << pos2))) {
					cnt--;
					if (cnt < 0) {
						return false;
					}
				}
				pos2++;
			}
		}

		return cnt == 0;
	}

	string recoverStr(const string & str, int lmask, vector<int> & left, int rmask, vector<int> & right) {
		string ans;
		int pos1 = 0;
		int pos2 = 0;

		for (int i = 0; i < str.size(); i++) {
			if (pos1 < left.size() && i == left[pos1]) {
				if (!(lmask & (1 << pos1))) {
					ans.push_back(str[i]);
				}
				pos1++;
			}
			else if (pos2 < right.size() && i == right[pos2]) {
				if (!(rmask & (1 << pos2))) {
					ans.push_back(str[i]);
				}
				pos2++;
			}
			else {
				ans.push_back(str[i]);
			}
		}

		return ans;
	}

	vector<string> removeInvalidParentheses(string s) {
		int lremove = 0;
		int rremove = 0;
		vector<int> left;
		vector<int> right;
		vector<string> ans;
		unordered_set<string> cnt;

		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(') {
				left.push_back(i);
				lremove++;
			}
			else if (s[i] == ')') {
				right.push_back(i);
				if (lremove == 0) {
					rremove++;
				}
				else {
					lremove--;
				}
			}
		}

		int m = left.size();
		int n = right.size();
		vector<int> maskArr1;
		vector<int> maskArr2;
		for (int i = 0; i < (1 << m); i++) {
			if (__builtin_popcount(i) != lremove) {
				continue;
			}
			maskArr1.push_back(i);
		}
		for (int j = 0; j < (1 << n); j++) {
			if (__builtin_popcount(j) != rremove) {
				continue;
			}
			maskArr2.push_back(j);
		}
		for (auto mask1 : maskArr1) {
			for (auto mask2 : maskArr2) {
				if (checkValid(s, mask1, left, mask2, right)) {
					cnt.insert(recoverStr(s, mask1, left, mask2, right));
				}
			}
		}
		for (auto v : cnt) {
			ans.emplace_back(v);
		}

		return ans;
	}
};

class CoinChange {
	int ret = 0;
public:
	void backTrack(vector<int>& coins, int residual, int k) {
		if (residual == 0) return;

		while (k >= 0 && residual < coins[k]) {
			--k;
		}
		if (k < 0) {
			ret = -1;
			return;
		}
		residual -= coins[k];
		ret++;
		backTrack(coins, residual, k);
	}

	int coinChange(vector<int>& coins, int amount) {
		sort(coins.begin(), coins.end());
		backTrack(coins, amount, coins.size() - 1);
		return ret;
	}
};

struct human {
	int x;
	int y;
	human(int col, int row):x(col), y(row){}
};

class Clearance {
	static int steps[4][2];

public:
	int maxHp(vector<vector<int>>& mat, int hp);
};