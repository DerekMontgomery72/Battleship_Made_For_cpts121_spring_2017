#include"battleship_header.h"


// print a welcome screen and the rules of battleship
void welcome_screen()
{
	printf("******Welcome to Battleship!******\n");
	printf("1. This is a two player game\n");
	printf("2. Player1 is you and Player2 is the computer.\n");
	printf("3. Each player has five ships of varying length to place on the 10x10 board\n");
	printf("You can choose to place these manually, or have the board randomly generated\n");
	printf("4. Once your ships are placed the the first player is randomly selected\n");
	printf("5. Each player will take turns firing at the opposing player ships by guessing the coordinates\n");
	printf("6. A ship must be hit at each of its coordinates to be ""sunk""\n");
	printf("7. The first player to sink all of the other's ships wins\n");

}

//This function displays the boards with all the ships on it.
void display_board(char board[][10], int r, int c)
{
	int r_index = 0, c_index = 0, r_print = 0, c_print = 0;
	printf("_____________________________________________________________________________\n");
	printf("|     ||  %d  |", c_print);
	c_print++;
	while (c_print < c)
	{
		printf("|  %d  |", c_print);
		c_print++;
	}
	printf("\n");

	for (r_index; r_index < r; ++r_index)
	{
		
		for (c_index = 0; c_index < c; ++c_index)
		{
			
				if (c_index == (0))
					printf("|  %d  |", r_print);
			if (c_index == (c - 1))
			{
				printf("|  %c  |\n", board[r_index][c_index]);
			}
			else
			{
				printf("|  %c  |", board[r_index][c_index]);
			}
		}
		r_print++;
	}
}

//This function initializes the boards before the ships are placed onto them.
void init_board(char board[][10], int r, int c) // when declaring a two dimensional array it is important to include the number of rows in the brackets
{
	int r_index = 0, c_index = 0;
	
	for (r_index; r_index < r; ++r_index)
	{
		for (c_index = 0; c_index < c; ++c_index)
		{
			board[r_index][c_index] = '~';

		} // end of inner loop
	} // end of outer loop
} // end of function


//This function will get the starting point for placing a ship.
void get_start_pt(int *r_ptr, int *c_ptr, int dir, int length)
{
	int r = 0, c = 0;
	r = rand() % 10 ;
	c = rand() % 10;
	if (dir == 2)
	{
		*c_ptr = rand() % 10;
		*r_ptr = rand() % (10 - length + 1);
	}
	else
	{
		*c_ptr = rand() % (10 - length + 1);
		*r_ptr = rand() % 10; 

	}

	//9,9
	//from start point go right
	//from start point go down
}

// This function will allow the player to manually place their ships onto the board.
void manual_place_ship(char p_board[][10], int n, int s, int *row_ptr, int *c_ptr,  int *dir_ptr)
{

	int row = 0, column = 0, dir = 0, a = 0;
	
	do
	{
		if (s == 5)
		{
			printf("select the coordinates for a starting point of your carrier");
			//scanf("%d %d %d %d %d %d %d %d %d %d", &row[0], &column[0], &row[1], &column[1], &row[2], &column[2], &row[3], &column[3], &row[4], &column[4]);
		}
		else if (s == 4)
		{
			printf("select the coordinates to place your battleship");
			//scanf("%d %d %d %d %d %d %d %d", &row[0], &column[0], &row[1], &column[1], &row[2], &column[2], &row[3], &column[3]);
		}
		else if (s == 3)
		{
			printf("select the coordinates to place your cruiser");
			//scanf("%d %d %d %d %d %d", &row[0], &column[0], &row[1], &column[1], &row[2], &column[2]);
		}
		else if (s == 2)
		{
			printf("select the coordinates to place your submarine");
			//scanf("%d %d %d %d %d %d", &row[0], &column[0], &row[1], &column[1], &row[2], &column[2]);
		}
		else
		{
			printf("select the coordinates to place your destroyer");
			//scanf("%d %d %d %d", &row[0], &column[0], &row[1], &column[1]);
		}
		do {
			do {

				scanf("%d %d", &row, &column);
				row = row - 1;
				column = column - 1;
			} while (row > 11 || row < 0);
		} while (column > 11 || column < 0);


		do {
			printf("In which direction from the starting point would you like your ship to be placed\n");
			printf("1. Up\n2. Down\n3.Left\n4.Right\n");
			scanf("%d", &dir);
		} while (dir < 0 || dir > 5);
		a = check_if_position_is_available(p_board, row, column, dir, n);
		if (a != 1)
		{
			printf("The position you selected is invalid\n");
		}
	} while (a != 1);
	*row_ptr = row;
	*c_ptr = column;
	*dir_ptr = dir;
}

