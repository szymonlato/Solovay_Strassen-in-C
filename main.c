#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long duze;

struct Dane{
    duze wejscie;
    duze iterator;
};

int Feed_Data(struct Dane *dane,char *wejscie,char *iterator){
    if(!dane)
        return -1;
    else {
        dane->wejscie = atoll(wejscie);
        dane->iterator = atoll(iterator);
    return 0;
    }
}


duze fast_power_mod(duze B,duze n,duze modulnik){
    duze result =1;
    duze x =B%modulnik;
    for (int i = 1; i <= n ; i<<=1) {
        x = x%modulnik;
        if((n&i) != 0){
            result = result * x;
            result = result%modulnik;
        }
        x = x*x;
    }
    return result;
}

int jacobi(unsigned long a, unsigned long n) {
    if (a >= n) a %= n;
    int result = 1;
    duze tmp;
    while (a) {
        while ((a & 1) == 0) {
            a >>= 1;
            if ((n & 7) == 3 || (n & 7) == 5) result = -result;
        }
        tmp=a;
        a=n;
        n=tmp;
        if ((a & 3) == 3 && (n & 3) == 3) result = -result;
        a %= n;
    }
    if (n == 1) return result;
    return 0;
}

int Solovay(struct Dane *dane){
    if(dane->wejscie == 2){
        printf("prime");
        return 1;
    }else if(dane->wejscie%2 == 0){
        return 2;
    } else {
        duze i = 0, B;
        srand(time(0));
        while (i < dane->iterator) {
            B =(duze)rand() % dane->wejscie;           //random_number(0,dane->wejscie);
            printf("\nB%lld", B);
            //B^(wejscie-1)/2 mod wejscie
            printf("\nf%lld",fast_power_mod(B, (dane->wejscie - 1) / 2, dane->wejscie));//potegowanie_mod(B,((dane->wejscie-1)/2),dane->wejscie));
            printf("\nj%lld", jacobi(B, dane->wejscie));
            duze z=(dane->wejscie-1)/2;
            if (fast_power_mod(B,z,dane->wejscie) != jacobi(B, dane->wejscie)) {
                return 2;
            }
            i++;
        }
        return 1;
    }
}


int main(int argc,char **argv) {
 struct Dane *dane = malloc(sizeof(struct Dane));
    if(Feed_Data(dane,argv[1],argv[2]) == -1){
        printf("-1");
        free(dane);
        exit(-1);
    }

    printf("%i\n",(-1)%17);
    printf("%lld,%lld\n",dane->wejscie,dane->iterator);

    int d = Solovay(dane);
    printf("\n%i wynik",d);
    free(dane);
    return 0;
}
