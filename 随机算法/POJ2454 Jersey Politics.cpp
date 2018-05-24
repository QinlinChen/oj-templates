// POJ2454 Jersey Politics
#include <cstdio>
#include <algorithm>

struct City {
    int city_id, cow_num;
};

#define MAXK 65
City cities[3 * MAXK];
int K;

bool cmpCity(const City &lhs, const City &rhs) {
    return lhs.cow_num > rhs.cow_num;
}

int main() {
    while (scanf("%d", &K) != EOF) {
        int num;
        for (int i = 0; i < 3 * K; ++i) {
            scanf("%d", &cities[i].cow_num);
            cities[i].city_id = i + 1;
        }
        std::sort(cities, cities + 3 * K, cmpCity);
        int district1 = 0, district2 = 0;
        for (int i = 0; i < K; ++i)
            district1 += cities[i].cow_num;
        for (int i = K; i < 2 * K; ++i)
            district2 += cities[i].cow_num;
        while (district1 <= 500 * K || district2 <= 500 * K) {
            int r1 = rand() % K, r2 = K + rand() % K;
            district1 = district1 - cities[r1].cow_num + cities[r2].cow_num;
            district2 = district2 - cities[r2].cow_num + cities[r1].cow_num;
            std::swap(cities[r1], cities[r2]);
        }
        for (int i = 0; i < 3 * K; ++i) 
            printf("%d\n", cities[i].city_id);
    }
}