//This function generates the direction for the ship to be placed in.
void gen_dir( int *dir_ptr)
{
	int dir = 0;
	
	dir = rand() % 2;

	if (dir == 0)
	{
		dir = 2;
	}
	else
	{
		dir = 4;
	}
	*dir_ptr = dir;
}

// This function will randomly place ships onto the board
void rondomly_place_ship( int n, char board[][10],int *r_ptr, int *c_ptr, int *dir_ptr)
{
	int dir = 0, r = 0, c = 0, a = 0;
	do {
		gen_dir(&dir);
		get_start_pt(&r, &c, dir, n);
		a = check_if_position_is_available(board, r, c, dir, n); // Check if the randomly selected position is available
	} while (a != 1);
	*r_ptr = r;
	*c_ptr = c;
	*dir_ptr = dir;
	
}

// This function checks if the position selected randomly, or manually is available for placing a ship.
int check_if_position_is_available(char board[][10], int row, int column, int dir, int n)
{
	int index = 0, a = 0; //a is the condition of if the positiion is available or not
	
	if (dir == 1) // If the direction is facing up
	{
		do
		{
			if (board[row - index][column] != '~')
			{
				a = 0;
			}
			else
			{
				a = 1;
			}
			++index;
		} while (a != 0 && index < n); // Check if the ship will be overlapping other ships
		if (row - n < -1)
		{
			a = 0;
		} // Check if the ship goes over the limits of the board
	}
			if (dir == 2) // If the ship facing down
			{
				do
				{
					if (board[row + index][column] != '~')
					{
						a = 0;
					}
					else
					{
						a = 1;
					}
					++index;
				} while (a != 0 && index < n);
				if (row + n > 10)
				{
					a = 0;
				}
			}

				if (dir == 3) //If the ship is facing left
				{
					do
					{
						if (board[row][column - index] != '~')
						{
							a = 0;
						}
						else
						{
							a = 1;
						}
						++index;
					} while (a != 0 && index < n);
					if (column - n < -1)
					{
						a = 0;
					}
				}
					if (dir == 4) //If the ship is facing right
					{
						do
						{
							if (board[row][column + index] != '~')
							{
								a = 0;
							}
							else
							{
								a = 1;
							}
							++index;
						} while (a != 0 && index < n);
						if (column + n > 10)
						{
							a = 0;
						}
					}
					
					return a;
}


// This function will place a ship onto the board.
void place_ship(char board[][10], char ship[], int n, int r, int c, int dir)
{
	int index = 0;
	if (dir == 1)
	{
		for (index = 0; index < n; ++index)
		{
			board[r - index][c] = ship[index];
		}
	}
	else if (dir == 2)
	{
		for (index = 0; index < n; ++index)
		{
			board[r + index][c] = ship[index];
		}
	}
	else if (dir == 3)
	{
		for (index = 0; index < n; ++index)
		{
			board[r][c - index] = ship[index];
		}
	}
	else
	{
		for (index = 0; index < n; ++index)
		{
			board[r][c + index] = ship[index];
		}
	}
}

// This function randomly selects which player will make the first shot.
int select_first(void)
{
	int f = 0;
	f = rand() % 2;
	return f;
}

// This function will get the coordinate for the player's shot
void player_shot(int *r_ptr, int *c_ptr, char board[][10])
{
	int r = 0, c = 0;
	do
	{
		printf("Choose the coordinates for your shot\n");
		scanf("%d %d", &r, &c);
	}while (board[r][c] == '-' && board[r][c] == 'X' && r > 9 && r < 0 && c > 9 && c < 0);
	*r_ptr = r;
	*c_ptr = c;
}

