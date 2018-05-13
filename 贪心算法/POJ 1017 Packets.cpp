// poj 1017 Packets
// Ì°ĞÄ

#include <cstdio>
using namespace std;

int ctr[7];
const int map[4] = { 0,5,3,1 };

int parcels()
{
	int need = ctr[6] + ctr[5] + ctr[4] + (ctr[3] + 3) / 4;
	int available2 = 5 * ctr[4] + map[ctr[3] % 4];
	if (available2 < ctr[2]) 
		need += ((ctr[2] - available2) + 8) / 9;
	int available1 = 36 * need - 36 * ctr[6] - 25 * ctr[5] - 16 * ctr[4] - 9 * ctr[3] - 4 * ctr[2];
	if (available1 < ctr[1])
		need += ((ctr[1] - available1) + 35) / 36;
	return need;
}

int main()
{
	while (true) {
		bool stop = true;
		for (int i = 1; i <= 6; ++i) {
			scanf("%d", &ctr[i]);
			if (ctr[i])
				stop = false;
		}
		if (stop)
			break;
		printf("%d\n", parcels());
	}
	return 0;
}