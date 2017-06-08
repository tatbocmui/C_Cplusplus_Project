#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H 

#include <iostream>
#include <vector>

using namespace std;
#define HU_PLAYER 0
#define AI_PLAYER 1
#define DRAW_PLAYER 2
#define NO_DETERMINE 3

char PLAYER_SYNTAX[2] = {' ', ' '};


struct AIBestMoves{
	AIBestMoves(){}
	AIBestMoves(int Score):score(Score){}
	int score;
	int row;
	int	col;
};

struct TABLE_BOARD{
	TABLE_BOARD(){}
	TABLE_BOARD(int ROW, int COL):b_row(ROW),b_col(COL){}
	TABLE_BOARD(TABLE_BOARD &tb){
		for(int k = 0; k < 2; k++){
			for(int i = 0; i< 3; i++){
				for(int j = 0; j<3; j++){
					player[k][i][j] = tb.player[k][i][j];
				}
		    }			
		}
		for(int i = 0; i< 3; i++){
			for(int j = 0; j<3; j++){
				board[i][j] = tb.board[i][j];
			}
	    }	
	    b_row = tb.b_row;
	    b_col = tb.b_col;

	}
	char player[2][3][3] = {{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}},{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}};
	char board[3][3] = {{'0', '1', '2'}, {'3', '4', '5'}, {'6', '7', '8'}};
	void setPos(int player, int row, int col);
	int checkWin();
	void draw_board();
	int b_row;
	int b_col;	
};

void TABLE_BOARD::setPos(int player_turn, int row, int col){
	player[player_turn][row][col] = PLAYER_SYNTAX[player_turn];
	board[row][col] = PLAYER_SYNTAX[player_turn];
}

