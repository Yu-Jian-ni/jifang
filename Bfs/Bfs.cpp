#include<iostream>
#include<queue>
#include"Codec.h"
using namespace std;

void Dfs(char** grid, int i, int j, int row, int col) {

	if (i < 0 || j < 0 || i >= row || j >= col|| grid[i][j] == '0') return;//Noting the "=="and"="

	grid[i][j] = '0';

	Dfs(grid, i - 1, j, row, col);
	Dfs(grid, i + 1, j, row, col);
	Dfs(grid, i, j - 1, row, col);
	Dfs(grid, i, j + 1, row, col);
}

int numIslands(char **grid, int row, int col) {
	if (grid == nullptr || sizeof(grid) / sizeof(grid[0]) == 0) {
		return 0;
	}

	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] == '1') {
				count++;

				Dfs(grid, i, j, row, col);
			}
		}
	}
	return count;
}

class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(NULL), right(NULL), next(NULL) {}

	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
};

Node *connect(Node* rt) {
	if (rt == nullptr) return rt;

	queue<Node*> que;
	que.push(rt);
	while (!que.empty()) {
		int size = que.size();

		for (int i = 0; i < size; i++) {
			auto node = que.front();
			que.pop();

			if (i < size - 1) {
				node->next = que.front();
			}

			if (node->left != nullptr) {
				que.push(node->left);
			}

			if (node->right != nullptr) {
				que.push(node->right);
			}
		}
	}
	return rt;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
	int m = matrix.size(), n = matrix[0].size();
	// 初始化动态规划的数组，所有的距离值都设置为一个很大的数
	vector<vector<int>> dist(m, vector<int>(n, INT_MAX / 2));
	// 如果 (i, j) 的元素为 0，那么距离为 0
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (matrix[i][j] == 0) {
				dist[i][j] = 0;
			}
		}
	}
	// 只有 水平向左移动 和 竖直向上移动，注意动态规划的计算顺序
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i - 1 >= 0) {
				dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
			}
			if (j - 1 >= 0) {
				dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
			}
		}
	}
	// 只有 水平向左移动 和 竖直向下移动，注意动态规划的计算顺序
	for (int i = m - 1; i >= 0; --i) {
		for (int j = 0; j < n; ++j) {
			if (i + 1 < m) {
				dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
			}
			if (j - 1 >= 0) {
				dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
			}
		}
	}
	// 只有 水平向右移动 和 竖直向上移动，注意动态规划的计算顺序
	for (int i = 0; i < m; ++i) {
		for (int j = n - 1; j >= 0; --j) {
			if (i - 1 >= 0) {
				dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
			}
			if (j + 1 < n) {
				dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
			}
		}
	}
	// 只有 水平向右移动 和 竖直向下移动，注意动态规划的计算顺序
	for (int i = m - 1; i >= 0; --i) {
		for (int j = n - 1; j >= 0; --j) {
			if (i + 1 < m) {
				dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
			}
			if (j + 1 < n) {
				dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
			}
		}
	}
	return dist;
}
 
 void mirror(TreeNode* root) {
	 if (root->left == nullptr && root->right != nullptr) return;
	 if (root->left != nullptr || root->right != nullptr) {
		 TreeNode* temp = new TreeNode(0);
		 temp = root->left;
		 root->left = root->right;
		 root->right = temp;
	 }
 }

 TreeNode* mirrorTree(TreeNode* root) {
	 if (root == nullptr) return root;
	 mirror(root);
	 root->left = mirrorTree(root->left);
	 root->right = mirrorTree(root->right);
	 return root;
 }

 vector<vector<int>> levelOrder(TreeNode* root) {
	 if (root == nullptr) return {};
	 deque<TreeNode*> visited;
	 visited.push_back(root);

	 vector<vector<int>> ans;
	 auto node = root;
	 while (!visited.empty()) {
		 vector<int> tmp;

		 int k = visited.size();
		 for (int i = 0; i < k; i++) {
			 TreeNode* newNode = visited.front();
			 visited.pop_front();
			 tmp.emplace_back(newNode->val);

			 if (newNode->left != nullptr) {
				 visited.push_back(newNode->left);
			 }

			 if (newNode->right != nullptr) {
				 visited.push_back(newNode->right);
			 }
		 }
		 ans.emplace_back(tmp);
		 tmp = vector<int>();

		 k = visited.size();
		 for (int i = 0; i < k; i++) {
			 TreeNode* newNode = visited.front();
			 visited.pop_front();
			 tmp.emplace_back(newNode->val);

			 if (newNode->right != nullptr) visited.push_front(newNode->right);
			 if (newNode->left != nullptr) visited.push_front(newNode->left);
		 }
		 ans.emplace_back(tmp);
	 }
	 return ans;
 }

 class A {
 public:
	 A(int _a = 11) :a(_a) {
	 }

	 virtual void print() {
		 cout << "a=" << a << endl;
	 }
 private:
	 int a;
 };

 class B:public A {
 public:
	 B(int _a = 11, int _b = 12) :A(_a), b(_b) {
	 }

	 void print() override {
		 cout << "b=" << b << endl;
		 A::print();
	 }
	 void unique() {
		 cout << "unique for B" << endl;
	 }
 private:
	 int b;
 };
 void fun(int a, int b) {
	 cout << a + b << endl;
 }

 bool fun2(bool a, bool b) {
	 return a || b;
 }

int main() {
	vector<vector<int>> map({ {1,2,-1},{4,-3,1}, {-2,2,1} });
	Clearance clear;
	int hp = clear.maxHp(map, 10);
	vector<int> coins({ 186,419,83,408 });
	CoinChange coin;
	int num = coin.coinChange(coins, 6249);
	string s = "()())()";
	RemoveInvalidParentheses removeInvalid;
	vector<string> ret = removeInvalid.removeInvalidParentheses(s);

	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);

	root->right->left = new TreeNode(4);
	root->right->right = new TreeNode(5);
	NewCodec codec;
	string ser = codec.serialize(root);
	TreeNode* newTree = codec.deserialize(ser);

	vector<vector<int>> prerequisites({ {0,1} });
	FinishCourse canFinish;
	bool ans = canFinish.canFinish(2, prerequisites);

	vector<vector<char>> grid_1 = { {'1', '1', '1', '1', '0'},
		{'1', '1', '0', '1', '0'},
		{'1', '1', '0', '0', '0'},
	{'0', '0', '0', '0', '0'} };
	Islands slt;
	int coinNums = slt.numIslands(grid_1);
	string str = "/0";
    vector<vector<int>> intervals{ {1,4},{0,2},{15,18},{8,10} };
	sort(intervals.begin(), intervals.end());
	MaxSubArray ob1;
	vector<int> arr({ -1,-2,-3,0 });
	
	Solution test;
	string permutes = test.getPermutation(4,9);

	root = mirrorTree(root);

	char **grid = new char*[4];
	for (int i = 0; i < 4; i++) {
		grid[i] = new char[5];
	}


	vector<vector<int>> mat(3, vector<int>(3));
	mat = { {0, 0, 0}, { 0, 1, 0 }, { 1, 1, 1 } };

	vector<vector<int>> newMat(3, vector<int> (3));

	newMat = updateMatrix(mat);
	//sizeof(grid) 与sizeof(grid_1)不等同

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			grid[i][j] = grid_1[i][j];
			cout << grid[i][j] << " ";
		}
	}

	cout << endl;

	//The requested memory needs to be released
	for (int i = 0; i < 4; i++) 
		delete[] grid[i];
	delete[] grid;

	return 0;
}