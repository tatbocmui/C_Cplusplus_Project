#include <iostream>
#include <string>
using namespace std;
/*Co 3 mang
	Phan xu ly so chu cai trong string
	Dem xem con bao nhieu chu cai can phai doan
*/
#define NUMBER_OF_LIFE 3

string ans; //Ket qua
size_t SIZE_ANS;//chieu dai cua chuoi ket qua	
string your_str;//The hien ket qua ban da doan;
char yans;//your answer 
char flag = 0;//neu dap an dung flag = 1; reset sau moi luot
int count_number_of_life = NUMBER_OF_LIFE; //dem so mang
int count_char;

void initialize();
void getYourAnswer();
void show_Result();
void checkYourAnswer();//Kiem tra ket qua neu co thi thay the vao vi tri trong, neu khong thi thoi
void countNumber();//dem so mang, so char can phai doan
void winOrLose();

int main(int argc, char const *argv[])
{
	/* code */
	initialize();
	//Main function xu ly ket qua:
	//+) hien thi ket qua
	//+) Xu ly ket qua
	while(count_number_of_life != 0 && count_char != 0){
		show_Result();
		getYourAnswer();
		//Check ket qua co trong dap an hay khong
		checkYourAnswer();
		countNumber();
	}
	//Quyet dinh thang thua
	winOrLose();
	return 0;
}

void initialize(){
	ans.assign("Cuong");
	SIZE_ANS = ans.size();
	count_char = SIZE_ANS;
	for(int i = SIZE_ANS; i>0;--i){
		your_str.push_back('_');
	}	
}

void getYourAnswer(){
	cout << "What is your prediced character?" << endl;
	cin >> yans;
}

void show_Result(){
	cout << your_str << endl;
}

void checkYourAnswer(){
	for(int i = SIZE_ANS; i>0;--i){
		if(yans == ans[i-1]){
			your_str[i-1] = yans;
			flag = 1;
			--count_char;//moi lan doan dung thi tru di
		}
	}	
	if(flag){
		cout << "Correct answer. We have " << yans << " in this string" << endl;
		flag = 0;
	}else{
		cout << "Wrong answer. We do not have " << yans <<  " in this string" << endl;
		--count_number_of_life;//tru so mang boi vi doan sai
		flag = 0;
	}
}

void countNumber(){
	cout << "You have " << count_char << " character to predict" << endl;
	cout << "You have " << count_number_of_life << " number of predictions" << endl;	
}

void winOrLose(){
	if(count_char == 0){
		cout << "You won!" << endl;
	}else{
		cout << "You lose!" << endl;
	}	
}