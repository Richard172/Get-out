#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>

#define SIZE 20


class Maze
{
private:
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
    }

    void printMaze() {
        for (auto &i : grid) {
            for (int &j : i)
                std::cout << (j == 1 ? "XX" : "  ");
            std::cout << '\n';
        }
    }
};


int main()
{
    auto maze = new Maze(SIZE, SIZE);
    maze->generateNewMaze();
    maze->printMaze();
}
