#include <stdio.h>
/* Head and Declarations */
void checkered(char * board[9][9], int k); /* Display the game board*/
void turn(char * board[9][9], int k); /*The main mechanics function*/
void capture(char * board[9][9], int * fsm, int chz, char s0, char s1); /*Capture/Movement Function*/
int cmcontrol(char * board[9][9]); /* King controller to see if game finishes */
/*Mechanical functions have void type while pieces have int type since they're returning INAPP variable*/
int pawn(char * board[9][9], char s0, char s1, int color, int direction); /*Moves horizontally by one unit, captures diagonally*/
int bishop(char * board[9][9], char s0, char s1, int color, int direction); /*Moves diagonally by any amount*/
int rook(char * board[9][9], char s0, char s1, int color, int direction); /*Moves vertically and horizontally by any amount*/
int queen(char * board[9][9], char s0, char s1, int color, int direction); /*Moves on any direction by any amount*/
int king(char * board[9][9], char s0, char s1, int color, int direction); /*Moves on any direction by one unit*/
int knight(char * board[9][9], char s0, char s1, int color, int direction); /*Moves on L route*/

/* Body */
void main() {
    int CheckMate = 0; /*Board*/
    int i, j, t, k = 0; /* Lööp params*/
    /* Mechanics */
    char * board[9][9] = {
        {
            "BR",
            "BK",
            "BB",
            "BQ",
            "BG",
            "BB",
            "BK",
            "BR",
            "8 "
        },
        {
            "BP",
            "BP",
            "BP",
            "BP",
            "BP",
            "BP",
            "BP",
            "BP",
            "7 "
        },
        {
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "6 "
        },
        {
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "5 "
        },
        {
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "4 "
        },
        {
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "00",
            "3 "
        },
        {
            "WP",
            "WP",
            "WP",
            "WP",
            "WP",
            "WP",
            "WP",
            "WP",
            "2 "
        },
        {
            "WR",
            "WK",
            "WB",
            "WQ",
            "WG",
            "WB",
            "WK",
            "WR",
            "1 "
        },
        {
            " A",
            " B",
            " C",
            " D",
            " E",
            " F",
            " G",
            " H",
            "  "
        },
    };

    while (!CheckMate) {
        /* Print Checkered Board*/
        checkered(board, k);
        turn(board, k);
        /* CheckMate controller*/
        CheckMate=cmcontrol(board);
        /* Turn counter*2 */
        k++;
    };
    /* The winner is chosen by the cmcontrol and k mutualism*/
    if(k%2==1)
		printf("White Wins");
    if(k%2==0)
		printf("Black Wins");
}

/*GAME MECHANICS FUNCTIONS*/
int cmcontrol(char * board[9][9]){
	int i,j,cntrl=0;
	/* Scan all 8x8 Grid to detect Kings*/
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if(board[i][j][1]=='G')
				cntrl++;
	/*There has to be 2 kings*/
	if (cntrl==2)
		return 1;
	/*Else the game ends with the victory of the side who has an alive king*/
	else
		return 0;
}
void checkered(char * board[9][9], int k) {
    /* Display the checkered board with respect to turn number*/
    int i, j;
    for (i = 0; i < 75; i++) printf("-");
    printf("\n\t\t");
    printf("Chess Board (t=%d)\n\n\t", k);
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            printf("%s\t", board[i][j]);
        }
        printf("\n\t");
    };
    printf("\n");
    for (i = 0; i < 75; i++) printf("-");
    printf("\n");
}

