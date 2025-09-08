#include <iostream>
#include <string>

using namespace std;

int main() {

   string phrase;

   cout << "Enter a phrase: ";

   cin >> phrase;

cout << phrase.length() << endl;

   cout << phrase.substr(0,1) << " " << phrase.substr(phrase.length()-1) << endl;


return 0;

}


// Class Exercises

/*
Ask the user for a phrase
print out the phrase twice
so if i type in good morning
print out good morning good morning
*/

/*
Ask the user for their name
Tell them how many letters long it is
name.length
*/

/*
Ask the user for a phrase
Print out the first and last letters
If i type good morning
Print out g and m
*/