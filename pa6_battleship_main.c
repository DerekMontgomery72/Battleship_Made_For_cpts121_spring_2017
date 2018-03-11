
/******************************************************
Programmer: Derek Montgomery
Collaborators: Andy O
Class: CPTS 121 Lab: 03
TA: Elizabeth Viele
Description: This program will play the game of battleship. It will initialize three boards, one for the computer,
one for the player, and one to be printed to show the player where they have shot already. It will play a full game
betweent the computer and the player. Once the game is over it will print the statistics to an outfile.


*/




#include"battleship_header.h"

int main(void)
{
	Stats p1_stats = { 0,0,0,0.0 }, comp_stats = { 0,0,0,0.0 };

	int option = 0, r = 0, c = 0, dir = 0, f = 0, hit = 0, player_tot = 17, comp_tot = 17, p1ships[6] = { 1, 5, 4, 3, 3, 2 },compships[6] = { 1, 5, 4, 3, 3, 2 }, player = 0, comp = 1,
		c_sunk = 0, p_sunk = 0, hit_in_row = 0, comp_shot_r = 0, comp_shot_c = 0, last_shot_row = 0, winner = 0;
	double player_tot_shots = 0.0, comp_tot_shots = 0.0, player_hits = 0.0, player_misses = 0.0,
		comp_hits = 0.0, comp_misses = 0.0;
	FILE *outfile = NULL;
	outfile = fopen("stats.txt", "w");
	srand((unsigned int)time(NULL));
	welcome_screen();
	system("pause");
	system("cls");

	char carrier[5] = { 'c', 'c', 'c' ,'c', 'c'},
		 battleship[4] = { 'b', 'b', 'b' , 'b'},
		 cruiser[3] = { 'r', 'r', 'r' },
		 sub[3] = { 's', 's', 's' },
		 destroyer[2] = { 'd', 'd' },
		p1_board[10][10],
		comp_board[10][10] = { {'~','~',}, {'~','~'} },
		show_board[10][10];
	do
	{

		printf("Please select from the following menu\n");
		printf("1. Place ships manually\n");
		printf("2. Allow program to randomly select positions of ships");
		scanf("%d", &option);

	} while (option < 1 || option > 2);

	init_board(comp_board, 10, 10);
	init_board(p1_board, 10, 10);
	init_board(show_board, 10, 10);
	if (option == 1)
	{
		manual_place_ship(p1_board, 5, 5, &r, &c, &dir);
		place_ship(p1_board, carrier, 5, r, c, dir);
		display_board(p1_board, 10, 10);
		manual_place_ship(p1_board, 4, 4, &r, &c, &dir);
		place_ship(p1_board, battleship, 4, r, c, dir);
		display_board(p1_board, 10, 10);
		manual_place_ship(p1_board, 3, 3, &r, &c, &dir);
		place_ship(p1_board, cruiser, 3, r, c, dir);
		display_board(p1_board, 10, 10);
		manual_place_ship(p1_board, 3, 2, &r, &c, &dir);
		place_ship(p1_board, sub, 3, r, c, dir);
		display_board(p1_board, 10, 10);
		manual_place_ship(p1_board, 2, 1, &r, &c, &dir);
		place_ship(p1_board, destroyer, 2, r, c, dir);
		display_board(p1_board, 10, 10);
		//manual_place_shipt(p1_board, cruiser);
		//manual_place_ship(p1_board, sub);
		//manual_place_ship(p1_board, destroyer);
	}
	else
	{
		rondomly_place_ship(5, p1_board, &r, &c, &dir);
		place_ship(p1_board, carrier, 5, r, c, dir);
		rondomly_place_ship(4, p1_board, &r, &c, &dir);
		place_ship(p1_board, battleship, 4, r, c, dir);
		rondomly_place_ship(3, p1_board, &r, &c, &dir);
		place_ship(p1_board, cruiser, 3, r, c, dir);
		rondomly_place_ship(3, p1_board, &r, &c, &dir);
		place_ship(p1_board, sub, 3, r, c, dir);
		rondomly_place_ship(2, p1_board, &r, &c, &dir);
		place_ship(p1_board, destroyer, 2, r, c, dir);
		display_board(p1_board, 10, 10);

	}
	// Generate the computer's board
	rondomly_place_ship(5, comp_board, &r, &c, &dir);
	place_ship(comp_board, carrier, 5, r, c, dir);
	rondomly_place_ship(4, comp_board, &r, &c, &dir);
	place_ship(comp_board, battleship, 4, r, c, dir);
	rondomly_place_ship(3, comp_board, &r, &c, &dir);
	place_ship(comp_board, cruiser, 3, r, c, dir);
	rondomly_place_ship(3, comp_board, &r, &c, &dir);
	place_ship(comp_board, sub, 3, r, c, dir);
	rondomly_place_ship(2, comp_board, &r, &c, &dir);
	place_ship(comp_board, destroyer, 2, r, c, dir);

	system("pause");

	f = select_first();
	if (f == 1)
	{
		
		printf("You have been selected to go first\n");
		while (player_tot != 0 && comp_tot != 0)
		{
			player_shot(&r, &c, comp_board);
			check_shot(comp_board, r, c, compships, &hit, &comp_tot);
			update_board(comp_board, hit, r, c);
			update_board(show_board, hit, r, c);
			if (hit)
				printf("HIT\n");
			else
				printf("MISS\n");
			check_if_sunk(comp_board, hit, r, c, compships, 6, player, &p_sunk);
			display_board(show_board, 10, 10);
			system("pause");

			p1_stats = update_stat(p1_stats, hit);

			hit = 0;
			// player's move

			computer_shot(&r, &c, c_sunk, &hit_in_row, p1_board, &comp_shot_r, &comp_shot_c, &last_shot_row);
			check_shot(p1_board, r, c, p1ships, &hit, &player_tot);
			update_board(p1_board, hit, r, c);
			check_if_sunk(p1_board, hit, r, c, p1ships, 6, comp, &c_sunk);
			calculate_hit_in_row(&hit_in_row, hit, p1_board, comp_shot_c, comp_shot_r);
			printf("The computer has chosen to shoot at %d %d\n", r, c);
			display_board(p1_board, 10, 10);
			if (hit)
				printf("HIT\n");
			else
				printf("MISS\n");
			system("pause");
			system("cls");

			comp_stats = update_stat(comp_stats, hit);
			hit = 0;

		}

	}
	else
	{
			printf("The computer gets to make the first move\n");
			while (player_tot != 0 && comp_tot != 0)
			{
			computer_shot(&r, &c, c_sunk, &hit_in_row, p1_board, &comp_shot_r, &comp_shot_c, &last_shot_row);
			check_shot(p1_board, r, c, p1ships, &hit, &comp_tot);
			update_board(p1_board, hit, r, c);
			check_if_sunk(p1_board, hit, r, c, p1ships, 6, comp, &c_sunk);
			printf("The computer has chosen to shoot at %d %d\n", r, c);
			calculate_hit_in_row(&hit_in_row, hit, p1_board, comp_shot_c, comp_shot_r);
			display_board(p1_board, 10, 10);
			if (hit)
				printf("HIT\n");
			else
				printf("MISS\n");
			comp_stats = update_stat(comp_stats, hit);
			system("pause");
			// end computer's turn

			player_shot(&r, &c, comp_board);
			check_shot(comp_board, r, c, compships, &hit, &comp_tot);
			update_board(comp_board, hit, r, c);
			update_board(show_board, hit, r, c);
			check_if_sunk(comp_board, hit, r, c, compships, 6, player, &p_sunk);
			display_board(show_board, 10, 10);
			if (hit)
				printf("HIT\n");
			else
				printf("MISS\n");
			p1_stats = update_stat(p1_stats, hit);
			system("pause");
			system("cls");



		}

	}

	winner = is_winner(comp_tot, player_tot);
	if (winner == 1)
		printf("You have won the game!!\n");
	else
		printf("You lose, the computer has sunk all of your ships.\n");


	printf("Your stats have been sent to an external document.\n");

	output_stats(outfile, p1_stats, comp_stats);

	return 0;
}