#include <stdio.h>

// to do: use http://www.cse.yorku.ca/~oz/hash.html to hashmap for chars
// i forgot why i used hash
// ' FLOX_' becomes 32 70 76 79 88 95
char board[81]; int player_bit;

char inrange(int x){
	return x < 0 || x > 80 ? 0 : board[x];
}
//if is a statement, not an expression
void pboard(){
	for (int i = 0; i < 81; i++)
	{
		if (!(i % 9))
		{
			printf("\n");
		}
		printf("%c%i%i", board[i], i%9, (int)(i/9));
	}
}
// type 0: _ type 1: |
int turn(int coord, int type){ // int coord = y_coord * 8 + x_coord;
	/*if(type) //switch-case bad here
	{
		if(board[coord] == '_'){board[coord] = 'L';}
	} else { // use else if, not elif
		if(board[coord] == 'F'){board[coord] = 'L';}
	}*/
	if(board[coord] == (type ? '_' : 'F')){board[coord] = 'L';printf("a");}
	if(board[coord] == ' '){board[coord] = (type ? 'F' : '_');printf("e");}
	for(int i = 0; i < 81; i++)
	{
		if(board[i] == 'L' &&
		inrange(i - 9) > 75 && // not 32 or f, l o x _ ok
		inrange(i + 1) != ' ' &&
		inrange(i + 1) != '_'
		){board[i] = player_bit ? 79 : 88;}
	}
	int z = 0, flip_pb = 0;
	for(int i = 0; i < 81; i++)
	{
		if(board[i] == 79 || board[i] == 88){z++; flip_pb = 1;}
	}
	player_bit ^= flip_pb;
		return z > 63;
}


int main(){
	player_bit = 0;
	int x_coord = 0, y_coord = 0, type = 0;

	for(int i = 0; i < 81; board[i++] = 32);
	board[0]='_';board[9]='L';board[10]='F';

	do
	{
	pboard();
	scanf("%d%d%d", &x_coord, &y_coord, &type); //only ' ' works
	} while(!(turn(y_coord * 9 + x_coord, type)));
}