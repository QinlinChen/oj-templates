// POJ3318 Matrix Multiplication
// Freivalds' algorithm

#include <cstdio>
#include <cstdlib>

#define MAXN 505
int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];

void scanf_matrix(int mat[MAXN][MAXN], int N) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            scanf("%d", &mat[i][j]);
}

bool witness(int A[MAXN][MAXN], int B[MAXN][MAXN],
             int C[MAXN][MAXN], int vector[MAXN], int N) {
    static int Bvec[MAXN];
    for (int i = 0; i < N; ++i) {
        int sum = 0;
        for (int j = 0; j < N; ++j) {
            sum += B[i][j] * vector[j];
        }
        Bvec[i] = sum;
    }
    for (int i = 0; i < N; ++i) {
        int Cvec = 0;
        int ABvec = 0;
        for (int j = 0; j < N; ++j) {
            ABvec += A[i][j] * Bvec[j];
            Cvec += C[i][j] * vector[j];
        }
        if (ABvec != Cvec)
            return true;
    }
    return false;
}

bool isEqual(int A[MAXN][MAXN], int B[MAXN][MAXN], 
             int C[MAXN][MAXN], int N) {
    static int vector[MAXN];
    const int tryCount = 10;
    
    for (int ctr = 0; ctr < tryCount; ++ctr) {
        for (int i = 0; i < N; ++i) 
            vector[i] = rand() % 2;
        if (witness(A, B, C, vector, N))
            return false;
    }
    return true;
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        scanf_matrix(A, N);
        scanf_matrix(B, N);
        scanf_matrix(C, N);
        printf("%s\n", (isEqual(A, B, C, N) ? "YES" : "NO"));
    }
}