#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_nb_valid (int i, int j, int nb, int grid[9][9]);
int solve(int n, int grid[9][9]);
int empty_element(int grid[9][9]);
void draw(int grid[9][9]);

int main(int argc , char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./sudoku_solver file.txt\n");
    }

    int grid[9][9]= {0};

    //##READ the text file and load the matrix board.
    //9*9 + 8*'\n' = 81 +8 = 89
    char buffer[89] = {'0'};
    int buf;

    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == NULL)
        return 1;

    fread(buffer, sizeof(char), 89, fp);

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            grid[i][j] = buffer[10*i+j] - '0';
            printf("%i ", grid[i][j]);
        }
        printf("\n");
    }
    fclose(fp);

    printf("\nempty element: %i\n", empty_element(grid));

    printf("\nsolving...\n\n");

    if(solve(empty_element(grid), grid))
    {
        draw(grid);
    }
    else
    {
        printf("No solution to this sudoku \n");
    }
    //printf("\nempty element: %i\n\n", empty_element(grid));
    
return 0;

}

bool is_nb_valid (int i, int j, int nb, int grid[9][9])
{
    for (int k = 0; k < 9; k++)
    {
        if(nb == grid[k][j] || nb == grid[i][k] || nb == grid[3*(i/3) + k/3][3*(j/3) + k%3])
        {
            return false;
        }
    }
    return true; 
}

int solve(int n, int grid[9][9])
{
    if(n == 0)
        return 1;
    else 
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if(grid[i][j] == 0)
                {//try out all possibilities
                    for(int k = 1; k < 10; k++)
                    {
                        if(is_nb_valid(i,j,k,grid))
                        {
                            grid[i][j] = k;
                            //draw(grid);
                            if(solve(n-1, grid))
                                return 1;
                            else grid[i][j] = 0;
                        }
                    }
                    return 0;//not possible
                }
            }
        }
    }
}

int empty_element(int grid[9][9])
{
    int n = 0;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (grid[i][j]== 0)
                n++;
        }
    }
    return n;
}

void draw(int grid[9][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            printf("%i ", grid[i][j]);
        }
            printf("\n");
    }
    printf("\n");
}