void turn(char * board[9][9], int k) {
    int inapp = 0, direction, remain, error;
    char s0, s1, color, piece;
    /* Movement Interface*/
    if (k % 2 == 0) printf("White's Turn:\n");
    else printf("Black's Turn:\n");
    while (inapp == 0) {
        /*INAPP makes value of 1 when the chosen piece has any possible moves*/
        error = 1; /*ERRROR makes value of 0 when the chosen cell has an appropiate piece*/
        while (error == 1) {
            printf("Select a piece:");
            scanf(" %c %c", & s1, & s0); /* It was in s0 s1 order but in the project file it's shown as s1 s0*/
            /*Inputs are int and char, so they should be converted to checkered board indices*/
            s0 = (56 - s0);
            /*Case-sensitive filtering for column letters*/
            if (s1 > 90) {
                s1 = s1 - 97;
            } else {
                s1 = s1 - 65;
            };
            /*Detect the piece and color*/
            color = board[s0][s1][0];
            piece = board[s0][s1][1];
            if (color == 66) /*black*/ {
                direction = 1; /*Indicates turn*/
                remain = 1;
            } else if (color == 87) /*white*/ {
                direction = -1;
                remain = 0; /*Indicates error*/
            }
            /* If user chooses a non-zero cell and is appropiate with their color, move */
            if ((piece > 64) && (piece < 91) && (k % 2 == remain)) {
                error = 0;
            } else printf("Incorrect selection,");
        };
        printf("Possible Moves for %c%c:\n", color, piece);
        /* Possibility function calls so that if it's detected to be one, call convenient function*/
        switch (piece) {
        case 'R':
            inapp = rook(board, s0, s1, color, direction);
            break;
        case 'K':
            inapp = knight(board, s0, s1, color, direction);
            break;
        case 'B':
            inapp = bishop(board, s0, s1, color, direction);
            break;
        case 'Q':
            inapp = queen(board, s0, s1, color, direction);
            break;
        case 'G':
            inapp = king(board, s0, s1, color, direction);
            break;
        case 'P':
            inapp = pawn(board, s0, s1, color, direction);
            break;
        default:
            break;
        };
    };
};

/*Capture/Movement Function*/
void capture(char * board[9][9], int * fsm, int chz, char s0, char s1) {
    int temp0, temp1, n0, n1;
    /*They were names, now indices*/
    n0 = 56 - fsm[2 * chz];
    n1 = fsm[2 * chz + 1] - 65;
    if (board[n0][n1] != "00") {
    	/*Print a message when a piece is captured*/
        printf("Capture: %s => %s\n", board[s0][s1], board[n0][n1]);
    };
    board[n0][n1] = board[s0][s1];
    board[s0][s1] = "00";
}

/* Possibility function declarations and definitions*/
int pawn(char * board[9][9], char s0, char s1, int color, int direction) {
    /*List possible moves*/
    int sz = 0, fsm[56];
    fsm[0] = 0;
    fsm[1] = 0;
    if ((board[s0 + direction][s1][1] == '0') && ( s0 == 1 || s0 == 6 ) ){
        /*Move Twice If Empty*/
        sz++;
        printf("%d.%c%c ", sz, s1 + 65, (56 - s0) - 2* direction);
        fsm[2 * sz] = 56 - (s0 + direction*2);
        fsm[2 * sz + 1] = s1 + 65;
    };
    if (board[s0 + direction][s1][1] == '0') {
        /*Move If Empty*/
        sz++;
        printf("%d.%c%c ", sz, s1 + 65, (56 - s0) - direction);
        fsm[2 * sz] = 56 - (s0 + direction);
        fsm[2 * sz + 1] = s1 + 65;
    };
    if (abs(board[s0 + direction][s1 - 1][0] - color) == 21) {
        /*Capture if counter color*/
        sz++;
        printf("%dX%c%c ", sz, s1 + 65 - 1, (56 - s0) - direction);
        fsm[2 * sz] = (56 - s0) - direction;
        fsm[2 * sz + 1] = s1 + 65 - 1;
	    
    };
    if (abs(board[s0 + direction][s1 + 1][0] - color) == 21) {
        sz++;
        printf("%dX%c%c ", sz, s1 + 65 + 1, (56 - s0) - direction);
		fsm[2 * sz] = 56 - (s0 + direction);
        fsm[2 * sz + 1] = 65 + s1 + 1;
    };
    printf("\n");
    /* Move! */
    int chs;
    while (1) {
        if (sz == 0) {
            return 0;
            break;
        };
        printf("Press\t");
        scanf("%d", & chs);
        if ((chs > sz) || (chs < 0))
            printf("Excuse me? ");
        else {
            /*Move here*/
            capture(board, fsm, chs, s0, s1);
            break;
        };
    };
    return 1;
};