// this function checks the shot of the player or computer, and updates the amount of hits left on each ship. 
void check_shot(char board[][10], int r, int c, int ship[], int *hit_ptr, int *tot_ship)
{
	int hit = 0;
	if (board[r][c] != '~' && board[r][c] != '-' && board[r][c] != 'X')
	{
		hit = 1;
	}
	else
	{
		hit = 0;
	}

	if (hit == 1)
	{
		if (board[r][c] == 'c')
		{
			ship[1] = ship[1] - 1;
		}
		else if (board[r][c] == 'b')
		{
			ship[2] = ship[2] - 1;
		}
		else if (board[c][r] == 'r')
		{
			ship[3] = ship[3] - 1;
		}
		else if (board[c][r] == 's')
		{
			ship[4] = ship[4] - 1;
		}
		else
		{
			ship[5] = ship[5] - 1;
		}
		*tot_ship = *tot_ship - 1;
	}

	*hit_ptr = hit;
}

// This function updates the board.
void update_board(char board[][10], int hit, int r, int c)
{
	if (hit == 1)
	{
		board[r][c] = 'X';
	}
	else
	{
		board[r][c] = '-';
	}
}

// This function checks if the last shot sunk a ship.
void check_if_sunk(char board[][10], int hit, int r, int c, int ship[], int n, int player, int *sunk_ptr)
{
	int index = 0;
	
	if(hit == 1)
	{ 
		for (index = 0; index < n; ++index)
		{
			if (ship[index] == 0)
			{
				if (player == 0)
				{
					printf("Sunk\n");
					break;
				}
				else
				{
					printf("The computer has sunk one of your ships\n");
						*sunk_ptr = 1;
						break;
				}
			}// end if statement
		}// end for loop
	}// end if hit
}


// This function will be used to update the stats for each player.
Stats update_stat(Stats current_stats, int hit)
{
	if (hit)
	{
		current_stats.total_hits += 1;

	}
	else
	{
		current_stats.total_misses += 1;
	}
	current_stats.total_shots = current_stats.total_shots + 1;

	return current_stats;
}

