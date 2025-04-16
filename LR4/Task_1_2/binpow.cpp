#include "sorts.h"

int binpow(int digit,int powder, int mod){
    int result=1;
    while(powder>0){
        if (powder%2==1){
            result=(long long)(result*digit)%mod;
        }
        digit=(long long)(digit*digit) % mod;
        powder/= 2;
    }
    return result;
}