int bishop(char * board[9][9], char s0, char s1, int color, int direction) {
    /*List possible moves*/
    /* This function mostly includes duplicate loops, just the signs differ*/
    int sz = 0, row, column; /*ROW and COLUMN vars are fyling on a new axis system originated on s0 and s1*/
    int fsm[56];
    fsm[0] = 0;
    fsm[0] = 0;
    for (row = s0 + 1, column = s1 + 1; column < 8 && row < 8; row++, column++) {
        /* Detects for the lower-right side of bishop*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 + 1, column = s1 - 1; column < 8 && row < 8; row++, column--) {
        /* Detects for the lower-left side of bishop*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 - 1, column = s1 - 1; column < 8 && row < 8; row--, column--) {
        /* Detects for the upper-left side of bishop*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 - 1, column = s1 + 1; column < 8 && row < 8; row--, column++) {
        /* Detects for the upper-right side of bishop*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    printf("\n");
    /* Move! */
    int chs;
    while (1) {
        if (sz == 0) {
            return 0;
            break;
        };

        printf("Press\t");
        scanf("%d", & chs);
        if ((chs > sz) || (chs < 0))
            printf("Excuse me? ");
        else {
            /*Move here*/
            capture(board, fsm, chs, s0, s1);
            break;
        };
    };
    return 1;
}

int rook(char * board[9][9], char s0, char s1, int color, int direction) {
    /*List possible moves*/
    /* This function mostly includes duplicate loops, just the signs differ*/
    int sz = 0, row, column; /*ROW and COLUMN vars are fyling on a new axis system originated on s0 and s1*/
    int fsm[56];
    fsm[0] = 0;
    fsm[0] = 0;
    for (row = s0 + 1, column = s1; row < 8; row++) {
        /* Detects for the lower side of rook*/
        if (row < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 - 1, column = s1; row < 8; row--) {
        /* Detects for the upper side of rook*/
        if (row < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0, column = s1 + 1; column < 8; column++) {
        /* Detects for the right side of the rook*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0, column = s1 - 1; column < 8; column--) {
        /* Detects for the left side of the rook*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);

            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);

            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    printf("\n");
    /* Move! */
    int chs;
    while (1) {
        if (sz == 0) {
            return 0;
            break;
        };

        printf("Press\t");
        scanf("%d", & chs);
        if ((chs > sz) || (chs < 0))
            printf("Excuse me? ");
        else {
            /*Move here*/
            capture(board, fsm, chs, s0, s1);
            break;
        };
    };
    return 1;
}
int queen(char * board[9][9], char s0, char s1, int color, int direction) {
    /*List possible moves*/
    /* This function mostly includes duplicate loops, just the signs differ*/
    int sz = 0, row, column; /*ROW and COLUMN vars are fyling on a new axis system originated on s0 and s1*/
    int fsm[56];
    fsm[0] = 0;
    fsm[0] = 0;
    for (row = s0 + 1, column = s1 + 1; column < 8 && row < 8; row++, column++) {
        /* Detects for the lower-right side of queen*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 + 1, column = s1 - 1; column < 8 && row < 8; row++, column--) {
        /* Detects for the lower-left side of queen*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 - 1, column = s1 - 1; column < 8 && row < 8; row--, column--) {
        /* Detects for the upper-left side of queen*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 - 1, column = s1 + 1; column < 8 && row < 8; row--, column++) {
        /* Detects for the upper-right side of queen*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 + 1, column = s1; row < 8; row++) {
        /* Detects for the lower side of queen*/
        if (row < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            /*Stop if same color*/
            break;
        };
    };
    for (row = s0 - 1, column = s1; row < 8; row--) {
        /* Detects for the upper side of queen*/
        if (row < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            break;
        };
    };
    for (row = s0, column = s1 + 1; column < 8; column++) {
        /* Detects for the right side of the queen*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65), 56 - row;
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            break;
        };
    };
    for (row = s0, column = s1 - 1; column < 8; column--) {
        /* Detects for the left side of the queen*/
        if (row < 0 || column < 0) break;
        if (board[row][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
        };
        if (abs(board[row][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column;
            break;
        };
        if (abs(board[row][column][0] - color) == 0) {
            break;
        };
    };
    printf("\n");
    /* Move! */
    int chs;
    while (1) {
        if (sz == 0) {
            return 0;
            break;
        };
        printf("Press\t");
        scanf("%d", & chs);
        if ((chs > sz) || (chs < 0)) /*User can not choose a move out of range*/
            printf("Excuse me? ");
        else {
            /*Move here*/
            capture(board, fsm, chs, s0, s1);
            break;
        };
    };
    return 1;
}

int king(char * board[9][9], char s0, char s1, int color, int direction) {
    /*List possible moves*/
    /* This function mostly includes duplicate loops, just the signs differ*/
    int sz = 0, row = s0, column = s1; /*ROW and COLUMN vars are fyling on a new axis system originated on s0 and s1*/
    int fsm[56];
    fsm[0] = 0;
    fsm[0] = 0;
    /* Detects for the lower-right side of king*/

    if (row + 1 > -1 & column + 1 > -1)
        if (board[row + 1][column + 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 + 1, 56 - row - 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column + 1;
        };
    if (row + 1 > -1 & column + 1 > -1)
        if (abs(board[row + 1][column + 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 + 1, 56 - row - 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column + 1;
        };
    /* Detects for the lower-left side of king*/
    if (column > 0)
        if (board[row + 1][column - 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 - 1, 56 - row - 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column - 1;
        };
    if (column > 0)
        if (abs(board[row + 1][column - 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 - 1, 56 - row - 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column - 1;

        };
    /* Detects for the upper-left side of king*/

    if (row > 0 & column > 0)
        if (board[row - 1][column - 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 - 1, 56 - row + 1);
            fsm[2 * sz] = 56 - row + 1;
            fsm[2 * sz + 1] = 65 + column - 1;
        };
    if (row > 0 & column > 0)
        if (abs(board[row - 1][column - 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 - 1, 56 - row + 1);
            fsm[2 * sz] = 56 - row + 1;
            fsm[2 * sz + 1] = 65 + column - 1;
        };

    /* Detects for the upper-right side of king*/
    if (row > 0)
        if (board[row - 1][column + 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 + 1, 56 - row + 1);
            fsm[2 * sz] = 56 - row + 1;
            fsm[2 * sz + 1] = 65 + column + 1;
        };
    if (row > 0)
        if (abs(board[row - 1][column + 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 + 1, 56 - row + 1);
            fsm[2 * sz] = 56 - row + 1;
            fsm[2 * sz + 1] = 65 + column + 1;
        };

    /* Detects for the lower side of king*/

    if (row > 0)
        if (board[row - 1][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row - 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column;
        };
    if (row > 0)
        if (abs(board[row - 1][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row - 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column;
        };
    /* Detects for the upper side of king*/
    if (row > 0)
        if (board[row - 1][column][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65, 56 - row + 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column;
        };
    if (row > 0)
        if (abs(board[row - 1][column][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65, 56 - row + 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column;
        };

    /* Detects for the right side of the king*/
    if (board[row][column + 1][1] == '0') {
        /*Move If Empty*/
        sz++;
        printf("%d.%c%c ", sz, column + 65 + 1, 56 - row);
        fsm[2 * sz] = 56 - row;
        fsm[2 * sz + 1] = 65 + column + 1;
    };
    if (abs(board[row][column + 1][0] - color) == 21) {
        /*Capture if counter color*/
        sz++;
        printf("%dX%c%c ", sz, column + 65 + 1, 56 - row);
        fsm[2 * sz] = 56 - row;
        fsm[2 * sz + 1] = 65 + column + 1;
    };

    /* Detects for the left side of the king*/
    if (column > 0)
        if (board[row][column - 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 - 1, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column - 1;
        };
    if (column > 0)
        if (abs(board[row][column - 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 - 1, 56 - row);
            fsm[2 * sz] = 56 - row;
            fsm[2 * sz + 1] = 65 + column - 1;
        };
    printf("\n");
    /* Move! */
    int chs;
    while (1) {
        if (sz == 0) {
            return 0;
            break;
        };

        printf("Press\t");
        scanf("%d", & chs);
        if ((chs > sz) || (chs < 0)) /*User can not choose a move out of range*/
            printf("Excuse me? ");
        else {
            /*Move here*/
            capture(board, fsm, chs, s0, s1);
            break;
        };
    };
    return 1;
}

int knight(char * board[9][9], char s0, char s1, int color, int direction) {
    /*List possible moves*/
    /* This function mostly includes duplicate loops, just the signs differ*/
    int sz = 0, row = s0, column = s1; /*ROW and COLUMN vars are fyling on a new axis system originated on s0 and s1*/
    int fsm[56];
    fsm[0] = 0;
    fsm[0] = 0;
    /* Different "L" routes are modelled with ROW and COLUMN, symbolized with clock-cycle*/
    /* Detects for the 5 o'clock of knight*/
    if (row < 7)
        if (board[row + 1 * 2][column + 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 + 1, 56 - row - 1 * 2);
            fsm[2 * sz] = 56 - row - 2;
            fsm[2 * sz + 1] = 65 + column + 1;
        };
    if (row < 7)
        if (abs(board[row + 1 * 2][column + 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 + 1, 56 - row - 1 * 2);
            fsm[2 * sz] = 56 - row - 2;
            fsm[2 * sz + 1] = 65 + column + 1;
        };
    /* Detects for the 8 o'clock of knight*/
    if (row < 8 && column > 1)
        if (board[row + 1][column - 1 * 2][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 - 1 * 2, 56 - row - 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column - 2;
        };
    if (row < 8 && column > 1)
        if (abs(board[row + 1][column - 1 * 2][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 - 1 * 2, 56 - row - 1);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column - 2;
        };
    /* Detects for the 11 o'clock of the knight*/

    if (column > 0 && row > 1)
        if (board[row - 1 * 2][column - 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 - 1, 56 - row + 1 * 2);
            fsm[2 * sz] = 56 - row + 2;
            fsm[2 * sz + 1] = 65 + column - 1;

        };
    if (column > 0 && row > 1)
        if (abs(board[row - 1 * 2][column - 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 - 1, 56 - row + 1 * 2);
            fsm[2 * sz] = 56 - row + 2;
            fsm[2 * sz + 1] = 65 + column - 1;

        };
    /* Detects for the 2 o'clock of knight*/
    if (row > 0)
        if (board[row - 1][column + 1 * 2][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 + 1 * 2, 56 - row + 1);
            fsm[2 * sz] = 56 - row + 1;
            fsm[2 * sz + 1] = 65 + column + 2;

        };
    if (row > 0)
        if (abs(board[row - 1][column + 1 * 2][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 + 1 * 2, 56 - row + 1);
            fsm[2 * sz] = 56 - row + 1;
            fsm[2 * sz + 1] = 65 + column + 2;

        };
    /* Detects for the 10 o'clock of knight*/

    if (column > 1 && row > 0)
        if (board[row - 1][column - 1 * 2][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column - 1 * 2 + 65, 56 - row + 1);
            fsm[2 * sz] = 56 - row + 1;
            fsm[2 * sz + 1] = 65 + column - 2;

        };
    if (column > 1 && row > 0)
        if (abs(board[row - 1][column - 1 * 2][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column - 1 * 2 + 65, 56 - row + 1);
            fsm[2 * sz] = 56 - row + 1;
            fsm[2 * sz + 1] = 65 + column - 2;

        };
    /* Detects for the 1 o'clock of knight*/
    if (row > 1)
        if (board[row - 1 * 2][column + 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 1 + 65, 56 - row + 1 * 2);
            fsm[2 * sz] = 56 - row + 2;
            fsm[2 * sz + 1] = 65 + column + 1;

        };
    if (row > 1)
        if (abs(board[row - 1 * 2][column + 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 1 + 65, 56 - row + 1 * 2);
            fsm[2 * sz] = 56 - row + 2;
            fsm[2 * sz + 1] = 65 + column + 1;

        };
    /* Detects for the 4 o'clock of knight*/
    if (board[row + 1][column + 1 * 2][1] == '0') {
        /*Move If Empty*/
        sz++;
        printf("%d.%c%c ", sz, column + 65 + 1 * 2, 56 - row - 1);
        fsm[2 * sz] = 56 - row - 1;
        fsm[2 * sz + 1] = 65 + column + 2;

    };
    if (abs(board[row + 1][column + 1 * 2][0] - color) == 21) {
        /*Capture if counter color*/
        sz++;
        printf("%dX%c%c ", sz, column + 65 + 1 * 2, 56 - row - 1);
        fsm[2 * sz] = 56 - row - 1;
        fsm[2 * sz + 1] = 65 + column + 2;

    };
    /* Detects for the 7 o'clock of knight*/
    if (row < 7 && column > 0)
        if (board[row + 1 * 2][column - 1][1] == '0') {
            /*Move If Empty*/
            sz++;
            printf("%d.%c%c ", sz, column + 65 - 1, 56 - row - 1 * 2);
            fsm[2 * sz] = 56 - row - 2;
            fsm[2 * sz + 1] = 65 + column - 1;
        };
    if (row < 7 && column > 0)
        if (abs(board[row + 1 * 2][column - 1][0] - color) == 21) {
            /*Capture if counter color*/
            sz++;
            printf("%dX%c%c ", sz, column + 65 - 1, 56 - row - 1 * 2);
            fsm[2 * sz] = 56 - row - 1;
            fsm[2 * sz + 1] = 65 + column - 2;

        };
    printf("\n");
    /* Move! */
    int chs;
    while (1) {
        if (sz == 0) {
            return 0;
            break;
        };

        printf("Press\t");
        scanf("%d", & chs);
        if ((chs > sz) || (chs < 0)) /*User can not choose a move out of range*/
            printf("Excuse me? ");
        else {
            /*Move here*/
            capture(board, fsm, chs, s0, s1);
            break;
        };
    };
    return 1;
}
