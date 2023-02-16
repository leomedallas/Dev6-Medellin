//Tic-Tac-Toe
//Playing Tic Tac Toe with an AI
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <locale.h>

using namespace std;

//Global Constants
const char X = 'X';
const char O = 'O';
const char TIE = 'T';
const char EMPTY = ' ';
const char NO_ONE = 'N';

//Prototype Functions
char winner(const vector<char>& board);
void instructions();
void displayBoard(const vector<char>& board);
char askYesNo(string question);
char humanSymbol();
char opponent(char symbol);
int askNumber(string question, int high, int low = 0);
bool isLegal(int move, const vector<char>& board);
int humanMove(const vector<char>& board);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char human, char computer);


//Function main
int main() {
	setlocale(LC_ALL, "spanish");

	const int NUM_SQUARES = 9;
	int move;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	char player = humanSymbol();
	char computer = opponent(player);
	char turn = X;

	//displayBoard(board);

	while (winner(board) == NO_ONE) {

		if (turn == player) {
			move = humanMove(board);
			board[move] = player;
		}
		else {
			move = computerMove(board, computer);
			board[move] = computer;
		}

		turn = opponent(turn);
		displayBoard(board);
	}

	announceWinner(winner(board), player, computer);

}

//Return the piece winner a tie or noBody
char winner(const vector<char>& board)
{
	//This are the posibilities to win.
	const int WINNING_POS[8][3] = { {0, 1, 2},
									{3, 4, 5},
									{6, 7, 8},
									{0, 3, 6},
									{1, 4, 7},
									{2, 5, 8},
									{2, 4, 6},
									{0, 4, 8} };

	const int TOTAL_ROWS = 8;

	//Return the winner
	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if ((board[WINNING_POS[row][0]] != EMPTY) &&
			(board[WINNING_POS[row][0]] == board[WINNING_POS[row][1]]) &&
			(board[WINNING_POS[row][1]] == board[WINNING_POS[row][2]]))
		{
			return board[WINNING_POS[row][0]];
		}

	}

	//Return a Tie
	if (count(board.begin(), board.end(), EMPTY) == 0) {
		return TIE;
	}

	//Return that no one is the winner yet
	return NO_ONE;
}

void instructions() {
	cout << "\n�Bienvenido al juego de Gato!\n";
	cout << "Donde te enfrentar�s a un digno oponente\n";
	cout << "Debes elegir un n�mero 0 - 8 para definir una posici�n en el tablero: \n";
	cout << " 0 | 1 | 2 \n";
	cout << " 3 | 4 | 5 \n";
	cout << " 6 | 7 | 8 \n";

	cout << "Prep�rate, la batalla est� a punto de comenzar.\n\n";
}

char askYesNo(string question) {
	char answer;
	do {
		cout << question << "(y/n)";
		cin >> answer;
	} while (answer != 'y' && answer != 'n');
	return answer;
}

int askNumber(string question, int high, int low) {
	int number;
	do {
		cout << question << "(" << low << " - " << high << ")";
		cin >> number;
	} while (number > high || number < low);

	return number;
}

//This function is used to define who starts playing.
char humanSymbol() {
	char go_first = askYesNo("�Quieres empezar?");

	if (go_first == 'y')
	{
		cout << "Buena elecci�n, la necesitar�s\n";
		return X;
	}
	else {
		cout << "Admiro tu valent�a, yo empezar� entonces\n";
		return O;
	}
}

char opponent(char symbol) {
	if (symbol == X) {
		return O;
	}
	else
	{
		return X;
	}
}

//Display board on console
void displayBoard(const vector<char>& board) {
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n";
}


//Returns wheater the move is legal or not.

inline bool isLegal(int move, const vector<char>& board) {

	return (board[move] == EMPTY);
}

//Capture the human's move and return int move
int humanMove(const vector<char>& board) {
	int move = askNumber("�Elige una posici�n del tablero?", (board.size() - 1));

	while (!isLegal(move, board)) {
		cout << "\nEsa posici�n ya est� ocupada humano tonto.\n";
		move = askNumber("�Elige una posici�n del tablero?", (board.size() - 1));
	}

	cout << "Bien..\n";
	return move;
}


int computerMove(vector<char> board, char computer) {
	int move = 0;
	bool foundSpace = false;

	//Try to know if I will be the winner with the next move
	while (!foundSpace && move < board.size()) {

		if (isLegal(move, board)) {

			//If I choose this square, 
			board[move] = computer;
			//I'm gonna be the winner?
			foundSpace = winner(board) == computer;
			//I undo the action because it's just a test.
			board[move] = EMPTY;
		}

		if (!foundSpace) {
			++move;
		}
	}

	//Try to know if the human will be the winner with the next move
	if (!foundSpace) {
		move = 0;
		char human = opponent(computer);
		while (!foundSpace && move < board.size()) {

			if (isLegal(move, board)) {

				//If I choose this square, 
				board[move] = human;
				//I'm gonna be the winner?
				foundSpace = winner(board) == human;
				//I undo the action because it's just a test.
				board[move] = EMPTY;
			}

			if (!foundSpace) {
				++move;
			}
		}

	}

	//Find the best move starting on center
	if (!foundSpace) {
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVE[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

		while (!foundSpace && i < board.size()) {

			move = BEST_MOVE[i];
			if (isLegal(move, board)) {
				foundSpace = true;
			}

			++i;
		}
	}

	cout << "\nUsar� la posici�n " << move << "." << endl;
	return move;
}

void announceWinner(char winner, char human, char computer) {
	if (winner == computer) {
		cout << "\nEl ganador es: " << winner << endl;
		cout << "\n Soy el ganador!! Probando una vez m�s que las computadoras somos mejores que ustedes en todo sentido.\n";
	}
	else if (winner == human) {
		cout << "\nEl ganador es: " << winner << endl;
		cout << "\nNo es posible!! Hiciste trampa humano!!";
	}
	else {
		cout << "\n ES UN EMPATE\n";
		cout << "\nQue suerte tienes humano, cel�bralo es lo mejor que lograr�s.\n";
	}
}