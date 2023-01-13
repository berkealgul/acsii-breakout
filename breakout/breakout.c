#include <stdio.h>
#include <unistd.h>


struct Vector2d
{
	int x;
	int y;
};


#define Width 32
#define Height 15

const char c_player = '^';
const char c_ball = 'o';
const char c_border = '#';
const char c_empty = ' ';
const char c_block = '0';
const char c_endl = '\n';

const int player_width = 5;
const int block_depth = 5;

struct Vector2d player_loc;
struct Vector2d ball_loc;
struct Vector2d ball_vel;

char field[Height][Width+2];

int state = 1; // 1 game running  0-game over 

void init_field()
{
        for(int i = 0; i < Height; i++)
        {
                for(int j = 0; j < Width; j++)
                {
                        //border_check
                        if(i == 0 || j == 0 || j == Width-1)
                        {
                                field[i][j] = c_border;
                        }
			else if(i <= block_depth)
			{
				field[i][j] = c_block;
			}
                        else
                        {
                                field[i][j] = c_empty;
                        }
                }

                field[i][Width] = c_endl;
        }
	
	for(int px=player_loc.x, py=player_loc.y, n=px+player_width; px < n; px++)
	{
		field[py][px] = c_player;
	}
}

void init()
{
	state = 1;

	player_loc.x = Width/2;
	player_loc.y = Height-1;

	ball_loc.x = Width/2;
	ball_loc.y = Height/2;

	ball_vel.x = 1;
	ball_vel.y = -1;

	init_field();
}	

void render_screen()
{
        for(int i = 0; i < Height; i++)
        {
                for(int j = 0; j < Width+1; j++)
                {
                        printf("%c", field[i][j]);
                }
        }

}

void game_step()
{
	int pbx = ball_loc.x;
	int pby = ball_loc.y;

	ball_loc.x += ball_vel.x;
	ball_loc.y += ball_vel.y;
	
	int bx = ball_loc.x;
      	int by = ball_loc.y;	
	
	int  revert_pos = 0; 

	if(by == 0)
	{
		revert_pos = 1;
		ball_vel.y *= -1;
	}
	else if(bx == 1 || bx >= Width)
	{
		revert_pos = 1;
		ball_vel.x *= -1;
	}
	else if(field[by][bx] == c_player)
	{
		revert_pos = 1;
		ball_vel.y *= -1;
	}
	else if(field[by][bx] == c_block)
	{
		revert_pos = 1;
		ball_vel.y *= -1;
		field[by][bx] = c_empty;
	}
	else if(by > Height)
	{
		state = 0;
		return;
	}
	

	if(revert_pos)
	{
		ball_loc.x = pbx;
		ball_loc.y = pby;
	}
	else
	{
		field[pby][pbx] = c_empty;
		field[by][bx] = c_ball;
	}
}

void move_player(int v)
{
	if(v == 1)
	{
		if(player_loc.x == Width-player_width) { return; }
		
		field[player_loc.y][player_loc.x] = c_empty;
		player_loc.x++;
		field[player_loc.y][player_loc.x+player_width-1] = c_player;
	}	
	else
	{
		if(player_loc.x == 1) { return; }

		field[player_loc.y][player_loc.x+player_width-1] = c_empty;
		player_loc.x--;
		field[player_loc.y][player_loc.x] = c_player;
	}
}

void manage_input()
{
	char c;
	scanf("%c", &c);
	
	if(c == 'a' || c == 'A')
	{
		move_player(-1);
	}
	else if(c == 'd' || c == 'D')
	{
		move_player(1);
	}
}

int main()
{
        init();

	while(state)
	{
		render_screen();
		game_step();
		manage_input();
		sleep(1);
	}

        return 0;
}

