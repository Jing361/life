/*  Game of Life
 *  
 *  Make 3D
 *  Field edge wrapping
 *  Variations on life
 *  Multiple on states
 *  Based on '23/3' rules(2 and 3 live / 3 birth)
 *  Allow other rule sets, custom(?)
 *  Hex-based, triangle-based
 *  'Wireworld' to simulate current in wires
 */
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int main(int argc, char **argv){
    bool wrap = false;
    int states = 1;
    int fieldSize = 32;
    bool field[fieldSize][fieldSize];
    int i, j;
    for(i = 0; i < fieldSize; i++){
        for(j = 0; j < fieldSize; j++){
            field[i][j] = false;
        }
    }

    // initialize glider at center-ish
    field[7][8] = true;
    field[8][8] = true;
    field[9][8] = true;
    field[9][9] = true;
    field[8][10] = true;

    while(1){
        printf("Waiting\n");
        getchar();
        bool work[fieldSize][fieldSize];
        // clear work array, new data completely dependent on field
        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                work[i][j] = false;
            }
        }
        //memcpy(work, 0, sizeof(work));
        // apply rules to work based on field
        // any live cell with fewer than 2 live neighbors dies (loneliness)
        // any live cell with two or three live neighbors lives
        // any live cell with more than three live neighbors dies(crowding)
        // any dead cell with exactly three live neighbors becomes a live cell(reproduction)

        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                // count neighbors
                // check each neighbor in turn, with error checking
                int neighbors = 0;
                if((i - 1) >= 0 && field[i - 1][j])
                    neighbors ++;
                if((i - 1) >= 0 && (j + 1) < fieldSize && field[i - 1][j + 1])
                    neighbors ++;
                if((j + 1) < fieldSize && field[i][j + 1])
                    neighbors ++;
                if((i + 1) < fieldSize && (j + 1) < fieldSize && field[i + 1][j + 1])
                    neighbors ++;
                if((i + 1) < fieldSize && field[i + 1][j])
                    neighbors ++;
                if((i + 1) < fieldSize && (j - 1) >= 0 && field[i + 1][j - 1])
                    neighbors ++;
                if((j - 1) >= 0 && field[i][j - 1])
                    neighbors ++;
                if((i - 1) >= 0 && (j - 1) >= 0 && field[i - 1][j - 1])
                    neighbors ++;
                
                if(field[i][j] && neighbors < 2) work[i][j] = false;
                if(field[i][j] && (neighbors == 2 || neighbors == 3)) work[i][j] = true;
                if(field[i][j] && neighbors > 3) work[i][j] = false;
                if(!field[i][j] && neighbors == 3) work[i][j] = true;
            }
        }
        // copy new data into working array
        memcpy(field, work, sizeof(field));
        //render new field
        for(i = 0; i <= fieldSize; i++)
            printf("_");
        printf("\n");
        for(i = 0; i < fieldSize; i++){
            printf("|");
            for(j = 0; j < fieldSize; j++){
                if(field[i][j])
                    printf("X");
                else
                    printf(" ");
            }
            printf("|\n");
        }
        for(i = 0; i < fieldSize; i++)
            printf("_");
        printf("\n");
    }

    return 0;
}

