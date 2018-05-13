// POJ 1568 Find the Winning Move
// minmax, alpha-beta prune
#include <cstdio>
#include <cstring>
using namespace std;

#define SIZE 4
char board[SIZE][SIZE];
int ans_r, ans_c;

// 'X' win returns 1, 'O' win returns -1, PAR returns 0
int check() {
	int ctr;
	for (int r = 0; r < SIZE; ++r) {
		ctr = 0;
		for (int c = 0; c < SIZE; ++c) {
			if (board[r][c] == 'x')
				ctr++;
			else if (board[r][c] == 'o')
				ctr--;
		}
		if (ctr == 4)
			return 1;
		if (ctr == -4)
			return -1;
	}
	for (int c = 0; c < SIZE; ++c) {
		ctr = 0;
		for (int r = 0; r < SIZE; ++r) {
			if (board[r][c] == 'x')
				ctr++;
			else if (board[r][c] == 'o')
				ctr--;
		}
		if (ctr == 4)
			return 1;
		if (ctr == -4)
			return -1;
	}
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

int minmax(int player, int alpha, int beta) {
	int result = check();
	if (result != 0)
		return result;

	if (player) {
		for (int r = 0; r < SIZE; ++r) 
			for (int c = 0; c < SIZE; ++c)
				if (board[r][c] == '.') {
					board[r][c] = 'x';
					int val = minmax(player ^ 1, alpha, beta);
					board[r][c] = '.';
					if (val > alpha) {
						alpha = val;
						ans_r = r;
						ans_c = c;
					}
					if (alpha >= beta)
						return alpha;
				}
		return alpha;
	}
	else {
		for (int r = 0; r < SIZE; ++r) 
			for (int c = 0; c < SIZE; ++c) 
				if (board[r][c] == '.') {
					board[r][c] = 'o';
					int val = minmax(player ^ 1, alpha, beta);
					board[r][c] = '.';
					if (val < beta)
						beta = val;
					if (alpha >= beta)
						return beta;
				}
		return beta;
	}
}

int main() {
	char ch;

	while (scanf("%c", &ch) != EOF) {
		if (ch == '$')
			break;
		getchar();

		int count = 0;
		for (int r = 0; r < SIZE; ++r) {
			for (int c = 0; c < SIZE; ++c) {
				board[r][c] = getchar();
				if (board[r][c] != '.')
					count++;
			}
			getchar();
		}

		if (count <= 4) {
			printf("#####\n");
			continue;
		}
		int result = minmax(1, -1, 1);
		if (result > 0)
			printf("(%d,%d)\n", ans_r, ans_c);
		else
			printf("#####\n");
	}

	return 0;
}