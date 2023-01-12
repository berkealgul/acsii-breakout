#include <stdio.h>


struct Vector2d
{
	int x;
	int y;
};


#define Width 52
#define Height 15

const char c_player = '^';
const char c_ball = 'o';
const char c_border = '#';
const char c_empty = ' ';
const char c_endl = '\n';

struct Vector2d player_loc;
struct Vector2d ball_loc;
struct Vector2d ball_vel;

char field[Height][Width+1];


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
                        else
                        {
                                field[i][j] = c_empty;
                        }
                }

                field[i][Width] = c_endl;
        }
}

void 

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

int main()
{
        init_field();
	render_screen();
        return 0;
}
