#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
int test(int testnum);
int main()
{
    int sum = 0;
    int n = 5;

    int total = test(n);

    cout << test(n) << endl;
    cout << test(20);
}

int test(int n1){

int sum1 = 0;

    for(int i = 1; i<=n1; i++) {

        sum1 += i;

    }

return sum1;

}