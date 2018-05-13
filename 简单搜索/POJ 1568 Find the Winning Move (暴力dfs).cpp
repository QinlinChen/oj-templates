#include <cstdio>
#include <cstring>
using namespace std;

#define SIZE 4
char board[SIZE][SIZE];
int ans_r, ans_c;

// 'X' win returns 1, 'O' win returns -1, PAR returns 0
int check(int x, int y) {
	int ctr = 0;
	for (int c = 0; c < SIZE; ++c) {
		if (board[x][c] == 'x')
			ctr++;
		else if (board[x][c] == 'o')
			ctr--;
	}
	if (ctr == 4)
		return 1;
	if (ctr == -4)
		return -1;
	
	ctr = 0;
	for (int r = 0; r < SIZE; ++r) {
		if (board[r][y] == 'x')
			ctr++;
		else if (board[r][y] == 'o')
			ctr--;
	}
	if (ctr == 4)
		return 1;
	if (ctr == -4)
		return -1;

	ctr = 0;
	for (int i = 0; i < SIZE; ++i) {
		if (board[i][i] == 'x')
			ctr++;
		else if (board[i][i] == 'o')
			ctr--;
	}
	if (ctr == 4)
		return 1;
	if (ctr == -4)
		return -1;

	ctr = 0;
	for (int i = 0; i < SIZE; ++i) {
		if (board[i][SIZE - 1 - i] == 'x')
			ctr++;
		else if (board[i][SIZE - 1 - i] == 'o')
			ctr--;
	}
	if (ctr == 4)
		return 1;
	if (ctr == -4)
		return -1;
	return 0;
}

int minmax(int x, int y, int player) {
	int result = check(x, y);
	if (result != 0)
		return result;

	if (player) {
		for (int r = 0; r < SIZE; ++r) 
			for (int c = 0; c < SIZE; ++c)
				if (board[r][c] == '.') {
					board[r][c] = 'x';
					int val = minmax(r, c, player ^ 1);
					board[r][c] = '.';
					if (val == 1) 
						return 1;
				}
		return -1;
	}
	else {
		for (int r = 0; r < SIZE; ++r) 
			for (int c = 0; c < SIZE; ++c) 
				if (board[r][c] == '.') {
					board[r][c] = 'o';
					int val = minmax(r, c, player ^ 1);
					board[r][c] = '.';
					if (val == -1)
						return -1;
				}
		return 1;
	}
}

bool solve(int player) {
	for (int r = 0; r < SIZE; ++r) 
		for (int c = 0; c < SIZE; ++c) 
			if (board[r][c] == '.') {
				board[r][c] = 'x';
				int val = minmax(r, c, player ^ 1);
				board[r][c] = '.';
				if (val == 1) {
					ans_r = r;
					ans_c = c;
					return true;
				}
			}
	return false;
}

int main() {
	char ch;

	while (scanf("%c", &ch) != EOF) {
		if (ch == '$')
			break;
		getchar();

		for (int r = 0; r < SIZE; ++r) {
			for (int c = 0; c < SIZE; ++c) 
				board[r][c] = getchar();
			getchar();
		}

		
		if (solve(1))
			printf("(%d,%d)\n", ans_r, ans_c);
		else
			printf("#####\n");
	}

	return 0;
}