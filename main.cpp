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
		std::cout << (char)(i + 97) << " " << VERTICAL_LINE << " ";
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

	return true;
}
bool Check_ADVANCED(char Grid[][8], char x, char y, char j, char z, char player)
{
	char piece = Grid[x][y];
	char dest = Grid[j][z];
	bool Castle_Left = false;
	bool Castle_Right = false;
	bool King_Move = false;
	char aux,aux_piece;
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
		if (abs(x - j) == 2 && (y - z) == 0)
		{
			if (player == WHITE_PLAYER && x == 6)
				goto CHECK_CHECK;
			else if (player == BLACK_PLAYER && x == 1)
				goto CHECK_CHECK;
		}
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
		}//ga ea bh dh ea da dh eh da ca eh fh ca bb fh gg bb aa
		break;
	case WHITE_HORSE:
	case BLACK_HORSE:
		if (abs(x - j) == 2 && abs(y - z) == 1)
			goto CHECK_CHECK;
		if (abs(y - z) == 2 && abs(x - j) == 1)
			goto CHECK_CHECK;
		return false;
	case WHITE_QUEEN:
	case BLACK_QUEEN:
	case WHITE_ROOK:
	case BLACK_ROOK:
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
		if (abs(x - j) != abs(y - z) || abs(x - j) == 0)
			return false;
		if (x > j && y > z) //Search TOP Left x-- y--
		{
			m = y - 1;
			for (int t = x - 1; t > j; t--)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m--;
			}
		}
		else if (x < j && y < z)//Search BOTTOM Right x++ y++
		{
			m = y + 1;
			for (int t = x + 1; t < j; t++)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m++;
			}
		}
		else if (x < j && y>z)//Search BOTTOM Left x++ y--
		{
			m = y - 1;
			for (int t = x + 1; t < j; t++)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m--;
			}
		}
		else//Search top Right x-- y++
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
		if (abs(j - x) > 1 || abs(y - z) > 2 || (abs(y - z) > 1 && y!=4))
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
						while (t >= 0 && s >= 0)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
								break;
							else if (Grid[t][s] == WHITE_KING)
								goto restore;
							s--;
							t--;
						}
					}
					//Search BOTTOM Right x++ y++
					s = m + 1;
					t = p + 1;
					if (t < 8 && s < 8)
					{
						while (t < 8 && s < 8)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
								break;
							else if (Grid[t][s] == WHITE_KING)
								goto restore;
							s++;
							t++;
						}
					}
					//Search BOTTOM Left x++ y--
					s = m - 1;
					t = p + 1;
					if (s >= 0 && t < 8)
					{
						while (s >= 0 && t < 8)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
								break;
							else if (Grid[t][s] == WHITE_KING)
								goto restore;
							s--;
							t++;
						}
					}
					//Search top Right x-- y++
					s = m + 1;
					t = p - 1;
					if (s < 8 && t >= 0)
					{
						while (s < 8 && t >= 0)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
								break;
							else if (Grid[t][s] == WHITE_KING)
								goto restore;
							s++;
							t--;
						}
					}
				}
				if (Grid[p][m] == BLACK_ROOK || Grid[p][m] == BLACK_QUEEN)
				{
					//Look Right
					for (int t = m+1; t < 8; t++)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != WHITE_KING)
							break;
						else if (Grid[p][t] == WHITE_KING)
							goto restore;
					}
					//Look Left
					for (int t = m-1; t >= 0; t--)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != WHITE_KING)
							break;
						else if (Grid[p][t] == WHITE_KING)
							goto restore;
					}
					//Look Up
					for (int t = p+1; t < 8; t++)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != WHITE_KING)
							break;
						else if (Grid[t][m] == WHITE_KING)
							goto restore;
					}
					//Look Down
					for (int t = p-1; t >= 0; t--)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != WHITE_KING)
							break;
						else if (Grid[t][m] == WHITE_KING)
							goto restore;
					}
				}
				else if (piece == WHITE_KING)
				{
					if (Grid[p][m] == BLACK_HORSE)
					{
						if (p + 2 < 8 && m + 1 < 8 && Grid[p + 2][m + 1] == WHITE_KING)
							goto restore;
						if (p + 2 < 8 && m - 1 >= 0 && Grid[p + 2][m - 1] == WHITE_KING)
							goto restore;
						if (p - 2 >= 0 && m + 1 < 8 && Grid[p - 2][m + 1] == WHITE_KING)
							goto restore;
						if (p - 2 >= 0 && m - 1 >= 0 && Grid[p - 2][m - 1] == WHITE_KING)
							goto restore;
						if (p + 1 < 8 && m + 2 < 8 && Grid[p + 1][m + 2] == WHITE_KING)
							goto restore;
						if (p + 1 < 8 && m - 2 >= 0 && Grid[p + 1][m - 2] == WHITE_KING)
							goto restore;
						if (p - 1 >= 0 && m + 2 < 8 && Grid[p - 1][m + 2] == WHITE_KING)
							goto restore;
						if (p - 1 >= 0 && m - 2 >= 0 && Grid[p - 1][m - 2] == WHITE_KING)
							goto restore;
					}
					else if (Grid[p][m] == BLACK_PAWN)
					{
						if (m + 1 < 8 && Grid[p + 1][m + 1] == WHITE_KING)
							goto restore;
						if (m + 1 < 8 && Grid[p + 1][m - 1] == WHITE_KING)
							goto restore;
					}
				}
			}
		}

		//update castle variables
		
		if (WHITE_CASTLE_KING == true) WHITE_CASTLE_KING = !King_Move;
		if (WHITE_CASTLE_LEFT == true) WHITE_CASTLE_LEFT = !Castle_Left;
		if (WHITE_CASTLE_RIGHT == true) WHITE_CASTLE_RIGHT = !Castle_Right;
	}
	if (player == BLACK_PLAYER)
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
						while (t >= 0 && s >= 0)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
								break;
							else if (Grid[t][s] == BLACK_KING)
								goto restore;
							s--;
							t--;
						}
					}
					//Search BOTTOM Right x++ y++
					s = m + 1;
					t = p + 1;
					if (t < 8 && s < 8)
					{
						while (t < 8 && s < 8)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
								break;
							else if (Grid[t][s] == BLACK_KING)
								goto restore;
							s++;
							t++;
						}
					}
					//Search BOTTOM Left x++ y--
					s = m - 1;
					t = p + 1;
					if (s >= 0 && t < 8)
					{
						while (s >= 0 && t < 8)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
								break;
							else if (Grid[t][s] == BLACK_KING)
								goto restore;
							s--;
							t++;
						}
					}
					//Search top Right x-- y++
					s = m + 1;
					t = p - 1;
					if (s < 8 && t >= 0)
					{
						while (s < 8 && t >= 0)
						{
							if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
								break;
							else if(Grid[t][s] == BLACK_KING)
								goto restore;
							s++;
							t--;
						}
					}
				}
				if (Grid[p][m] == WHITE_ROOK || Grid[p][m] == WHITE_QUEEN)
				{
					//Look Right
					for (int t = m+1; t < 8; t++)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != BLACK_KING)
							break;
						else if (Grid[p][t] == BLACK_KING)
							goto restore;
					}
					//Look Left
					for (int t = m-1; t >= 0; t--)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != BLACK_KING)
							break;
						else if (Grid[p][t] == BLACK_KING)
							goto restore;
					}
					//Look Up
					for (int t = p+1; t < 8; t++)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != BLACK_KING)
							break;
						else if (Grid[t][m] == BLACK_KING)
							goto restore;
					}
					//Look Down
					for (int t = p-1; t >= 0; t--)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != BLACK_KING)
							break;
						else if (Grid[t][m] == BLACK_KING)
							goto restore;
					}
				}
				else if (piece == BLACK_KING)
				{
					if (Grid[p][m] == WHITE_HORSE)
					{
						if (p + 2 < 8 && m + 1 < 8 && Grid[p + 2][m + 1] == BLACK_KING)
							goto restore;
						if (p + 2 < 8 && m - 1 >= 0 && Grid[p + 2][m - 1] == BLACK_KING)
							goto restore;
						if (p - 2 >= 0 && m + 1 < 8 && Grid[p - 2][m + 1] == BLACK_KING)
							goto restore;
						if (p - 2 >= 0 && m - 1 >= 0 && Grid[p - 2][m - 1] == BLACK_KING)
							goto restore;
						if (p + 1 < 8 && m + 2 < 8 && Grid[p + 1][m + 2] == BLACK_KING)
							goto restore;
						if (p + 1 < 8 && m - 2 >= 0 && Grid[p + 1][m - 2] == BLACK_KING)
							goto restore;
						if (p - 1 >= 0 && m + 2 < 8 && Grid[p - 1][m + 2] == BLACK_KING)
							goto restore;
						if (p - 1 >= 0 && m - 2 >= 0 && Grid[p - 1][m - 2] == BLACK_KING)
							goto restore;
					}
					else if (Grid[p][m] == WHITE_PAWN)
					{
						if (m + 1 < 8 && Grid[p - 1][m + 1] == BLACK_KING)
							goto restore;
						if (m + 1 < 8 && Grid[p - 1][m - 1] == BLACK_KING)
							goto restore;
					}
				}

			}
		}
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
bool Check_Win(char Grid[][8], char player)
{
	if (Player_In_Check(Grid, player) == true)
	{
		//Anlaisis Checkmate
		//look all king moves and all the other pieces moves to see if they can cover the check
		int x, y;
		char pos;
		if (player==WHITE_PLAYER)
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
						return false;
				}
			}
			if (x + 1 < 8 && y-1>=0)
			{
				pos = Grid[x + 1][y-1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x + 1][y - 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
						return false;
				}
			}
			if (x + 1 < 8 && y + 1 < 8)
			{
				pos = Grid[x + 1][y+1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x + 1][y + 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
						return false;
				}
			}
			if (y + 1 < 8)
			{
				pos = Grid[x][y+1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x][y + 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
						return false;
				}
			}
			if (y - 1 >= 0)
			{
				pos = Grid[x][y-1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x][y - 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
						return false;
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
						return false;
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
						return false;
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
						return false;
				}
			}
			//Check the movement of the other pieces
			return true;
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
						return false;
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
						return false;
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
						return false;
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
						return false;
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
						return false;
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
						return false;
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
						return false;
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
						return false;
				}
			}
			//Check the movement of the other pieces
			return true;
		}
		if (player == BLACK_PLAYER) std::cout << "White player (UPERCASE/ALL CAPS) is in CHECK! " << std::endl;
		else std::cout << "Black player (LOWER CASE) is in CHECK! " << std::endl;
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
	std::cout << "Row = ";
	std::cin >> x;
	std::cout << "Column = ";
	std::cin >> y;
	while (!std::cin.good() || x < 97 || x >= (8 + 97) || y < 97 || y >= (8 + 97) || !Check_Start(Grid, x - 97, y - 97, PlayerX))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("CLS");
		Display_Grid(Grid);	
		Player_In_Check(Grid, PlayerX % 2 + 1);
		if (PlayerX == WHITE_PLAYER)
			std::cout << "----White to move(UPERCASE)----" << std::endl;
		else std::cout << "----Black to move(lowercase)----" << std::endl;
		std::cout << "Choose the piece you want to move:  " << std::endl;
		std::cout << "Insert a valid coordenate" << std::endl;
		std::cout << "Row = ";
		std::cin >> x;
		std::cout << "Column = ";
		std::cin >> y;
	}
	std::cout << "Choose where to go or write q if you messed up:  " << std::endl;
	std::cout << "Row = ";
	std::cin >> j;
	if (j == 'q')
	{
		system("CLS");
		Display_Grid(Grid);
		Player_In_Check(Grid, PlayerX % 2 + 1);
		goto start;
	}
	std::cout << "Column = ";
	std::cin >> z;
	if (z == 'q')
	{
		system("CLS");
		Display_Grid(Grid);
		Player_In_Check(Grid, PlayerX % 2 + 1);
		goto start;
	}

	while (!std::cin.good() || j < 97 || j >= (8 + 97) || z < 97 || z >= (8 + 97) || !Check_END(Grid, x - 97, y - 97, j - 97, z - 97, PlayerX))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("CLS");
		Display_Grid(Grid);
		Player_In_Check(Grid, PlayerX % 2 + 1);
		if (PlayerX == WHITE_PLAYER)
			std::cout << "----White to move(UPERCASE)----" << std::endl;
		else std::cout << "----Black to move(lowercase)----" << std::endl;
		std::cout << "Insert a valid move" << std::endl;
		std::cout << "Choose where to go or write q if you messed up:  " << std::endl;
		std::cout << "Row = ";
		std::cin >> j;
		if (j == 'q')
		{
			system("CLS");
			Display_Grid(Grid);
			Player_In_Check(Grid, PlayerX % 2 + 1);
			goto start;
		}
		std::cout << "Column = ";
		std::cin >> z;
		if (z == 'q')
		{
			system("CLS");
			Display_Grid(Grid);
			Player_In_Check(Grid, PlayerX % 2 + 1);
			goto start;
		}
	}
}

int main()
{
	char Grid[8][8];
	char player = WHITE_PLAYER;
	bool win = false;
	Create_Grid(Grid);
	Display_Grid(Grid);
	while (!win)
	{
		Player_Choice(Grid, player);
		Display_Grid(Grid);
		win=Check_Win(Grid,player);
		player = player % 2 + 1;
	}
	return 0;
}
