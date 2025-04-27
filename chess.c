#include <stdio.h>
#include <string.h>
#include "chess.h"

int main(void)
{
    for (unsigned int t = 0; t < 30; t++)
    {
        resetOverallEvallArrays(&overallEvalArray);
        // Step 1: Get the iteration Array for the Current Board Position, and obtain the attack matrices and a positional evaluation.
        processBoardPosition(chessMatrix, &positionEval, &wAttackMatrix, &bAttackMatrix, &iterationArrayW, &iterationIndexW, &iterationArrayB, &iterationIndexB);
        // Step 2: Amend the Iteration Array with pawn moves and special moves like castling and en passant.
        amendIterationArray(chessMatrix, &iterationArrayW, &iterationIndexW, 1, bAttackMatrix, previousMovePlay, previousMoveXLoc, previousMoveYLoc, previousMoveDestXLoc, previousMoveDestYLoc);
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
        unsigned int i;
        unsigned int numAvlMovesW = 0;
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
            previousMovePlay = iterationPieceW;
            previousMoveXLoc = iterationXLocW;
            previousMoveYLoc = iterationYLocW;
            previousMoveDestXLoc = iterationXOrgLocW;
            previousMoveDestYLoc = iterationYOrgLocW;
            // Step 10: Update the chess board for Ply1.
            updateChessMatrix(&chessMatrixPly1, iterationPieceW, iterationXOrgLocW, iterationYOrgLocW, iterationXLocW, iterationYLocW);
            // Step 11: Get the iteration Array for the New (Ply1) Board Position, and obtain the attack matrices and a positional evaluation.
            processBoardPosition(chessMatrixPly1, &positionEvalPly1, &wAttackMatrixPly1, &bAttackMatrixPly1, &iterationArrayWPly1, &iterationIndexWPly1, &iterationArrayBPly1, &iterationIndexBPly1);
            // Step 12: Amend the black Iteration Array for Ply2.
            amendIterationArray(chessMatrixPly1, &iterationArrayBPly1, &iterationIndexBPly1, 0, wAttackMatrixPly1, previousMovePlay, previousMoveXLoc, previousMoveYLoc, previousMoveDestXLoc, previousMoveDestYLoc);
            // Step 13: Get piece positions for the new board
            getPiecePositions(chessMatrixPly1, &xPositionArrayPly1, &yPositionArrayPly1);
            // Step 14: Check if the White King is  under attack in the new position.
            kingXLocW = xPositionArrayPly1[WKING - 1];
            kingYLocW = yPositionArrayPly1[WKING - 1];
            kingUnderAttackWPly1 = !!bAttackMatrixPly1[kingYLocW][kingXLocW];
            // Step 15: If the White King is under attack after the move, this is not allowed, and will be skipped.
            if (kingUnderAttackWPly1)
                continue;
            ++numAvlMovesW;
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
            unsigned int j;
            unsigned int numAvlMovesB = 0;
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
                previousMovePlay = iterationPieceW;
                previousMoveXLoc = iterationXLocW;
                previousMoveYLoc = iterationYLocW;
                previousMoveDestXLoc = iterationXOrgLocW;
                previousMoveDestYLoc = iterationYOrgLocW;
                // Step 25: Update the chess board for Ply2.
                updateChessMatrix(&chessMatrixPly2, iterationPieceB, iterationXOrgLocB, iterationYOrgLocB, iterationXLocB, iterationYLocB);
                // Step 26: Get the iteration Array for the New (Ply2) Board Position, and obtain the attack matrices and a positional evaluation.
                processBoardPosition(chessMatrixPly2, &positionEvalPly2, &wAttackMatrixPly2, &bAttackMatrixPly2, &iterationArrayWPly2, &iterationIndexWPly2, &iterationArrayBPly2, &iterationIndexBPly2);
                // Step 27: Amend the Iteration Array with pawn moves and special moves like castling and en passant.
                amendIterationArray(chessMatrixPly2, &iterationArrayWPly2, &iterationIndexWPly2, 1, bAttackMatrixPly2, previousMovePlay, previousMoveXLoc, previousMoveYLoc, previousMoveDestXLoc, previousMoveDestYLoc);
                // Step 28: Get piece positions for the new board
                getPiecePositions(chessMatrixPly2, &xPositionArrayPly2, &yPositionArrayPly2);
                // Step 29: Check if the Black King is  under attack in the new position.
                kingXLocB = xPositionArrayPly2[BKING - 1];
                kingYLocB = yPositionArrayPly2[BKING - 1];
                kingUnderAttackBPly2 = !!wAttackMatrixPly2[kingYLocB][kingXLocB];
                // Step 30: If the Black King is under attack after the move, this is not allowed, and will be skipped.
                if (kingUnderAttackBPly2)
                    continue;
                ++numAvlMovesB;
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
                    previousMovePlay = iterationPieceW;
                    previousMoveXLoc = iterationXLocW;
                    previousMoveYLoc = iterationYLocW;
                    previousMoveDestXLoc = iterationXOrgLocW;
                    previousMoveDestYLoc = iterationYOrgLocW;
                    // Step 40: Update the chess board for Ply3.
                    updateChessMatrix(&chessMatrixPly3, iterationPieceW, iterationXOrgLocW, iterationYOrgLocW, iterationXLocW, iterationYLocW);
                    // Step 41: Get the iteration Array for the New (Ply3) Board Position, and obtain the attack matrices and a positional evaluation.
                    processBoardPosition(chessMatrixPly3, &positionEvalPly3, &wAttackMatrixPly3, &bAttackMatrixPly3, &iterationArrayWPly3, &iterationIndexWPly3, &iterationArrayBPly3, &iterationIndexBPly3);
                    // Step 42: Amend the black Iteration Array for Ply2.
                    amendIterationArray(chessMatrixPly3, &iterationArrayBPly3, &iterationIndexBPly3, 0, wAttackMatrixPly3, previousMovePlay, previousMoveXLoc, previousMoveYLoc, previousMoveDestXLoc, previousMoveDestYLoc);
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
                        previousMovePlay = iterationPieceW;
                        previousMoveXLoc = iterationXLocW;
                        previousMoveYLoc = iterationYLocW;
                        previousMoveDestXLoc = iterationXOrgLocW;
                        previousMoveDestYLoc = iterationYOrgLocW;
                        // Step 55: Update the chess board for Ply4.
                        updateChessMatrix(&chessMatrixPly4, iterationPieceB, iterationXOrgLocB, iterationYOrgLocB, iterationXLocB, iterationYLocB);
                        // Step 56: Get the iteration Array for the New (Ply4) Board Position, and obtain the attack matrices and a positional evaluation.
                        processBoardPosition(chessMatrixPly4, &positionEvalPly4, &wAttackMatrixPly4, &bAttackMatrixPly4, &iterationArrayWPly4, &iterationIndexWPly4, &iterationArrayBPly4, &iterationIndexBPly4);
                        // Step 57: Amend the Iteration Array with pawn moves and special moves like castling and en passant.
                        amendIterationArray(chessMatrixPly4, &iterationArrayWPly4, &iterationIndexWPly4, 1, bAttackMatrixPly4, previousMovePlay, previousMoveXLoc, previousMoveYLoc, previousMoveDestXLoc, previousMoveDestYLoc);
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
            if (!numAvlMovesB && kingUnderAttackBPly1)
            {
                whiteBestMovePieceW = iterationArrayW[0][i];
                whiteBestMoveXLocW = iterationArrayW[1][i];
                whiteBestMoveYLocW = iterationArrayW[2][i];
                whiteBestMoveXOrgLocW = xPositionArrayBase[whiteBestMovePieceW - 1];
                whiteBestMoveYOrgLocW = yPositionArrayBase[whiteBestMovePieceW - 1];
                // Step 71: Update the chess matrix with the white move.
                chessNotation(&chessMatrix, whiteBestMovePieceW, whiteBestMoveXOrgLocW, whiteBestMoveYOrgLocW, whiteBestMoveXLocW, whiteBestMoveYLocW);
                printf("Checkmate Black. I win!");
                return 0;
            }
        }
        // Step 69: Checkmate Recognition:
        if (!numAvlMovesW && kingUnderAttackW)
        {
            printf("Checkmate White. Congratulations!");
            return 0;
        }
        else if (!numAvlMovesW && !kingUnderAttackW)
        {
            printf("Stalemate. Draw!");
            return 0;
        }

        // Step 70: Selecting the best 1st move for White based on 4th Ply Evaluation:
        whiteBestMoveEval = -2000.0F;
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
        previousMovePlay = userPiecePlay;
        previousMoveXLoc = userPieceXLoc;
        previousMoveYLoc = userPieceYLoc;
        previousMoveDestXLoc = userPieceDestXLoc;
        previousMoveDestYLoc = userPieceDestYLoc;
        updateChessMatrix(&chessMatrix, userPiecePlay, userPieceXLoc, userPieceYLoc, userPieceDestXLoc, userPieceDestYLoc);
    }
}