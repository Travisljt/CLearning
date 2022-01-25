#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define BOARD 37
#define BOARDLIST 100000
#define BIGSTR 10

struct rollerboard
{
    char board[BOARD];
    int father;
    int row, column;
};
typedef struct rollerboard roll;



char* shift_left(const roll* board_list, int row, int n);
char* shift_right(const roll* board_list, int row, int n);
char* shift_up(const roll* board_list, int column, int n);
char* shift_down(const roll* board_list, int column, int n);
int get_newboard(roll* board_list, int list_number, int n, char* final_board);
bool compare_previous_board(const roll* board_list, char* board, int n);
void print_result(roll* board_list, int result, char* argv[]);
void print_board(roll* board_list, int n);
void test();


int main(int argc, char* argv[])
{
    test();
    //Initialise the board
    char str[BIGSTR];
    roll* board_list = (roll*)calloc(BOARDLIST, sizeof(roll));
    int list_number = 0;
    roll board_init;
    strcpy(board_init.board, "");

    if (argc == 2) {
        FILE* fp1 = fopen(argv[1], "r");
        if (fp1 == NULL) {
            fprintf(stderr, "Cannot read file");
            exit(EXIT_FAILURE);
        }
        if (fgets(str, BIGSTR, fp1) == NULL) {
            fprintf(stderr, "Cannot read %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        //get first board in list
        board_init.row = atoi(str);
        board_init.column = atoi(str + 1);
        board_init.father = 0;
        int lenth = 0;
        while (fscanf(fp1, "%s", str) == 1) {
            int width = strlen(str);
            if (width != board_init.column) {
                printf("Invalid board\n");
                exit(EXIT_FAILURE);
            }
            strcat(board_init.board, str);
            lenth++;
        };
        if (lenth != board_init.row) {
            printf("Invalid board\n");
            exit(EXIT_FAILURE);
        }
        board_list[list_number] = board_init;
        fclose(fp1);
    }
    else if (argc == 3) {
        FILE* fp2 = fopen(argv[2], "r");
        if (fp2 == NULL) {
            fprintf(stderr, "Cannot read file");
            exit(EXIT_FAILURE);
        }
        if (fgets(str, BIGSTR, fp2) == NULL) {
            fprintf(stderr, "Cannot read %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }

        //get first board in list
        board_init.row = atoi(str);
        board_init.column = atoi(str + 1);
        board_init.father = 0;
        int lenth = 0;
        while (fscanf(fp2, "%s", str) == 1) {
            int width = strlen(str);
            if (width != board_init.column) {
                printf("Invalid board\n");
                exit(EXIT_FAILURE);
            }
            strcat(board_init.board, str);
            lenth++;
        };
        if (lenth != board_init.row) {
            printf("Invalid board\n");
            exit(EXIT_FAILURE);
        }
        board_list[list_number] = board_init;
        fclose(fp2);
    }
    else {
        fprintf(stderr, "Usage : %s <file> or %s -v <file> \n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    //check board
    int cell_number = strlen(board_init.board);
    int one_number = 0;
    for (int check = 0;check < cell_number;check++) {
        if (board_init.board[check] != '0' && board_init.board[check] != '1') {
            printf("Invalid board\n");
            exit(EXIT_FAILURE);
        }
        else if (board_init.board[check] == '1') {
            one_number++;
        }
    }
    if (one_number != board_init.column) {
        printf("Invalid board\n");
        exit(EXIT_FAILURE);
    }


    //get finial board
    char final_board[BOARD] = "";
    int i;
    for (i = 0;i < board_list[0].column;i++) {
        final_board[i] = '1';
    }
    while (i < board_list[0].column * board_list[0].row) {
        final_board[i] = '0';
        i++;
    }

    //looking for final_board in list
    int n = 0;
    while (strcmp(board_list[list_number].board, final_board) != 0)
    {
        list_number = get_newboard(board_list, list_number, n, final_board);
        n++;
    }

    print_result(board_list, list_number, argv);

    free(board_list);
    return 0;

}

char* shift_left(const roll* board_list, int row, int n)
{

    char* board = (char*)calloc(BOARD, sizeof(char*));
    char temp;
    int position = row * board_list[n].column;
    strcpy(board, board_list[n].board);
    temp = board[position];
    while (position < (row + 1) * board_list[n].column - 1)
    {
        board[position] = board[position + 1];
        position++;
    }
    board[position] = temp;
    return board;

}

char* shift_right(const roll* board_list, int row, int n)
{
    char* board = (char*)calloc(BOARD, sizeof(char*));
    char temp;
    int position = (row + 1) * board_list[n].column - 1;
    strcpy(board, board_list[n].board);
    temp = board[position];
    while (position > row * board_list[n].column)
    {
        board[position] = board[position - 1];
        position--;
    }
    board[position] = temp;
    return board;
}

char* shift_up(const roll* board_list, int column, int n)
{
    char* board = (char*)calloc(BOARD, sizeof(char*));
    char temp;
    int position = column;
    strcpy(board, board_list[n].board);
    temp = board[position];
    while (position < (board_list[n].row - 1) * board_list[n].column + column)
    {
        board[position] = board[position + board_list[n].column];
        position = position + board_list[n].column;
    }
    board[position] = temp;
    return board;
}

char* shift_down(const roll* board_list, int column, int n)
{
    char* board = (char*)calloc(BOARD, sizeof(char*));
    char temp;
    int position = (board_list[n].row - 1) * board_list[n].column + column;
    strcpy(board, board_list[n].board);
    temp = board[position];
    while (position > column)
    {
        board[position] = board[position - board_list[n].column];
        position = position - board_list[n].column;
    }
    board[column] = temp;
    return board;
}

int get_newboard(roll* board_list, int list_number, int n, char* final_board)
{
    for (int column = 0;column < board_list[n].column;column++) {

        char* next_board = shift_up(board_list, column, n);
        if (compare_previous_board(board_list, next_board, list_number) == 1) {
            if (list_number < BOARDLIST - 1) {
                list_number++;
                strcpy(board_list[list_number].board, next_board);
                board_list[list_number].father = n;
                board_list[list_number].row = board_list[n].row;
                board_list[list_number].column = board_list[n].column;
                
                
            }
            else {
                //free(next_board);
                printf("Can not find answer\n");
                exit(EXIT_FAILURE);
            }

        }
        if (strcmp(final_board, board_list[list_number].board) == 0) {
            return list_number;
        }
        free(next_board);
    }

    for (int column = 0;column < board_list[n].column;column++) {
        char* next_board = shift_down(board_list, column, n);
        if (compare_previous_board(board_list, next_board, list_number) == 1) {
            if (list_number < BOARDLIST - 1) {
                list_number++;
                strcpy(board_list[list_number].board, next_board);
                board_list[list_number].father = n;
                board_list[list_number].row = board_list[n].row;
                board_list[list_number].column = board_list[n].column;
                
            }
            else {
                //free(next_board);
                printf("Can not find answer\n");
                exit(EXIT_FAILURE);
            }

        }
        if (strcmp(final_board, board_list[list_number].board) == 0) {
            return list_number;
        }
          free(next_board);
    }

    for (int row = 0;row < board_list[n].row;row++) {
        char* next_board = shift_left(board_list, row, n);
        if (compare_previous_board(board_list, next_board, list_number) == 1) {
            if (list_number < BOARDLIST - 1) {
                list_number++;
                strcpy(board_list[list_number].board, next_board);
                board_list[list_number].father = n;
                board_list[list_number].row = board_list[n].row;
                board_list[list_number].column = board_list[n].column;
                
            }
            else {
                //free(next_board);
                printf("Can not find answer\n");
                exit(EXIT_FAILURE);
            }
        }
        if (strcmp(final_board, board_list[list_number].board) == 0) {
            return list_number;
        }
         free(next_board);
    }

    for (int row = 0;row < board_list[n].row;row++) {
        char* next_board = shift_right(board_list, row, n);
        if (compare_previous_board(board_list, next_board, list_number) == 1) {
            if (list_number < BOARDLIST - 1) {
                list_number++;
                strcpy(board_list[list_number].board, next_board);
                board_list[list_number].father = n;
                board_list[list_number].row = board_list[n].row;
                board_list[list_number].column = board_list[n].column;
                
            }
            else {
                //free(next_board);
                printf("Can not find answer\n");
                exit(EXIT_FAILURE);
            }
        }
        if (strcmp(final_board, board_list[list_number].board) == 0) {
            return list_number;
        }
      free(next_board);
    }

    return list_number;
}

bool compare_previous_board(const roll* board_list, char* board, int list_number)
{
    for (int m = 0;m <= list_number;m++) {
        if (strcmp(board_list[m].board, board) == 0) {
            return 0;
        }
    }
    return 1;
}

void print_result(roll* board_list, int result, char* argv[])
{
    static int cnt = 0;
    if (strcmp(argv[1], "-v") == 0) {
        if (result == 0) {
            printf("%d:moves\n", cnt++);
            print_board(board_list, result);
            return;
        }
        else {
            print_result(board_list, board_list[result].father, argv);
        }
        if (strcmp(argv[1], "-v") == 0) {
            printf("%d:moves\n", cnt++);
            print_board(board_list, result);
        }
    }
    else {
        int cnt = 0;
        while (result != 0) {
            cnt++;
            result = board_list[result].father;
        }
        printf("%d:moves\n", cnt);
    }



}

void print_board(roll* board_list, int n)
{
    for (int a = 0;a < board_list[n].row;a++) {
        for (int b = 0;b < board_list[n].column;b++) {
            printf("%c", board_list[n].board[a * board_list[n].column + b]);
        }
        printf("\n");
    }
    printf("\n");
}

void test()
{
    roll* test_list = (roll*)calloc(20, sizeof(roll));
    strcpy(test_list[0].board, "100010001");
    test_list->father = 0;
    test_list->column = 3;
    test_list->row = 3;
    char* final_board = "111000000";

    char* str = shift_left(test_list, 0, 0);
    assert(strcmp("001010001", str) == 0);
    str = shift_right(test_list, 0, 0);
    assert(strcmp("010010001", str) == 0);
    str = shift_up(test_list, 2, 0);
    assert(strcmp("100011000", str) == 0);
    str = shift_down(test_list, 2, 0);
    assert(strcmp("101010000", str) == 0);

    int test_number = get_newboard(test_list, 0, 0, final_board);
    assert(test_number == 12);

    assert(compare_previous_board(test_list, str, 12) != 1);

    free(test_list);
}