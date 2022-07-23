#include <iostream>
#include <cstdlib>

const char WHITE_ROOK = 'R';
const char WHITE_PAWN = 'P';
const char WHITE_HORSE = 'H';
const char WHITE_BISHOP = 'B';
const char WHITE_QUEEN = 'Q';
const char WHITE_KING = 'K';

const char BLACK_ROOK = 'r';
const char BLACK_PAWN = 'p';
const char BLACK_HORSE = 'h';
const char BLACK_BISHOP = 'b';
const char BLACK_QUEEN = 'q';
const char BLACK_KING = 'k';

bool WHITE_CASTLE_LEFT = true;
bool WHITE_CASTLE_RIGHT = true;
bool WHITE_CASTLE_KING = true;

bool BLACK_CASTLE_LEFT = true;
bool BLACK_CASTLE_RIGHT = true;
bool BLACK_CASTLE_KING = true;

const char EMPTY_SQUARE = -2;
const char VERTICAL_LINE = -70;
const char HORIZONTAL_LINE = -51;

const char WHITE_PLAYER = 1;
const char BLACK_PLAYER = 2;

int StartUP_menu()
{
	int input;
start:
	system("CLS");
	std::cout << "   SIMPLE CHESS   " << std::endl;
	std::cout << std::endl;
	std::cout << "  1) Start P vs P Game (2 players)" << std::endl;
	std::cout << "  2) Start P vs IA Game (1 players/Work in progress currently unavailable)" << std::endl;
	std::cout << "  3) Basic Rules" << std::endl;
	std::cout << "  4) Exit Game" << std::endl;
	std::cout << std::endl;
	std::cout << "  Select Option(1-4): ";
	std::cin >> input;
	while (!std::cin.good()||input<1||input>4)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("CLS");
		std::cout << "   SIMPLE CHESS   " << std::endl;
		std::cout << std::endl;
		std::cout << "  1) Start P vs P Game (2 players)" << std::endl;
		std::cout << "  2) Start P vs IA Game (1 players/Work in progress currently unavailable)" << std::endl;
		std::cout << "  3) Basic Rules" << std::endl;
		std::cout << "  4) Exit Game" << std::endl;
		std::cout << std::endl;
		std::cout << "  Select Option(1-4): ";
		std::cin >> input;
	}
	switch (input)
	{
	case 1:
		break;
	case 2:
		std::cout << "NOT READY YET .... , select any other option" << std::endl;
		system("pause");
		goto start;
	case 3:
		system("CLS");
		std::cout << "White Player (UPERCASE)--> P,Q,K,R,B,H" << std::endl;
		std::cout << "BLACK Player (LOWERCASE)--> p,q,k,r,b,h" << std::endl;
		std::cout << std::endl;
		std::cout << "Pieces List/ Movement:" << std::endl;
		std::cout << std::endl;
		std::cout << "PAWN (P/p) --> Moves one square at a time, it can only move forward, it can only capture enemy pieces diagonally (one square to the left/Right and one up),if it has not moved yet they can start by moving two squares forward, it can do an en passant capture this happens when the opponent pawn does a double move start then if you have a pawn that could have killed the enemy pawn if it had moved only one square then you can still caputre it, if it reaches the final square on the board you can promote it to whatever piece you want." << std::endl;
		std::cout << "Rook (R/r) --> Moves vertically and horizontally the amount of squares you want without passing through any pieces." << std::endl;
		std::cout << "Horse (H/h) --> Moves in an L shape, two squares horizontally and one vertically or two squares vertically and one square horizontally." << std::endl;
		std::cout << "Bishop (B/b) --> Moves Diagonally the amount of squares you want without passing through any pieces." << std::endl;
		std::cout << "Queen (Q/q) --> Moves like a rook and a bishop, it can move diagonally/vertically/horizontally the amount of squares you want without passing through any pieces" << std::endl;
		std::cout << "King (K/k) --> Can only move one square in any direction, you can castle the king queen side or king side, this means that if there are no pieces between your king and either of your rooks you can move yout king two squares in the direction you are castling and put the rook on that side next to the king(if you castled king side then your king will go from e1 to g1 and the rook will gor from h1 to f1), this can only be done if neither the king and rook that you are using to castle have moved that game and if your king isn't in check." << std::endl;
		std::cout << std::endl;
		std::cout << "Basic Knowledge:" << std::endl;
		std::cout << std::endl;
		std::cout << "Check --> Your King is being attacked by an enemy piece you must move your king to a safe spot or kill the atacker or interpose the attack with another piece." << std::endl;
		std::cout << "Checkmate --> Your King is being attacked and you can't do anything to protect him, you lost the game." << std::endl;
		std::cout << "Stalemate --> The player that has to make a move can't move any of his pieces, it is a tie." << std::endl;
		system("pause");
		goto start;
	case 4:
	return 4;
	}
	return 0;
}
void Create_Grid(char Grid[][8])
{
	//Create Empty Board
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Grid[i][j] = EMPTY_SQUARE;
		}
	}
	//Setup Pieces
	for (int i = 0; i < 8; i++)
	{
		Grid[1][i] = BLACK_PAWN;
		Grid[6][i] = WHITE_PAWN;
	}
	Grid[0][0] = BLACK_ROOK;
	Grid[0][1] = BLACK_HORSE;
	Grid[0][2] = BLACK_BISHOP;
	Grid[0][3] = BLACK_QUEEN;
	Grid[0][4] = BLACK_KING;
	Grid[0][5] = BLACK_BISHOP;
	Grid[0][6] = BLACK_HORSE;
	Grid[0][7] = BLACK_ROOK;

	Grid[7][0] = WHITE_ROOK;
	Grid[7][1] = WHITE_HORSE;
	Grid[7][2] = WHITE_BISHOP;
	Grid[7][3] = WHITE_QUEEN;
	Grid[7][4] = WHITE_KING;
	Grid[7][5] = WHITE_BISHOP;
	Grid[7][6] = WHITE_HORSE;
	Grid[7][7] = WHITE_ROOK;
}
void Display_Grid(char Grid[][8])
{
	system("CLS");
	std::cout << "    ";
	for (int j = 0; j < 8; j++)
		std::cout << (char)(j + 97) << " ";
	std::cout << std::endl;
	std::cout << "   ";
	for (int i = 0; i < 16; i++)
		std::cout << HORIZONTAL_LINE;
	std::cout << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << (8 - i) << " " << VERTICAL_LINE << " ";
		for (int j = 0; j < 8; j++)
		{
			std::cout << Grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
bool Check_Start(char Grid[][8], char x, char y, char player)
{
	char pos = Grid[x][y];

	//Check piece existence
	if (pos == EMPTY_SQUARE)
	{
		return false;
	}

	//Check if it is your piece
	if (player == WHITE_PLAYER)
	{
		if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_KING && pos != WHITE_QUEEN && pos != WHITE_PAWN)
			return false;
	}
	else
	{
		if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_KING && pos != BLACK_QUEEN && pos != BLACK_PAWN)
			return false;
	}
	//Returns false if the starting position is wrong
	return true;
}
bool Player_In_Check(char Grid[][8], char player)
{
	int s, t;
	if (player == BLACK_PLAYER)
	{
		for (int p = 0; p < 8; p++)
		{
			for (int m = 0; m < 8; m++)
			{
				if (Grid[p][m] == BLACK_BISHOP || Grid[p][m] == BLACK_QUEEN)
				{
					//Look on all directions
					//Search TOP Left x-- y--
					s = m - 1;
					t = p - 1;
					if (t >= 0 && s >= 0)
					{
						while (t >= 0)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
								break;
							else if (Grid[t][s] == WHITE_KING)
								return true;
							s--;
							t--;
						}
					}
					//Search BOTTOM Right x++ y++
					s = m + 1;
					t = p + 1;
					if (t < 8 && s < 8)
					{
						while (t < 8)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
								break;
							else if (Grid[t][s] == WHITE_KING)
								return true;
							s++;
							t++;
						}
					}
					//Search BOTTOM Left x++ y--
					s = m - 1;
					t = p + 1;
					if (s >= 0 && t < 8)
					{
						while (t < 8)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
								break;
							else if (Grid[t][s] == WHITE_KING)
								return true;
							s--;
							t++;
						}
					}
					//Search top Right x-- y++
					s = m + 1;
					t = p - 1;
					if (s < 8 && t >= 0)
					{
						while (t >= 0)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
								break;
							else if (Grid[t][s] == WHITE_KING)
								return true;
							s++;
							t--;
						}
					}
				}
				if (Grid[p][m] == BLACK_ROOK || Grid[p][m] == BLACK_QUEEN)
				{
					//Look Right
					for (int t = m + 1; t < 8; t++)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != WHITE_KING)
							break;
						else if (Grid[p][t] == WHITE_KING)
							return true;
					}
					//Look Left
					for (int t = m - 1; t >= 0; t--)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != WHITE_KING)
							break;
						else if (Grid[p][t] == WHITE_KING)
							return true;
					}
					//Look Up
					for (int t = p + 1; t < 8; t++)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != WHITE_KING)
							break;
						else if (Grid[t][m] == WHITE_KING)
							return true;
					}
					//Look Down
					for (int t = p - 1; t >= 0; t--)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != WHITE_KING)
							break;
						else if (Grid[t][m] == WHITE_KING)
							return true;
					}
				}
				if (Grid[p][m] == BLACK_HORSE)
				{
					if (p + 2 < 8 && m + 1 < 8 && Grid[p + 2][m + 1] == WHITE_KING)
						return true;
					if (p + 2 < 8 && m - 1 >= 0 && Grid[p + 2][m - 1] == WHITE_KING)
						return true;
					if (p - 2 >= 0 && m + 1 < 8 && Grid[p - 2][m + 1] == WHITE_KING)
						return true;
					if (p - 2 >= 0 && m - 1 >= 0 && Grid[p - 2][m - 1] == WHITE_KING)
						return true;
					if (p + 1 < 8 && m + 2 < 8 && Grid[p + 1][m + 2] == WHITE_KING)
						return true;
					if (p + 1 < 8 && m - 2 >= 0 && Grid[p + 1][m - 2] == WHITE_KING)
						return true;
					if (p - 1 >= 0 && m + 2 < 8 && Grid[p - 1][m + 2] == WHITE_KING)
						return true;
					if (p - 1 >= 0 && m - 2 >= 0 && Grid[p - 1][m - 2] == WHITE_KING)
						return true;
				}
				else if (Grid[p][m] == BLACK_PAWN)
				{
					if (m + 1 < 8 && Grid[p + 1][m + 1] == WHITE_KING)
						return true;
					if (m + 1 < 8 && Grid[p + 1][m - 1] == WHITE_KING)
						return true;
				}
			}
		}
	}
	else if (player == WHITE_PLAYER)
	{
		for (int p = 0; p < 8; p++)
		{
			for (int m = 0; m < 8; m++)
			{
				if (Grid[p][m] == WHITE_BISHOP || Grid[p][m] == WHITE_QUEEN)
				{
					//Look on all directions
					//Search TOP Left x-- y--
					s = m - 1;
					t = p - 1;
					if (t >= 0 && s >= 0)
					{
						while (t >= 0)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
								break;
							else if (Grid[t][s] == BLACK_KING)
								return true;
							s--;
							t--;
						}
					}
					//Search BOTTOM Right x++ y++
					s = m + 1;
					t = p + 1;
					if (t < 8 && s < 8)
					{
						while (t < 8)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
								break;
							else if (Grid[t][s] == BLACK_KING)
								return true;
							s++;
							t++;
						}
					}
					//Search BOTTOM Left x++ y--
					s = m - 1;
					t = p + 1;
					if (s >= 0 && t < 8)
					{
						while (t < 8)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
								break;
							else if (Grid[t][s] == BLACK_KING)
								return true;
							s--;
							t++;
						}
					}
					//Search top Right x-- y++
					s = m + 1;
					t = p - 1;
					if (s < 8 && t >= 0)
					{
						while (t >= 0)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
								break;
							else if (Grid[t][s] == BLACK_KING)
								return true;
							s++;
							t--;
						}
					}
				}
				if (Grid[p][m] == WHITE_ROOK || Grid[p][m] == WHITE_QUEEN)
				{
					//Look Right
					for (int t = m + 1; t < 8; t++)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != BLACK_KING)
							break;
						else if (Grid[p][t] == BLACK_KING)
							return true;
					}
					//Look Left
					for (int t = m - 1; t >= 0; t--)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != BLACK_KING)
							break;
						else if (Grid[p][t] == BLACK_KING)
							return true;
					}
					//Look Up
					for (int t = p + 1; t < 8; t++)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != BLACK_KING)
							break;
						else if (Grid[t][m] == BLACK_KING)
							return true;
					}
					//Look Down
					for (int t = p - 1; t >= 0; t--)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != BLACK_KING)
							break;
						else if (Grid[t][m] == BLACK_KING)
							return true;
					}
				}
				if (Grid[p][m] == WHITE_HORSE)
				{
					if (p + 2 < 8 && m + 1 < 8 && Grid[p + 2][m + 1] == BLACK_KING)
						return true;
					if (p + 2 < 8 && m - 1 >= 0 && Grid[p + 2][m - 1] == BLACK_KING)
						return true;
					if (p - 2 >= 0 && m + 1 < 8 && Grid[p - 2][m + 1] == BLACK_KING)
						return true;
					if (p - 2 >= 0 && m - 1 >= 0 && Grid[p - 2][m - 1] == BLACK_KING)
						return true;
					if (p + 1 < 8 && m + 2 < 8 && Grid[p + 1][m + 2] == BLACK_KING)
						return true;
					if (p + 1 < 8 && m - 2 >= 0 && Grid[p + 1][m - 2] == BLACK_KING)
						return true;
					if (p - 1 >= 0 && m + 2 < 8 && Grid[p - 1][m + 2] == BLACK_KING)
						return true;
					if (p - 1 >= 0 && m - 2 >= 0 && Grid[p - 1][m - 2] == BLACK_KING)
						return true;
				}
				else if (Grid[p][m] == WHITE_PAWN)
				{
					if (m + 1 < 8 && Grid[p - 1][m + 1] == BLACK_KING)
						return true;
					if (m + 1 < 8 && Grid[p - 1][m - 1] == BLACK_KING)
						return true;
				}
			}
		}
	}
	return false;
}
bool Check_ADVANCED(char Grid[][8], char x, char y, char j, char z, char player)
{
	char piece = Grid[x][y];
	char dest = Grid[j][z];
	bool Castle_Left = false;
	bool Castle_Right = false;
	bool King_Move = false;
	bool check = false;
	char aux, aux_piece;
	int m, s, t;
	//Basic movement and Captures
	switch (piece)
	{
	case WHITE_PAWN:
	case BLACK_PAWN:
		//Check backwards movement
		if (piece == WHITE_PAWN && j > x)
			return false;
		else if (piece == BLACK_PAWN && x > j)
			return false;
		//Check posible double move if first time moving pawn
		if (abs(x - j) == 2 && abs(y - z) == 0)
		{
			if (player == WHITE_PLAYER && x == 6)
				goto CHECK_CHECK;
			else if (player == BLACK_PLAYER && x == 1)
				goto CHECK_CHECK;
		}
		//Check en passant
		//Check that the move is not further than one square and if it goes diagonally there is not an empty square and can t kill enemies just walking forward
		if (abs(y - z) > 1 || abs(x - j) > 1 || ((y != z) && (dest == EMPTY_SQUARE)) || ((y == z) && (dest != EMPTY_SQUARE)))
			return false;
		//check promote
		if (j == 0 || j == 7)
		{
			std::cout << "What do you want to promote to?" << std::endl;
			std::cout << "Queen (Q/q) Bishop (B/b) Horse (H/h) Rook (R/r)" << std::endl;
			std::cin >> piece;
			bool white_promote = (player == WHITE_PLAYER && (piece == WHITE_HORSE || piece == WHITE_BISHOP || piece == WHITE_QUEEN || piece == WHITE_ROOK));
			bool black_promote = (player == BLACK_PLAYER && (piece == BLACK_HORSE || piece == BLACK_BISHOP || piece == BLACK_QUEEN || piece == BLACK_ROOK));
			bool result = !(white_promote ^ black_promote);
			while (!std::cin.good() || result)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("CLS");
				Display_Grid(Grid);
				std::cout << "What do you want to promote to?" << std::endl;
				std::cout << "Queen (Q/q) Bishop (B/b) Horse (H/h) Rook (R/r)" << std::endl;
				std::cout << "Insert Correct data" << std::endl;
				std::cin >> piece;
				white_promote = (player == WHITE_PLAYER && (piece == WHITE_HORSE || piece == WHITE_BISHOP || piece == WHITE_QUEEN || piece == WHITE_ROOK));
				black_promote = (player == BLACK_PLAYER && (piece == BLACK_HORSE || piece == BLACK_BISHOP || piece == BLACK_QUEEN || piece == BLACK_ROOK));
				result = !(white_promote ^ black_promote);
			}
			Grid[x][y] = piece;
		}
		break;
	case WHITE_HORSE:
	case BLACK_HORSE:
		//Basic movement
		if (abs(x - j) == 2 && abs(y - z) == 1)
			goto CHECK_CHECK;
		if (abs(y - z) == 2 && abs(x - j) == 1)
			goto CHECK_CHECK;
		return false;
	case WHITE_QUEEN:
	case BLACK_QUEEN:
	case WHITE_ROOK:
	case BLACK_ROOK:
		//Check Vertical movement
		if (x == j && y != z)
		{
			y < z ? aux = y : aux = z;
			for (int t = 1; t < abs(y - z); t++)
				if (Grid[x][t + aux] != EMPTY_SQUARE)
					return false;
			if (piece == BLACK_ROOK || piece == WHITE_ROOK)
			{
				if (y == 7) Castle_Right = true;
				if (y == 0) Castle_Left = true;
			}
			goto CHECK_CHECK;
		}
		//Check Horizontal movement
		if (z == y && x != j)
		{
			x < j ? aux = x : aux = j;
			for (int t = 1; t < abs(x - j); t++)
				if (Grid[t + aux][y] != EMPTY_SQUARE)
					return false;
			if (piece == BLACK_ROOK || piece == WHITE_ROOK)
			{
				if (y == 7) Castle_Right = true;
				if (y == 0) Castle_Left = true;
			}
			goto CHECK_CHECK;
		}
		if (piece == BLACK_ROOK || piece == WHITE_ROOK)
			return false;
	case WHITE_BISHOP:
	case BLACK_BISHOP:
		//Check diagonal movement
		if (abs(x - j) != abs(y - z) || abs(x - j) == 0)
			return false;
		//Search TOP Left x-- y--
		if (x > j && y > z)
		{
			m = y - 1;
			for (int t = x - 1; t > j; t--)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m--;
			}
		}
		//Search BOTTOM Right x++ y++
		else if (x < j && y < z)
		{
			m = y + 1;
			for (int t = x + 1; t < j; t++)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m++;
			}
		}
		//Search BOTTOM Left x++ y--
		else if (x < j && y>z)
		{
			m = y - 1;
			for (int t = x + 1; t < j; t++)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m--;
			}
		}
		//Search top Right x-- y++
		else
		{
			m = y + 1;
			for (int t = x - 1; t > j; t--)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m++;
			}
		}
		goto CHECK_CHECK;
		break;
	case WHITE_KING:
	case BLACK_KING:
		//Basic movement
		if (abs(j - x) > 1 || abs(y - z) > 2 || (abs(y - z) > 1 && y != 4))
			return false;
		//Castle
		if (abs(y - z) == 2 && abs(j - x) == 0 && (x == 0 || x == 7) && y == 4)
		{
			if (player == WHITE_PLAYER && WHITE_CASTLE_KING == true && (WHITE_CASTLE_LEFT == true || WHITE_CASTLE_RIGHT == true))
			{
				if (z == 6)//Castle right
				{
					if (Grid[x][5] != EMPTY_SQUARE || Grid[x][6] != EMPTY_SQUARE || WHITE_CASTLE_RIGHT == false)
						return false;
					Grid[x][5] = WHITE_ROOK;
					Grid[x][6] = WHITE_KING;
					Grid[x][7] = EMPTY_SQUARE;
					King_Move = true;
					goto CHECK_CHECK;
				}
				if (z == 2)
				{
					if (Grid[x][3] != EMPTY_SQUARE || Grid[x][2] != EMPTY_SQUARE || Grid[x][1] != EMPTY_SQUARE || WHITE_CASTLE_LEFT == false)
						return false;
					Grid[x][3] = WHITE_ROOK;
					Grid[x][2] = WHITE_KING;
					Grid[x][0] = EMPTY_SQUARE;
					King_Move = true;
					goto CHECK_CHECK;
				}
			}
			if (player == BLACK_PLAYER && BLACK_CASTLE_KING == true && (BLACK_CASTLE_LEFT == true || BLACK_CASTLE_RIGHT == true))
			{
				if (z == 6)//Castle right
				{
					if (Grid[x][5] != EMPTY_SQUARE || Grid[x][6] != EMPTY_SQUARE || BLACK_CASTLE_RIGHT == false)
						return false;
					Grid[x][5] = BLACK_ROOK;
					Grid[x][6] = BLACK_KING;
					Grid[x][7] = EMPTY_SQUARE;
					King_Move = true;
					goto CHECK_CHECK;
				}
				if (z == 2)
				{
					if (Grid[x][3] != EMPTY_SQUARE || Grid[x][2] != EMPTY_SQUARE || Grid[x][1] != EMPTY_SQUARE || BLACK_CASTLE_LEFT == false)
						return false;
					Grid[x][3] = BLACK_ROOK;
					Grid[x][2] = BLACK_KING;
					Grid[x][0] = EMPTY_SQUARE;
					King_Move = true;
					goto CHECK_CHECK;
				}
			}
			return false;
		}
		King_Move = true;
		break;
	}