// This function will create a row and column for the cmoputer's shot in the next turn. It uses basic if else statements to generate a coordinate that is relatively like a real player.
void computer_shot(int *r_ptr, int *c_ptr, int sunk, int *hit_in_row_ptr, int board[][10], int *comp_shot_r_ptr, int *comp_shot_c_ptr, int *last_shot_row_ptr)
{
	if (*hit_in_row_ptr == 0) // If the previous shot was a miss, and it has not hit anything in the immediate surroundings
	{
		do {
			*c_ptr = rand() % 10;
			*r_ptr = rand() % (10);
		} while (board[*r_ptr][*r_ptr] == '-'); // randomly select a place to shoot, where it has not yet shot
	}
	else if (*hit_in_row_ptr == 1)// If the previous shot the was a hit, and it has not yet hit two others before it
	{
		if(comp_shot_c_ptr + 1 < 11)
		{
			*c_ptr = *comp_shot_c_ptr + 1;
		}
		else
		{
			*c_ptr = *comp_shot_c_ptr - 1;
		}
	}
	else if (*hit_in_row_ptr == 2)// if the previous shot was a hit and it has now hit two time in a row on the column
	{
		if (sunk != 1) // If the computer has not yet sunk the destroyer
		{
			if (*last_shot_row_ptr == 1) // If the last hit was by adding to the 1 to the row of the shot before it
			{
				if ((*comp_shot_r_ptr + 1) < 11) // If the next shot will not go over the bounds of the board
				{
					*r_ptr = *comp_shot_r_ptr + 1;
				}
				else // Shoot in the same column, but keep it within the bounds of the board
				{
					*r_ptr = *comp_shot_r_ptr - 1;
				}
			}
			else // If the last hit was by adding to the column of the shot before it
			{
				if ((*comp_shot_c_ptr + 1) < 11)
				{
					*c_ptr = *comp_shot_c_ptr + 1;
				}
				else
				{
					*c_ptr = *comp_shot_c_ptr - 1;
				}

			}
		}
		
	} // end hits in row else if
	else if (*hit_in_row_ptr == 3) // if the computer has now hit a ship three times in a row, This will also be used for any more hits directly in a row after this
	{
		if (sunk != 1)
		{
			if (*last_shot_row_ptr == 1) // If the last hit was by adding to the 1 to the row of the shot before it
			{
				if ((*comp_shot_r_ptr + 1) < 11) // If the next shot will not go over the bounds of the board
				{
					*r_ptr = *comp_shot_r_ptr + 1;
				}
				else // Shoot in the same column, but keep it within the bounds of the board
				{
					do {
						*r_ptr = *comp_shot_r_ptr - 1;
						*comp_shot_r_ptr = *r_ptr;
					} while (board[*r_ptr][*c_ptr] == '-');
				}
			}
			else // If the last hit was by adding to the column of the shot before it
			{
				if ((*comp_shot_c_ptr + 1) < 11)
				{
					*c_ptr = *comp_shot_c_ptr + 1;
				}
				else
				{
					do {
						*c_ptr = *comp_shot_c_ptr - 1;
						*comp_shot_c_ptr = *c_ptr;
					} while (board[*r_ptr][*c_ptr] == '-');
				}

			}
		}
		
	}
	else if (*hit_in_row_ptr == 4) // If the first shot hit, but the second shot missed
	{
		if (*comp_shot_r_ptr + 1 < 11)
		{
			*r_ptr = comp_shot_r_ptr + 1;
		}
		else
		{
			do
			{
				*r_ptr = *comp_shot_r_ptr + 1;
				*comp_shot_r_ptr = *r_ptr;
			} while (board[*r_ptr][*c_ptr] == '-');
		}
		}
	*comp_shot_c_ptr = *c_ptr;
	*comp_shot_r_ptr = *r_ptr;
}


// This function caclulates the correct hits in a row for the computer's ai to use for its next shot
void calculate_hit_in_row(int *hit_in_row_ptr, int hit, char board[][10], int comp_shot_c, int comp_shot_r)
{
	if (*hit_in_row_ptr == 1)
	{
		if (hit)
		{
			*hit_in_row_ptr = 2;
		}
		else
		{
			if (board[comp_shot_c][comp_shot_r] == 'X')
			{
				*hit_in_row_ptr = 4;
			}
			else
			{
				*hit_in_row_ptr = 0;
			}
		}

	}
	else if (*hit_in_row_ptr == 2)
	{
		if (hit)
		{
			*hit_in_row_ptr = 3;
		}
		else
		{
			*hit_in_row_ptr = 0;
		}
	}
}

// This function evaluates who is the winner of the game
int is_winner(int comp_tot, int p1_tot)
{
	int winner = 0;
	if (comp_tot == 0)
		winner = 1;
	else
		winner = 0;

	return winner;
}

// This function will print the stats to the outfile to be viewed after the game
void output_stats(FILE *outfile, Stats player_stats, Stats comp_stats)
{
	player_stats.hits_misses = (player_stats.total_hits / player_stats.total_shots) * 100;
	comp_stats.hits_misses = (comp_stats.total_hits / comp_stats.total_shots) * 100;

	fprintf(outfile, "Player total hits: %d\n", player_stats.total_hits);
	fprintf(outfile, "Player total misses: %d\n", player_stats.total_misses);
	fprintf(outfile, "Player total shots: %d\n", player_stats.total_shots);
	fprintf(outfile, "Player accuracy percentage: %lf\n", player_stats.hits_misses);
	fprintf(outfile, "computer total hits: %d\n", comp_stats.total_hits);
	fprintf(outfile, "computer total misses: %d\n", comp_stats.total_misses);
	fprintf(outfile, "computer total shots: %d\n", comp_stats.total_shots);
	fprintf(outfile, "computer accuracy percentage: %lf\n", comp_stats.hits_misses);

}

