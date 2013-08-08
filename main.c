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
//    bool wrap = false;
    bool wrap = true;
    int states = 1;
    int fieldSize = 12;
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

        //render new field
        for(i = 0; i <= fieldSize + 1; i++)
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
        for(i = 0; i <= fieldSize + 1; i++)
            printf("_");
        printf("\n");

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
        int test = 0;
        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                if(field[i][j]){
                    test ++; 
                }
            }
        }
        printf("field: %d\n", test);

        for(i = 0; i < fieldSize; i++){
                int iUP, iDN;
                iUP = i + 1;
                iDN = i - 1;
            for(j = 0; j < fieldSize; j++){
                int jUP, jDN;
                jUP = i + 1;
                jDN = i - 1;

                if(wrap){
                    if(iUP >= fieldSize){
                        iUP = 0;
                    }
                    if(iDN < 0){
                        iDN = fieldSize - 1;
                    }
                    if(jUP >= fieldSize){
                        jUP = 0;
                    }
                    if(jDN < 0){
                        jDN = fieldSize - 1;
                    }
                }

                // count neighbors
                // check each neighbor in turn, with error checking
                int neighbors = 0;
                if(field[iDN][j])
                    neighbors ++;
                if(field[iDN][jUP])
                    neighbors ++;
                if(field[i][jUP])
                    neighbors ++;
                if(field[iUP][jUP])
                    neighbors ++;
                if(field[iUP][j])
                    neighbors ++;
                if(field[iUP][jDN])
                    neighbors ++;
                if(field[i][jDN])
                    neighbors ++;
                if(field[iDN][jDN])
                    neighbors ++;
                
                if(field[i][j] && neighbors < 2)
                    work[i][j] = false;
                if(field[i][j] && (neighbors == 2 || neighbors == 3))
                    work[i][j] = true;
                if(field[i][j] && neighbors > 3)
                    work[i][j] = false;
                if(!field[i][j] && neighbors == 3)
                    work[i][j] = true;
            }
        }
        test = 0;
        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                if(work[i][j]){
                    test ++; 
                }
            }
        }
        printf("work: %d\n", test);
        // copy new data into working array
        memcpy(field, work, sizeof(field));
        test = 0;
        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                if(field[i][j]){
                    test ++; 
                }
            }
        }
        printf("field: %d\n", test);

        test = 0;
        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                if(work[i][j]){
                    test ++; 
                }
            }
        }
        printf("work: %d\n", test);

        //render new field
        for(i = 0; i <= fieldSize + 1; i++)
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
        for(i = 0; i <= fieldSize + 1; i++)
            printf("_");
        printf("\n");
    }

    return 0;
}