CHECK_CHECK:
	//We simulate the move on the actual Grid but if the move is not posible we goto restore and we change the grid again.
	Grid[x][y] = EMPTY_SQUARE;
	aux_piece = Grid[j][z];
	Grid[j][z] = piece;
	if (player == WHITE_PLAYER)
	{
		check=Player_In_Check(Grid, player % 2 + 1);
		if (check == true) goto restore;

		//update castle variables

		if (WHITE_CASTLE_KING == true) WHITE_CASTLE_KING = !King_Move;
		if (WHITE_CASTLE_LEFT == true) WHITE_CASTLE_LEFT = !Castle_Left;
		if (WHITE_CASTLE_RIGHT == true) WHITE_CASTLE_RIGHT = !Castle_Right;
	}
	if (player == BLACK_PLAYER)
	{
		check = Player_In_Check(Grid, player % 2 + 1);
		if (check == true) goto restore;

		//update castle variables
		if (BLACK_CASTLE_KING == true) BLACK_CASTLE_KING = !King_Move;
		if (BLACK_CASTLE_LEFT == true) BLACK_CASTLE_LEFT = !Castle_Left;
		if (BLACK_CASTLE_RIGHT == true) BLACK_CASTLE_RIGHT = !Castle_Right;

	}
	//returns false if the move is not possible
	return true;
