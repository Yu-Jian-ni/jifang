#include "Codec.h"

int Clearance::steps[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };

int Clearance::maxHp(vector<vector<int>>& mat, int hp)
{
	int m = mat.size();
	int n = mat[0].size();
	int ans = -1;
	//
	int gx, gy;
	int hx, hy;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (mat[i][j] == -2) {
				hx = i;
				hy = j;
			}
			else if (mat[i][j] == -3) {
				gx = i;
				gy = j;
			}
		}
	}
	vector<vector<int>> hps(m, vector<int>(n, 0));
	hps[hx][hy] = hp;

	queue<human> que;
	que.push(human(hx, hy));

	while (!que.empty()) {
		human cur = que.front();
		que.pop();
		int curx = cur.x;
		int cury = cur.y;

		for (int i = 0; i < 4; ++i) {
			int nx = curx + steps[i][0];
			int ny = cury + steps[i][1];

			//越界判断
			if (nx >= m || nx < 0 || ny >= n || ny < 0 || mat[nx][ny] == -3 || mat[nx][ny] == -2) continue;

			//到达出口且生命值大于0，更新
			if (mat[nx][ny] == -1 && hps[curx][cury] > 0) {
				ans = max(ans, hps[curx][cury]);
				continue;
			}
			
			int curHp = hps[curx][cury] - mat[nx][ny];
			if (curHp <= 0) continue;//生命值判断							
			
			//update hps
			if (hps[nx][ny] < curHp) {
				hps[nx][ny] = curHp;
				que.push(human(nx, ny));
			}
		}
	}

	return ans;
}
