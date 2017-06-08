#include "tic_tac_toe.h"

int main(int argc, char const *argv[])
{
	/* code */
	menu();
	int player_turn = HU_PLAYER;
	int state;
	TABLE_BOARD tb(3,3);
	while(1){
		tb.draw_board();
		if(player_turn == AI_PLAYER){
			AI_set_pos(tb);
			player_turn = HU_PLAYER;
		}else{
			Hu_set_pos(tb);
			player_turn = AI_PLAYER;
		}
		state = tb.checkWin();
		if(state == HU_PLAYER || state == AI_PLAYER){
			tb.draw_board();
			if(state == AI_PLAYER){
				cout << "Player AI win!" << endl;				
			}else{
				cout << "Player Human win!" << endl;
			}
			
			break;
		}else if(state == DRAW_PLAYER){
			tb.draw_board();
			cout << "DRAW" << endl;
			break;
		}
			
	}
	return 0;
}

