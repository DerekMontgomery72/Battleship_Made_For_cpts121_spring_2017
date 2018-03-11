


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void welcome_screen();

typedef struct stats
{
	int total_hits;
	int total_misses;
	int total_shots;
	double hits_misses;
}Stats;
Stats update_stat(Stats current_stats, int hit);

void init_board(char board[][10], int r, int c);

int select_first();

void get_start_pt(int *r_ptr, int *c_ptr, int dir, int length);

void manual_place_ship(char p_board[][10], int n, int s, int *row_ptr, int *c_ptr, int *dir_ptr);

void gen_dir(int *dir_ptr);

int check_if_position_is_available(char board[][10], int row, int column, int dir, int n);

void place_ship(char board[][10], char ship[], int n, int r, int c, int dir);

void rondomly_place_ship( int n, char board[][10], int *r_ptr, int *c_ptr, int *dir_ptr);

void player_shot(int *r_ptr, int *c_ptr, char board[][10]);

void check_shot(char board[][10], int r, int c, int ship[], int *hit_ptr, int *tot_ship);

void computer_shot(int *r_ptr, int *c_ptr, int sunk, int *hit_in_row_ptr, int board[][10], int *comp_shot_r_ptr, int *comp_shot_c_ptr, int *last_shot_row_ptr);

int is_winner(int comp_tot, int p1_tot);

void update_board(char board[][10], int hit, int r, int c);

void display_board(char board[][10], int r, int c);

void output_stats(FILE *outfile, Stats player_stats, Stats comp_stats);

void check_if_sunk(char board[][10], int hit, int r, int c, int ship[], int n, int player, int *sunk_ptr);

void calculate_hit_in_row(int *hit_in_row_ptr, int hit, char board[][10], int comp_shot_c, int comp_shot_r);

