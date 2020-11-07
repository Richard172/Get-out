#include <iostream>

template <typename T, size_t rows, size_t cols>
void print(T arr[rows][cols])
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << arr[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

int main()
{
	int arr[3][2] = {{1, 2}, {0, 1}, {2, 3}};
	print<int, 3, 2>(arr);
}