#include<bits/stdc++.h>
using namespace std;

char game[3][3]; // 3X3 matrix 
int bestX=-1,bestY=-1; // to store coordinates of best move 
char player,oponent; // player is user and oponent is computer //

bool checkMoveLeft(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++)
			if(game[i][j]==' ')
				return true;
	}
	return false;
}

void display(){      //printing the game on screen //
	cout<<"\n\n\n\t\t\t"<<game[0][0]<<" | "<<game[0][1]<<" | "<<game[0][2]<<endl<<endl;
	cout<<"\t\t\t"<<game[1][0]<<" | "<<game[1][1]<<" | "<<game[1][2]<<endl<<endl;
	cout<<"\t\t\t"<<game[2][0]<<" | "<<game[2][1]<<" | "<<game[2][2]<<endl<<"\n\n\n";
}

int evaluate(int depth){
	if( game[0][0]==game[1][1] && game[1][1]==game[2][2] ){
		if(game[0][0] == player)
			return -10+depth;
		if(game[0][0]==oponent)
			return 10-depth ;
	}
	if( game[2][0]==game[1][1] && game[1][1]==game[0][2] ) {
		if(game[1][1] == player)
			return -10+depth;
		if(game[1][1]==oponent)
			return 10-depth;
	}

	for(int i=0;i<3;i++){
		if(game[i][0]==game[i][1]&&game[i][1]==game[i][2]){
			if(game[i][0]==player)
				return -10+depth;
			if(game[i][0]==oponent)
				return 10-depth;
		}
	}

	for(int i=0;i<3;i++){
		if(game[0][i]==game[1][i]&&game[1][i]==game[2][i]){
			if(game[0][i]==player)
				return -10+depth;
			if(game[0][i]==oponent)
				return 10-depth;
		}
	}

	return 0;
}

int miniMax(int depth, bool isMax){
	int score = evaluate(depth);
	int bestScore;
	if(score == 10-depth)
		return score;
	if(score == -10+depth)
		return score;
	if(!checkMoveLeft())
		return 0;

	if(isMax){
		bestScore = -10000;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(game[i][j]==' '){
					game[i][j] = oponent;
					bestScore = max(miniMax(depth+1,false),bestScore);
					game[i][j] = ' ';



				}
			}
		}
		return bestScore;
	}

	else{
		bestScore = 10000;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(game[i][j] == ' '){
					game[i][j] = player;
					bestScore = min(miniMax(depth+1,true),bestScore);
					game[i][j] = ' ';


				}
			}
		}
		return bestScore;
	}

}

int bestMove(int depth){
	int bestValue = -1000;
	int value;
	for(int i=0;i<3;i++){

		for(int j=0;j<3;j++){
			if(game[i][j] == ' '){

				game[i][j] = oponent;

				value = miniMax(depth,false);

				if(value > bestValue){
					bestX = i;
					bestY = j;
					bestValue = value;
				}
				game[i][j] = ' ';  // undo changes // 
			}

		}

	}
}

void playGame(){
	int i,j;
	int depth = 0;
	while(true){
		cout<<"Enter the coordinate of your input: ";
		cin>>i>>j;
		game[i-1][j-1] = player;
		if(!checkMoveLeft()){
			display();
			cout<<"\nDRAW GAME!..."<<endl;
			break;
		}
		if(evaluate(0)==-10){
			cout<<"CONGRATULATIONS...You have won !! :):)"<<endl;
			break;
		}
		bestMove(depth);
		if(player == 'X')
			oponent =  game[bestX][bestY] = 'O';
		else
			oponent = game[bestX][bestY] = 'X';
		if(evaluate(0)==10){
			display();
			cout<<"sorry:(, try again to win..."<<endl;
			break;
		}
		display();
		depth++;
	}
}

int main(){
	int i,j; // variable i,j to store the coordinate of input by user 
	cout<<"Welcome to Tic-Tac-Toe game!!!"<<endl;
	cout<<"Please enter your choice 'O' or 'X' for the game: ";
	cin>>player;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++)
			game[i][j]=' ';
	} 

	cout<<"Lets start with your turn...."<<endl;
	playGame();
}
