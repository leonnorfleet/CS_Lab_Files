// C++ implementation to find
// square root of given number
// upto given precision using
// binary search.
#include <iostream>
#include <float.h>
using namespace std;

// Function to find square root
// of given number upto given
// precision
float squareRoot(int number)
{
	int start = 0, end = number;
	int mid;

	// variable to store the answer
	float ans;

	// for computing integral part
	// of square root of number
	while (start <= end) {
		mid = (start + end) / 2;
		if (mid * mid == number) {
			ans = mid;
			break;
		}

		// incrementing start if integral
		// part lies on right side of the mid
		if (mid * mid < number) {
			start = mid + 1;
			ans = mid;
		}

		// decrementing end if integral part
		// lies on the left side of the mid
		else {
			end = mid - 1;
		}
	}

	// For computing the fractional parts
	float increment = 0.1;
	while (ans * ans < number) {
		ans += increment;
	}

		// loop terminates when ans * ans > number
	ans = ans - increment;
	//increment = increment / 10;
	std::cout << start << endl;
	return ans;
}

// Driver code
int main()
{
	// Function calling
	cout << squareRoot(3) << endl;

	return 0;
}
