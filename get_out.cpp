#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>

#define SIZE 4


class Maze
{
public:
    int H;
    int W;
    std::vector<std::vector<int>> grid;

    auto check_neighbors(int r, int c, bool checkIsBorder){
        std::vector<std::vector<int>> neighbors{};

        if (r > 1 && grid[r-2][c] == checkIsBorder)
            neighbors.push_back({r-2, c});
        if (r < H - 2 && grid[r + 2][c] == checkIsBorder)
            neighbors.push_back({r+2, c});
        if (c > 1 && grid[r][c - 2] == checkIsBorder)
            neighbors.push_back({r, c-2});
        if (c < W - 2 && grid[r][c + 2] == checkIsBorder)
            neighbors.push_back({r, c+2});

        auto rd = std::random_device {};
        auto rng = std::default_random_engine { rd() };
        std::shuffle(std::begin(neighbors), std::end(neighbors), rng);

        return neighbors;
    }

public:
    int h;
    int w;
    int startPos;
    int endPos;
	std::pair <int, int> playerPos;

    Maze(int height, int width){
        h = height;
        w = width;
        H = (2 * h) + 1;
        W = (2 * w) + 1;
    };

    void generateNewMaze() {
        grid.resize(W, std::vector<int>(H, 1));
        std::srand(std::time(nullptr));
        int currentRow = std::rand() % H + 1;
        currentRow = (currentRow % 2 == 1 ? currentRow : currentRow - 1);
        int currentCol = std::rand() % W + 1;
        currentCol = (currentCol % 2 == 1 ? currentCol : currentCol - 1);
        grid[currentRow][currentCol] = 0;
        int visited = 1;

        while (visited < h * w) {
            auto neighbors = check_neighbors(currentRow, currentCol, true);
            if (neighbors.empty()) {
                auto x = check_neighbors(currentRow, currentCol, false);
                int index = std::rand() % x.size();
                currentRow = x[index][0];
                currentCol = x[index][1];
                continue;
            }
            for (auto &neighbor : neighbors) {
                int checkRow = neighbor[0];
                int checkCol = neighbor[1];
                if (grid[checkRow][checkCol] > 0) {
                    grid[(checkRow + currentRow) / 2][(checkCol + currentCol) / 2] = 0;
                    grid[checkRow][checkCol] = 0;
                    visited++;
                    currentRow = checkRow;
                    currentCol = checkCol;
                    break;
                }
            }
        }
        startPos = -1;
        while (startPos == -1) {
            int index = std::rand() % H;
            if (grid[index][1] == 0) {
                startPos = index;
                grid[index][0] = 0;
            }
        }
        endPos = -1;
        while (endPos == -1) {
            int index = std::rand() % H;
            if (grid[index][W-2] == 0) {
                endPos = index;
                grid[index][W-1] = 0;
            }
        }
		playerPos.first = startPos;
		playerPos.second = 0;
		grid[playerPos.first][playerPos.second] = -1;
    }

    void printMaze() {
        for (auto &i : grid) {
            for (int &j : i)
			{
				if (j == 1)
				{
					std::cout << "XX";
				}
				else if (j == -1)
				{
					std::cout << "OO";
				}
				else
				{
					std::cout << "  "; 
				}
			}
            std::cout << '\n';
        }
    }
};

// prompt
int prompt(int x)
{
	int input = -1;
	
	if (x == 1)
	{
		while (input != 1 && input != 2 && input != 3 && input != 4)
		{
			std::cout << "Please choose one of the following prompt by entering the number:" << std::endl;
			std::cout << "(1). moves left" << std::endl;
			std::cout << "(2). moves right" << std::endl;
			std::cout << "(3). moves up" << std::endl;
			std::cout << "(4). moves down" << std::endl;
			std::cin >> input;
			if (input != 1 && input != 2 && input != 3 && input != 4)
			{
				std::cout << "Invalid input, please try again" << std::endl;
			}
		}
	}
	if (x == 2)
	{
		std::cout << "\"OO\" is where your position is at. Your objective is to move to the gap in the right" << std::endl;
	}
	
	return input;
}

void gameSystem(Maze* maze)
{
	std::string error = "There's a wall there. Please choose again\n";
	
	int input = -1; 
	
	maze -> generateNewMaze();
	prompt(2);
	maze -> printMaze();
	while (maze -> playerPos.first != maze -> endPos || maze -> playerPos.second != maze -> H)
	{
		input = prompt(1);
		if (input == 1)
		{
			if (maze -> playerPos.second == 0 || maze -> grid[maze -> playerPos.first][maze -> playerPos.second - 1] == 1)
			{
				std::cout << error << std::endl;
			}
			else
			{
				maze -> grid[maze -> playerPos.first][maze -> playerPos.second] = 0;
				maze -> playerPos.second -= 1;
				maze -> grid[maze -> playerPos.first][maze -> playerPos.second] = -1;
				maze -> printMaze();
			}
		}
		else if (input == 2)
		{
			if (maze -> grid[maze -> playerPos.first][maze -> playerPos.second + 1] == 1)
			{
				std::cout << error << std::endl;
			}
			else
			{
				maze -> grid[maze -> playerPos.first][maze -> playerPos.second] = 0;
				maze -> playerPos.second += 1;
				maze -> grid[maze -> playerPos.first][maze -> playerPos.second] = -1;
				maze -> printMaze();
			}
		}
		else if (input == 3)
		{
			if (maze -> grid[maze -> playerPos.first - 1][maze -> playerPos.second] == 1)
			{
				std::cout << error << std::endl;
			}
			else
			{
				maze -> grid[maze -> playerPos.first][maze -> playerPos.second] = 0;
				maze -> playerPos.first -= 1;
				maze -> grid[maze -> playerPos.first][maze -> playerPos.second] = -1;
				maze -> printMaze();
			}
		}
		else if (input == 4)
		{
			if (maze -> grid[maze -> playerPos.first + 1][maze -> playerPos.second] == 1)
			{
				std::cout << error << std::endl;
			}
			else
			{
				maze -> grid[maze -> playerPos.first][maze -> playerPos.second] = 0;
				maze -> playerPos.first += 1;
				maze -> grid[maze -> playerPos.first][maze -> playerPos.second] = -1;
				maze -> printMaze();
			}
		}
	}
	
	std::cout << "Congratulations! You made it out of the maze!" << std::endl;
}

int main()
{
    auto maze = new Maze(SIZE, SIZE);
	
	gameSystem(maze);
	//std::cout << maze -> startPos;
}
