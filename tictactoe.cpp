#include    <iostream>
#include    <limits>
#include    <cstdlib>
#include    <ctime>
#include    <stdio.h>
#include    <string>
#include    <cctype>
#include    <algorithm>

int         SIDE;
int         BoardSize;
int         MainOption;

int         MainMenue();
void        PlaySinglePlayer();
void        PlayMultiplayer();
void        HelpMenue();
int         GetSide();
std::string GetPlayerName(int Player);
void        Fill(char Board[], int size, char c);
void        Draw(char Board[]);
void        RecordPlayerOneMove(char Board[], std::string Name);
void        RecordPlayerTwoMove(char Board[], std::string Name);
int         CheckWinner(char Board[]);
bool        BoardFull(char Board[]);
char        CheckRow(char Board[], int Index);
char        CheckColumn(char Board[], int Index);
char        CheckFirstDiagonal(char Board[], int Index);
char        CheckSecondDiagonal(char Board[], int Index);
void        PrintOutcome(char Board[], int GameState, std::string PlayerOne, std::string PlayerTwo);

int         main()
{
    do
    {
        MainOption = MainMenue();

        switch (MainOption)
        {
        case 1:
            PlaySinglePlayer();
            break;
    
        case 2:
            PlayMultiplayer();
            break;

        case 3:
            HelpMenue();
            break;
        
        case 4:
            std::cout << "\nThanks for playing!\n\n";
            continue;
            break;
        }
    } 
    while (MainOption != 4);
    
    return 0;
}

int         MainMenue()
{
    int Option;

    std::cout << '\n';
    std::cout << "-----------------------------\n";
    std::cout << "|         TicTacToe         |\n";
    std::cout << "-----------------------------\n\n";
    std::cout << "1: Single Player\n";
    std::cout << "2: Multiplayer\n";
    std::cout << "3: How to play\n";
    std::cout << "4: Quit\n\n";

    std::string InputString;

    while(true)
    {
        std::cout << "Chose game-mode: ";
        std::getline(std::cin, InputString);

        if(!InputString.empty() && std::all_of(InputString.begin(), InputString.end(), ::isdigit))
        {
            Option = std::stoi(InputString);

            if(Option > 0 && Option < 5)
            {
                break;
            }
        }
    }

    return Option;
}

void        PlaySinglePlayer()
{
    std::string PlayerOneName = GetPlayerName(1);
    std::string PlayerTwoName;
    int GameState = 0;
    SIDE = GetSide();
    BoardSize = (SIDE * SIDE);

    char Board[BoardSize];
    Fill(Board, BoardSize, ' ');

    while (GameState == 0)
    {
        Draw(Board);
        RecordPlayerOneMove(Board, PlayerOneName);
        GameState = CheckWinner(Board);
        if (GameState != 0) {break;}
        RecordPlayerTwoMove(Board, PlayerTwoName);
        GameState = CheckWinner(Board);
    }

    PrintOutcome(Board, GameState, PlayerOneName, PlayerTwoName);

    return;
}

void        PlayMultiplayer()
{
    std::string PlayerOneName = GetPlayerName(1);
    std::string PlayerTwoName = GetPlayerName(2);
    int GameState = 0;
    SIDE = GetSide();
    BoardSize = (SIDE * SIDE);

    char Board[BoardSize];
    Fill(Board, BoardSize, ' ');

    while (GameState == 0)
    {
        Draw(Board);
        RecordPlayerOneMove(Board, PlayerOneName);
        GameState = CheckWinner(Board);
        if (GameState != 0) {break;}
        Draw(Board);
        RecordPlayerTwoMove(Board, PlayerTwoName);
        GameState = CheckWinner(Board);
    }

    PrintOutcome(Board, GameState, PlayerOneName, PlayerTwoName);

    return;
}

void        HelpMenue()
{
    std::string Input;

    std::cout << "\nHow to play:\n";
    std::cout << "  TicTacToe is a game where two players take turns placing\n";
    std::cout << "either X (Player 1) or O (Player 2) on a square board.\n";
    std::cout << "The first player to get their symbol in an entire\n";
    std::cout << "row, column or diagonal wins the game.\n\n";
    std::cout << "Enter to continue... ";

    std::getline(std::cin, Input);

    return;
}

std::string GetPlayerName(int Player)
{
    std::string Name;
    
    std::cout << "\nEnter Player " << Player << " name: ";
    std::getline(std::cin, Name);

    if (Name.empty())
    {
        std::string DefOut = "Player ";
        return DefOut.append(std::to_string(Player));
    }

    return Name;
}

int         GetSide()
{
    int Input;
    std::string InputString;

    std::cout << '\n';
    
    while(true)
    {
        std::cout << "Enter side-length of board: ";
        std::getline(std::cin, InputString);

        if(!InputString.empty() && std::all_of(InputString.begin(), InputString.end(), ::isdigit))
        {
            Input = std::stoi(InputString);

            if(Input > 0)
            {
                break;
            }
        }
    }

    return Input;
}

void        Fill(char Board[], int size, char c)
{
    for (int i = 0; i < size; i++)
    {
        Board[i] = c;
    }
}

void        Draw(char Board[])
{
    std::cout << "\n\n";

    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            std::cout << "------";
        }

        std::cout << "-\n";

        for (int j = 0; j < SIDE; j++)
        {
            std::cout << "|     ";        
        }

        std::cout << "|\n";

        for (int j = 0; j < SIDE; j++)
        {
            std::cout << "|  " << Board[(SIDE * i) + j] << "  ";        
        }

        std::cout << "|\n";

        for (int j = 0; j < SIDE; j++)
        {
            std::cout << "|     ";        
        }

        std::cout << "|\n";
    }

        for (int i = 0; i < SIDE; i++)
        {
            std::cout << "------";
        }
        
        std::cout << "-\n";
        
        std::cout << "\n";
}

