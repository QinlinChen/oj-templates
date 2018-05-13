#include <cstdio>
#include <string>
using namespace std;

#define SIZE 20

string ans;
int R, C;
char board[SIZE][SIZE];
int mov[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

void dfs(int x, int y, string &num)
{
	if (ans.size() < num.size())
		ans = num;

	for (int i = 0; i < 4; ++i) {
		int nx = x + mov[i][0], ny = y + mov[i][1];
		if (nx >= 0 && nx < R && y >= 0 && y < C && board[nx][ny] != '#') {
			char save = board[nx][ny];
			board[nx][ny] = '#';
			num.push_back(save);
			dfs(nx, ny, num);
			num.pop_back();
			board[nx][ny] = save;
		}
	}
}

int main() {
	while (scanf("%d %d", &R, &C) != EOF) {
		if (R == 0 || C == 0)
			break;
		for (int r = 0; r < R; ++r)
			scanf("%s", board[r]);

		for (int r = 0 ; r < R; ++r)
			for (int c = 0; c < C; ++c)
				if (board[r][c] != '#') {
					string num;
					num.reserve(30);
					char save = board[r][c];
					board[r][c] = '#';
					num.push_back(save);
					dfs(r, c, num);
					num.pop_back();
					board[r][c] = save;
				}
		
		printf("%s\n", ans.c_str());
	}

	return 0;
}