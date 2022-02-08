#include <iostream>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <stdlib.h>

using namespace std;
int board[9][9] = { 0 };
int SolvedBoard[9][9] = { 0 };
int LockBoard[9][9] = { 0 };
vector<vector<vector<int>>> Vboard;//First num is col, second is row, third is pencils

void rows(int col, int row, int num) {//delete pencils from affected rows
	for (int i = 0; i < 9; i++) {//cycle through each vector for that row
		for (int j = 0; j < Vboard[i][row].size(); j++) {//cycle through all pencil marks
			if (Vboard[i][row][j] == num) {//if a pencil matches newly put number
				Vboard[i][row].erase(Vboard[i][row].begin() + j);//delete that sucker
				break;
			}
		}
	}
}
void cols(int col, int row, int num) {//delete pencils from affected cols
	for (int i = 0; i < 9; i++) {//cycle through each vector for that col
		for (int j = 0; j < Vboard[col][i].size(); j++) {//cycle through all pencil marks
			if (Vboard[col][i][j] == num) {//if a pencil matches newly put number
				Vboard[col][i].erase(Vboard[col][i].begin() + j);//delete that sucker
				break;
			}
		}
	}
}
void boxes(int col, int row, int num) {//delete pencils from affected boxes
	int colsHigh; 
	int colsLow;
	int rowsHigh;
	int rowsLow;
	if (col == 0 || col == 1 || col == 2) {//first 3 cols
		colsLow = 0;
		colsHigh = 3;
	}
	else if (col == 3 || col == 4 || col == 5) {//middle 3 cols
		colsLow = 3;
		colsHigh = 6;
	}
	else {//last 3 cols
		colsLow = 6;
		colsHigh = 9;
	}
	if (row == 0 || row == 1 || row == 2) {//top 3 rows
		rowsLow = 0;
		rowsHigh = 3;
	}
	else if (row == 3 || row == 4 || row == 5) {//middle 3 rows
		rowsLow = 3;
		rowsHigh = 6;
	}
	else {//bottom 3 rows
		rowsLow = 6;
		rowsHigh = 9;
	}
	for (int i = colsLow; i < colsHigh; i++) {//cycle thru cols
		for (int j = rowsLow; j < rowsHigh; j++) {//cycle thru rows
			for (int k = 0; k < Vboard[i][j].size(); k++) {//cycle thru pencils
				if (Vboard[i][j][k] == num) {//found it 
					Vboard[i][j].erase(Vboard[i][j].begin() + k);//delete that sucker
					break;
				}
			}
		}
	}
}
void print() {//print gameboard
	for (int i = 0; i < 9; i++) {//cols
		for (int j = 0; j < 9; j++) {//rows
			cout << board[i][j] << " ";//output number
			if ((j + 1) % 3 == 0) {//every 3rd coloum create extra space
				cout << " ";
			}
		}
		cout << endl;//create new row
		if ((i + 1) % 3 == 0) {//every 3rd row create extra row
			cout << endl;
		}
	}
}
void move() {//takes player move..somehow I totally switched row and column in this function and dont have the will to go back and figure it out
	int row = 0;//reset every time to avoid confusion
	int col = 0;
	int num = 0;
	cout << "At any moment, if you wish no longer play enter these numbers for the ROW and enter anything else for column and number\n99 = Quit\n88 = Solution\n77 = Reset board\n";
	cout << "Please enter a column, row and number to replace with(in that order (C R N)):";
	cin >> row >> col >> num;
	if (row > 70) {//assistive moves
		if (row == 99) {//quit
			exit(EXIT_FAILURE);
		}
		else if (row == 88) {//show solution board and end game
			cout << "Your board:\n";
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					cout << board[i][j] << " ";//output number
					if ((j + 1) % 3 == 0) {//every 3rd coloum create extra space
						cout << " ";
					}
				}
				cout << endl;//create new row
				if ((i + 1) % 3 == 0) {//every 3rd row create extra row
					cout << endl;
				}
			}
			cout << "Solution Board:\n";
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					cout << SolvedBoard[i][j] << " ";//output number
					if ((j + 1) % 3 == 0) {//every 3rd coloum create extra space
						cout << " ";
					}
				}
				cout << endl;//create new row
				if ((i + 1) % 3 == 0) {//every 3rd row create extra row
					cout << endl;
				}
			}
			exit(EXIT_FAILURE);//end game
		}
		else if (row == 77) {//reset board
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					board[i][j] = LockBoard[i][j];//reset nums to locked board
				}
				cout << "Reset board, Continue to play as normal\n";
				print();
				cout << "Please enter a column, row and number to replace with(in that order (C R N)):";
				cin >> row >> col >> num;//resume play
			}
		}
	}
		for (;;) {//check valid numbers
			if (0 > num || num > 9) {
				cout << "That number is invalid. Please enter a new number:";
				cin >> num;
			}
			else if (0 > row || row > 9) {
				cout << "That row is invalid. Please enter a new row:";
				cin >> row;
			}
			else if (0 > col || col > 9) {
				cout << "That column is invalid. Please enter a new number:";
				cin >> col;
			}
			else if (board[col - 1][row - 1] = LockBoard[col - 1][row - 1]) {
				cout << "That number is part of the original board. Do NOT touch. Try again:";
				cin >> row >> col >> num;
			}
			else {//continue if okay
				break;
			}
		}
		board[col - 1][row - 1] = num;//change nums in board
		system("CLS");//clear screen
		cout << "You changed the " << col << " row and the " << row << " column to a " << num << endl;
		print();//print new board
}
int number() {//start in square 1 and pick random number, after that remove 1 from all affected squares. Repeat 2-81
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (Vboard[i][j].size() == 0) {//if broken restart
				return 0;
			}
			int random = rand() % (Vboard[i][j].size());//find random num in the vector
			board[i][j] = Vboard[i][j][random];//assign to printed board
			rows(i, j, board[i][j]);///delete from all other boxes
			cols(i, j, board[i][j]);
			boxes(i, j, board[i][j]);
		}
	}
	return 1;
}
void vectors() {//set vectors 1-9
	for (int k = 0; k < 9; k++) {//vector 1
		vector<vector<int>> v2;
		for (int i = 0; i < 9; i++) {//vector 2
			vector<int> v1;
			for (int j = 0; j < 9; j++) {//vector 3
				v1.push_back(j + 1);//assign 1-9 to inside vector
			}
			v2.push_back(v1);//assign vectors to the vector
		}
		Vboard.push_back(v2);//assign vector of vectors to vector
	}
}
void reset() {
	for (int i = 0; i < 9; i++) {//cols
		for (int j = 0; j < 9; j++) {//rows			
			board[i][j] = 0;//zero out the array
		}
	}
	Vboard.erase(Vboard.begin(), Vboard.begin() + Vboard.size());//clean the entire 3d vector
}
void create() {
	for(;;) {
		vectors();//create vectors
		int check = number();//make board
		if (check == 0) {//fail restart
			reset();
		}else {//pass means output
			print();
			break;
		}
	} 
}
void difficulty(int hide) {
	int remove;
	for (int i = 0; i < 9; i++) {//before edits hold one version of solve
		for (int j = 0; j < 9; j++) {
			SolvedBoard[i][j] = board[i][j];
		}
	}
	for (;;) {
		if (hide == 1) {//easy
			remove = 24;
			break;
		}
		else if (hide == 2) {//medium
			remove = 32;
			break;
		}
		else if (hide == 3) {//hard
			remove = 40;
			break;
		}
		else {//try again
			cout << "You entered an invalid difficulty, Please enter a number between 1 and 3:";
			cin >> hide;
		}
	}
	for (int i = 0; i < remove; i++) {//do difficulty times
		for (;;) {//keep going until it finds an untouched number
			int row = rand() % 9;
			int col = rand() % 9;
			if (board[row][col] != 0) {//if number still there remove and proceed
				board[row][col] = 0;
				break;
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			LockBoard[i][j] = board[i][j];//create new board to compare playable actions against
		}
	}
}
int full() {//If no 0s then begin solve process
	for (int i = 0; i < 9; i++) {//cycle rows
		for (int j = 0; j < 9; j++) {//cycle cols
			if (board[i][j] == 0) {//if 0 return to play
				return 0;
			}
		}
	}
	return 1;//if all are ones, begin solve
}
int solve() {//solves for any board, it solves independantly of the original board. Hoping it would "catch" any mistakes
	for (int i = 0; i < 9; i++) {//cycle through all numbers of the board
		for (int j = 0; j < 9; j++) {
			int number = board[i][j];//create variable of current number to check
			for (int k = 0; k < 9; k++) {//check col
				if (k == i) {//if its the same as current box, skip
					continue;
				}
				else if (number == board[k][j]) {//if same num, tell user they failed and check again. Output which box broke
					cout << "This board is not correct, Please try again\n";
					cout << "A box that caused the error is column " << i+1 << ", row " << j +1<< endl;
					return 0;
				}
			}
			for (int k = 0; k < 9; k++) {//check row
				if (k == j) {//if its the same as current box, skip
					continue;
				}
				else if (number == board[i][k]) {//if same num, tell user they failed and check again. Output which box broke
					cout << "This board is not correct, Please try again\n";
					cout << "A box that caused the error is column " << i +1<< ", row " << j +1<< endl;
					return 0;
				}
			}//check box
			int colsHigh = 0;
			int colsLow = 0;
			int rowsHigh= 0;
			int rowsLow= 0;
			if (i == 0 || i == 1 || i == 2) {//first 3 cols
				colsLow = 0;
				colsHigh = 3;
			}
			else if (i == 3 || i == 4 || i == 5) {//middle 3 cols
				colsLow = 3;
				colsHigh = 6;
			}
			else {//last 3 cols
				colsLow = 6;
				colsHigh = 9;
			}
			if (j == 0 || j == 1 || j == 2) {//top 3 rows
				rowsLow = 0;
				rowsHigh = 3;
			}
			else if (j == 3 || j == 4 || j == 5) {//middle 3 rows
				rowsLow = 3;
				rowsHigh = 6;
			}
			else {//bottom 3 rows
				rowsLow = 6;
				rowsHigh = 9;
			}
			for (int k = colsLow; k < colsHigh; k++) {//cycle thru cols
				for (int l = rowsLow; l < rowsHigh; l++) {//cycle thru rows
					if (k == i && l == j) {//if same coord, keep moving
						continue;
					}
					else if (number == board[k][l]) {
						cout << "This board is not correct, please try again\n";
						cout << "A box that caused the error is column " << i + 1<< ", row " << j + 1<< endl;
						return 0;
					}
				}
			}
		}
	}
	cout << "Congratulations, You solved the board!\n";//you won somehow
	return 1;
}
int main() {
	srand(time(NULL));
	cout << "Welcome to the Sudoku board generator\n";
	create();//create board
	int level;
	cout << "What level of difficulty would you like?\n1 = Easy\n2 = Medium\n3 = Hard\n";
	cin >> level;
	difficulty(level);
	print();//original print
	for (;;) {
		for (;;) {//play keeps going until solved
			move();
			if (full() == 1) {//check for full board
				break;
			}
		}
		if (solve() == 0){//check for solve
			continue;//you lose keep going
		}
		else {//you win
			break;
		}
	}
	cout << "Thank you for playing Quinton's Sudoku. I hope you have a good day!\n";
	system("pause");
	return 0;
}
