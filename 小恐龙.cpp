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
                cout << "O";  // С����
            else if (i == height - 1)
                cout << "-";  // ����
            else {
                bool isObstacle = false;
                for (int k = 0; k < obstacles.size(); k++) {
                    if (obstacles[k] == j && i == height - 2) {
                        cout << "#";  // ������
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
                y -= jumpHeight;  // ��Ծ
            break;
        case 'q':
            gameOver = true;  // �˳���Ϸ
            break;
        }
    }
}

void logic() {
    if (y < height - 2) {
        if (fallCounter >= fallDelay) {
            y++;  // �ָ��½�
            fallCounter = 0;
        } else {
            fallCounter++;
        }
    }

    // �����ϰ���λ��
    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i]--;
        if (obstacles[i] < 0) {
            obstacles[i] = width - 1;
            score++;
        }
    }

    // �����ϰ�������ɹ��򣬱��������ϰ���̫��
    if (rand() % 20 == 0) {
        bool canPlace = true;
        int lastObstaclePos = obstacles.back();
        for (int i = 0; i < obstacles.size(); i++) {
            // ȷ�������ɵ��ϰ�����ǰһ���ϰ���ľ�������Ϊ3
            if (width - lastObstaclePos < 4) {
                canPlace = false;
                break;
            }
        }

        if (canPlace) {
            obstacles.push_back(width - 1);  // �������ϰ���
        }
    }

    // ��ײ���
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
        Sleep(50);  // ������Ϸ�ٶ�
    }
    cout << "Game Over!" << endl;
    return 0;
}