void        RecordPlayerOneMove(char Board[], std::string Name)
{
    int Place;
    std::string InputString;

    std::cout << '\n';
    
    while(true)
    {
        std::cout << "Your turn, " << Name << ". Enter a number (1-" << BoardSize <<"): ";
        std::getline(std::cin, InputString);

        if(!InputString.empty() && std::all_of(InputString.begin(), InputString.end(), ::isdigit))
        {
            Place = std::stoi(InputString);

            if((Place > 0 && Place <= BoardSize) && Board[Place - 1] == ' ')
            {
                break;
            }
        }
    }

    Board[Place - 1] = 'X';
}

void        RecordPlayerTwoMove(char Board[], std::string Name)
{
    int Place;
    
    if (MainOption == 1)
    {
        srand(time(NULL));
    
        do
        {
            Place = rand() % BoardSize;
        }
        while (Board[Place] != ' ');

        Board[Place] = 'O'; 
    }
    else
    {
        int Place;
        std::string InputString;

        std::cout << '\n';

        while(true)
        {
            std::cout << "Your turn, " << Name << ". Enter a number (1-" << BoardSize <<"): ";
            std::getline(std::cin, InputString);

            if(!InputString.empty() && std::all_of(InputString.begin(), InputString.end(), ::isdigit))
            {
                Place = std::stoi(InputString);

                if((Place > 0 && Place <= BoardSize) && Board[Place - 1] == ' ')
                {
                    break;
                }
            }
        }

        Board[Place - 1] = 'O';
    }
}

int         CheckWinner(char Board[])
{   
    for (int i = 0; i < BoardSize; i += SIDE)
    {
        char Winner = CheckRow(Board, i);
        
        switch (Winner)
        {
        case 'X':
            return 1;
            break;
        
        case 'O':
            return 2;
            break;
        
        default:
            continue;
        }
    }

    for (int i = 0; i < SIDE; i++)
    {
        char Winner = CheckColumn(Board, i);

        switch (Winner)
        {
        case 'X':
            return 1;
            break;
        
        case 'O':
            return 2;
            break;

        default:
            continue;
        }
    }

    {
        char Winner = CheckFirstDiagonal(Board, 0);

        switch (Winner)
        {
        case 'X':
            return 1;
            break;
        
        case 'O':
            return 2;
            break;

        default:
            break;
        }
    }

    {
        char Winner = CheckSecondDiagonal(Board, 0);

        switch (Winner)
        {
        case 'X':
            return 1;
            break;
        
        case 'O':
            return 2;
            break;

        default:
            break;
        }
    }

    if (BoardFull(Board))
    {
        return 3;
    }

    return 0;
}

bool        BoardFull(char Board[])
{
    for (int i = 0; i < BoardSize; i++)
    {
        if (Board[i] == ' ')
        {
            return false;
        }
    }

    return true;
}

char        CheckRow(char Board[], int Index)
{
    if ((Index % SIDE) == (SIDE - 1))
    {
        return Board[Index];
    }
    else if (Board[Index] == CheckRow(Board, (Index + 1)))
    {
        return Board[Index];
    }
    else
    {
        return ' ';
    }
}

char        CheckColumn(char Board[], int Index)
{
    if ((Index/SIDE) == (SIDE - 1))
    {
        return Board[(Index)];
    }
    else if (Board[(Index)] == CheckColumn(Board, (Index + SIDE)))
    {
        return Board[(Index)];
    }
    else
    {
        return ' ';
    }
}

char        CheckFirstDiagonal(char Board[], int Index)
{
    if ((SIDE - Index) == 1)
    {
        return Board[((SIDE + 1) * Index)];
    }
    else if (Board[((SIDE + 1) * Index)] == CheckFirstDiagonal(Board, (Index + 1)))
    {
        return Board[((SIDE + 1) * Index)];
    }
    else
    {
        return ' ';
    }
}

char        CheckSecondDiagonal(char Board[], int Index)
{
    if ((SIDE - Index) == 1)
    {
        return Board[(SIDE - 1) * (Index + 1)];
    }
    else if (Board[(SIDE - 1) * (Index + 1)] == CheckSecondDiagonal(Board, (Index + 1)))
    {
        return Board[(SIDE - 1) * (Index + 1)];
    }
    else
    {
        return ' ';
    }
}

void        PrintOutcome(char Board[], int GameState, std::string PlayerOne, std::string PlayerTwo)
{
    if (MainOption == 1)
    {
        switch (GameState)
        {
        case 1:
            Draw(Board);
            std::cout << "\nYou won, " << PlayerOne << "!\n\n";
            break;

        case 2:
            Draw(Board);
            std::cout << "\nYou lost, " << PlayerOne << "!\n\n";
            break;

        case 3:
            Draw(Board);
            std::cout << "\nIt's a draw!\n\n";
            break;
        }
    }
    else
    {
        switch (GameState)
        {
        case 1:
            Draw(Board);
            std::cout << "\nYou won, " << PlayerOne << "!\n\n";
            break;

        case 2:
            Draw(Board);
            std::cout << "\nYou won, " << PlayerTwo << "!\n\n";
            break;

        case 3:
            Draw(Board);
            std::cout << "\nIt's a draw!\n\n";
            break;
        }
    }
}
