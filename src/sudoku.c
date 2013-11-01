#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printString(char *string, char *descrip);
void printInt(int zero);

char *getRowValues(int index, char *board)
{
    int row = index / 9;
    char *rowValues = malloc(10 * sizeof(char));
    memcpy(rowValues, &board[row * 9], 9);
    rowValues[9] = '\0';
    // printString(rowValues, "row");

    return rowValues;

}

char *getColValues(int index, char *board)
{
    int col = index % 9;
    char *colValues = malloc(10 * sizeof(char));
    for(int i = 0; i < 9; i++) {
        int value = 9 * i + col;
        memcpy(colValues+i, &board[value], 1);
    }
    colValues[9] = '\0';
    // printString(colValues, "col");

    return colValues;

}

char *getBoxValues(int index, char *board)
{
    int boxIndices[9][9] = {0, 1, 2, 9, 10, 11, 18, 19, 20, 3, 4, 5, 12, 13, 14, 21, 22, 23, 6, 7, 8, 15, 16, 17, 24, 25, 26, 27, 28, 29, 36, 37, 38, 45, 46, 47, 30, 31, 32, 39, 40, 41, 48, 49, 50, 33, 34, 35, 42, 43, 44, 51, 52, 53, 54, 55, 56, 63, 64, 65, 72, 73, 74, 57, 58, 59, 66, 67, 68, 75, 76, 77, 60, 61, 62, 69, 70, 71, 78, 79, 80};
    int boxNumber = ((( index / 9) / 3) * 3) + (( index % 9 ) / 3);
    // printInt(boxNumber);
    char *boxValues = malloc(10 * sizeof(char));
    for(int i = 0; i < 9; i++) {
        int value = boxIndices[boxNumber][i];
        // printInt(boxIndices[boxNumber][i]);
        // printf("\"%s\"[%d] = %c", board, boxIndices[boxNumber][i], board[boxIndices[boxNumber][i]]);
        boxValues[i] = board[boxIndices[boxNumber][i]];
        //memcpy(boxValues+i, &board[i], 1);
    }
    // printString(boxValues, "box");

    return boxValues;
}

void printString(char *string, char *descrip)
{
    //printf("The %s string is %s\n",descrip, string);
    puts(string);
}

void printInt(int zero)
{
    printf("The integer is %d\n", zero);
}

int getNextZero(char *board)
{
    int zero = strcspn(board, "0");

    return zero;
}

char *getValues(int index, char *board)
{
    char *all_values = malloc(28 * sizeof(char));
    char *row_values = getRowValues(index, board);
    char *col_values = getColValues(index, board);
    char *box_values = getBoxValues(index, board);

    strncpy(all_values, row_values, 9);
    strncat(all_values, col_values, 9);
    strncat(all_values, box_values, 9);
    all_values[27] = '\0';
    // printString(all_values, "all");

    return all_values;
}

char *getPossibilities(int index, char *board)
{
    char *numbers = "123456789";
    char *possibilities = malloc(10 * sizeof(char));
    char *values = getValues(index, board);

    for(int i = 0; i < strlen(numbers) && numbers[i] != '\0' ; i++) {
        char *checkInValues = strchr(values, numbers[i]);

        if(checkInValues == NULL) {
            possibilities[strlen(possibilities)] = numbers[i];
        }
    }

    possibilities[strlen(possibilities)] = '\0';

    return possibilities;

}

char *solve(char *board)
{
    int zero = strcspn(board, "0");
    if(zero == 81) {
        return board;
    } else {
        char *possibilities = getPossibilities(zero, board);
        for(int i = 0; i < strlen(possibilities); i++) {
            // printf("Character is %c\n", possibilities[i]);
            char *new_string = malloc(strlen(board));
            memcpy(new_string, board, strlen(board));
            new_string[zero] = possibilities[i];
            // if there are no zeros in the solved board
            // then you've solved it and can return
            // otherwise, keep looking
            char *result = solve(new_string);
            if(result)
              return result;
        }
    }

    return NULL;
}


int main(int argc, char *argv[])
{

    // char *the_board = "302609005500730000000000900000940000000000109000057060008500006000000003019082040";

    char *unsolved_boards[] = {
        "096040001100060004504810390007950043030080000405023018010630059059070830003590007",
        "105802000090076405200400819019007306762083090000061050007600030430020501600308900",
        "005030081902850060600004050007402830349760005008300490150087002090000600026049503",
        "096040001100060004504810390007950043030080000405023018010630059059070830003590007",
        "105802000090076405200400819019007306762083090000061050007600030430020501600308900",
        "005030081902850060600004050007402830349760005008300490150087002090000600026049503",
        "290500007700000400004738012902003064800050070500067200309004005000080700087005109",
        "080020000040500320020309046600090004000640501134050700360004002407230600000700450",
        "608730000200000460000064820080005701900618004031000080860200039050000100100456200",
        "370000001000700005408061090000010000050090460086002030000000000694005203800149500",
        "000689100800000029150000008403000050200005000090240801084700910500000060060410000",
        "030500804504200010008009000790806103000005400050000007800000702000704600610300500",
        "000075400000000008080190000300001060000000034000068170204000603900000020530200000",
        "300000000050703008000028070700000043000000000003904105400300800100040000968000200",
        "302609005500730000000000900000940000000000109000057060008500006000000003019082040"
    };

    for(int i = 0; i < sizeof(unsolved_boards)/sizeof(*unsolved_boards); i++) {
        printString(solve(unsolved_boards[i]), "board");
    }
    // FILE *fp;
    // char *line = NULL;
    // size_t len = 0;
    // ssize_t read;

    // fp = fopen("puzzles.txt", "r");
    // if(fp == NULL)
    //     exit(EXIT_FAILURE);

    // while ((read = getline(&line, &len, fp)) != -1) {
    //     printString(solve(line), "board");
    //     // printf("Retrieved line of length %zu :\n", read);
    //     // printf("%s", line);
    // }

    // if(line)
    //     free(line);
    // printString(solve(the_board), "board");

    return 0;

}

