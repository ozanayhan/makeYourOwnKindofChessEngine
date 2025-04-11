#include <stdio.h>
#include "chess.h"

// Function to find the minimum of 5 numbers
int findMin(int a, int b, int c, int d, int e)
{
    int min = a; // Assume the first number is the smallest

    if (b < min)
        min = b;
    if (c < min)
        min = c;
    if (d < min)
        min = d;
    if (e < min)
        min = e;

    return min;
}

// Function to find the maximum of 5 numbers
int findMax(int a, int b, int c, int d, int e)
{
    int max = a; // Assume the first number is the biggest

    if (b > max)
        max = b;
    if (c > max)
        max = c;
    if (d > max)
        max = d;
    if (e > max)
        max = e;

    return max;
}

// Function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // Choosing the last element as pivot
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// QuickSort function
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void getPiecePositions(unsigned int chessMatrix[8][8], unsigned int (*xPositionArray)[36], unsigned int (*yPositionArray)[36])
{
    for (unsigned int pieces = WROOK1; pieces <= BPROMOTION2; pieces++)
    {
        for (unsigned int j = 0; j < 8; j++)
        {
            for (unsigned int i = 0; i < 8; i++)
            {
                if (pieces == chessMatrix[j][i])
                {
                    (*xPositionArray)[pieces - 1] = i;
                    (*yPositionArray)[pieces - 1] = j;
                    goto outw;
                }
            }
        }
        (*xPositionArray)[pieces - 1] = NOTHING;
        (*yPositionArray)[pieces - 1] = NOTHING;
        outw:
        ;
    }
}

void updateChessMatrix(unsigned int (*chessMatrix)[8][8], unsigned int piecePlay, unsigned int pieceXLoc, unsigned int pieceYLoc, unsigned int pieceDestXLoc, unsigned int pieceDestYLoc)
{
    if (piecePlay == SHORT_CASTLE_W)
    {
        (*chessMatrix)[0][4] = NOTHING;
        (*chessMatrix)[0][5] = WROOK2;
        (*chessMatrix)[0][6] = WKING;
        (*chessMatrix)[0][7] = NOTHING;
    }
    else if (piecePlay == LONG_CASTLE_W)
    {
        (*chessMatrix)[0][0] = NOTHING;
        (*chessMatrix)[0][1] = NOTHING;
        (*chessMatrix)[0][2] = WKING;
        (*chessMatrix)[0][3] = WROOK1;
        (*chessMatrix)[0][4] = NOTHING;
    }
    if (piecePlay == SHORT_CASTLE_B)
    {
        (*chessMatrix)[7][4] = NOTHING;
        (*chessMatrix)[7][5] = BROOK2;
        (*chessMatrix)[7][6] = BKING;
        (*chessMatrix)[7][7] = NOTHING;
    }
    else if (piecePlay == LONG_CASTLE_B)
    {
        (*chessMatrix)[7][0] = NOTHING;
        (*chessMatrix)[7][1] = NOTHING;
        (*chessMatrix)[7][2] = BKING;
        (*chessMatrix)[7][3] = BROOK1;
        (*chessMatrix)[7][4] = NOTHING;
    }
    else if (piecePlay > WROOK2 && piecePlay < WPROMOTION1 && pieceDestYLoc == 7)
    {
        (*chessMatrix)[pieceDestYLoc][pieceDestXLoc] = WPROMOTION1;
        (*chessMatrix)[pieceYLoc][pieceXLoc] = NOTHING;
    }
    else if (piecePlay > BROOK2 && piecePlay < BPROMOTION1 && pieceDestYLoc == 0)
    {
        (*chessMatrix)[pieceDestYLoc][pieceDestXLoc] = BPROMOTION1;
        (*chessMatrix)[pieceYLoc][pieceXLoc] = NOTHING;
    }
    else if (((*chessMatrix)[pieceDestYLoc][pieceDestXLoc] >= BROOK1) && ((*chessMatrix)[pieceDestYLoc][pieceDestXLoc] <= BPROMOTION2))
    {
        (*chessMatrix)[pieceDestYLoc][pieceDestXLoc] = piecePlay;
        (*chessMatrix)[pieceYLoc][pieceXLoc] = NOTHING;
    }
    else if (((*chessMatrix)[pieceDestYLoc][pieceDestXLoc] >= WROOK1) && ((*chessMatrix)[pieceDestYLoc][pieceDestXLoc] <= WPROMOTION2))
    {
        (*chessMatrix)[pieceDestYLoc][pieceDestXLoc] = piecePlay;
        (*chessMatrix)[pieceYLoc][pieceXLoc] = NOTHING;
    }
    else if ((*chessMatrix)[pieceDestYLoc][pieceDestXLoc] == NOTHING)
    {
        (*chessMatrix)[pieceDestYLoc][pieceDestXLoc] = piecePlay;
        (*chessMatrix)[pieceYLoc][pieceXLoc] = NOTHING;
    }
}

void reverseChessNotation(unsigned char (*userMove)[10], unsigned int (*chessMatrix)[8][8], unsigned int *userPiecePlay, unsigned int *userPieceXLoc, unsigned int *userPieceYLoc, unsigned int *userPieceDestXLoc, unsigned int *userPieceDestYLoc)
{
    getPiecePositions((*chessMatrix), &xPositionArray, &yPositionArray);
    if ((*userMove)[1] == 88 || (*userMove)[1] == 120)
    {
        (*userPieceDestXLoc) = (*userMove)[2] - 97;
        (*userPieceDestYLoc)= (*userMove)[3] - 49;
    }
    else if ((*userMove)[0] > 96 && (*userMove)[0] < 105) {
        (*userPieceDestXLoc) = (*userMove)[0] - 97;
        (*userPieceDestYLoc)= (*userMove)[1] - 49;
    }
    else if ((*userMove)[0] > 65 && (*userMove)[0] < 83) {
        (*userPieceDestXLoc) = (*userMove)[1] - 97;
        (*userPieceDestYLoc)= (*userMove)[2] - 49;
    }


    if ((*userMove)[0] == 79 && (*userMove)[1] == 45 && (*userMove)[2] == 79 && (*userMove)[3] == 45)
    {
        // Long Castle
        (*userPiecePlay) = BKING;
        (*userPieceDestXLoc) = 2;
        (*userPieceDestYLoc)= 7;
        (*userPieceXLoc) = 4;
        (*userPieceYLoc)= 7;
        
    }
    else if ((*userMove)[0] == 79 && (*userMove)[1] == 45 && (*userMove)[2] == 79)
    {
        // Short Castle
        (*userPiecePlay) = BKING;
        (*userPieceDestXLoc) = 6;
        (*userPieceDestYLoc)= 7;
        (*userPieceXLoc) = 4;
        (*userPieceYLoc)= 7;
    }
    else if ((*userMove)[0] == 75)
    {
        // King Move
        (*userPiecePlay) = BKING;
        (*userPieceXLoc) = xPositionArray[BKING - 1];
        (*userPieceYLoc)= yPositionArray[BKING - 1];
    }
    else if ((*userMove)[0] == 81)
    {
        // Queen Move
        (*userPiecePlay) = BQUEEN;
        (*userPieceXLoc) = xPositionArray[BQUEEN - 1];
        (*userPieceYLoc)= yPositionArray[BQUEEN - 1];
    }
    else if ((*userMove)[0] == 82)
    {
        // Rook Move
        (*userPiecePlay) = BROOK1;
        (*userPieceXLoc) = xPositionArray[BROOK1 - 1];
        (*userPieceYLoc)= yPositionArray[BROOK1 - 1];
        if (((*userPieceXLoc) != (*userPieceDestXLoc)) && ((*userPieceYLoc) != (*userPieceDestYLoc))) {
            (*userPiecePlay) = BROOK2;
            (*userPieceXLoc) = xPositionArray[BROOK2 - 1];
            (*userPieceYLoc)= yPositionArray[BROOK2 - 1];
        }
        if (((*userPieceXLoc) != (*userPieceDestXLoc)) && ((*userPieceYLoc) != (*userPieceDestYLoc))) {
            (*userPiecePlay) = NOTHING;
        }
    }
    else if ((*userMove)[0] == 66)
    {
        // Bishop Move
        if (((*userPieceDestXLoc) + (*userPieceDestYLoc)) % 2) {
            (*userPiecePlay) = BBISHOP1;
            (*userPieceXLoc) = xPositionArray[BBISHOP1 - 1];
            (*userPieceYLoc)= yPositionArray[BBISHOP1 - 1];
        }
        else {
            (*userPiecePlay) = BBISHOP2;
            (*userPieceXLoc) = xPositionArray[BBISHOP2 - 1];
            (*userPieceYLoc)= yPositionArray[BBISHOP2 - 1];
        }
    }
    else if ((*userMove)[0] == 78)
    {
        // Knight Move
        (*userPiecePlay) = BKNIGHT1;
        (*userPieceXLoc) = xPositionArray[BKNIGHT1 - 1];
        (*userPieceYLoc)= yPositionArray[BKNIGHT1 - 1];
        if ((((*userPieceDestXLoc) - (*userPieceXLoc)) > 7 ? ((*userPieceXLoc) - (*userPieceDestXLoc)) : ((*userPieceDestXLoc) - (*userPieceXLoc))) + (((*userPieceDestYLoc) - (*userPieceYLoc)) > 7 ? ((*userPieceYLoc) - (*userPieceDestYLoc)) : ((*userPieceDestYLoc) - (*userPieceYLoc))) != 3 || (*userPieceDestYLoc) == (*userPieceYLoc) || (*userPieceDestXLoc) == (*userPieceXLoc)) {
            (*userPiecePlay) = BKNIGHT2;
            (*userPieceXLoc) = xPositionArray[BKNIGHT2 - 1];
            (*userPieceYLoc)= yPositionArray[BKNIGHT2 - 1];
        }
        if ((((*userPieceDestXLoc) - (*userPieceXLoc)) > 7 ? ((*userPieceXLoc) - (*userPieceDestXLoc)) : ((*userPieceDestXLoc) - (*userPieceXLoc))) + (((*userPieceDestYLoc) - (*userPieceYLoc)) > 7 ? ((*userPieceYLoc) - (*userPieceDestYLoc)) : ((*userPieceDestYLoc) - (*userPieceYLoc))) != 3 || (*userPieceDestYLoc) == (*userPieceYLoc) || (*userPieceDestXLoc) == (*userPieceXLoc)) {
            (*userPiecePlay) = NOTHING;
        }
    }
    else if ((*userMove)[0] > 96 && (*userMove)[0] < 105)
    {
        // Pawn Move
        if ((*userMove)[0] == 97) {
            (*userPiecePlay) = BPAWN1;
            (*userPieceXLoc) = xPositionArray[BPAWN1 - 1];
            (*userPieceYLoc)= yPositionArray[BPAWN1 - 1];
        }
        else if ((*userMove)[0] == 98) {
            (*userPiecePlay) = BPAWN2;
            (*userPieceXLoc) = xPositionArray[BPAWN2 - 1];
            (*userPieceYLoc)= yPositionArray[BPAWN2 - 1];
        }
        else if ((*userMove)[0] == 99) {
            (*userPiecePlay) = BPAWN3;
            (*userPieceXLoc) = xPositionArray[BPAWN3 - 1];
            (*userPieceYLoc)= yPositionArray[BPAWN3 - 1];
        }
        else if ((*userMove)[0] == 100) {
            (*userPiecePlay) = BPAWN4;
            (*userPieceXLoc) = xPositionArray[BPAWN4 - 1];
            (*userPieceYLoc)= yPositionArray[BPAWN4 - 1];
        }
        else if ((*userMove)[0] == 101) {
            (*userPiecePlay) = BPAWN5;
            (*userPieceXLoc) = xPositionArray[BPAWN5 - 1];
            (*userPieceYLoc)= yPositionArray[BPAWN5 - 1];
        }
        else if ((*userMove)[0] == 102) {
            (*userPiecePlay) = BPAWN6;
            (*userPieceXLoc) = xPositionArray[BPAWN6 - 1];
            (*userPieceYLoc)= yPositionArray[BPAWN6 - 1];
        }
        else if ((*userMove)[0] == 103) {
            (*userPiecePlay) = BPAWN7;
            (*userPieceXLoc) = xPositionArray[BPAWN7 - 1];
            (*userPieceYLoc)= yPositionArray[BPAWN7 - 1];
        }
        else if ((*userMove)[0] == 104) {
            (*userPiecePlay) = BPAWN8;
            (*userPieceXLoc) = xPositionArray[BPAWN8 - 1];
            (*userPieceYLoc)= yPositionArray[BPAWN8 - 1];
        }
    }

}

