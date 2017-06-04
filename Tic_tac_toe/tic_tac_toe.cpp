#include <iostream>

using namespace std;

//global variable
int yourChoice;
int pos;
char player[2][3][3] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
char board[3][3] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
int player_index = 1;//1 = player 1; 2 = player 2
char player_syntax[2] = {' ', ' '};
int flag = 0;//Have winner
//Game Function
void menu();//Draw Menu and choose menu
void draw_board();//Draw board to play
void put_X_O();
void checkWin();
void changeTurn();
int main(int argc, char const *argv[])
{
	/* code */
	menu();
	if(yourChoice == 3){
		return 0;
	}
	while(1){
		draw_board();
		put_X_O();
		checkWin();
		changeTurn();
		if(flag == 1){
			draw_board();
			break;
		}
	}
	return 0;
}


void menu(){
	cout << "_____Menu______" << endl;
	cout << "1: Play with X" << endl;
	cout << "2: Play with O" << endl;
	cout << "3: Exit" << endl;
	cout << "Enter player "<< player_index << " choice:> ";
	cin >> yourChoice;
	if(yourChoice == 1){
		player_syntax[0] = 'X';
		player_syntax[1] = 'O';
	}
	else{
		player_syntax[0] = 'O';
		player_syntax[1] = 'X';
	}
}

void draw_board(){
	for(auto row = 0; row < 3; row++){
		for (auto i = 0; i < 2; i++){
			cout << "\t\t|";
		}
		cout << "\t\t" << endl;
		auto col = 0;
		for (col = 0; col < 2; col++){
			cout << "\t" << board[row][col] << "\t|";
		}
		cout << "\t" << board[row][col] <<"\t" << endl;		
		if(row != 2){
			for(auto i = 0; i< 50; i++){
			cout << "_";
			}
		}
		
		cout << endl;		
	}

}

void put_X_O(){
	cout << "Player " << player_index << " turn :> ";
	cin >> pos;
	switch (pos){
		case 0: player[player_index - 1][0][0] = player_syntax[player_index-1];board[0][0] = player_syntax[player_index-1];break;
		case 1: player[player_index - 1][0][1] = player_syntax[player_index-1];board[0][1] = player_syntax[player_index-1];break;
		case 2: player[player_index - 1][0][2] = player_syntax[player_index-1];board[0][2] = player_syntax[player_index-1];break;
		case 3: player[player_index - 1][1][0] = player_syntax[player_index-1];board[1][0] = player_syntax[player_index-1];break;
		case 4: player[player_index - 1][1][1] = player_syntax[player_index-1];board[1][1] = player_syntax[player_index-1];break;
		case 5: player[player_index - 1][1][2] = player_syntax[player_index-1];board[1][2] = player_syntax[player_index-1];break;
		case 6: player[player_index - 1][2][0] = player_syntax[player_index-1];board[2][0] = player_syntax[player_index-1];break;
		case 7: player[player_index - 1][2][1] = player_syntax[player_index-1];board[2][1] = player_syntax[player_index-1];break;
		case 8: player[player_index - 1][2][2] = player_syntax[player_index-1];board[2][2] = player_syntax[player_index-1];break;
		default: break;
	}
}

void checkWin(){
	int col, row;
	switch(pos){
		case 0:col = 0; row = 0;break;
		case 1:col = 1; row = 0;break;
		case 2:col = 2; row = 0;break;
		case 3:col = 0; row = 1;break;
		case 4:col = 1; row = 1;break;
		case 5:col = 2; row = 1;break;
		case 6:col = 0; row = 2;break;
		case 7:col = 1; row = 2;break;
		case 8:col = 2; row = 2;break;
	}
	//Check row
	auto row_index = 0;//check each row
	auto col_index = 0; //check each col
	auto count = 0;
	for(row_index = 0; row_index <3; row_index++){
		count = 0;
		for(col_index = 0; col_index < 3; col_index++){
			if(player[player_index - 1][row_index][col_index] == player_syntax[player_index-1])
				count++;
			if(count == 3){
				//report win
				cout << "Player " << player_index << " won" << endl;
				flag = 1;
			}
		}
	}

	//Check diagonal
	if ((player[player_index - 1][0][0] == player_syntax[player_index-1] && player[player_index - 1][4][4] == player_syntax[player_index-1] && player[player_index - 1][8][8] == player_syntax[player_index-1]) || (player[player_index - 1][2][2] == player_syntax[player_index-1] && player[player_index - 1][4][4] == player_syntax[player_index-1] && player[player_index - 1][6][6] == player_syntax[player_index-1])){
		//report win
		cout << "Player " << player_index << " won" << endl;
		flag = 1;
	}

	//Check col
	for(col_index = 0; col_index < 3; col_index++){
		count = 0;
		for(row_index = 0; row_index < 3; row_index++){
			if(player[player_index - 1][row_index][col_index] == player_syntax[player_index-1]){
				count++;
			}
			if(count == 3){
				//report win
				cout << "Player " << player_index << " won" << endl;
				flag = 1;				
			}
		}
	}		
}

void changeTurn(){
	if (player_index == 1){
		player_index = 2;	
	}else{
		player_index = 1;
	}
}