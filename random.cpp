#include <iostream>
#include <cstdlib>
#include <ctime>

int randBetweenTwoNumber(int firstNum, int secondNum)
{
	// a smaller number between the two
	int smallerNum = (firstNum > secondNum ? secondNum : firstNum);
	int difference = std::abs(firstNum - secondNum);
	return rand() % (difference + 1) + smallerNum;
}

int main()
{
	// this is a must have in the beginning of the main, the system will
	// generate a random seed based on what time the pc is (in sec)
	std::srand(std::time(NULL));
	
	std::cout << randBetweenTwoNumber(3, 6);
}