void chessNotation(unsigned int (*chessMatrix)[8][8], unsigned int piecePlay, unsigned int pieceXLoc, unsigned int pieceYLoc, unsigned int pieceDestXLoc, unsigned int pieceDestYLoc)
{
    printf("Move Played: ");
    if (piecePlay == WROOK1 || piecePlay == WROOK2 || piecePlay == BROOK1 || piecePlay == BROOK2)
        printf("R");
    if (piecePlay == WKNIGHT1 || piecePlay == WKNIGHT2 || piecePlay == BKNIGHT1 || piecePlay == BKNIGHT2)
        printf("N");
    if (piecePlay == WBISHOP1 || piecePlay == WBISHOP2 || piecePlay == BBISHOP1 || piecePlay == BBISHOP2)
        printf("B");
    if (piecePlay == WQUEEN || piecePlay == BQUEEN)
        printf("Q");
    if (piecePlay == WKING || piecePlay == BKING)
        printf("K");
    if (piecePlay == SHORT_CASTLE_W || piecePlay == SHORT_CASTLE_B)
        printf("O-O");
    if (piecePlay == LONG_CASTLE_W || piecePlay == LONG_CASTLE_B)
        printf("O-O-O");
    if ((((*chessMatrix)[pieceDestYLoc][pieceDestXLoc]) != NOTHING) && piecePlay != SHORT_CASTLE_W && piecePlay != LONG_CASTLE_W && piecePlay != SHORT_CASTLE_B && piecePlay != LONG_CASTLE_B)
    {
        if ((piecePlay > WROOK2 && piecePlay < WPROMOTION1) || (piecePlay > BROOK2 && piecePlay < BPROMOTION1))
            printf("%c", str[pieceXLoc]);
        printf("x");
    }
    else if (((piecePlay > WROOK2 && piecePlay < WPROMOTION1) || (piecePlay > BROOK2 && piecePlay < BPROMOTION1)) && pieceXLoc != pieceDestXLoc)
    {
        printf("%c", str[pieceXLoc]);
        printf("x");
    }
    if (piecePlay != SHORT_CASTLE_W && piecePlay != LONG_CASTLE_W && piecePlay != SHORT_CASTLE_B && piecePlay != LONG_CASTLE_B)
    {
        printf("%c", str[pieceDestXLoc]);
        printf("%d", pieceDestYLoc + 1);
    }
    printf(" \n");
}
void resetBoardMatrix(unsigned int (*BoardMatrix)[8][8])
{
    for (unsigned int j = 0; j < 8; j++)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
            (*BoardMatrix)[j][i] = 0;
        }
    }
}

void resetBoardMappings(unsigned int (*MappingMatrix)[36][5])
{
    for (unsigned int j = 0; j < 36; j++)
    {
        for (unsigned int i = 0; i < 5; i++)
        {
            (*MappingMatrix)[j][i] = 0;
        }
    }
}

void resetIterationArrays(unsigned int (*IterationArray)[3][300])
{
    for (unsigned int j = 0; j < 3; j++)
    {
        for (unsigned int i = 0; i < 300; i++)
        {
            (*IterationArray)[j][i] = 0;
        }
    }
}

void resetIterationIndex(unsigned int(*IterationIndex))
{
    (*IterationIndex) = 0;
}

void resetEvaluation(float(*Eval))
{
    (*Eval) = 0.0F;
}

void resetPositions(unsigned int (*PositionArray)[36])
{
    for (unsigned int i = 0; i < 36; i++)
    {
        (*PositionArray)[i] = NOTHING;
    }
}