restore:
	Grid[x][y] = Grid[j][z];
	Grid[j][z] = aux_piece;
	return false;
}
bool Check_END(char Grid[][8], char x, char y, char j, char z, char player)
{
	char pos = Grid[j][z];

	//Check if destination is empty
	if (pos == EMPTY_SQUARE)
	{
		return Check_ADVANCED(Grid, x, y, j, z, player);
	}

	//Check if destination is one of your pieces
	if (player == WHITE_PLAYER)
	{
		if (pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_ROOK || pos == WHITE_KING || pos == WHITE_QUEEN || pos == WHITE_PAWN)
			return false;
	}
	else
	{
		if (pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_ROOK || pos == BLACK_KING || pos == BLACK_QUEEN || pos == BLACK_PAWN)
			return false;
	}
	return Check_ADVANCED(Grid, x, y, j, z, player);
}
bool Check_Win(char Grid[][8], char player)
{
	if (Player_In_Check(Grid, player) == true)
	{
		if (player == BLACK_PLAYER) std::cout << "White player (UPERCASE/ALL CAPS) is in CHECK! " << std::endl;
		else std::cout << "Black player (LOWER CASE) is in CHECK! " << std::endl;

		//Anlaisis Checkmate
		//look all king moves and all the other pieces moves to see if they can cover the check
		int x, y, s, t;
		char pos, prev;
		if (player == WHITE_PLAYER)
		{
			//First locate the king
			for (x = 0; x < 8; x++)
				for (y = 0; y < 8; y++)
					if (Grid[x][y] == BLACK_KING)
						goto found;
		found:
			//Check King moves
			if (x + 1 < 8)
			{
				pos = Grid[x + 1][y];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x + 1][y] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x + 1][y] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x + 1 < 8 && y - 1 >= 0)
			{
				pos = Grid[x + 1][y - 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x + 1][y - 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y - 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x + 1][y - 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x + 1 < 8 && y + 1 < 8)
			{
				pos = Grid[x + 1][y + 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x + 1][y + 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y + 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x + 1][y + 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (y + 1 < 8)
			{
				pos = Grid[x][y + 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x][y + 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x][y + 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x][y + 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (y - 1 >= 0)
			{
				pos = Grid[x][y - 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x][y - 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x][y - 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x][y - 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x - 1 >= 0)
			{
				pos = Grid[x - 1][y];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x - 1][y] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x - 1][y] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x - 1 >= 0 && y - 1 >= 0)
			{
				pos = Grid[x - 1][y - 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x - 1][y - 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y - 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x - 1][y - 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x - 1 >= 0 && y + 1 < 8)
			{
				pos = Grid[x - 1][y + 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x - 1][y + 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y + 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x - 1][y + 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			//Check the movement of the other pieces
			for (int j = 0; j < 8; j++)
			{
				for (int q = 0; q < 8; q++)
				{
					if (Grid[j][q] != EMPTY_SQUARE)
					{
						if (Grid[j][q] == BLACK_PAWN)
						{
							//Forward Pawn Move (haven t checked if double starting move works)
							if (j + 1 < 8 && Grid[j + 1][q] == EMPTY_SQUARE)
							{
								Grid[j + 1][q] = BLACK_PAWN;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 1][q] = EMPTY_SQUARE;
									Grid[j][q] = BLACK_PAWN;
									return false;
								}
								Grid[j + 1][q] = EMPTY_SQUARE;
								Grid[j][q] = BLACK_PAWN;
							}
							//Capture left
							if (j + 1 < 8 && q - 1 >= 0)
							{
								pos = Grid[j + 1][q - 1];
								if (pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN)
								{
									Grid[j + 1][q - 1] = BLACK_PAWN;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q - 1] = pos;
										Grid[j][q] = BLACK_PAWN;
										return false;
									}
									Grid[j + 1][q - 1] = pos;
									Grid[j][q] = BLACK_PAWN;
								}
							}
							//Capture right
							if (j + 1 < 8 && q + 1 < 8)
							{
								pos = Grid[j + 1][q + 1];
								if (pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN)
								{
									Grid[j + 1][q + 1] = BLACK_PAWN;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q + 1] = pos;
										Grid[j][q] = BLACK_PAWN;
										return false;
									}
									Grid[j + 1][q + 1] = pos;
									Grid[j][q] = BLACK_PAWN;
								}
							}

						}
						else if (Grid[j][q] == BLACK_HORSE)
						{
							if (j + 2 < 8 && q + 1 < 8)
							{
								pos = Grid[j + 2][q + 1];
								Grid[j + 2][q + 1] = BLACK_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 2][q + 1] = pos;
									Grid[j][q] = BLACK_HORSE;
									return false;
								}
								Grid[j + 2][q + 1] = pos;
								Grid[j][q] = BLACK_HORSE;
							}
							if (j + 2 < 8 && q - 1 >= 0)
							{
								pos = Grid[j + 2][q - 1];
								Grid[j + 2][q - 1] = BLACK_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 2][q - 1] = pos;
									Grid[j][q] = BLACK_PAWN;
									return false;
								}
								Grid[j + 2][q - 1] = pos;
								Grid[j][q] = BLACK_PAWN;
							}
							if (j - 2 >= 0 && q + 1 < 8)
							{
								pos = Grid[j - 2][q + 1];
								Grid[j - 2][q + 1] = BLACK_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j - 2][q + 1] = pos;
									Grid[j][q] = BLACK_HORSE;
									return false;
								}
								Grid[j - 2][q + 1] = pos;
								Grid[j][q] = BLACK_HORSE;
							}
							if (j - 2 >= 0 && q - 1 >= 0)
							{
								pos = Grid[j - 2][q - 1];
								Grid[j - 2][q - 1] = BLACK_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j - 2][q - 1] = pos;
									Grid[j][q] = BLACK_HORSE;
									return false;
								}
								Grid[j - 2][q - 1] = pos;
								Grid[j][q] = BLACK_HORSE;
							}
							if (j + 1 < 8 && q + 2 < 8)
							{
								pos = Grid[j + 1][q + 2];
								Grid[j + 1][q + 2] = BLACK_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 1][q + 2] = pos;
									Grid[j][q] = BLACK_HORSE;
									return false;
								}
								Grid[j + 1][q + 2] = pos;
								Grid[j][q] = BLACK_HORSE;
							}
							if (j + 1 < 8 && q - 2 >= 0)
							{
								pos = Grid[j + 1][q - 2];
								Grid[j + 1][q - 2] = BLACK_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 1][q - 2] = pos;
									Grid[j][q] = BLACK_HORSE;
									return false;
								}
								Grid[j + 1][q - 2] = pos;
								Grid[j][q] = BLACK_HORSE;
							}
							if (j - 1 >= 0 && q + 2 < 8)
							{
								pos = Grid[j - 1][q + 2];
								Grid[j - 1][q + 2] = BLACK_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j - 1][q + 2] = pos;
									Grid[j][q] = BLACK_HORSE;
									return false;
								}
								Grid[j - 1][q + 2] = pos;
								Grid[j][q] = BLACK_HORSE;
							}
							if (j - 1 >= 0 && q - 2 >= 0)
							{
								pos = Grid[j - 1][q - 2];
								Grid[j - 1][q - 2] = BLACK_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j - 1][q - 2] = pos;
									Grid[j][q] = BLACK_HORSE;
									return false;
								}
								Grid[j - 1][q - 2] = pos;
								Grid[j][q] = BLACK_HORSE;
							}
						}
						else if (Grid[j][q] == BLACK_BISHOP || Grid[j][q] == BLACK_QUEEN)
						{
							//Look on all directions
							//Search TOP Left x-- y--
							s = q - 1;
							t = j - 1;
							if (t >= 0 && s >= 0)
							{
								while (t >= 0 && s >= 0)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) && x != t && y != s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									s--;
									t--;
								}
							}
							//Search BOTTOM Right x++ y++
							s = q + 1;
							t = j + 1;
							if (t < 8 && s < 8)
							{
								while (t < 8 && s < 8)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s++;
									t++;
								}
							}
							//Search BOTTOM Left x++ y--
							s = q - 1;
							t = j + 1;
							if (s >= 0 && t < 8)
							{
								while (s >= 0 && t < 8)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s--;
									t++;
								}
							}
							//Search top Right x-- y++
							s = q + 1;
							t = j - 1;
							if (s < 8 && t >= 0)
							{
								while (s < 8 && t >= 0)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s++;
									t--;
								}
							}
						}
						if (Grid[j][q] == BLACK_ROOK || Grid[j][q] == BLACK_QUEEN)
						{
							//Look Right
							for (int t = q + 1; t < 8; t++)
							{
								pos = Grid[j][t];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == j || y == t))
									break;
								else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
								{
									Grid[j][t] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j][t] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[j][t] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Left
							for (int t = q - 1; t >= 0; t--)
							{
								pos = Grid[j][t];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == j || y == t))
									break;
								else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
								{
									Grid[j][t] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j][t] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[j][t] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Up
							for (int t = j + 1; t < 8; t++)
							{
								pos = Grid[t][q];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == t || y == q))
									break;
								else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
								{
									Grid[t][q] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[t][q] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[t][q] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Down
							for (int t = j - 1; t >= 0; t--)
							{
								pos = Grid[t][q];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == t || y == q))
									break;
								else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
								{
									Grid[t][q] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[t][q] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[t][q] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
						}
					}
				}
			}
		}
		else if (player == BLACK_PLAYER)
		{
			for (x = 7; x >= 0; x--)
				for (y = 0; y < 8; y++)
					if (Grid[x][y] == WHITE_KING)
						goto found2;
		found2:
			//Check King moves
			if (x + 1 < 8)
			{
				pos = Grid[x + 1][y];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x + 1][y] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x + 1][y] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x + 1 < 8 && y - 1 >= 0)
			{
				pos = Grid[x + 1][y - 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x + 1][y - 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y - 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x + 1][y - 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x + 1 < 8 && y + 1 < 8)
			{
				pos = Grid[x + 1][y + 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x + 1][y + 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y + 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x + 1][y + 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (y + 1 < 8)
			{
				pos = Grid[x][y + 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x][y + 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x][y + 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x][y + 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (y - 1 >= 0)
			{
				pos = Grid[x][y - 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x][y - 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x][y - 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x][y - 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x - 1 >= 0)
			{
				pos = Grid[x - 1][y];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x - 1][y] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x - 1][y] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x - 1 >= 0 && y - 1 >= 0)
			{
				pos = Grid[x - 1][y - 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x - 1][y - 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y - 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x - 1][y - 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x - 1 >= 0 && y + 1 < 8)
			{
				pos = Grid[x - 1][y + 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x - 1][y + 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y + 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x - 1][y + 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			//Check the movement of the other pieces
			for (int j = 0; j < 8; j++)
			{
				for (int q = 0; q < 8; q++)
				{
					if (Grid[j][q] != EMPTY_SQUARE)
					{
						if (Grid[j][q] == WHITE_PAWN)
						{
							//Forward Pawn Move (haven t checked if double starting move works)
							if (j + 1 < 8 && Grid[j + 1][q] == EMPTY_SQUARE)
							{
								Grid[j + 1][q] = WHITE_PAWN;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 1][q] = EMPTY_SQUARE;
									Grid[j][q] = WHITE_PAWN;
									return false;
								}
								Grid[j + 1][q] = EMPTY_SQUARE;
								Grid[j][q] = WHITE_PAWN;
							}
							//Capture left
							if (j + 1 < 8 && q - 1 >= 0)
							{
								pos = Grid[j + 1][q - 1];
								if (pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN)
								{
									Grid[j + 1][q - 1] = WHITE_PAWN;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q - 1] = pos;
										Grid[j][q] = WHITE_PAWN;
										return false;
									}
									Grid[j + 1][q - 1] = pos;
									Grid[j][q] = WHITE_PAWN;
								}
							}
							//Capture right
							if (j + 1 < 8 && q + 1 < 8)
							{
								pos = Grid[j + 1][q + 1];
								if (pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN)
								{
									Grid[j + 1][q + 1] = WHITE_PAWN;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q + 1] = pos;
										Grid[j][q] = WHITE_PAWN;
										return false;
									}
									Grid[j + 1][q + 1] = pos;
									Grid[j][q] = WHITE_PAWN;
								}
							}
						}
						else if (Grid[j][q] == WHITE_HORSE)
						{
							if (j + 2 < 8 && q + 1 < 8)
							{
								pos = Grid[j + 2][q + 1];
								Grid[j + 2][q + 1] = WHITE_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 2][q + 1] = pos;
									Grid[j][q] = WHITE_HORSE;
									return false;
								}
								Grid[j + 2][q + 1] = pos;
								Grid[j][q] = WHITE_HORSE;
							}
							if (j + 2 < 8 && q - 1 >= 0)
							{
								pos = Grid[j + 2][q - 1];
								Grid[j + 2][q - 1] = WHITE_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 2][q - 1] = pos;
									Grid[j][q] = WHITE_PAWN;
									return false;
								}
								Grid[j + 2][q - 1] = pos;
								Grid[j][q] = WHITE_PAWN;
							}
							if (j - 2 >= 0 && q + 1 < 8)
							{
								pos = Grid[j - 2][q + 1];
								Grid[j - 2][q + 1] = WHITE_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j - 2][q + 1] = pos;
									Grid[j][q] = WHITE_HORSE;
									return false;
								}
								Grid[j - 2][q + 1] = pos;
								Grid[j][q] = WHITE_HORSE;
							}
							if (j - 2 >= 0 && q - 1 >= 0)
							{
								pos = Grid[j - 2][q - 1];
								Grid[j - 2][q - 1] = WHITE_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j - 2][q - 1] = pos;
									Grid[j][q] = WHITE_HORSE;
									return false;
								}
								Grid[j - 2][q - 1] = pos;
								Grid[j][q] = WHITE_HORSE;
							}
							if (j + 1 < 8 && q + 2 < 8)
							{
								pos = Grid[j + 1][q + 2];
								Grid[j + 1][q + 2] = WHITE_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 1][q + 2] = pos;
									Grid[j][q] = WHITE_HORSE;
									return false;
								}
								Grid[j + 1][q + 2] = pos;
								Grid[j][q] = WHITE_HORSE;
							}
							if (j + 1 < 8 && q - 2 >= 0)
							{
								pos = Grid[j + 1][q - 2];
								Grid[j + 1][q - 2] = WHITE_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 1][q - 2] = pos;
									Grid[j][q] = WHITE_HORSE;
									return false;
								}
								Grid[j + 1][q - 2] = pos;
								Grid[j][q] = WHITE_HORSE;
							}
							if (j - 1 >= 0 && q + 2 < 8)
							{
								pos = Grid[j - 1][q + 2];
								Grid[j - 1][q + 2] = WHITE_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j - 1][q + 2] = pos;
									Grid[j][q] = WHITE_HORSE;
									return false;
								}
								Grid[j - 1][q + 2] = pos;
								Grid[j][q] = WHITE_HORSE;
							}
							if (j - 1 >= 0 && q - 2 >= 0)
							{
								pos = Grid[j - 1][q - 2];
								Grid[j - 1][q - 2] = WHITE_HORSE;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j - 1][q - 2] = pos;
									Grid[j][q] = WHITE_HORSE;
									return false;
								}
								Grid[j - 1][q - 2] = pos;
								Grid[j][q] = WHITE_HORSE;
							}
						}
						else if (Grid[j][q] == WHITE_BISHOP || Grid[j][q] == WHITE_QUEEN)
						{
							//Look on all directions
							//Search TOP Left x-- y--
							s = q - 1;
							t = j - 1;
							if (t >= 0 && s >= 0)
							{
								while (t >= 0 && s >= 0)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) && x != t && y != s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s--;
									t--;
								}
							}
							//Search BOTTOM Right x++ y++
							s = q + 1;
							t = j + 1;
							if (t < 8 && s < 8)
							{
								while (t < 8 && s < 8)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s++;
									t++;
								}
							}
							//Search BOTTOM Left x++ y--
							s = q - 1;
							t = j + 1;
							if (s >= 0 && t < 8)
							{
								while (s >= 0 && t < 8)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s--;
									t++;
								}
							}
							//Search top Right x-- y++
							s = q + 1;
							t = j - 1;
							if (s < 8 && t >= 0)
							{
								while (s < 8 && t >= 0)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s++;
									t--;
								}
							}
						}
						if (Grid[j][q] == WHITE_ROOK || Grid[j][q] == WHITE_QUEEN)
						{
							//Look Right
							for (int t = q + 1; t < 8; t++)
							{
								pos = Grid[j][t];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == j || y == t))
									break;
								else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
								{
									Grid[j][t] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j][t] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[j][t] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Left
							for (int t = q - 1; t >= 0; t--)
							{
								pos = Grid[j][t];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == j || y == t))
									break;
								else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
								{
									Grid[j][t] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j][t] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[j][t] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Up
							for (int t = j + 1; t < 8; t++)
							{
								pos = Grid[t][q];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == t || y == q))
									break;
								else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
								{
									Grid[t][q] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[t][q] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[t][q] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Down
							for (int t = j - 1; t >= 0; t--)
							{
								pos = Grid[t][q];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == t || y == q))
									break;
								else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
								{
									Grid[t][q] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[t][q] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[t][q] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
						}
					}
				}
			}
		}
		return true;
	}
	else
	{
		//check tie
	}
	return false;
}
void Player_Choice(char Grid[][8], char PlayerX)
{
	char x, y;
	char j, z;
start:
	if (PlayerX == WHITE_PLAYER)
		std::cout << "----White to move(UPERCASE)----" << std::endl;
	else std::cout << "----Black to move(lowercase)----" << std::endl;
	std::cout << "Choose the piece you want to move:  " << std::endl;
	std::cout << "Column = ";
	std::cin >> y;
	std::cout << "Row = ";
	std::cin >> x;
	while (!std::cin.good() || x < 49 || x >(7 + 49) || y < 97 || y >= (8 + 97) || !Check_Start(Grid, 56 - x, y - 97, PlayerX))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("CLS");
		Display_Grid(Grid);
		Check_Win(Grid, PlayerX % 2 + 1);
		if (PlayerX == WHITE_PLAYER)
			std::cout << "----White to move(UPERCASE)----" << std::endl;
		else std::cout << "----Black to move(lowercase)----" << std::endl;
		std::cout << "Choose the piece you want to move:  " << std::endl;
		std::cout << "Insert a valid coordenate" << std::endl;
		std::cout << "Column = ";
		std::cin >> y;
		std::cout << "Row = ";
		std::cin >> x;
	}
	std::cout << "Choose where to go or write q if you messed up:  " << std::endl;
	std::cout << "Column = ";
	std::cin >> z;
	if (z == 'q')
	{
		system("CLS");
		Display_Grid(Grid);
		Check_Win(Grid, PlayerX % 2 + 1);
		goto start;
	}
	std::cout << "Row = ";
	std::cin >> j;
	if (j == 'q')
	{
		system("CLS");
		Display_Grid(Grid);
		Check_Win(Grid, PlayerX % 2 + 1);
		goto start;
	}
	while (!std::cin.good() || j < 49 || j >(49 + 7) || z < 97 || z >= (8 + 97) || !Check_END(Grid, 56 - x, y - 97, 56 - j, z - 97, PlayerX))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("CLS");
		Display_Grid(Grid);
		Check_Win(Grid, PlayerX % 2 + 1);
		if (PlayerX == WHITE_PLAYER)
			std::cout << "----White to move(UPERCASE)----" << std::endl;
		else std::cout << "----Black to move(lowercase)----" << std::endl;
		std::cout << "Insert a valid move" << std::endl;
		std::cout << "Choose where to go or write q if you messed up:  " << std::endl;
		std::cout << "Column = ";
		std::cin >> z;
		if (z == 'q')
		{
			system("CLS");
			Display_Grid(Grid);
			Check_Win(Grid, PlayerX % 2 + 1);
			goto start;
		}
		std::cout << "Row = ";
		std::cin >> j;
		if (j == 'q')
		{
			system("CLS");
			Display_Grid(Grid);
			Check_Win(Grid, PlayerX % 2 + 1);
			goto start;
		}
	}
}

int main()
{
	char Grid[8][8];
	char player = WHITE_PLAYER;
	bool win = false;
	int end;
	start:
	end=StartUP_menu();
	if (end == 4) goto end;
	Create_Grid(Grid);
	Display_Grid(Grid);
	while (!win)
	{
		Player_Choice(Grid, player);
		Display_Grid(Grid);
		win = Check_Win(Grid, player);
		player = player % 2 + 1;
	}
	Display_Grid(Grid);
	if (player == WHITE_PLAYER && win == true)
		std::cout << "Black Player WON!!!! CHECKMATE!!!";
	else
		std::cout << "White Player WON!!!! CHECKMATE!!!";
	//Tie remaining
	system("pause");
	goto start;
	end:
	return 0;
}
