#include <iostream>
#include <string>

using namespace std;

int main() {

//Problem 1

/*string lastChar_3;

cout << "Enter a phrase that is 4 or more characters long: ";

cin >> lastChar_3;

cout << lastChar_3.substr(lastChar_3.length() - 3) << endl;

*/

//Problem 2

/*string inputMoney;

cout << "Enter an amount of money between 10 and 99 dollars in dollars and cents. Format has to be $ab.cd: ";

cin >> inputMoney;

cout << inputMoney.substr(inputMoney.length() - 5, 2) << " dollars and " << inputMoney.substr(inputMoney.length() - 2, 2) << " cents" << endl;
*/

//Problem 3

/*string inputWord;

cout << "Enter a word: ";

cin >> inputWord;

int n = inputWord.length() - 1;

cout << inputWord.substr(inputWord.length() - n) << inputWord.substr(inputWord.length() - inputWord.length(), 1) << "ay" << endl;
*/

//Problem 4

string days = "ThuFriSatSunMonTueWed";

int dayInput;

cout << "Enter a day: ";

cin >> dayInput;

int d = days.length();

cout << "October " << dayInput << ": " << days.substr(dayInput % 7 * 3, 3);

return 0;

}