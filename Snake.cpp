#include <iostream>
#include <windows.h>
#include <iomanip>
#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
int fieldWidth = 10, fieldHeight = 10, applePosX, applePosY, snakeSpeed = 5, moveCounter, score;
vector<int> snakeXPos;
vector<int> snakeYPos;
enum ENUM_MOVE_DIRECTION
{
    none,
    up,
    down,
    left,
    right,
};
ENUM_MOVE_DIRECTION moveDirection = none;
ENUM_MOVE_DIRECTION lastMove = none;
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
void Redraw()
{
    system("cls");

    cout << "+";
    for (int i = 0; i < fieldWidth; i++)
    {
        cout << setw(2) << "-";
    }
    cout << "+" << endl;

    for (int i = 0; i < fieldHeight; i++)
    {
        cout << "|";
        for (int j = 0; j < fieldWidth; j++)
        {
            bool snakeCell = false;
            for (int k = 0; k < snakeXPos.size(); k++)
            {
                if (i + 1 == snakeYPos[k] && j + 1 == snakeXPos[k])
                {
                    cout << setw(2) << "#";
                    snakeCell = true;
                    break;
                }
            }
            if (!snakeCell && i + 1 == applePosY && j + 1 == applePosX)
            {
                cout << setw(2) << "o";
            }
            else if (!snakeCell)
            {
                cout << setw(2) << " ";
            }
        }
        cout << "|" << endl;
    }

    cout << "+";
    for (int i = 0; i < fieldWidth; i++)
    {
        cout << setw(2) << "-";
    }
    cout << "+" << endl;
    cout << "Score: " << score << endl;
}
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
int Random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
void UpdateMoveDirection()
{
    if (!kbhit())
    {
        return;
    }

    int key = _getch();
    switch (key)
    {
    case 80:
        if (moveDirection != ENUM_MOVE_DIRECTION::up && lastMove != ENUM_MOVE_DIRECTION::up)
            moveDirection = ENUM_MOVE_DIRECTION::down;
        break;
    case 72:
        if (moveDirection != ENUM_MOVE_DIRECTION::down && lastMove != ENUM_MOVE_DIRECTION::down)
            moveDirection = ENUM_MOVE_DIRECTION::up;
        break;
    case 75:
        if (moveDirection != ENUM_MOVE_DIRECTION::right && lastMove != ENUM_MOVE_DIRECTION::right)
            moveDirection = ENUM_MOVE_DIRECTION::left;
        break;
    case 77:
        if (moveDirection != ENUM_MOVE_DIRECTION::left && lastMove != ENUM_MOVE_DIRECTION::left)
            moveDirection = ENUM_MOVE_DIRECTION::right;
        break;

    default:
        break;
    }
}
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
void MoveSnake()
{
    for (int i = snakeYPos.size() - 1; i > 0; i--)
    {
        snakeXPos[i] = snakeXPos[i - 1];
        snakeYPos[i] = snakeYPos[i - 1];
    }
    switch (moveDirection)
    {
    case 1: // Up
        snakeYPos[0] -= 1;
        lastMove = ENUM_MOVE_DIRECTION::up;
        break;
    case 2: // Down
        snakeYPos[0] += 1;
        lastMove = ENUM_MOVE_DIRECTION::down;
        break;
    case 3: // Left
        snakeXPos[0] -= 1;
        lastMove = ENUM_MOVE_DIRECTION::left;
        break;
    case 4: // Right
        snakeXPos[0] += 1;
        lastMove = ENUM_MOVE_DIRECTION::right;
        break;

    default:
        break;
    }
}
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
bool WasAppleEaten()
{
    if (snakeXPos[0] == applePosX && snakeYPos[0] == applePosY)
    {
        return true;
    }
    return false;
}
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
void SetNewApplePos()
{
    int i = 1;
    while (snakeXPos[0] == applePosX || snakeYPos[0] == applePosY)
    {
        srand(time(0) - i);
        applePosX = Random(1, fieldWidth);
        applePosY = Random(1, fieldHeight);
        i++;
    }
}
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
int main()
{
    cout << "Welcome to the Snake Game. Press any key to start." << endl;
    getchar();
    system("cls");

    bool isGameOver = false;
    snakeXPos.push_back(0);
    snakeYPos.push_back(0);
    srand(time(0));
    snakeXPos[0] = applePosX = Random(1, fieldWidth);
    snakeYPos[0] = applePosY = Random(1, fieldHeight);
    SetNewApplePos();

    while (!isGameOver)
    {
        if (WasAppleEaten())
        {
            score++;
            snakeSpeed > 0.5 ? snakeSpeed = snakeSpeed -0.5 : snakeSpeed = snakeSpeed;
            SetNewApplePos();

            switch (lastMove)
            {
            case 1: // Up
                snakeXPos.push_back(snakeXPos[snakeXPos.size() - 1]);
                snakeYPos.push_back(snakeYPos[snakeYPos.size() - 1]+1);
                break;
            case 2: // Down
                snakeXPos.push_back(snakeXPos[snakeXPos.size() - 1]);
                snakeYPos.push_back(snakeYPos[snakeYPos.size() - 1]-1);
                break;
            case 3: // Left
                snakeXPos.push_back(snakeXPos[snakeXPos.size() - 1]+1);
                snakeYPos.push_back(snakeYPos[snakeYPos.size() - 1]);
                break;
            case 4: // Right
                snakeXPos.push_back(snakeXPos[snakeXPos.size() - 1]-1);
                snakeYPos.push_back(snakeYPos[snakeYPos.size() - 1]);
                break;

            default:
                break;
            }
        }

        UpdateMoveDirection();
        if (moveCounter < snakeSpeed)
        {
            moveCounter++;
        }
        else
        {
            moveCounter = 0;
            MoveSnake();
        }
        for (int i = 3; i < snakeXPos.size(); i++)
        {
            if (snakeXPos[0] == snakeXPos[i] && snakeYPos[0] == snakeYPos[i])
            {
                isGameOver = true;
                break;
            }
        }

        if ((snakeXPos[0] > fieldWidth || snakeXPos[0] < 1) || (snakeYPos[0] > fieldHeight || snakeYPos[0] < 1))
        {
            isGameOver = true;
            break;
        }

        Redraw();

        Sleep(50);
    }
    cout << "Game Over!" << endl;
    getchar();
    return 0;
}