void resetEval(void)
{

    resetBoardMatrix(&bAttackMatrix);
    resetBoardMatrix(&wAttackMatrix);
    resetBoardMappings(&ProtectionMapping);
    resetBoardMappings(&AttackMapping);

    resetBoardMatrix(&wRook1PositionalControl);
    resetBoardMatrix(&wRook1AttackMatrix);
    resetBoardMatrix(&wRook1ProtectionMatrix);
    resetBoardMatrix(&wKnight1PositionalControl);
    resetBoardMatrix(&wKnight1AttackMatrix);
    resetBoardMatrix(&wKnight1ProtectionMatrix);
    resetBoardMatrix(&wBishop1PositionalControl);
    resetBoardMatrix(&wBishop1AttackMatrix);
    resetBoardMatrix(&wBishop1ProtectionMatrix);
    resetBoardMatrix(&wQueenPositionalControl);
    resetBoardMatrix(&wQueenAttackMatrix);
    resetBoardMatrix(&wQueenProtectionMatrix);
    resetBoardMatrix(&wKingPositionalControl);
    resetBoardMatrix(&wKingAttackMatrix);
    resetBoardMatrix(&wKingProtectionMatrix);
    resetBoardMatrix(&wBishop2PositionalControl);
    resetBoardMatrix(&wBishop2AttackMatrix);
    resetBoardMatrix(&wBishop2ProtectionMatrix);
    resetBoardMatrix(&wKnight2PositionalControl);
    resetBoardMatrix(&wKnight2AttackMatrix);
    resetBoardMatrix(&wKnight2ProtectionMatrix);
    resetBoardMatrix(&wRook2PositionalControl);
    resetBoardMatrix(&wRook2AttackMatrix);
    resetBoardMatrix(&wRook2ProtectionMatrix);
    resetBoardMatrix(&wPawn1PositionalControl);
    resetBoardMatrix(&wPawn1AttackMatrix);
    resetBoardMatrix(&wPawn1ProtectionMatrix);
    resetBoardMatrix(&wPawn2PositionalControl);
    resetBoardMatrix(&wPawn2AttackMatrix);
    resetBoardMatrix(&wPawn2ProtectionMatrix);
    resetBoardMatrix(&wPawn3PositionalControl);
    resetBoardMatrix(&wPawn3AttackMatrix);
    resetBoardMatrix(&wPawn3ProtectionMatrix);
    resetBoardMatrix(&wPawn4PositionalControl);
    resetBoardMatrix(&wPawn4AttackMatrix);
    resetBoardMatrix(&wPawn4ProtectionMatrix);
    resetBoardMatrix(&wPawn5PositionalControl);
    resetBoardMatrix(&wPawn5AttackMatrix);
    resetBoardMatrix(&wPawn5ProtectionMatrix);
    resetBoardMatrix(&wPawn6PositionalControl);
    resetBoardMatrix(&wPawn6AttackMatrix);
    resetBoardMatrix(&wPawn6ProtectionMatrix);
    resetBoardMatrix(&wPawn7PositionalControl);
    resetBoardMatrix(&wPawn7AttackMatrix);
    resetBoardMatrix(&wPawn7ProtectionMatrix);
    resetBoardMatrix(&wPawn8PositionalControl);
    resetBoardMatrix(&wPawn8AttackMatrix);
    resetBoardMatrix(&wPawn8ProtectionMatrix);

    resetBoardMatrix(&bRook1PositionalControl);
    resetBoardMatrix(&bRook1AttackMatrix);
    resetBoardMatrix(&bRook1ProtectionMatrix);
    resetBoardMatrix(&bKnight1PositionalControl);
    resetBoardMatrix(&bKnight1AttackMatrix);
    resetBoardMatrix(&bKnight1ProtectionMatrix);
    resetBoardMatrix(&bBishop1PositionalControl);
    resetBoardMatrix(&bBishop1AttackMatrix);
    resetBoardMatrix(&bBishop1ProtectionMatrix);
    resetBoardMatrix(&bQueenPositionalControl);
    resetBoardMatrix(&bQueenAttackMatrix);
    resetBoardMatrix(&bQueenProtectionMatrix);
    resetBoardMatrix(&bKingPositionalControl);
    resetBoardMatrix(&bKingAttackMatrix);
    resetBoardMatrix(&bKingProtectionMatrix);
    resetBoardMatrix(&bBishop2PositionalControl);
    resetBoardMatrix(&bBishop2AttackMatrix);
    resetBoardMatrix(&bBishop2ProtectionMatrix);
    resetBoardMatrix(&bKnight2PositionalControl);
    resetBoardMatrix(&bKnight2AttackMatrix);
    resetBoardMatrix(&bKnight2ProtectionMatrix);
    resetBoardMatrix(&bRook2PositionalControl);
    resetBoardMatrix(&bRook2AttackMatrix);
    resetBoardMatrix(&bRook2ProtectionMatrix);
    resetBoardMatrix(&bPawn1PositionalControl);
    resetBoardMatrix(&bPawn1AttackMatrix);
    resetBoardMatrix(&bPawn1ProtectionMatrix);
    resetBoardMatrix(&bPawn2PositionalControl);
    resetBoardMatrix(&bPawn2AttackMatrix);
    resetBoardMatrix(&bPawn2ProtectionMatrix);
    resetBoardMatrix(&bPawn3PositionalControl);
    resetBoardMatrix(&bPawn3AttackMatrix);
    resetBoardMatrix(&bPawn3ProtectionMatrix);
    resetBoardMatrix(&bPawn4PositionalControl);
    resetBoardMatrix(&bPawn4AttackMatrix);
    resetBoardMatrix(&bPawn4ProtectionMatrix);
    resetBoardMatrix(&bPawn5PositionalControl);
    resetBoardMatrix(&bPawn5AttackMatrix);
    resetBoardMatrix(&bPawn5ProtectionMatrix);
    resetBoardMatrix(&bPawn6PositionalControl);
    resetBoardMatrix(&bPawn6AttackMatrix);
    resetBoardMatrix(&bPawn6ProtectionMatrix);
    resetBoardMatrix(&bPawn7PositionalControl);
    resetBoardMatrix(&bPawn7AttackMatrix);
    resetBoardMatrix(&bPawn7ProtectionMatrix);
    resetBoardMatrix(&bPawn8PositionalControl);
    resetBoardMatrix(&bPawn8AttackMatrix);
    resetBoardMatrix(&bPawn8ProtectionMatrix);
}


void processPieceActivity(unsigned int chessMatrix[8][8], unsigned int pieces, unsigned int PiecexPosition, unsigned int PieceyPosition, unsigned int (*PositionalControl)[8][8], unsigned int (*ProtectionMatrix)[8][8], unsigned int (*AttackMatrix)[8][8], unsigned int (*ProtectionMapping)[36][5], unsigned int (*AttackMapping)[36][5], unsigned int (*iterationArrayW)[3][300], unsigned int(*iterationIndexW), unsigned int (*iterationArrayB)[3][300], unsigned int(*iterationIndexB))
{
    flgRookPiece = pieces == WROOK1 || pieces == WROOK2 || pieces == BROOK1 || pieces == BROOK2;
    flgKnightPiece = pieces == WKNIGHT1 || pieces == WKNIGHT2 || pieces == BKNIGHT1 || pieces == BKNIGHT2;
    flgBishopPiece = pieces == WBISHOP1 || pieces == WBISHOP2 || pieces == BBISHOP1 || pieces == BBISHOP2;
    flgQueenPiece = pieces == WQUEEN || pieces == BQUEEN || pieces == WPROMOTION1 || pieces == WPROMOTION2 || pieces == BPROMOTION1 || pieces == WPROMOTION2;
    flgKingPiece = pieces == WKING || pieces == BKING;
    flgPawnPiece = (pieces > WROOK2 && pieces < WPROMOTION1) || (pieces > BROOK2 && pieces < BPROMOTION1);
    flgRangePiece = flgRookPiece || flgBishopPiece || flgQueenPiece;
    flgWhitePiece = (pieces >= WROOK1 && pieces <= WPROMOTION2);
    flgBlackPiece = (pieces >= BROOK1 && pieces <= BPROMOTION2);
    searchIndex = 1;
    unsigned int i = 0;
    unsigned int pieceAtPosition = 0;
    for (int searchDirection = 0; searchDirection < searchDimension[pieces - 1]; searchDirection++)
    {
        while (1)
        {
            if (flgRookPiece)
            {
                xIndex = searchDirection == 0 ? PiecexPosition + searchIndex : (searchDirection == 1 ? PiecexPosition - searchIndex : PiecexPosition);
                yIndex = searchDirection == 2 ? PieceyPosition + searchIndex : (searchDirection == 3 ? PieceyPosition - searchIndex : PieceyPosition);
            }
            else if (flgKnightPiece)
            {
                xIndex = (searchDirection == 0 || searchDirection == 3) ? PiecexPosition + 1 : (searchDirection == 1 || searchDirection == 2) ? PiecexPosition + 2
                                                                                           : (searchDirection == 4 || searchDirection == 7)   ? PiecexPosition - 1
                                                                                           : (searchDirection == 5 || searchDirection == 6)   ? PiecexPosition - 2
                                                                                                                                              : PiecexPosition;

                yIndex = (searchDirection == 0 || searchDirection == 7) ? PieceyPosition + 2 : (searchDirection == 1 || searchDirection == 6) ? PieceyPosition + 1
                                                                                           : (searchDirection == 2 || searchDirection == 5)   ? PieceyPosition - 1
                                                                                           : (searchDirection == 3 || searchDirection == 4)   ? PieceyPosition - 2
                                                                                                                                              : PieceyPosition;
            }
            else if (flgBishopPiece)
            {
                xIndex = searchDirection == 0 || searchDirection == 1 ? PiecexPosition + searchIndex : (searchDirection == 2 || searchDirection == 3 ? PiecexPosition - searchIndex : PiecexPosition);
                yIndex = searchDirection == 0 || searchDirection == 3 ? PieceyPosition + searchIndex : (searchDirection == 1 || searchDirection == 2 ? PieceyPosition - searchIndex : PieceyPosition);
            }
            else if (flgQueenPiece || flgKingPiece)
            {
                xIndex = searchDirection == 0 || searchDirection == 1 || searchDirection == 2 ? PiecexPosition + searchIndex : (searchDirection == 4 || searchDirection == 5 || searchDirection == 6 ? PiecexPosition - searchIndex : PiecexPosition);
                yIndex = searchDirection == 0 || searchDirection == 6 || searchDirection == 7 ? PieceyPosition + searchIndex : (searchDirection == 2 || searchDirection == 3 || searchDirection == 4 ? PieceyPosition - searchIndex : PieceyPosition);
            }
            if (flgPawnPiece)
            {
                xIndex = searchDirection == 0 ? PiecexPosition + 1 : PiecexPosition - 1;
                yIndex = flgWhitePiece ? PieceyPosition + 1 : PieceyPosition - 1;
            }

            if ((xIndex >= 8 || yIndex >= 8))
            {
                searchIndex = 1;
                break;
            }
            pieceAtPosition = chessMatrix[yIndex][xIndex];
            if (pieceAtPosition == NOTHING)
            {
                (*PositionalControl)[yIndex][xIndex] = 1;
                if (flgWhitePiece && !flgPawnPiece)
                {
                    (*iterationArrayW)[0][(*iterationIndexW)] = pieces;
                    (*iterationArrayW)[1][(*iterationIndexW)] = xIndex;
                    (*iterationArrayW)[2][(*iterationIndexW)] = yIndex;
                    ++(*iterationIndexW);
                }
                else if (flgBlackPiece && !flgPawnPiece)
                {
                    (*iterationArrayB)[0][(*iterationIndexB)] = pieces;
                    (*iterationArrayB)[1][(*iterationIndexB)] = xIndex;
                    (*iterationArrayB)[2][(*iterationIndexB)] = yIndex;
                    ++(*iterationIndexB);
                }

                if (flgRangePiece)
                {
                    searchIndex++;
                }
                else
                {
                    searchIndex = 1;
                    break;
                }
            }
            else if ((flgWhitePiece && (pieceAtPosition <= WPROMOTION2)) || (flgBlackPiece && (pieceAtPosition > WPROMOTION2)))
            {
                if ((flgWhitePiece && pieceAtPosition != WKING) || (flgBlackPiece && pieceAtPosition != BKING))
                {
                    (*ProtectionMatrix)[yIndex][xIndex] = pieceAtPosition;
                    i = 0;
                    while ((*ProtectionMapping)[(pieceAtPosition - 1)][i] && i < 6)
                    {
                        i++;
                    }
                    if (i < 6)
                        (*ProtectionMapping)[(pieceAtPosition - 1)][i] = pieces;
                }
                searchIndex = 1;
                break;
            }
            else if ((flgWhitePiece && (pieceAtPosition > WPROMOTION2)) || (flgBlackPiece && (pieceAtPosition <= WPROMOTION2)))
            {
                (*AttackMatrix)[yIndex][xIndex] = pieceAtPosition;
                if (flgWhitePiece)
                {
                    (*iterationArrayW)[0][(*iterationIndexW)] = pieces;
                    (*iterationArrayW)[1][(*iterationIndexW)] = xIndex;
                    (*iterationArrayW)[2][(*iterationIndexW)] = yIndex;
                    ++(*iterationIndexW);
                }
                else if (flgBlackPiece)
                {
                    (*iterationArrayB)[0][(*iterationIndexB)] = pieces;
                    (*iterationArrayB)[1][(*iterationIndexB)] = xIndex;
                    (*iterationArrayB)[2][(*iterationIndexB)] = yIndex;
                    ++(*iterationIndexB);
                }
                i = 0;
                while ((*AttackMapping)[(pieceAtPosition - 1)][i] && i < 6)
                {
                    i++;
                }
                if (i < 6)
                    (*AttackMapping)[(pieceAtPosition - 1)][i] = pieces;
                searchIndex = 1;
                break;
            }
        }
    }
}

