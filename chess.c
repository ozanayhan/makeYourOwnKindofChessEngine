#include <stdio.h>
#include <string.h>
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
    outw:;
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
    else if (piecePlay == SHORT_CASTLE_B)
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
        (*userPieceDestYLoc) = (*userMove)[3] - 49;
    }
    else if ((*userMove)[0] > 96 && (*userMove)[0] < 105)
    {
        (*userPieceDestXLoc) = (*userMove)[0] - 97;
        (*userPieceDestYLoc) = (*userMove)[1] - 49;
    }
    else if ((*userMove)[0] > 65 && (*userMove)[0] < 83)
    {
        (*userPieceDestXLoc) = (*userMove)[1] - 97;
        (*userPieceDestYLoc) = (*userMove)[2] - 49;
    }

    if ((*userMove)[0] == 79 && (*userMove)[1] == 45 && (*userMove)[2] == 79 && (*userMove)[3] == 45)
    {
        // Long Castle
        (*userPiecePlay) = BKING;
        (*userPieceDestXLoc) = 2;
        (*userPieceDestYLoc) = 7;
        (*userPieceXLoc) = 4;
        (*userPieceYLoc) = 7;
    }
    else if ((*userMove)[0] == 79 && (*userMove)[1] == 45 && (*userMove)[2] == 79)
    {
        // Short Castle
        (*userPiecePlay) = BKING;
        (*userPieceDestXLoc) = 6;
        (*userPieceDestYLoc) = 7;
        (*userPieceXLoc) = 4;
        (*userPieceYLoc) = 7;
    }
    else if ((*userMove)[0] == 75)
    {
        // King Move
        (*userPiecePlay) = BKING;
        (*userPieceXLoc) = xPositionArray[BKING - 1];
        (*userPieceYLoc) = yPositionArray[BKING - 1];
    }
    else if ((*userMove)[0] == 81)
    {
        // Queen Move
        (*userPiecePlay) = BQUEEN;
        (*userPieceXLoc) = xPositionArray[BQUEEN - 1];
        (*userPieceYLoc) = yPositionArray[BQUEEN - 1];
    }
    else if ((*userMove)[0] == 82)
    {
        // Rook Move
        (*userPiecePlay) = BROOK1;
        (*userPieceXLoc) = xPositionArray[BROOK1 - 1];
        (*userPieceYLoc) = yPositionArray[BROOK1 - 1];
        if (((*userPieceXLoc) != (*userPieceDestXLoc)) && ((*userPieceYLoc) != (*userPieceDestYLoc)))
        {
            (*userPiecePlay) = BROOK2;
            (*userPieceXLoc) = xPositionArray[BROOK2 - 1];
            (*userPieceYLoc) = yPositionArray[BROOK2 - 1];
        }
        if (((*userPieceXLoc) != (*userPieceDestXLoc)) && ((*userPieceYLoc) != (*userPieceDestYLoc)))
        {
            (*userPiecePlay) = NOTHING;
        }
    }
    else if ((*userMove)[0] == 66)
    {
        // Bishop Move
        if (((*userPieceDestXLoc) + (*userPieceDestYLoc)) % 2)
        {
            (*userPiecePlay) = BBISHOP1;
            (*userPieceXLoc) = xPositionArray[BBISHOP1 - 1];
            (*userPieceYLoc) = yPositionArray[BBISHOP1 - 1];
        }
        else
        {
            (*userPiecePlay) = BBISHOP2;
            (*userPieceXLoc) = xPositionArray[BBISHOP2 - 1];
            (*userPieceYLoc) = yPositionArray[BBISHOP2 - 1];
        }
    }
    else if ((*userMove)[0] == 78)
    {
        // Knight Move
        (*userPiecePlay) = BKNIGHT1;
        (*userPieceXLoc) = xPositionArray[BKNIGHT1 - 1];
        (*userPieceYLoc) = yPositionArray[BKNIGHT1 - 1];
        if ((((*userPieceDestXLoc) - (*userPieceXLoc)) > 7 ? ((*userPieceXLoc) - (*userPieceDestXLoc)) : ((*userPieceDestXLoc) - (*userPieceXLoc))) + (((*userPieceDestYLoc) - (*userPieceYLoc)) > 7 ? ((*userPieceYLoc) - (*userPieceDestYLoc)) : ((*userPieceDestYLoc) - (*userPieceYLoc))) != 3 || (*userPieceDestYLoc) == (*userPieceYLoc) || (*userPieceDestXLoc) == (*userPieceXLoc))
        {
            (*userPiecePlay) = BKNIGHT2;
            (*userPieceXLoc) = xPositionArray[BKNIGHT2 - 1];
            (*userPieceYLoc) = yPositionArray[BKNIGHT2 - 1];
        }
        if ((((*userPieceDestXLoc) - (*userPieceXLoc)) > 7 ? ((*userPieceXLoc) - (*userPieceDestXLoc)) : ((*userPieceDestXLoc) - (*userPieceXLoc))) + (((*userPieceDestYLoc) - (*userPieceYLoc)) > 7 ? ((*userPieceYLoc) - (*userPieceDestYLoc)) : ((*userPieceDestYLoc) - (*userPieceYLoc))) != 3 || (*userPieceDestYLoc) == (*userPieceYLoc) || (*userPieceDestXLoc) == (*userPieceXLoc))
        {
            (*userPiecePlay) = NOTHING;
        }
    }
    else if ((*userMove)[0] > 96 && (*userMove)[0] < 105)
    {
        // Pawn Move
        if ((*userMove)[0] == 97)
        {
            (*userPiecePlay) = BPAWN1;
            (*userPieceXLoc) = xPositionArray[BPAWN1 - 1];
            (*userPieceYLoc) = yPositionArray[BPAWN1 - 1];
        }
        else if ((*userMove)[0] == 98)
        {
            (*userPiecePlay) = BPAWN2;
            (*userPieceXLoc) = xPositionArray[BPAWN2 - 1];
            (*userPieceYLoc) = yPositionArray[BPAWN2 - 1];
        }
        else if ((*userMove)[0] == 99)
        {
            (*userPiecePlay) = BPAWN3;
            (*userPieceXLoc) = xPositionArray[BPAWN3 - 1];
            (*userPieceYLoc) = yPositionArray[BPAWN3 - 1];
        }
        else if ((*userMove)[0] == 100)
        {
            (*userPiecePlay) = BPAWN4;
            (*userPieceXLoc) = xPositionArray[BPAWN4 - 1];
            (*userPieceYLoc) = yPositionArray[BPAWN4 - 1];
        }
        else if ((*userMove)[0] == 101)
        {
            (*userPiecePlay) = BPAWN5;
            (*userPieceXLoc) = xPositionArray[BPAWN5 - 1];
            (*userPieceYLoc) = yPositionArray[BPAWN5 - 1];
        }
        else if ((*userMove)[0] == 102)
        {
            (*userPiecePlay) = BPAWN6;
            (*userPieceXLoc) = xPositionArray[BPAWN6 - 1];
            (*userPieceYLoc) = yPositionArray[BPAWN6 - 1];
        }
        else if ((*userMove)[0] == 103)
        {
            (*userPiecePlay) = BPAWN7;
            (*userPieceXLoc) = xPositionArray[BPAWN7 - 1];
            (*userPieceYLoc) = yPositionArray[BPAWN7 - 1];
        }
        else if ((*userMove)[0] == 104)
        {
            (*userPiecePlay) = BPAWN8;
            (*userPieceXLoc) = xPositionArray[BPAWN8 - 1];
            (*userPieceYLoc) = yPositionArray[BPAWN8 - 1];
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
    for (unsigned int j = 0; j < 7; j++)
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

void materialBalance(unsigned int (*chessMatrix)[8][8], float(*materialEval), unsigned int (*wAttackMatrix)[8][8], unsigned int (*bAttackMatrix)[8][8], unsigned int ProtectionMapping[36][5], unsigned int AttackMapping[36][5], unsigned int moveWhite)
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
            if (moveWhite)
            {
                if ((*wAttackMatrix)[j][i])
                {
                    wAttackedPiece = (*chessMatrix)[j][i];
                    bNumProtectingPiece = 0;
                    wNumAttackingPiece = 0;
                    for (unsigned int k = 0; k < 5; k++)
                    {
                        protectionIndex = (ProtectionMapping[wAttackedPiece - 1][k]);
                        attackIndex = (AttackMapping[wAttackedPiece - 1][k]);
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

                    if (wNumAttackingPiece <= bNumProtectingPiece)
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
            }
            else
            {

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
                    bAttackedPiece = (*chessMatrix)[j][i];
                    for (unsigned int k = 0; k < 5; k++)
                    {
                        protectionIndex = (ProtectionMapping[bAttackedPiece - 1][k]);
                        attackIndex = (AttackMapping[bAttackedPiece - 1][k]);
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
    }
    wMaterialBalance = (float)wMaterialCount - (float)bMaterialCount;
    (*materialEval) = wMaterialBalance + (float)wMaxMaterialGain + (float)wMaxMaterialLoss;
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

            wTotNumPcsEnPrise += ((*bAttackMatrix)[j][i] > wProtectionMatrix[j][i]);
            bTotNumPcsEnPrise += ((*wAttackMatrix)[j][i] > bProtectionMatrix[j][i]);

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
}

void amendIterationArray(unsigned int chessMatrix[8][8], unsigned int (*iterationArray)[3][300], unsigned int(*iterationIndex), unsigned int moveWhite, unsigned int AttackMatrix[8][8])
{
    getPiecePositions(chessMatrix, &xPositionArray, &yPositionArray);
    if (moveWhite)
    {
        for (unsigned int pieces = WPAWN1; pieces <= WPAWN8; pieces++)
        {
            pawnXLoc = xPositionArray[pieces - 1];
            pawnYLoc = yPositionArray[pieces - 1];
            if (chessMatrix[pawnYLoc + 1][pawnXLoc] == NOTHING)
            {
                (*iterationArray)[0][(*iterationIndex)] = pieces;
                (*iterationArray)[1][(*iterationIndex)] = pawnXLoc;
                (*iterationArray)[2][(*iterationIndex)] = pawnYLoc + 1;
                ++(*iterationIndex);
            }
            if ((chessMatrix[3][pawnXLoc] == NOTHING) && (chessMatrix[2][pawnXLoc] == NOTHING) && pawnYLoc == 1)
            {
                (*iterationArray)[0][(*iterationIndex)] = pieces;
                (*iterationArray)[1][(*iterationIndex)] = pawnXLoc;
                (*iterationArray)[2][(*iterationIndex)] = 3;
                ++(*iterationIndex);
            }
        }
        if (!AttackMatrix[0][4] && !AttackMatrix[0][5] && !AttackMatrix[0][6] && chessMatrix[0][4] == WKING && chessMatrix[0][7] == WROOK2 && chessMatrix[0][5] == NOTHING && chessMatrix[0][6] == NOTHING)
        {
            (*iterationArray)[0][(*iterationIndex)] = SHORT_CASTLE_W;
            (*iterationArray)[1][(*iterationIndex)] = NOTHING;
            (*iterationArray)[2][(*iterationIndex)] = NOTHING;
            ++(*iterationIndex);
        }
        if (!AttackMatrix[0][2] && !AttackMatrix[0][3] && !AttackMatrix[0][4] && chessMatrix[0][4] == WKING && chessMatrix[0][0] == WROOK1 && chessMatrix[0][1] == NOTHING && chessMatrix[0][2] == NOTHING && chessMatrix[0][3] == NOTHING)
        {
            (*iterationArray)[0][(*iterationIndex)] = LONG_CASTLE_W;
            (*iterationArray)[1][(*iterationIndex)] = NOTHING;
            (*iterationArray)[2][(*iterationIndex)] = NOTHING;
            ++(*iterationIndex);
        }
    }
    else
    {
        for (unsigned int pieces = BPAWN1; pieces <= BPAWN8; pieces++)
        {
            pawnXLoc = xPositionArray[pieces - 1];
            pawnYLoc = yPositionArray[pieces - 1];
            if (chessMatrix[pawnYLoc - 1][pawnXLoc] == NOTHING)
            {
                (*iterationArray)[0][(*iterationIndex)] = pieces;
                (*iterationArray)[1][(*iterationIndex)] = pawnXLoc;
                (*iterationArray)[2][(*iterationIndex)] = pawnYLoc - 1;
                ++(*iterationIndex);
            }
            if ((chessMatrix[4][pawnXLoc] == NOTHING) && (chessMatrix[5][pawnXLoc] == NOTHING) && pawnYLoc == 6)
            {
                (*iterationArray)[0][(*iterationIndex)] = pieces;
                (*iterationArray)[1][(*iterationIndex)] = pawnXLoc;
                (*iterationArray)[2][(*iterationIndex)] = 4;
                ++(*iterationIndex);
            }
        }
        if (!AttackMatrix[7][4] && !AttackMatrix[7][5] && !AttackMatrix[7][6] && chessMatrix[7][4] == BKING && chessMatrix[7][7] == BROOK2 && chessMatrix[7][5] == NOTHING && chessMatrix[7][6] == NOTHING)
        {
            (*iterationArray)[0][(*iterationIndex)] = SHORT_CASTLE_B;
            (*iterationArray)[1][(*iterationIndex)] = NOTHING;
            (*iterationArray)[2][(*iterationIndex)] = NOTHING;
            ++(*iterationIndex);
        }
        if (!AttackMatrix[7][2] && !AttackMatrix[7][3] && !AttackMatrix[7][4] && chessMatrix[7][4] == BKING && chessMatrix[7][0] == BROOK1 && chessMatrix[7][1] == NOTHING && chessMatrix[7][2] == NOTHING && chessMatrix[7][3] == NOTHING)
        {
            (*iterationArray)[0][(*iterationIndex)] = LONG_CASTLE_B;
            (*iterationArray)[1][(*iterationIndex)] = NOTHING;
            (*iterationArray)[2][(*iterationIndex)] = NOTHING;
            ++(*iterationIndex);
        }
    }
}

void updateOverallEval(float (*overallEvalArray)[6][300], float overallEval, unsigned int movesIndex, unsigned int Ply)
{
    (*overallEvalArray)[(Ply)][movesIndex] = overallEval;
}

int main(void)
{
    unsigned int previousMove = 0;
    for (unsigned int t = 0; t < 30; t++)
    {
        // Step 1: Get the iteration Array for the Current Board Position, and obtain the attack matrices and a positional evaluation.
        processBoardPosition(chessMatrix, &positionEval, &wAttackMatrix, &bAttackMatrix, &iterationArrayW, &iterationIndexW, &iterationArrayB, &iterationIndexB);
        // Step 2: Amend the Iteration Array with pawn moves and special moves like castling and en passant.
        amendIterationArray(chessMatrix, &iterationArrayW, &iterationIndexW, 1, bAttackMatrix);
        // Step 3: Get piece positions
        getPiecePositions(chessMatrix, &xPositionArray, &yPositionArray);
        // Step 4: Make a material assessment based on the current board position.
        materialBalance(&chessMatrix, &materialEval, &wAttackMatrix, &bAttackMatrix, ProtectionMapping, AttackMapping, 1);
        // Step 5: Make an overall assessment for the current board position.
        overallEval = materialEval + positionEval;
        // Step 6: Check if the White and Black Kings are currently under attack.
        kingXLocW = xPositionArray[WKING - 1];
        kingYLocW = yPositionArray[WKING - 1];
        kingUnderAttackW = !!bAttackMatrix[kingYLocW][kingXLocW];
        kingXLocB = xPositionArray[BKING - 1];
        kingYLocB = yPositionArray[BKING - 1];
        kingUnderAttackB = !!wAttackMatrix[kingYLocB][kingXLocB];
        // Step 7: Copy Attack Matrix, Protection Matrix and position arrays, because they will be overwritten.
        memcpy(AttackMappingBase, AttackMapping, sizeof(AttackMapping));
        memcpy(ProtectionMappingBase, ProtectionMapping, sizeof(ProtectionMapping));
        memcpy(xPositionArrayBase, xPositionArray, sizeof(xPositionArray));
        memcpy(yPositionArrayBase, yPositionArray, sizeof(yPositionArray));
        // Step 8: For all the elements of the iteration array, update the board position and re-evaluate the board.
        unsigned int i = 0;
        unsigned int j = 0;
        for (i = 0; i < iterationIndexW; i++) // iterationIndexW
        {
            resetEval();
            // Step 9: Copy the current chess board to Ply1.
            memcpy(chessMatrixPly1, chessMatrix, sizeof(chessMatrix));
            // Step 10: Iterate for the next piece.
            iterationPieceW = iterationArrayW[0][i];
            iterationXLocW = iterationArrayW[1][i];
            iterationYLocW = iterationArrayW[2][i];
            iterationXOrgLocW = xPositionArrayBase[iterationPieceW - 1];
            iterationYOrgLocW = yPositionArrayBase[iterationPieceW - 1];
            // Step 10: Update the chess board for Ply1.
            updateChessMatrix(&chessMatrixPly1, iterationPieceW, iterationXOrgLocW, iterationYOrgLocW, iterationXLocW, iterationYLocW);
            // Step 11: Get the iteration Array for the New (Ply1) Board Position, and obtain the attack matrices and a positional evaluation.
            processBoardPosition(chessMatrixPly1, &positionEvalPly1, &wAttackMatrixPly1, &bAttackMatrixPly1, &iterationArrayWPly1, &iterationIndexWPly1, &iterationArrayBPly1, &iterationIndexBPly1);
            // Step 12: Amend the black Iteration Array for Ply2.
            amendIterationArray(chessMatrixPly1, &iterationArrayBPly1, &iterationIndexBPly1, 0, wAttackMatrixPly1);
            // Step 13: Get piece positions for the new board
            getPiecePositions(chessMatrixPly1, &xPositionArrayPly1, &yPositionArrayPly1);
            // Step 14: Check if the White King is  under attack in the new position.
            kingXLocW = xPositionArrayPly1[WKING - 1];
            kingYLocW = yPositionArrayPly1[WKING - 1];
            kingUnderAttackWPly1 = !!bAttackMatrixPly1[kingYLocW][kingXLocW];
            // Step 15: If the White King is under attack after the move, this is not allowed, and will be skipped.
            if (kingUnderAttackWPly1)
                continue;
            // Step 16: Check if the Black King is  under attack in the new position.
            kingXLocB = xPositionArrayPly1[BKING - 1];
            kingYLocB = yPositionArrayPly1[BKING - 1];
            kingUnderAttackBPly1 = !!wAttackMatrixPly1[kingYLocB][kingXLocB];
            // Step 17: Copy Attack Matrix and Protection Matrix because they will be overwritten.
            memcpy(AttackMappingPly1, AttackMapping, sizeof(AttackMapping));
            memcpy(ProtectionMappingPly1, ProtectionMapping, sizeof(ProtectionMapping));
            // Step 18: Make a material assessment based on the new board position.
            materialBalance(&chessMatrixPly1, &materialEvalPly1, &wAttackMatrixPly1, &bAttackMatrixPly1, ProtectionMappingPly1, AttackMappingPly1, 0);
            // Step 19: Make an overall assessment for the new board position.
            overallEvalPly1 = materialEvalPly1 + positionEvalPly1;
            // Step 20: Enter the Overall Evaluation to the Iteration Array (1st Ply = 0th Position)
            updateOverallEval(&overallEvalArray, overallEvalPly1, i, 0);
            // Step 21: Assign a high value to overallEvalPly2, so it will be replaced with better moves.
            overallEvalPly2 = 1000.0F;
            overallEvalPly3 = 1000.0F;
            overallEvalPly4 = 1000.0F;
            // Step 22: For all the elements of the iteration array, update the board position and re-evaluate the board.
            for (j = 0; j < iterationIndexBPly1; j++) // iterationIndexBPly1
            {
                resetEval();
                // Step 23: Copy the current chess board to Ply2.
                memcpy(chessMatrixPly2, chessMatrixPly1, sizeof(chessMatrixPly1));
                // Step 24: Iterate for the next piece.
                iterationPieceB = iterationArrayBPly1[0][j];
                iterationXLocB = iterationArrayBPly1[1][j];
                iterationYLocB = iterationArrayBPly1[2][j];
                iterationXOrgLocB = xPositionArrayPly1[iterationPieceB - 1];
                iterationYOrgLocB = yPositionArrayPly1[iterationPieceB - 1];
                // Step 25: Update the chess board for Ply2.
                updateChessMatrix(&chessMatrixPly2, iterationPieceB, iterationXOrgLocB, iterationYOrgLocB, iterationXLocB, iterationYLocB);
                // Step 26: Get the iteration Array for the New (Ply2) Board Position, and obtain the attack matrices and a positional evaluation.
                processBoardPosition(chessMatrixPly2, &positionEvalPly2, &wAttackMatrixPly2, &bAttackMatrixPly2, &iterationArrayWPly2, &iterationIndexWPly2, &iterationArrayBPly2, &iterationIndexBPly2);
                // Step 27: Amend the Iteration Array with pawn moves and special moves like castling and en passant.
                amendIterationArray(chessMatrixPly2, &iterationArrayWPly2, &iterationIndexWPly2, 1, bAttackMatrixPly2);
                // Step 28: Get piece positions for the new board
                getPiecePositions(chessMatrixPly2, &xPositionArrayPly2, &yPositionArrayPly2);
                // Step 29: Check if the Black King is  under attack in the new position.
                kingXLocB = xPositionArrayPly2[BKING - 1];
                kingYLocB = yPositionArrayPly2[BKING - 1];
                kingUnderAttackBPly2 = !!wAttackMatrixPly2[kingYLocB][kingXLocB];
                // Step 30: If the Black King is under attack after the move, this is not allowed, and will be skipped.
                if (kingUnderAttackBPly2)
                    continue;
                // Step 31: Check if the White King is  under attack in the new position.
                kingXLocW = xPositionArrayPly2[WKING - 1];
                kingYLocW = yPositionArrayPly2[WKING - 1];
                kingUnderAttackWPly2 = !!bAttackMatrixPly2[kingYLocW][kingXLocW];
                // Step 32: Copy Attack Matrix and Protection Matrix because they will be overwritten.
                memcpy(AttackMappingPly2, AttackMapping, sizeof(AttackMapping));
                memcpy(ProtectionMappingPly2, ProtectionMapping, sizeof(ProtectionMapping));
                // Step 33: Make a material assessment based on the new board position.
                materialBalance(&chessMatrixPly2, &materialEvalPly2, &wAttackMatrixPly2, &bAttackMatrixPly2, ProtectionMappingPly2, AttackMappingPly2, 1);
                // Step 34: If the overall assessment is less than previous evaluation, it@s a better move for black, so update the Array.
                if ((materialEvalPly2 + positionEvalPly2) < overallEvalPly2)
                {
                    // Step 35: Make an overall assessment for the new board position. (2nd Ply = 1st Position)
                    overallEvalPly2 = materialEvalPly2 + positionEvalPly2;
                    updateOverallEval(&overallEvalArray, overallEvalPly2, i, 1);
                }
                // Step 36: Assign a low value to overallEvalPly3Temp, so it will be replaced with better moves.
                overallEvalPly3Temp = -1000.0F;
                overallEvalPly4Temp2 = -1000.0F;
                // Step 37: For all the elements of the iteration array, update the board position and re-evaluate the board.
                for (unsigned int k = 0; k < iterationIndexWPly2; k++) // iterationIndexWPly2
                {
                    resetEval();
                    // Step 38: Copy the current chess board to Ply2.
                    memcpy(chessMatrixPly3, chessMatrixPly2, sizeof(chessMatrixPly2));
                    // Step 39: Iterate for the next piece.
                    iterationPieceW = iterationArrayWPly2[0][k];
                    iterationXLocW = iterationArrayWPly2[1][k];
                    iterationYLocW = iterationArrayWPly2[2][k];
                    iterationXOrgLocW = xPositionArrayPly2[iterationPieceW - 1];
                    iterationYOrgLocW = yPositionArrayPly2[iterationPieceW - 1];
                    // Step 40: Update the chess board for Ply3.
                    updateChessMatrix(&chessMatrixPly3, iterationPieceW, iterationXOrgLocW, iterationYOrgLocW, iterationXLocW, iterationYLocW);
                    // Step 41: Get the iteration Array for the New (Ply3) Board Position, and obtain the attack matrices and a positional evaluation.
                    processBoardPosition(chessMatrixPly3, &positionEvalPly3, &wAttackMatrixPly3, &bAttackMatrixPly3, &iterationArrayWPly3, &iterationIndexWPly3, &iterationArrayBPly3, &iterationIndexBPly3);
                    // Step 42: Amend the black Iteration Array for Ply2.
                    amendIterationArray(chessMatrixPly3, &iterationArrayBPly3, &iterationIndexBPly3, 0, wAttackMatrixPly3);
                    // Step 43: Get piece positions for the new board
                    getPiecePositions(chessMatrixPly3, &xPositionArrayPly3, &yPositionArrayPly3);
                    // Step 44: Check if the White King is  under attack in the new position.
                    kingXLocW = xPositionArrayPly3[WKING - 1];
                    kingYLocW = yPositionArrayPly3[WKING - 1];
                    kingUnderAttackWPly3 = !!bAttackMatrixPly3[kingYLocW][kingXLocW];
                    // Step 45: If the White King is under attack after the move, this is not allowed, and will be skipped.
                    if (kingUnderAttackWPly3)
                        continue;
                    // Step 46: Check if the Black King is  under attack in the new position.
                    kingXLocB = xPositionArrayPly3[BKING - 1];
                    kingYLocB = yPositionArrayPly3[BKING - 1];
                    kingUnderAttackBPly3 = !!wAttackMatrixPly3[kingYLocB][kingXLocB];
                    // Step 47: Copy Attack Matrix and Protection Matrix because they will be overwritten.
                    memcpy(AttackMappingPly3, AttackMapping, sizeof(AttackMapping));
                    memcpy(ProtectionMappingPly3, ProtectionMapping, sizeof(ProtectionMapping));
                    // Step 48: Make a material assessment based on the new board position.
                    materialBalance(&chessMatrixPly3, &materialEvalPly3, &wAttackMatrixPly3, &bAttackMatrixPly3, ProtectionMappingPly3, AttackMappingPly3, 0);
                    // Step 49: If the overall assessment is higher than previous evaluation, it's a better move for white, so update the Array.
                    if ((materialEvalPly3 + positionEvalPly3) > overallEvalPly3Temp)
                    {
                        // Step 50: Make an overall assessment for the new board position. (3rd Ply = 2nd Position)
                        overallEvalPly3Temp = materialEvalPly3 + positionEvalPly3;
                    }
                    // Step 51: Assign a high value to overallEvalPly4Temp, so it will be replaced with better moves.
                    overallEvalPly4Temp = 1000.0F;
                    // Step 52: For all the elements of the iteration array, update the board position and re-evaluate the board.
                    for (unsigned int l = 0; l < iterationIndexBPly3; l++) // iterationIndexBPly3
                    {
                        resetEval();
                        // Step 53: Copy the current chess board to Ply4.
                        memcpy(chessMatrixPly4, chessMatrixPly3, sizeof(chessMatrixPly3));
                        // Step 54: Iterate for the next piece.
                        iterationPieceB = iterationArrayBPly3[0][l];
                        iterationXLocB = iterationArrayBPly3[1][l];
                        iterationYLocB = iterationArrayBPly3[2][l];
                        iterationXOrgLocB = xPositionArrayPly3[iterationPieceB - 1];
                        iterationYOrgLocB = yPositionArrayPly3[iterationPieceB - 1];
                        // Step 55: Update the chess board for Ply4.
                        updateChessMatrix(&chessMatrixPly4, iterationPieceB, iterationXOrgLocB, iterationYOrgLocB, iterationXLocB, iterationYLocB);
                        // Step 56: Get the iteration Array for the New (Ply4) Board Position, and obtain the attack matrices and a positional evaluation.
                        processBoardPosition(chessMatrixPly4, &positionEvalPly4, &wAttackMatrixPly4, &bAttackMatrixPly4, &iterationArrayWPly4, &iterationIndexWPly4, &iterationArrayBPly4, &iterationIndexBPly4);
                        // Step 57: Amend the Iteration Array with pawn moves and special moves like castling and en passant.
                        amendIterationArray(chessMatrixPly4, &iterationArrayWPly4, &iterationIndexWPly4, 1, bAttackMatrixPly4);
                        // Step 58: Get piece positions for the new board
                        getPiecePositions(chessMatrixPly4, &xPositionArrayPly4, &yPositionArrayPly4);
                        // Step 59: Check if the Black King is  under attack in the new position.
                        kingXLocB = xPositionArrayPly4[BKING - 1];
                        kingYLocB = yPositionArrayPly4[BKING - 1];
                        kingUnderAttackBPly4 = !!wAttackMatrixPly4[kingYLocB][kingXLocB];
                        // Step 60: If the Black King is under attack after the move, this is not allowed, and will be skipped.
                        if (kingUnderAttackBPly4)
                            continue;
                        // Step 61: Check if the White King is  under attack in the new position.
                        kingXLocW = xPositionArrayPly4[WKING - 1];
                        kingYLocW = yPositionArrayPly4[WKING - 1];
                        kingUnderAttackWPly4 = !!bAttackMatrixPly4[kingYLocW][kingXLocW];
                        // Step 62: Copy Attack Matrix and Protection Matrix because they will be overwritten.
                        memcpy(AttackMappingPly4, AttackMapping, sizeof(AttackMapping));
                        memcpy(ProtectionMappingPly4, ProtectionMapping, sizeof(ProtectionMapping));
                        // Step 63: Make a material assessment based on the new board position.
                        materialBalance(&chessMatrixPly4, &materialEvalPly4, &wAttackMatrixPly4, &bAttackMatrixPly4, ProtectionMappingPly4, AttackMappingPly4, 1);
                        // Step 64: If the overall assessment is less than previous evaluation, it's a better move for black, so update the Array.
                        if ((materialEvalPly4 + positionEvalPly4) < overallEvalPly4Temp)
                        {
                            // Step 65: Make an overall assessment for the new board position. (4th Ply = 3rd Position)
                            overallEvalPly4Temp = materialEvalPly2 + positionEvalPly2;
                        }
                    }
                    if (overallEvalPly4Temp > overallEvalPly4Temp2)
                    {
                        // Step 66: Make an overall assessment for the new board position. (4th Ply = 3rd Position)
                        overallEvalPly4Temp2 = overallEvalPly4Temp;
                    }
                }
                if (overallEvalPly4Temp2 < overallEvalPly4)
                {
                    // Step 67: Make an overall assessment for the new board position. (4th Ply = 3rd Position)
                    overallEvalPly4 = overallEvalPly4Temp2;
                    updateOverallEval(&overallEvalArray, overallEvalPly4, i, 3);
                }
                // Step 68: Make an overall assessment for the new board position. (3rd Ply = 2nd Position)
                if (overallEvalPly3Temp < overallEvalPly3)
                {
                    overallEvalPly3 = overallEvalPly3Temp;
                    updateOverallEval(&overallEvalArray, overallEvalPly3, i, 2);
                }
            }
        }
        // Step 69: Checkmate Recognition:
        if (!i)
        {
            printf("checkmate White");
            return 0;
        }
        if (!j)
        {
            printf("checkmate Black");
            return 0;
        }
        // Step 70: Selecting the best 1st move for White based on 4th Ply Evaluation:
        whiteBestMoveEval = -1000.0F;
        for (unsigned int i = 0; i < iterationIndexW; i++)
        {
            if (overallEvalArray[3][i] > whiteBestMoveEval)
            {
                whiteBestMoveEval = overallEvalArray[3][i];
                whiteBestMoveIndex = i;
                whiteBestMovePieceW = iterationArrayW[0][i];
                whiteBestMoveXLocW = iterationArrayW[1][i];
                whiteBestMoveYLocW = iterationArrayW[2][i];
                whiteBestMoveXOrgLocW = xPositionArrayBase[whiteBestMovePieceW - 1];
                whiteBestMoveYOrgLocW = yPositionArrayBase[whiteBestMovePieceW - 1];
            }
        }
        // Step 71: Update the chess matrix with the white move.
        chessNotation(&chessMatrix, whiteBestMovePieceW, whiteBestMoveXOrgLocW, whiteBestMoveYOrgLocW, whiteBestMoveXLocW, whiteBestMoveYLocW);
        updateChessMatrix(&chessMatrix, whiteBestMovePieceW, whiteBestMoveXOrgLocW, whiteBestMoveYOrgLocW, whiteBestMoveXLocW, whiteBestMoveYLocW);

        // Step 72: Inquire the user to enter his move.
        printf("Please enter your move in Algebraic Notation:\n");
        scanf("%s", &userMove);
        // Step 73: Update the chess matrix with the user move.
        reverseChessNotation(&userMove, &chessMatrix, &userPiecePlay, &userPieceXLoc, &userPieceYLoc, &userPieceDestXLoc, &userPieceDestYLoc);
        updateChessMatrix(&chessMatrix, userPiecePlay, userPieceXLoc, userPieceYLoc, userPieceDestXLoc, userPieceDestYLoc);
    }
}