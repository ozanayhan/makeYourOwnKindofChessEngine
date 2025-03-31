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
    }
}

void processPieceActivity(unsigned int chessMatrix[8][8], unsigned int pieces, unsigned int PiecexPosition, unsigned int PieceyPosition, unsigned int (*PositionalControl)[8][8], unsigned int (*ProtectionMatrix)[8][8], unsigned int (*AttackMatrix)[8][8], unsigned int (*ProtectionMapping)[36][5], unsigned int (*AttackMapping)[36][5])
{
    flgRookPiece = pieces == WROOK1 || pieces == WROOK2 || pieces == BROOK1 || pieces == BROOK2;
    flgKnightPiece = pieces == WKNIGHT1 || pieces == WKNIGHT2 || pieces == BKNIGHT1 || pieces == BKNIGHT2;
    flgBishopPiece = pieces == WBISHOP1 || pieces == WBISHOP2 || pieces == BBISHOP1 || pieces == BBISHOP2;
    flgQueenPiece = pieces == WQUEEN || pieces == BQUEEN;
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
                (*ProtectionMatrix)[yIndex][xIndex] = pieceAtPosition;
                i = 0;
                while ((*ProtectionMapping)[(pieceAtPosition - 1)][i] && i < 6)
                {
                    i++;
                }
                if (i < 6)
                    (*ProtectionMapping)[(pieceAtPosition - 1)][i] = pieces;
                searchIndex = 1;
                break;
            }
            else if ((flgWhitePiece && (pieceAtPosition > WPROMOTION2)) || (flgBlackPiece && (pieceAtPosition <= WPROMOTION2)))
            {
                (*AttackMatrix)[yIndex][xIndex] = pieceAtPosition;
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

void materialBalance(unsigned int chessMatrix[8][8], float (*materialEval), unsigned int (*wAttackMatrix)[8][8], unsigned int (*bAttackMatrix)[8][8], unsigned int (*ProtectionMapping)[36][5], unsigned int (*AttackMapping)[36][5])
{
    for (unsigned int j = 0; j < 8; j++)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
            chessMatrixTemp[j][i] = chessMatrix[j][i];
        }
    }
    for (unsigned int j = 0; j < 8; j++)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
            if ((*wAttackMatrix)[j][i])
            {
                wAttackedPiece = chessMatrixTemp[j][i];
                for (unsigned int k = 0; k < 5; k++)
                {
                    protectionIndex = ((*ProtectionMapping)[wAttackedPiece - 1][k]);
                    attackIndex = ((*AttackMapping)[wAttackedPiece - 1][k]);
                    ProtectionArray[k] = protectionIndex ? ValPcs[protectionIndex - 1] : NOTHING;
                    AttackArray[k] = attackIndex ? ValPcs[attackIndex - 1] : NOTHING;
                    if (protectionIndex)
                        bNumProtectingPiece = k;
                    if (attackIndex)
                        wNumAttackingPiece = k;
                }
                quickSort(ProtectionArray, 0, 4);
                quickSort(AttackArray, 0, 4);

                for (unsigned int k = 0; k < 5; k++) {
                    ProtectionArray[k] = ProtectionArray[k] == NOTHING ? 0 : ProtectionArray[k];
                    AttackArray[k] = AttackArray[k] == NOTHING ? 0 : AttackArray[k];
                }

                if (wNumAttackingPiece < bNumProtectingPiece)
                {
                    wMaterialGainCapture1 = ValPcs[wAttackedPiece - 1] - AttackArray[1];
                    wMaterialGainCapture2 = wMaterialGainCapture1 + ProtectionArray[1] - AttackArray[2];
                    wMaterialGainCapture3 = wMaterialGainCapture2 + ProtectionArray[2] - AttackArray[3];
                    wMaterialGainCapture4 = wMaterialGainCapture3 + ProtectionArray[3] - AttackArray[4];
                    wMaterialGainCapture5 = wMaterialGainCapture4 + ProtectionArray[4] - AttackArray[5];
                }
                else
                {
                    wMaterialGainCapture1 = ValPcs[wAttackedPiece - 1];
                    wMaterialGainCapture2 = wMaterialGainCapture1 - AttackArray[1] + ProtectionArray[1];
                    wMaterialGainCapture3 = wMaterialGainCapture2 - AttackArray[2] + ProtectionArray[2];
                    wMaterialGainCapture4 = wMaterialGainCapture3 - AttackArray[3] + ProtectionArray[3];
                    wMaterialGainCapture5 = wMaterialGainCapture4 - AttackArray[4] + ProtectionArray[4];
                }
                wMaterialGain = findMin(wMaterialGainCapture1, wMaterialGainCapture2, wMaterialGainCapture3, wMaterialGainCapture4, wMaterialGainCapture5);
                wMaterialGain = wMaterialGain < 0 ? 0 : wMaterialGain;
                wMaxMaterialGain = wMaterialGain > wMaxMaterialGain ? wMaterialGain : wMaxMaterialGain;
            }

            if ((*bAttackMatrix)[j][i])
            {
                bAttackedPiece = chessMatrixTemp[j][i];
                for (unsigned int k = 0; k < 5; k++)
                {
                    protectionIndex = ((*ProtectionMapping)[bAttackedPiece - 1][k]);
                    attackIndex = ((*AttackMapping)[bAttackedPiece - 1][k]);
                    ProtectionArray[k] = protectionIndex ? ValPcs[protectionIndex - 1] : NOTHING;
                    AttackArray[k] = attackIndex ? ValPcs[attackIndex - 1] : NOTHING;
                    if (protectionIndex)
                        wNumProtectingPiece = k;
                    if (attackIndex)
                        bNumAttackingPiece = k;
                }
                quickSort(ProtectionArray, 0, 4);
                quickSort(AttackArray, 0, 4);

                for (unsigned int k = 0; k < 5; k++) {
                    ProtectionArray[k] = ProtectionArray[k] == NOTHING ? 0 : ProtectionArray[k];
                    AttackArray[k] = AttackArray[k] == NOTHING ? 0 : AttackArray[k];
                }

                if (bNumAttackingPiece > wNumProtectingPiece)
                {
                    wMaterialLossCapture1 = -ProtectionArray[1];
                    wMaterialLossCapture2 = wMaterialLossCapture1 + AttackArray[1] - ProtectionArray[2];
                    wMaterialLossCapture3 = wMaterialLossCapture2 + AttackArray[2] - ProtectionArray[3];
                    wMaterialLossCapture4 = wMaterialLossCapture3 + AttackArray[3] - ProtectionArray[4];
                    wMaterialLossCapture5 = wMaterialLossCapture4 + AttackArray[4] - ProtectionArray[5];
                }
                else
                {
                    wMaterialLossCapture1 = AttackArray[1] - ProtectionArray[1];
                    wMaterialLossCapture2 = wMaterialLossCapture1 + AttackArray[2] - ProtectionArray[2];
                    wMaterialLossCapture3 = wMaterialLossCapture2 + AttackArray[3] - ProtectionArray[3];
                    wMaterialLossCapture4 = wMaterialLossCapture3 + AttackArray[4] - ProtectionArray[4];
                    wMaterialLossCapture5 = wMaterialLossCapture4 + AttackArray[5] - ProtectionArray[5];
                }
                wMaterialLoss = findMax(wMaterialLossCapture1, wMaterialLossCapture2, wMaterialLossCapture3, wMaterialLossCapture4, wMaterialLossCapture5);
                wMaterialLoss = wMaterialLoss > 0 ? 0 : wMaterialLoss;
                wMaxMaterialLoss = wMaterialLoss < wMaxMaterialLoss ? wMaterialLoss : wMaxMaterialLoss;
            }
        }
    }

    (*materialEval) = (float)wMaxMaterialGain - (float)wMaxMaterialLoss;
}