void materialBalance(unsigned int (*chessMatrix)[8][8], unsigned int (*chessMatrixTemp)[8][8], float(*materialEval), unsigned int (*wAttackMatrix)[8][8], unsigned int (*bAttackMatrix)[8][8], unsigned int (*ProtectionMapping)[36][5], unsigned int (*AttackMapping)[36][5])
{
    wMaterialCount = 0;
    bMaterialCount = 0;
    wMaxMaterialGain = 0;
    wMaterialGain = 0;
    for (unsigned int j = 0; j < 8; j++)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
            if ((*chessMatrix)[j][i] >= WROOK1 && (*chessMatrix)[j][i] <= WPROMOTION2)
            {
                wMaterialCount += ValPcs[((*chessMatrix)[j][i] - 1)];
            }
            if ((*chessMatrix)[j][i] >= BROOK1 && (*chessMatrix)[j][i] <= BPROMOTION2)
            {
                bMaterialCount += ValPcs[((*chessMatrix)[j][i] - 1)];
            }

            if ((*wAttackMatrix)[j][i])
            {
                wAttackedPiece = (*chessMatrixTemp)[j][i];
                bNumProtectingPiece = 0;
                wNumAttackingPiece = 0;
                for (unsigned int k = 0; k < 5; k++)
                {
                    protectionIndex = ((*ProtectionMapping)[wAttackedPiece - 1][k]);
                    attackIndex = ((*AttackMapping)[wAttackedPiece - 1][k]);
                    ProtectionArray[k] = protectionIndex ? ValPcs[protectionIndex - 1] : NOTHING;
                    AttackArray[k] = attackIndex ? ValPcs[attackIndex - 1] : NOTHING;
                    if (protectionIndex)
                        bNumProtectingPiece = k + 1;
                    if (attackIndex)
                        wNumAttackingPiece = k + 1;
                }
                quickSort(ProtectionArray, 0, 4);
                quickSort(AttackArray, 0, 4);

                for (unsigned int k = 0; k < 5; k++)
                {
                    ProtectionArray[k] = ProtectionArray[k] == NOTHING ? 0 : ProtectionArray[k];
                    AttackArray[k] = AttackArray[k] == NOTHING ? 0 : AttackArray[k];
                }

                if (wNumAttackingPiece < bNumProtectingPiece)
                {
                    wMaterialGainCapture1 = ValPcs[wAttackedPiece - 1] - AttackArray[0];
                    wMaterialGainCapture2 = wMaterialGainCapture1 + (AttackArray[1] ? ProtectionArray[0] : 0) - AttackArray[1];
                    wMaterialGainCapture3 = wMaterialGainCapture2 + (AttackArray[2] ? ProtectionArray[1] : 0) - AttackArray[2];
                    wMaterialGainCapture4 = wMaterialGainCapture3 + (AttackArray[3] ? ProtectionArray[2] : 0) - AttackArray[3];
                    wMaterialGainCapture5 = wMaterialGainCapture4 + (AttackArray[4] ? ProtectionArray[3] : 0) - AttackArray[4];
                }
                else
                {
                    wMaterialGainCapture1 = ValPcs[wAttackedPiece - 1];
                    wMaterialGainCapture2 = wMaterialGainCapture1 - (ProtectionArray[0] ? AttackArray[0] : 0) + ProtectionArray[0];
                    wMaterialGainCapture3 = wMaterialGainCapture2 - (ProtectionArray[1] ? AttackArray[1] : 0) + ProtectionArray[1];
                    wMaterialGainCapture4 = wMaterialGainCapture3 - (ProtectionArray[2] ? AttackArray[2] : 0) + ProtectionArray[2];
                    wMaterialGainCapture5 = wMaterialGainCapture4 - (ProtectionArray[3] ? AttackArray[3] : 0) + ProtectionArray[3];
                }
                wMaterialGain = findMin(wMaterialGainCapture1, wMaterialGainCapture2, wMaterialGainCapture3, wMaterialGainCapture4, wMaterialGainCapture5);
                wMaterialGain = wMaterialGain < 0 ? 0 : wMaterialGain;
                wMaxMaterialGain = wMaterialGain > wMaxMaterialGain ? wMaterialGain : wMaxMaterialGain;
            }

            for (unsigned int k = 0; k < 5; k++)
            {
                ProtectionArray[k] = 0;
                AttackArray[k] = 0;
            }
            wNumProtectingPiece = 0;
            bNumAttackingPiece = 0;
            wMaxMaterialLoss = 0;
            wMaterialLoss = 0;
            if ((*bAttackMatrix)[j][i])
            {
                bAttackedPiece = (*chessMatrixTemp)[j][i];
                for (unsigned int k = 0; k < 5; k++)
                {
                    protectionIndex = ((*ProtectionMapping)[bAttackedPiece - 1][k]);
                    attackIndex = ((*AttackMapping)[bAttackedPiece - 1][k]);
                    ProtectionArray[k] = protectionIndex ? ValPcs[protectionIndex - 1] : NOTHING;
                    AttackArray[k] = attackIndex ? ValPcs[attackIndex - 1] : NOTHING;
                    if (protectionIndex)
                        wNumProtectingPiece = k + 1;
                    if (attackIndex)
                        bNumAttackingPiece = k + 1;
                }
                quickSort(ProtectionArray, 0, 4);
                quickSort(AttackArray, 0, 4);

                for (unsigned int k = 0; k < 5; k++)
                {
                    ProtectionArray[k] = ProtectionArray[k] == NOTHING ? 0 : ProtectionArray[k];
                    AttackArray[k] = AttackArray[k] == NOTHING ? 0 : AttackArray[k];
                }

                if (bNumAttackingPiece > wNumProtectingPiece)
                {
                    wMaterialLossCapture1 = -ValPcs[bAttackedPiece - 1];
                    wMaterialLossCapture2 = wMaterialLossCapture1 + (ProtectionArray[0] ? AttackArray[0] : 0) - ProtectionArray[0];
                    wMaterialLossCapture3 = wMaterialLossCapture2 + (ProtectionArray[1] ? AttackArray[1] : 0) - ProtectionArray[1];
                    wMaterialLossCapture4 = wMaterialLossCapture3 + (ProtectionArray[2] ? AttackArray[2] : 0) - ProtectionArray[2];
                    wMaterialLossCapture5 = wMaterialLossCapture4 + (ProtectionArray[3] ? AttackArray[3] : 0) - ProtectionArray[3];
                }
                else
                {
                    wMaterialLossCapture1 = -ValPcs[bAttackedPiece - 1] + AttackArray[0];
                    wMaterialLossCapture2 = wMaterialLossCapture1 + AttackArray[1] - (AttackArray[1] ? ProtectionArray[0] : 0);
                    wMaterialLossCapture3 = wMaterialLossCapture2 + AttackArray[2] - (AttackArray[2] ? ProtectionArray[1] : 0);
                    wMaterialLossCapture4 = wMaterialLossCapture3 + AttackArray[3] - (AttackArray[3] ? ProtectionArray[2] : 0);
                    wMaterialLossCapture5 = wMaterialLossCapture4 + AttackArray[4] - (AttackArray[4] ? ProtectionArray[3] : 0);
                }
                wMaterialLoss = findMax(wMaterialLossCapture1, wMaterialLossCapture2, wMaterialLossCapture3, wMaterialLossCapture4, wMaterialLossCapture5);
                wMaterialLoss = wMaterialLoss > 0 ? 0 : wMaterialLoss;
                wMaxMaterialLoss = wMaterialLoss < wMaxMaterialLoss ? wMaterialLoss : wMaxMaterialLoss;
            }
        }
    }
    wMaterialBalance = (float)wMaterialCount - (float)bMaterialCount;
    (*materialEval) = wMaterialBalance + (float)wMaxMaterialGain + (float)wMaxMaterialLoss;
    // printf("Material Evaluation: %f\n", *materialEval);
}

