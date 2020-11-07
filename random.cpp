#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int randBetweenTwoNumber(int firstNum, int secondNum)
{
	// a smaller number between the two
	int smallerNum = (firstNum > secondNum ? secondNum : firstNum);
	int difference = std::abs(firstNum - secondNum);
	return std::rand() % (difference + 1) + smallerNum;
}

int oddrand(int x)
{
	int moduloOperant = x;
	int randomNum = std::rand() % moduloOperant + 1;
	return (randomNum % 2 == 1 ? randomNum : randomNum - 1);
}

void shuffle(int* arr, int size)
{
	int randomNum;
	int* newArr = new int[size];
	std::vector <int> v;
	
	for(int i = 0; i < size; i++)
	{
		v.push_back(arr[i]);
	}
	
	for(int i = 0; i < size; i++)
	{
		randomNum = std::rand() % (size - i);
		newArr[i] = v[randomNum];
		v.erase(v.begin() + randomNum);
	}
	
	for(int i = 0; i < size; i++)
	{
		arr[i] = newArr[i];
	}
	delete[] newArr;
}

int main()
{
	// this is a must have in the beginning of the main, the system will
	// generate a random seed based on what time the pc is (in sec)
	std::srand(std::time(NULL));
	
	int arr[10] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	shuffle(arr, 10);
	
	for (int i = 0; i < 10; i++)
	{
		std::cout << arr[i] << " ";
	}
}