void processBoardPosition(unsigned int chessMatrix[8][8], float (*positionEval), unsigned int (*wAttackMatrix)[8][8], unsigned int (*bAttackMatrix)[8][8])
{
    getPiecePositions(chessMatrix, &xPositionArray, &yPositionArray);
    for (unsigned int pieces = WROOK1; pieces <= BPROMOTION2; pieces++)
    {
        if (xPositionArray[pieces - 1] == NOTHING || yPositionArray[pieces - 1] == NOTHING)
            continue;
        PiecexPosition = xPositionArray[pieces - 1];
        PieceyPosition = yPositionArray[pieces - 1];
        switch (pieces)
        {
        case WROOK1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wRook1PositionalControl, &wRook1ProtectionMatrix, &wRook1AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WKNIGHT1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wKnight1PositionalControl, &wKnight1ProtectionMatrix, &wKnight1AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WBISHOP1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wBishop1PositionalControl, &wBishop1ProtectionMatrix, &wBishop1AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WQUEEN:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wQueenPositionalControl, &wQueenProtectionMatrix, &wQueenAttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WKING:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wKingPositionalControl, &wKingProtectionMatrix, &wKingAttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WBISHOP2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wBishop2PositionalControl, &wBishop2ProtectionMatrix, &wBishop2AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WKNIGHT2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wKnight2PositionalControl, &wKnight2ProtectionMatrix, &wKnight2AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WROOK2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wRook2PositionalControl, &wRook2ProtectionMatrix, &wRook2AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WPAWN1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn1PositionalControl, &wPawn1ProtectionMatrix, &wPawn1AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WPAWN2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn2PositionalControl, &wPawn2ProtectionMatrix, &wPawn2AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WPAWN3:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn3PositionalControl, &wPawn3ProtectionMatrix, &wPawn3AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WPAWN4:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn4PositionalControl, &wPawn4ProtectionMatrix, &wPawn4AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WPAWN5:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn5PositionalControl, &wPawn5ProtectionMatrix, &wPawn5AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WPAWN6:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn6PositionalControl, &wPawn6ProtectionMatrix, &wPawn6AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WPAWN7:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn7PositionalControl, &wPawn7ProtectionMatrix, &wPawn7AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case WPAWN8:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &wPawn8PositionalControl, &wPawn8ProtectionMatrix, &wPawn8AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;

        case BROOK1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bRook1PositionalControl, &bRook1ProtectionMatrix, &bRook1AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BKNIGHT1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bKnight1PositionalControl, &bKnight1ProtectionMatrix, &bKnight1AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BBISHOP1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bBishop1PositionalControl, &bBishop1ProtectionMatrix, &bBishop1AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BQUEEN:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bQueenPositionalControl, &bQueenProtectionMatrix, &bQueenAttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BKING:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bKingPositionalControl, &bKingProtectionMatrix, &bKingAttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BBISHOP2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bBishop2PositionalControl, &bBishop2ProtectionMatrix, &bBishop2AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BKNIGHT2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bKnight2PositionalControl, &bKnight2ProtectionMatrix, &bKnight2AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BROOK2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bRook2PositionalControl, &bRook2ProtectionMatrix, &bRook2AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BPAWN1:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn1PositionalControl, &bPawn1ProtectionMatrix, &bPawn1AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BPAWN2:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn2PositionalControl, &bPawn2ProtectionMatrix, &bPawn2AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BPAWN3:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn3PositionalControl, &bPawn3ProtectionMatrix, &bPawn3AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BPAWN4:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn4PositionalControl, &bPawn4ProtectionMatrix, &bPawn4AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BPAWN5:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn5PositionalControl, &bPawn5ProtectionMatrix, &bPawn5AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BPAWN6:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn6PositionalControl, &bPawn6ProtectionMatrix, &bPawn6AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BPAWN7:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn7PositionalControl, &bPawn7ProtectionMatrix, &bPawn7AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        case BPAWN8:
            processPieceActivity(chessMatrix, pieces, PiecexPosition, PieceyPosition, &bPawn8PositionalControl, &bPawn8ProtectionMatrix, &bPawn8AttackMatrix, &ProtectionMapping, &AttackMapping);
            break;
        }
    }

    for (unsigned int j = 0; j < 8; j++)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
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
    (*positionEval) = (((float)wTotNumSqControlled - (float)bTotNumSqControlled) * VAL_SINGLE_SQUARE)  + 
    (((float)wTotNumPcsAttacked - (float)bTotNumPcsAttacked) * VAL_ATTACKED_PIECE) + 
    (((float)wTotNumPcsProtected - (float)bTotNumPcsProtected) * VAL_PROTECTED_PIECE) + 
    (((float)wValPcsAttack - (float)bValPcsAttack) * VAL_ATTACKED_PIECE_VALUE) + 
    (((float)wValPcsProtect - (float)bValPcsProtect) * VAL_PROTECTED_PIECE_VALUE);
}

int main(void)
{
    processBoardPosition(chessMatrix, &positionEval, &wAttackMatrix, &bAttackMatrix);

    materialBalance(chessMatrix, &materialEval, &wAttackMatrix, &bAttackMatrix, &ProtectionMapping, &AttackMapping);
    overallEval = materialEval + positionEval;
}