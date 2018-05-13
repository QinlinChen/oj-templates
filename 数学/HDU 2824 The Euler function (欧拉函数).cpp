#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int N=3000010;

int prime[N],isprime[N];
int phi[N];

void get_phi(){
    int i,j,cnt=0;
    for(i=2;i<N;i++){
        if(isprime[i]==0){
            prime[cnt++]=i;
            phi[i]=i-1;
        }
        for(j=0;j<cnt && i*prime[j]<N;j++){     //注意这里，i*prime[j]<N 可换成 prime[j]<=N/i（带等号）
            isprime[i*prime[j]]=1;
            if(i%prime[j]==0)
                phi[i*prime[j]]=phi[i]*prime[j];
            else
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}

int main(){

    //freopen("input.txt","r",stdin);

    long long sum;
    int a,b;
    get_phi();
    while(~scanf("%d%d",&a,&b)){
        sum=0;
        for(int i=a;i<=b;i++)
            sum+=phi[i];
        cout<<sum<<endl;
    }
    return 0;
}