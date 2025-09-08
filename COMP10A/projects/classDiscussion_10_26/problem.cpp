#include <iostream>
#include <cmath>

using namespace std;

string input;

int main(){

/*int x = 2 + 3;

bool y = 0; //will print out a 1, since it is true

int i = 0;

while(i < 10){

    bool x = (i == 5);

    i+= 1;

} */

/*traverse the matrix above by diagonal

0,0  0,1  0,2  0,3
1,0  1,1  1,2  1,3
2,0  2,1  2,2  2,3
3,0  3,1  3,2  3,3

so 
0,0
1,0
0,1

2,0
1,1
0,2*/

/*for(int i = 0; i < 7; i++){

    
    for(int j = i; j >= 0; j--){

        if(j <= 3 && (i - j) <= 3){

        cout << j << "," << i - j << endl;

        }

    }


}*/

/* Ask the user for a positive number
Print a right triangle with the right angle in the bottom left corner*/

int input;

cout << "Enter a value: ";

cin >> input;

string asterisk;

for(int i = 0; i <= input; i ++){

    for(int n = 0; n < i; n++){

        asterisk = asterisk + "*";

        cout << asterisk << endl;

    }

    

}

}