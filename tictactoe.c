#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define INPUT_BUFFER_SIZE 64

void render_grid(const char grid[9])
{
	printf("\n     0   1   2\n");
	printf("   +-----------+\n");
	printf(" 0 | %c | %c | %c |\n", grid[0], grid[1], grid[2]);
	printf("   |---+---+---|\n");
	printf(" 1 | %c | %c | %c |\n", grid[3], grid[4], grid[5]);
	printf("   |---+---+---|\n");
	printf(" 2 | %c | %c | %c |\n", grid[6], grid[7], grid[8]);
	printf("   +-----------+\n");
}

bool same_row(const char grid[9], int row)
{
	char a = grid[3 * row];
	char b = grid[3 * row + 1];
	char c = grid[3 * row + 2];
	if (a == ' ' || b == ' ' || c == ' ')
		return false;
	
	return a == b && b == c;
}
		
bool same_column(const char grid[9], int col)
{
	char a = grid[col];
	char b = grid[3 + col];
	char c = grid[6 + col];
	if (a == ' ' || b == ' ' || c == ' ')
		return false;
	
	return a == b && b == c;
}

bool same_diagonal(const char grid[9])
{
	char center = grid[4];
	char nw = grid[0];
	char ne = grid[2];
	char sw = grid[6];
	char se = grid[8];
	if (center == ' ' || nw == ' ' || ne == ' ' || sw == ' ' || se == ' ')
		return false;

	return (nw == center && center == se)
		|| (ne == center && center == sw);
}

bool check_for_win(const char grid[9], int x, int y)
{
	return same_column(grid, x) || same_row(grid, y) || same_diagonal(grid);
}

// Returns true if input is valid
bool get_int_input(int* dest, char* prompt)
{
	char input_buffer[INPUT_BUFFER_SIZE];
	memset(input_buffer, '\0', INPUT_BUFFER_SIZE);
	
	printf("%s", prompt);
	fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);

	// Check if input is valid
	if (strlen(input_buffer) != 2 || !isdigit(input_buffer[0]))
	{
		printf("\n+----------------+\n");
		printf("| Invalid input! |\n");
		printf("+----------------+\n");
		return false;
	}
	
	*dest = atoi(input_buffer);
	return true;
}

int main()
{
	char grid[9];
	memset(grid, ' ', 9);

	int turn = 0;

	for (;;)
	{
		char marker = turn % 2 == 0 ? 'X' : 'O';
		int x, y;
		
		render_grid(grid);

		// Get input
		printf("\nCurrent Turn: %c\n", marker);
		if (!get_int_input(&x, "Enter X Coordinate [0, 1, 2]: ")
			|| !get_int_input(&y, "Enter Y Coordinate [0, 1, 2]: "))
			continue;

		// Check if coordinate is within bounds
		if (x < 0 || x > 2 || y < 0 || y > 2)
		{
			printf("\n+---------------------------+\n");
			printf("| Coordinate out of bounds! |\n");
			printf("+---------------------------+\n");
			continue;
		}

		// Check if that coordinate is already used
		if (grid[3 * y + x] != ' ')
		{
			printf("\n+--------------------------------+\n");
			printf("| That cell is already occupied! |\n");
			printf("+--------------------------------+\n");
			continue;
		}

		// Place marker
		grid[3 * y + x] = marker;
		turn++;

		// Did you win, son?
		if (check_for_win(grid, x, y))
		{
			render_grid(grid);
			printf("\n+----------+\n");
			printf("| %c WON!!! |\n", marker);
			printf("+----------+\n");
			break;
		}

		// Check for draw
		if (turn == 9)
		{
			render_grid(grid);
			printf("\n+---------+\n");
			printf("| DRAW!!! |\n");
			printf("+---------+\n");
			break;
		}
	}

	return 0;
}