void processBoardPosition(unsigned int chessMatrix[8][8], float(*positionEval), unsigned int (*wAttackMatrix)[8][8], unsigned int (*bAttackMatrix)[8][8], unsigned int (*iterationArrayW)[3][300], unsigned int(*iterationIndexW), unsigned int (*iterationArrayB)[3][300], unsigned int(*iterationIndexB))
{
    territoryIndexW = 0;
    territoryIndexB = 0;
    getPiecePositions(chessMatrix, &xPositionArray, &yPositionArray);
    (*iterationIndexW) = 0;
    (*iterationIndexB) = 0;
    for (unsigned int pieces = WROOK1; pieces <= BPROMOTION2; pieces++)
    {
        if (xPositionArray[pieces - 1] == NOTHING || yPositionArray[pieces - 1] == NOTHING)
            continue;
        PiecexPosition = xPositionArray[pieces - 1];
        PieceyPosition = yPositionArray[pieces - 1];
        switch (pieces)
        {
        case WROOK1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wRook1PositionalControl, &wRook1ProtectionMatrix, &wRook1AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WKNIGHT1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wKnight1PositionalControl, &wKnight1ProtectionMatrix, &wKnight1AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WBISHOP1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wBishop1PositionalControl, &wBishop1ProtectionMatrix, &wBishop1AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WQUEEN:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wQueenPositionalControl, &wQueenProtectionMatrix, &wQueenAttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WKING:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wKingPositionalControl, &wKingProtectionMatrix, &wKingAttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WBISHOP2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wBishop2PositionalControl, &wBishop2ProtectionMatrix, &wBishop2AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WKNIGHT2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wKnight2PositionalControl, &wKnight2ProtectionMatrix, &wKnight2AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WROOK2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wRook2PositionalControl, &wRook2ProtectionMatrix, &wRook2AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WPAWN1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn1PositionalControl, &wPawn1ProtectionMatrix, &wPawn1AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WPAWN2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn2PositionalControl, &wPawn2ProtectionMatrix, &wPawn2AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WPAWN3:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn3PositionalControl, &wPawn3ProtectionMatrix, &wPawn3AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WPAWN4:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn4PositionalControl, &wPawn4ProtectionMatrix, &wPawn4AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WPAWN5:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn5PositionalControl, &wPawn5ProtectionMatrix, &wPawn5AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WPAWN6:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn6PositionalControl, &wPawn6ProtectionMatrix, &wPawn6AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WPAWN7:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn7PositionalControl, &wPawn7ProtectionMatrix, &wPawn7AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case WPAWN8:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn8PositionalControl, &wPawn8ProtectionMatrix, &wPawn8AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;

        case BROOK1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bRook1PositionalControl, &bRook1ProtectionMatrix, &bRook1AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BKNIGHT1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bKnight1PositionalControl, &bKnight1ProtectionMatrix, &bKnight1AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BBISHOP1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bBishop1PositionalControl, &bBishop1ProtectionMatrix, &bBishop1AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BQUEEN:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bQueenPositionalControl, &bQueenProtectionMatrix, &bQueenAttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BKING:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bKingPositionalControl, &bKingProtectionMatrix, &bKingAttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BBISHOP2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bBishop2PositionalControl, &bBishop2ProtectionMatrix, &bBishop2AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BKNIGHT2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bKnight2PositionalControl, &bKnight2ProtectionMatrix, &bKnight2AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BROOK2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bRook2PositionalControl, &bRook2ProtectionMatrix, &bRook2AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BPAWN1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn1PositionalControl, &bPawn1ProtectionMatrix, &bPawn1AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BPAWN2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn2PositionalControl, &bPawn2ProtectionMatrix, &bPawn2AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BPAWN3:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn3PositionalControl, &bPawn3ProtectionMatrix, &bPawn3AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BPAWN4:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn4PositionalControl, &bPawn4ProtectionMatrix, &bPawn4AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BPAWN5:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn5PositionalControl, &bPawn5ProtectionMatrix, &bPawn5AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BPAWN6:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn6PositionalControl, &bPawn6ProtectionMatrix, &bPawn6AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BPAWN7:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn7PositionalControl, &bPawn7ProtectionMatrix, &bPawn7AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        case BPAWN8:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn8PositionalControl, &bPawn8ProtectionMatrix, &bPawn8AttackMatrix, &ProtectionMapping, &AttackMapping, iterationArrayW, iterationIndexW, iterationArrayB, iterationIndexB);
            break;
        }
    }

    wTotNumSqControlled = 0;
    wTotNumPcsProtected = 0;
    wTotNumPcsAttacked = 0;
    bTotNumSqControlled = 0;
    bTotNumPcsProtected = 0;
    bTotNumPcsAttacked = 0;
    wTotNumPcsEnPrise = 0;
    bTotNumPcsEnPrise = 0;
    wValPcsAttack = 0;
    bValPcsAttack = 0;
    wValPcsProtect = 0;
    bValPcsProtect = 0;

    for (unsigned int i = WROOK1; i < WPROMOTION2; i++)
    {
        if (yPositionArray[i] != NOTHING)
            territoryIndexW += yPositionArray[i];
    }
    for (unsigned int i = BROOK1; i < BPROMOTION2; i++)
    {
        if (yPositionArray[i] != NOTHING)
            territoryIndexB += (7 - yPositionArray[i]);
    }
    wMaterialCount = 0;
    bMaterialCount = 0;
    for (unsigned int j = 0; j < 8; j++)
    {
        for (unsigned int i = 0; i < 8; i++)
        {

            if ((chessMatrix)[j][i] >= WROOK1 && (chessMatrix)[j][i] <= WPROMOTION2)
            {
                wMaterialCount += ValPcs[((chessMatrix)[j][i] - 1)];
            }
            if ((chessMatrix)[j][i] >= BROOK1 && (chessMatrix)[j][i] <= BPROMOTION2)
            {
                bMaterialCount += ValPcs[((chessMatrix)[j][i] - 1)];
            }

            wPositionalControl[j][i] = wRook1PositionalControl[j][i] + wKnight1PositionalControl[j][i] +
                                       wBishop1PositionalControl[j][i] + wQueenPositionalControl[j][i] + wKingPositionalControl[j][i] +
                                       wBishop2PositionalControl[j][i] + wKnight2PositionalControl[j][i] + wRook2PositionalControl[j][i] +
                                       wPawn1PositionalControl[j][i] + wPawn2PositionalControl[j][i] + wPawn3PositionalControl[j][i] +
                                       wPawn4PositionalControl[j][i] + wPawn5PositionalControl[j][i] + wPawn6PositionalControl[j][i] +
                                       wPawn7PositionalControl[j][i] + wPawn8PositionalControl[j][i];

            wTotNumSqControlled += !!wPositionalControl[j][i];

            wProtectionMatrix[j][i] = !!wRook1ProtectionMatrix[j][i] + !!wKnight1ProtectionMatrix[j][i] +
                                      !!wBishop1ProtectionMatrix[j][i] + !!wQueenProtectionMatrix[j][i] + !!wKingProtectionMatrix[j][i] +
                                      !!wBishop2ProtectionMatrix[j][i] + !!wKnight2ProtectionMatrix[j][i] + !!wRook2ProtectionMatrix[j][i] +
                                      !!wPawn1ProtectionMatrix[j][i] + !!wPawn2ProtectionMatrix[j][i] + !!wPawn3ProtectionMatrix[j][i] +
                                      !!wPawn4ProtectionMatrix[j][i] + !!wPawn5ProtectionMatrix[j][i] + !!wPawn6ProtectionMatrix[j][i] +
                                      !!wPawn7ProtectionMatrix[j][i] + !!wPawn8ProtectionMatrix[j][i];

            wTotNumPcsProtected += !!wProtectionMatrix[j][i];

            (*wAttackMatrix)[j][i] = !!wRook1AttackMatrix[j][i] + !!wKnight1AttackMatrix[j][i] +
                                     !!wBishop1AttackMatrix[j][i] + !!wQueenAttackMatrix[j][i] + !!wKingAttackMatrix[j][i] +
                                     !!wBishop2AttackMatrix[j][i] + !!wKnight2AttackMatrix[j][i] + !!wRook2AttackMatrix[j][i] +
                                     !!wPawn1AttackMatrix[j][i] + !!wPawn2AttackMatrix[j][i] + !!wPawn3AttackMatrix[j][i] +
                                     !!wPawn4AttackMatrix[j][i] + !!wPawn5AttackMatrix[j][i] + !!wPawn6AttackMatrix[j][i] +
                                     !!wPawn7AttackMatrix[j][i] + !!wPawn8AttackMatrix[j][i];

            wTotNumPcsAttacked += !!(*wAttackMatrix)[j][i];

            bPositionalControl[j][i] = bRook1PositionalControl[j][i] + bKnight1PositionalControl[j][i] +
                                       bBishop1PositionalControl[j][i] + bQueenPositionalControl[j][i] + bKingPositionalControl[j][i] +
                                       bBishop2PositionalControl[j][i] + bKnight2PositionalControl[j][i] + bRook2PositionalControl[j][i] +
                                       bPawn1PositionalControl[j][i] + bPawn2PositionalControl[j][i] + bPawn3PositionalControl[j][i] +
                                       bPawn4PositionalControl[j][i] + bPawn5PositionalControl[j][i] + bPawn6PositionalControl[j][i] +
                                       bPawn7PositionalControl[j][i] + bPawn8PositionalControl[j][i];

            bTotNumSqControlled += !!bPositionalControl[j][i];

            bProtectionMatrix[j][i] = !!bRook1ProtectionMatrix[j][i] + !!bKnight1ProtectionMatrix[j][i] +
                                      !!bBishop1ProtectionMatrix[j][i] + !!bQueenProtectionMatrix[j][i] + !!bKingProtectionMatrix[j][i] +
                                      !!bBishop2ProtectionMatrix[j][i] + !!bKnight2ProtectionMatrix[j][i] + !!bRook2ProtectionMatrix[j][i] +
                                      !!bPawn1ProtectionMatrix[j][i] + !!bPawn2ProtectionMatrix[j][i] + !!bPawn3ProtectionMatrix[j][i] +
                                      !!bPawn4ProtectionMatrix[j][i] + !!bPawn5ProtectionMatrix[j][i] + !!bPawn6ProtectionMatrix[j][i] +
                                      !!bPawn7ProtectionMatrix[j][i] + !!bPawn8ProtectionMatrix[j][i];

            bTotNumPcsProtected += !!bProtectionMatrix[j][i];

            (*bAttackMatrix)[j][i] = !!bRook1AttackMatrix[j][i] + !!bKnight1AttackMatrix[j][i] +
                                     !!bBishop1AttackMatrix[j][i] + !!bQueenAttackMatrix[j][i] + !!bKingAttackMatrix[j][i] +
                                     !!bBishop2AttackMatrix[j][i] + !!bKnight2AttackMatrix[j][i] + !!bRook2AttackMatrix[j][i] +
                                     !!bPawn1AttackMatrix[j][i] + !!bPawn2AttackMatrix[j][i] + !!bPawn3AttackMatrix[j][i] +
                                     !!bPawn4AttackMatrix[j][i] + !!bPawn5AttackMatrix[j][i] + !!bPawn6AttackMatrix[j][i] +
                                     !!bPawn7AttackMatrix[j][i] + !!bPawn8AttackMatrix[j][i];

            bTotNumPcsAttacked += !!(*bAttackMatrix)[j][i];

            wTotNumPcsEnPrise += ((*bAttackMatrix)[j][i] - wProtectionMatrix[j][i]) > 0;
            bTotNumPcsEnPrise += ((*wAttackMatrix)[j][i] - bProtectionMatrix[j][i]) > 0;

            wValPcsAttack += (!!(*wAttackMatrix)[j][i]) * ValPcsPos[(chessMatrix[j][i]) - 1];
            bValPcsAttack += (!!(*bAttackMatrix)[j][i]) * ValPcsPos[(chessMatrix[j][i]) - 1];
            wValPcsProtect += (!!wProtectionMatrix[j][i]) * ValPcsPos[(chessMatrix[j][i]) - 1];
            bValPcsProtect += (!!bProtectionMatrix[j][i]) * ValPcsPos[(chessMatrix[j][i]) - 1];
        }
    }
    (*positionEval) = (((float)wTotNumSqControlled - (float)bTotNumSqControlled) * VAL_SINGLE_SQUARE) +
                      (((float)wTotNumPcsAttacked - (float)bTotNumPcsAttacked) * VAL_ATTACKED_PIECE) +
                      (((float)wTotNumPcsProtected - (float)bTotNumPcsProtected) * VAL_PROTECTED_PIECE) +
                      (((float)wValPcsAttack - (float)bValPcsAttack) * VAL_ATTACKED_PIECE_VALUE) +
                      (((float)territoryIndexW - (float)territoryIndexB) * VAL_TERRITORY_VALUE) +
                      (((float)bTotNumPcsEnPrise - (float)wTotNumPcsEnPrise) * VAL_ENPRISE_VALUE) +
                      ((float)wMaterialCount - (float)bMaterialCount) * 0.5F +
                      (((float)wValPcsProtect - (float)bValPcsProtect) * VAL_PROTECTED_PIECE_VALUE);

    // printf("Number of Squares Controlled by White: %d\n", wTotNumSqControlled);
    // printf("Bumber of Squares Controlled by Black: %d\n", bTotNumSqControlled);
    // printf("Number of Black Pieces Attacked: %d\n", wTotNumPcsAttacked);
    // printf("Number of White Pieces Attacked: %d\n", bTotNumPcsAttacked);
    // printf("Number of White Pieces Protected: %d\n", wTotNumPcsProtected);
    // printf("Number of Black Pieces Protected: %d\n", bTotNumPcsProtected);
    // printf("Value of Black Pieces Attacked: %d\n", wValPcsAttack);
    // printf("Value of White Pieces Attacked: %d\n", bValPcsAttack);
    // printf("Value of White Pieces Protected: %d\n", wValPcsProtect);
    // printf("Value of Black Pieces Protected: %d\n", bValPcsProtect);
    // printf("Position Evaluation: %f\n", *positionEval);
}

