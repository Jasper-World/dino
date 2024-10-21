#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;

const int width = 20;
const int height = 10;
int x, y;
bool gameOver;
vector<int> obstacles;
int score;
int jumpHeight = 2;
int fallDelay = 2;
int fallCounter = 0;

void setup() {
    gameOver = false;
    x = 5;
    y = height - 2;
    score = 0;
    obstacles.clear();
    srand(time(0));
    obstacles.push_back(width - 1);
}

void draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";  // 小恐龙
            else if (i == height - 1)
                cout << "-";  // 地面
            else {
                bool isObstacle = false;
                for (int k = 0; k < obstacles.size(); k++) {
                    if (obstacles[k] == j && i == height - 2) {
                        cout << "#";  // 仙人掌
                        isObstacle = true;
                        break;
                    }
                }
                if (!isObstacle)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    cout << "Google dino game" << endl;
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case ' ':
            if (y == height - 2)
                y -= jumpHeight;  // 跳跃
            break;
        case 'q':
            gameOver = true;  // 退出游戏
            break;
        }
    }
}

void logic() {
    if (y < height - 2) {
        if (fallCounter >= fallDelay) {
            y++;  // 恢复下降
            fallCounter = 0;
        } else {
            fallCounter++;
        }
    }

    // 更新障碍物位置
    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i]--;
        if (obstacles[i] < 0) {
            obstacles[i] = width - 1;
            score++;
        }
    }

    // 控制障碍物的生成规则，避免连续障碍物太近
    if (rand() % 20 == 0) {
        bool canPlace = true;
        int lastObstaclePos = obstacles.back();
        for (int i = 0; i < obstacles.size(); i++) {
            // 确保新生成的障碍物与前一个障碍物的距离至少为3
            if (width - lastObstaclePos < 4) {
                canPlace = false;
                break;
            }
        }

        if (canPlace) {
            obstacles.push_back(width - 1);  // 生成新障碍物
        }
    }

    // 碰撞检测
    for (int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i] == x && y == height - 2) {
            gameOver = true;
        }
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(50);  // 控制游戏速度
    }
    cout << "Game Over!" << endl;
    return 0;
}

