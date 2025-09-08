// hw5_2.cpp
//

#include <iostream>
using namespace std;

void sort5(double& x1, double& x2, double& x3, double& x4, double& x5);

int main()
{
    double x1, x2, x3, x4, x5;
    cout << "Please enter 5 numbers (seperated by spaces): ";
    cin >> x1 >> x2 >> x3 >> x4 >> x5;
    sort5(x1, x2, x3, x4, x5);
    cout << x1 << ", " << x2 << ", " << x3 << ", " << x4 << ", " << x5 << endl;
}

// implement your function here
void sort5(double& x1, double& x2, double& x3, double& x4, double& x5) {

    for (int i = 0; i < 5; i++) {
        
        double holder;

        if (x5 < x4) {

            holder = x5;

            x5 = x4;

            x4 = holder;

        }

        if (x4 < x3) {

            holder = x4;

            x4 = x3;

            x3 = holder;

        }

        if (x3 < x2) {

            holder = x3;

            x3 = x2;

            x2 = holder;

        }

        if (x2 < x1) {

            holder = x2;

            x2 = x1;

            x1 = holder;

        }

    }

}