int main(void)
{
    unsigned int previousMove = 0;
    for (unsigned int t = 0; t < 25; t++)
    {
        overallEval = 0.0F;
        newEval = 0.0F;
        deltaEval = 0.0F;
        blackBestMoveEval = 1100.0F;
        whiteBestMoveEval = -1100.0F;
        whiteTempBestMoveEval = -1100.0F;
        processBoardPosition(chessMatrix, &positionEval, &wAttackMatrix, &bAttackMatrix, &iterationArrayW, &iterationIndexW, &iterationArrayB, &iterationIndexB);

        materialBalance(&chessMatrix, &chessMatrix, &materialEval, &wAttackMatrix, &bAttackMatrix, &ProtectionMapping, &AttackMapping);
        overallEval = materialEval + positionEval;

        getPiecePositions(chessMatrix, &xPositionArray, &yPositionArray);
        unsigned int movesIndexW = iterationIndexW;
        for (unsigned int pieces = WPAWN1; pieces <= WPAWN8; pieces++)
        {
            pawnXLoc = xPositionArray[pieces - 1];
            pawnYLoc = yPositionArray[pieces - 1];
            if (chessMatrix[pawnYLoc + 1][pawnXLoc] == NOTHING)
            {
                iterationArrayW[0][movesIndexW] = pieces;
                iterationArrayW[1][movesIndexW] = pawnXLoc;
                iterationArrayW[2][movesIndexW] = pawnYLoc + 1;
                ++movesIndexW;
            }
            if ((chessMatrix[3][pawnXLoc] == NOTHING) && (chessMatrix[2][pawnXLoc] == NOTHING) && pawnYLoc == 1)
            {
                iterationArrayW[0][movesIndexW] = pieces;
                iterationArrayW[1][movesIndexW] = pawnXLoc;
                iterationArrayW[2][movesIndexW] = 3;
                ++movesIndexW;
            }
        }
        if (!bAttackMatrix[0][4] && !bAttackMatrix[0][5] && !bAttackMatrix[0][6] && chessMatrix[0][4] == WKING && chessMatrix[0][7] == WROOK2 && chessMatrix[0][5] == NOTHING && chessMatrix[0][6] == NOTHING)
        {
            iterationArrayW[0][movesIndexW] = SHORT_CASTLE_W;
            iterationArrayW[1][movesIndexW] = NOTHING;
            iterationArrayW[2][movesIndexW] = NOTHING;
            ++movesIndexW;
        }
        if (!bAttackMatrix[0][2] && !bAttackMatrix[0][3] && !bAttackMatrix[0][4] && chessMatrix[0][4] == WKING && chessMatrix[0][0] == WROOK1 && chessMatrix[0][1] == NOTHING && chessMatrix[0][2] == NOTHING && chessMatrix[0][3] == NOTHING)
        {
            iterationArrayW[0][movesIndexW] = LONG_CASTLE_W;
            iterationArrayW[1][movesIndexW] = NOTHING;
            iterationArrayW[2][movesIndexW] = NOTHING;
            ++movesIndexW;
        }

        for (unsigned int m = 0; m < 36; m++)
        {
            xPositionArrayTemp[m] = xPositionArray[m];
            yPositionArrayTemp[m] = yPositionArray[m];
        }

        for (unsigned int i = 0; i < movesIndexW; i++) // movesIndexW
        {
            kingXLocW = xPositionArrayTemp[WKING - 1];
            kingYLocW = yPositionArrayTemp[WKING - 1];
            kingUnderAttackW = !!bAttackMatrix[kingYLocW][kingXLocW];
            resetEval();
            newEval = 0.0F;
            blackBestMoveEval = 1100.0F;
            for (unsigned int n = 0; n < 8; n++)
            {
                for (unsigned int m = 0; m < 8; m++)
                {
                    chessMatrixTempW[n][m] = chessMatrix[n][m];
                }
            }
            for (unsigned int n = 0; n < 3; n++)
            {
                for (unsigned int m = 0; m < 300; m++)
                {
                    iterationArrayWTemp[n][m] = iterationArrayW[n][m];
                }
            }

            iterationIndexWTemp = iterationIndexW;
            iterationPieceW = iterationArrayW[0][i];
            iterationXLocW = iterationArrayW[1][i];
            iterationYLocW = iterationArrayW[2][i];
            iterationXOrgLocW = xPositionArrayTemp[iterationPieceW - 1];
            iterationYOrgLocW = yPositionArrayTemp[iterationPieceW - 1];

            // chessNotation(&chessMatrix, iterationPieceW, iterationXOrgLocW, iterationYOrgLocW, iterationXLocW, iterationYLocW);
            if (iterationPieceW == SHORT_CASTLE_W)
            {
                chessMatrixTempW[0][4] = NOTHING;
                chessMatrixTempW[0][5] = WROOK2;
                chessMatrixTempW[0][6] = WKING;
                chessMatrixTempW[0][7] = NOTHING;
            }
            else if (iterationPieceW == LONG_CASTLE_W)
            {
                chessMatrixTempW[0][0] = NOTHING;
                chessMatrixTempW[0][1] = NOTHING;
                chessMatrixTempW[0][2] = WKING;
                chessMatrixTempW[0][3] = WROOK1;
                chessMatrixTempW[0][4] = NOTHING;
            }
            else if (iterationPieceW > WROOK2 && iterationPieceW < WPROMOTION1 && iterationYLocW == 7)
            {
                chessMatrixTempW[iterationYLocW][iterationXLocW] = WPROMOTION1;
                chessMatrixTempW[iterationYOrgLocW][iterationXOrgLocW] = NOTHING;
            }
            else if ((chessMatrix[iterationYLocW][iterationXLocW] >= BROOK1) && (chessMatrix[iterationYLocW][iterationXLocW] <= BPROMOTION2))
            {
                chessMatrixTempW[iterationYLocW][iterationXLocW] = iterationPieceW;
                chessMatrixTempW[iterationYOrgLocW][iterationXOrgLocW] = NOTHING;
            }
            else if (chessMatrix[iterationYLocW][iterationXLocW] == NOTHING)
            {
                chessMatrixTempW[iterationYLocW][iterationXLocW] = iterationPieceW;
                chessMatrixTempW[iterationYOrgLocW][iterationXOrgLocW] = NOTHING;
            }

            for (unsigned int n = 0; n < 3; n++)
            {
                for (unsigned int m = 0; m < 300; m++)
                {
                    iterationArrayBTemp[n][m] = 0;
                }
            }
            processBoardPosition(chessMatrixTempW, &positionEval, &wAttackMatrix, &bAttackMatrix, &iterationArrayWTemp, &iterationIndexWTemp, &iterationArrayBTemp, &iterationIndexBTemp);
            getPiecePositions(chessMatrixTempW, &xPositionArray, &yPositionArray);
            kingXLocW = xPositionArray[WKING - 1];
            kingYLocW = yPositionArray[WKING - 1];
            kingUnderAttackWAfter = !!bAttackMatrix[kingYLocW][kingXLocW];
            if (kingUnderAttackWAfter)
                continue;
            // chessNotation(&chessMatrix, iterationPieceW, iterationXOrgLocW, iterationYOrgLocW, iterationXLocW, iterationYLocW);

            unsigned int movesIndexB = iterationIndexBTemp;
            for (unsigned int pieces = BPAWN1; pieces <= BPAWN8; pieces++)
            {
                pawnXLoc = xPositionArray[pieces - 1];
                pawnYLoc = yPositionArray[pieces - 1];
                if (chessMatrix[pawnYLoc - 1][pawnXLoc] == NOTHING)
                {
                    iterationArrayBTemp[0][movesIndexB] = pieces;
                    iterationArrayBTemp[1][movesIndexB] = pawnXLoc;
                    iterationArrayBTemp[2][movesIndexB] = pawnYLoc - 1;
                    ++movesIndexB;
                }
                if ((chessMatrix[4][pawnXLoc] == NOTHING) && (chessMatrix[5][pawnXLoc] == NOTHING) && pawnYLoc == 6)
                {
                    iterationArrayBTemp[0][movesIndexB] = pieces;
                    iterationArrayBTemp[1][movesIndexB] = pawnXLoc;
                    iterationArrayBTemp[2][movesIndexB] = 4;
                    ++movesIndexB;
                }
            }
            if (!wAttackMatrix[7][4] && !wAttackMatrix[7][5] && !wAttackMatrix[7][6] && chessMatrix[7][4] == BKING && chessMatrix[7][7] == BROOK2 && chessMatrix[7][5] == NOTHING && chessMatrix[7][6] == NOTHING)
            {
                iterationArrayBTemp[0][movesIndexB] = SHORT_CASTLE_B;
                iterationArrayBTemp[1][movesIndexB] = NOTHING;
                iterationArrayBTemp[2][movesIndexB] = NOTHING;
                ++movesIndexB;
            }
            if (!wAttackMatrix[7][2] && !wAttackMatrix[7][3] && !wAttackMatrix[7][4] && chessMatrix[7][4] == BKING && chessMatrix[7][0] == BROOK1 && chessMatrix[7][1] == NOTHING && chessMatrix[7][2] == NOTHING && chessMatrix[7][3] == NOTHING)
            {
                iterationArrayBTemp[0][movesIndexB] = LONG_CASTLE_B;
                iterationArrayBTemp[1][movesIndexB] = NOTHING;
                iterationArrayBTemp[2][movesIndexB] = NOTHING;
                ++movesIndexB;
            }

            for (unsigned int m = 0; m < 36; m++)
            {
                xPositionArrayTemp2[m] = xPositionArrayTemp[m];
                yPositionArrayTemp2[m] = yPositionArrayTemp[m];
            }

            for (unsigned int j = 0; j < movesIndexB; j++) // movesIndexB
            {
                kingXLocB = xPositionArrayTemp2[BKING - 1];
                kingYLocB = yPositionArrayTemp2[BKING - 1];
                kingUnderAttackB = !!wAttackMatrixTemp[kingYLocB][kingXLocB];
                resetEval();
                for (unsigned int n = 0; n < 8; n++)
                {
                    for (unsigned int m = 0; m < 8; m++)
                    {
                        chessMatrixTempB[n][m] = chessMatrixTempW[n][m];
                        wAttackMatrixTemp[n][m] = wAttackMatrix[n][m];
                    }
                }
                for (unsigned int n = 0; n < 3; n++)
                {
                    for (unsigned int m = 0; m < 300; m++)
                    {
                        iterationArrayBTemp2[n][m] = iterationArrayBTemp[n][m];
                    }
                }

                iterationIndexBTemp2 = iterationIndexBTemp;
                iterationPieceB = iterationArrayBTemp[0][j];
                iterationXLocB = iterationArrayBTemp[1][j];
                iterationYLocB = iterationArrayBTemp[2][j];
                iterationXOrgLocB = xPositionArrayTemp2[iterationPieceB - 1];
                iterationYOrgLocB = yPositionArrayTemp2[iterationPieceB - 1];

                // chessNotation(&chessMatrixTempW, iterationPieceB, iterationXOrgLocB, iterationYOrgLocB, iterationXLocB, iterationYLocB);

                if (iterationPieceB == SHORT_CASTLE_B)
                {
                    chessMatrixTempB[7][4] = NOTHING;
                    chessMatrixTempB[7][5] = BROOK2;
                    chessMatrixTempB[7][6] = BKING;
                    chessMatrixTempB[7][7] = NOTHING;
                }
                else if (iterationPieceB == LONG_CASTLE_B)
                {
                    chessMatrixTempB[7][0] = NOTHING;
                    chessMatrixTempB[7][1] = NOTHING;
                    chessMatrixTempB[7][2] = BKING;
                    chessMatrixTempB[7][3] = BROOK1;
                    chessMatrixTempB[7][4] = NOTHING;
                }
                else if (iterationPieceB > BROOK2 && iterationPieceB < BPROMOTION1 && iterationYLocB == 0)
                {
                    chessMatrixTempB[iterationYLocB][iterationXLocB] = BPROMOTION1;
                    chessMatrixTempB[iterationYOrgLocB][iterationXOrgLocB] = NOTHING;
                }
                else if ((chessMatrixTempW[iterationYLocB][iterationXLocB] >= WROOK1) && (chessMatrixTempW[iterationYLocW][iterationXLocW] <= WPROMOTION2))
                {
                    chessMatrixTempB[iterationYLocB][iterationXLocB] = iterationPieceB;
                    chessMatrixTempB[iterationYOrgLocB][iterationXOrgLocB] = NOTHING;
                }
                else if (chessMatrixTempW[iterationYLocB][iterationXLocB] == NOTHING)
                {
                    chessMatrixTempB[iterationYLocB][iterationXLocB] = iterationPieceB;
                    chessMatrixTempB[iterationYOrgLocB][iterationXOrgLocB] = NOTHING;
                }

                processBoardPosition(chessMatrixTempB, &positionEval, &wAttackMatrix, &bAttackMatrix, &iterationArrayWTemp, &iterationIndexWTemp, &iterationArrayBTemp2, &iterationIndexBTemp2);
                kingXLocB = xPositionArray[BKING - 1];
                kingYLocB = yPositionArray[BKING - 1];
                kingUnderAttackBAfter = !!wAttackMatrix[kingYLocB][kingXLocB];
                if (kingUnderAttackBAfter)
                    continue;

                materialBalance(&chessMatrixTempB, &chessMatrixTempB, &materialEval, &wAttackMatrix, &bAttackMatrix, &ProtectionMapping, &AttackMapping);
                newEval = (float)materialEval + (float)positionEval;

                if (newEval < blackBestMoveEval)
                {
                    blackBestMoveEval = newEval;
                    blackBestMoveIndex = j;
                    // chessNotation(&chessMatrixTempW, iterationPieceB, iterationXOrgLocB, iterationYOrgLocB, iterationXLocB, iterationYLocB);
                    // deltaEval = (float)newEval - (float)overallEval;
                    // printf("Material Evaluation: %f\n", materialEval);
                    // printf("Position Evaluation: %f\n", positionEval);
                    // printf("Delta Evaluation: %f\n", deltaEval);

                    blackBestMovePieceB = iterationPieceB;
                    blackBestMoveXOrgLocB = iterationXOrgLocB;
                    blackBestMoveYOrgLocB = iterationYOrgLocB;
                    blackBestMoveXLocB = iterationXLocB;
                    blackBestMoveYLocB = iterationYLocB;
                }
            }
            if (blackBestMoveEval > whiteBestMoveEval)
            {
                whiteBestMoveEval = blackBestMoveEval;

                whiteBestMovePieceW = iterationPieceW;
                whiteBestMoveXOrgLocW = iterationXOrgLocW;
                whiteBestMoveYOrgLocW = iterationYOrgLocW;
                whiteBestMoveXLocW = iterationXLocW;
                whiteBestMoveYLocW = iterationYLocW;

                blackBestMoveforWBMPieceB = blackBestMovePieceB;
                blackBestMoveforWBMXOrgLocB = blackBestMoveXOrgLocB;
                blackBestMoveforWBMYOrgLocB = blackBestMoveYOrgLocB;
                blackBestMoveforWBMXLocB = blackBestMoveXLocB;
                blackBestMoveforWBMYLocB = blackBestMoveYLocB;

                whiteBestMoveIndex = i;

                deltaEval = (float)newEval - (float)overallEval;
                // printf("Material Evaluation: %f\n", materialEval);
                // printf("Position Evaluation: %f\n", positionEval);
                // printf("Delta Evaluation: %f\n", deltaEval);
            }
        }
        chessNotation(&chessMatrix, whiteBestMovePieceW, whiteBestMoveXOrgLocW, whiteBestMoveYOrgLocW, whiteBestMoveXLocW, whiteBestMoveYLocW);
        updateChessMatrix(&chessMatrix, whiteBestMovePieceW, whiteBestMoveXOrgLocW, whiteBestMoveYOrgLocW, whiteBestMoveXLocW, whiteBestMoveYLocW);
        processBoardPosition(chessMatrix, &positionEval, &wAttackMatrix, &bAttackMatrix, &iterationArrayWTemp, &iterationIndexWTemp, &iterationArrayBTemp, &iterationIndexBTemp);
        getPiecePositions(chessMatrix, &xPositionArray, &yPositionArray);
        kingXLocW = xPositionArray[WKING - 1];
        kingYLocW = yPositionArray[WKING - 1];
        kingUnderAttackWAfter = !!bAttackMatrix[kingYLocW][kingXLocW];
        if (kingUnderAttackWAfter)
        {
            printf("checkmate White");
            return 0;
        }

        resetPositions(&xPositionArray);
        resetPositions(&yPositionArray);
        resetPositions(&xPositionArrayTemp);
        resetPositions(&yPositionArrayTemp);
        resetPositions(&xPositionArrayTemp2);
        resetPositions(&yPositionArrayTemp2);
        resetEval();

        resetBoardMatrix(&chessMatrixTempB);
        resetBoardMatrix(&chessMatrixTempW);

        resetIterationArrays(&iterationArrayW);
        resetIterationArrays(&iterationArrayB);
        resetIterationArrays(&iterationArrayWTemp);
        resetIterationArrays(&iterationArrayBTemp);
        resetIterationArrays(&iterationArrayBTemp2);

        resetIterationIndex(&iterationIndexW);
        resetIterationIndex(&iterationIndexB);
        resetIterationIndex(&iterationIndexWTemp);
        resetIterationIndex(&iterationIndexBTemp);
        resetIterationIndex(&iterationIndexBTemp2);

        resetEvaluation(&materialEval);
        resetEvaluation(&positionEval);

        // chessNotation(&chessMatrix, blackBestMoveforWBMPieceB, blackBestMoveforWBMXOrgLocB, blackBestMoveforWBMYOrgLocB, blackBestMoveforWBMXLocB, blackBestMoveforWBMYLocB);

        printf("Please enter your move in Algebraic Notation:\n");
        scanf("%s", &userMove);


        reverseChessNotation(&userMove, &chessMatrix, &userPiecePlay, &userPieceXLoc, &userPieceYLoc, &userPieceDestXLoc, &userPieceDestYLoc);
        updateChessMatrix(&chessMatrix, userPiecePlay, userPieceXLoc, userPieceYLoc, userPieceDestXLoc, userPieceDestYLoc);
        processBoardPosition(chessMatrix, &positionEval, &wAttackMatrix, &bAttackMatrix, &iterationArrayWTemp, &iterationIndexWTemp, &iterationArrayBTemp, &iterationIndexBTemp);
        getPiecePositions(chessMatrix, &xPositionArray, &yPositionArray);
        kingXLocB = xPositionArray[BKING - 1];
        kingYLocB = yPositionArray[BKING - 1];
        kingUnderAttackBAfter = !!wAttackMatrix[kingYLocB][kingXLocB];
        if (kingUnderAttackBAfter)
        {
            printf("checkmate Black");
            return 0;
        }

        resetPositions(&xPositionArray);
        resetPositions(&yPositionArray);
        resetPositions(&xPositionArrayTemp);
        resetPositions(&yPositionArrayTemp);
        resetPositions(&xPositionArrayTemp2);
        resetPositions(&yPositionArrayTemp2);
        resetEval();

        resetBoardMatrix(&chessMatrixTempB);
        resetBoardMatrix(&chessMatrixTempW);

        resetIterationArrays(&iterationArrayW);
        resetIterationArrays(&iterationArrayB);
        resetIterationArrays(&iterationArrayWTemp);
        resetIterationArrays(&iterationArrayBTemp);
        resetIterationArrays(&iterationArrayBTemp2);

        resetIterationIndex(&iterationIndexW);
        resetIterationIndex(&iterationIndexB);
        resetIterationIndex(&iterationIndexWTemp);
        resetIterationIndex(&iterationIndexBTemp);
        resetIterationIndex(&iterationIndexBTemp2);

        resetEvaluation(&materialEval);
        resetEvaluation(&positionEval);
    }
}