void TABLE_BOARD::draw_board(){
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

int TABLE_BOARD::checkWin(){
	//Check row
	auto row_index = 0;//check each row
	auto col_index = 0; //check each col
	auto count = 0;
	int player_turn = 0;
	for(;player_turn < 2; player_turn++){
		for(row_index = 0; row_index <3; row_index++){
			count = 0;
			for(col_index = 0; col_index < 3; col_index++){
				if(player[player_turn][row_index][col_index] == PLAYER_SYNTAX[player_turn])
					count++;
				if(count == 3){
					//report win
					// cout << "Player " << player_turn << " won" << endl;
					return player_turn;
				}
			}
		}

		//Check diagonal
		if ((player[player_turn][0][0] == PLAYER_SYNTAX[player_turn] && player[player_turn][4][4] == PLAYER_SYNTAX[player_turn] && player[player_turn][8][8] == PLAYER_SYNTAX[player_turn]) || (player[player_turn][2][2] == PLAYER_SYNTAX[player_turn] && player[player_turn][4][4] == PLAYER_SYNTAX[player_turn] && player[player_turn][6][6] == PLAYER_SYNTAX[player_turn])){
			//report win
			// cout << "Player " << player_turn << " won" << endl;
			return player_turn;
		}

		//Check col
		for(col_index = 0; col_index < 3; col_index++){
			count = 0;
			for(row_index = 0; row_index < 3; row_index++){
				if(player[player_turn][row_index][col_index] == PLAYER_SYNTAX[player_turn]){
					count++;
				}
				if(count == 3){
					//report win
					// cout << "Player " << player_turn << " won" << endl;
					return player_turn;			
				}
			}
		}	
	}
	int col, row;
	int count_board_element = 0;
	for(row = 0; row < 3; row++){
		for(col = 0; col < 3; col++){
			if(board[row][col] == 'X' || board[row][col] == 'O')
				count_board_element++;
		}
	}
	if(count_board_element == 9){
		return DRAW_PLAYER;
	}	

	return NO_DETERMINE;
}


AIBestMoves getBestMoves(TABLE_BOARD tb, int player_turn);
void menu();
void Hu_set_pos(TABLE_BOARD &tb);
void AI_set_pos(TABLE_BOARD &tb);

void menu(){
	int yourChoice;
	cout << "_____Menu______" << endl;
	cout << "1: Play with X" << endl;
	cout << "2: Play with O" << endl;
	cout << "3: Exit" << endl;
	cout << "Enter player your choice:> ";
	cin >> yourChoice;
	if(yourChoice == 1){
		PLAYER_SYNTAX[0] = 'X';
		PLAYER_SYNTAX[1] = 'O';
	}
	else{
		PLAYER_SYNTAX[0] = 'O';
		PLAYER_SYNTAX[1] = 'X';
	}
}


void Hu_set_pos(TABLE_BOARD &tb){
	int row, col;
	int pos;
	cout << "Human player set pos :> ";
	cin >> pos;
	while(tb.board[row][col] == 'X' || tb.board[row][col] == 'O'){
		cout << "Can not set this position" << endl;
		cout << "Human player set pos :> ";
		cin >> pos;	
	}
	switch(pos){
		case 0: row = 0; col = 0; break;
		case 1: row = 0; col = 1; break;
		case 2: row = 0; col = 2; break;
		case 3: row = 1; col = 0; break;
		case 4: row = 1; col = 1; break;
		case 5: row = 1; col = 2; break;
		case 6: row = 2; col = 0; break;
		case 7: row = 2; col = 1; break;
		case 8: row = 2; col = 2; break;
	}	
	tb.setPos(HU_PLAYER, row, col);
}

void AI_set_pos(TABLE_BOARD &tb){
	AIBestMoves temp = getBestMoves(tb, AI_PLAYER);
	tb.setPos(AI_PLAYER, temp.row, temp.col);
	int pos;
	if(temp.row == 0 && temp.col == 0){
		pos = 0;
	}else if(temp.row == 0 && temp.col == 1){
		pos = 1;
	}else if(temp.row == 0 && temp.col == 2){
		pos = 2;
	}else if(temp.row == 1 && temp.col == 0){
		pos = 3;
	}else if(temp.row == 1 && temp.col == 1){
		pos = 4;
	}else if(temp.row == 1 && temp.col == 2){
		pos = 5;
	}else if(temp.row == 2 && temp.col == 0){
		pos = 6;
	}else if(temp.row == 2 && temp.col == 1){
		pos = 7;
	}else if(temp.row == 2 && temp.col == 2){
		pos = 8;
	}
	cout << "AI player set pos :> " << pos << endl;
}

AIBestMoves getBestMoves(TABLE_BOARD tb, int player_turn){
	//Case of end state
	int temp = tb.checkWin();
	if(temp == HU_PLAYER){
		// cout << "HU_PLAYER" << endl;
		return AIBestMoves(-10);
	}else if(temp == AI_PLAYER){
		// cout << "AI_PLAYER" << endl;
		return AIBestMoves(10);
	}else if(temp == DRAW_PLAYER){
		// cout << "DRAW_PLAYER" << endl;
		return AIBestMoves(0);
	}

	vector<AIBestMoves> moves;

	for(auto row = 0; row < 3; row++){
		for(auto col = 0; col < 3; col++){
			if(tb.board[row][col] != 'X' && tb.board[row][col] != 'O'){
				auto temp_board = tb.board[row][col];//save this state to temp
				auto temp_player = tb.player[player_turn][row][col];
				AIBestMoves move;
				move.row = row;
				move.col = col;
				tb.player[player_turn][row][col] = PLAYER_SYNTAX[player_turn];
				tb.board[row][col] = PLAYER_SYNTAX[player_turn];//try this state to calculate score
				if(player_turn == HU_PLAYER){//human player
					// cout << "if(player_turn == HU_PLAYER)" << endl;
					move.score = getBestMoves(tb, AI_PLAYER).score;
					// cout << "move.score (AI_PLAYER) = " << move.score << endl;
				}else{//ai player
					// cout << "if(player_turn == AI_PLAYER)" << endl;
					move.score = getBestMoves(tb, HU_PLAYER).score;
					// cout << "move.score (HU_PLAYER) = " << move.score << endl;
				}
				moves.push_back(move);
				// tb.player[player_turn][row][col] = temp_player;
				// tb.board[row][col] = temp_board;//return the original value
			}
		}
	}
	int bestMove = 0;
	if(player_turn == AI_PLAYER){
		int bestScore = -10000;
		for(int i = 0; i<moves.size(); i++){
			if(moves[i].score>bestScore){
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}else{
		int bestScore = 10000;
		for(int i = 0; i<moves.size();i++){
			if(moves[i].score<bestScore){
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	return moves[bestMove];	
}
#endif