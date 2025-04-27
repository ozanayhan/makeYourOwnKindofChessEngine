#define WROOK1 1
#define WKNIGHT1 2
#define WBISHOP1 3
#define WQUEEN 4
#define WKING 5
#define WBISHOP2 6
#define WKNIGHT2 7
#define WROOK2 8
#define WPAWN1 9
#define WPAWN2 10
#define WPAWN3 11
#define WPAWN4 12
#define WPAWN5 13
#define WPAWN6 14
#define WPAWN7 15
#define WPAWN8 16
#define WPROMOTION1 17
#define WPROMOTION2 18

#define BROOK1 19
#define BKNIGHT1 20
#define BBISHOP1 21
#define BQUEEN 22
#define BKING 23
#define BBISHOP2 24
#define BKNIGHT2 25
#define BROOK2 26
#define BPAWN1 27
#define BPAWN2 28
#define BPAWN3 29
#define BPAWN4 30
#define BPAWN5 31
#define BPAWN6 32
#define BPAWN7 33
#define BPAWN8 34
#define BPROMOTION1 35
#define BPROMOTION2 36

#define SHORT_CASTLE_W 37
#define LONG_CASTLE_W 38
#define SHORT_CASTLE_B 39
#define LONG_CASTLE_B 40

#define NOTHING 255

#define VAL_SINGLE_SQUARE  0.05F
#define VAL_ATTACKED_PIECE  0.05F
#define VAL_PROTECTED_PIECE  0.01F
#define VAL_ATTACKED_PIECE_VALUE  0.02F
#define VAL_PROTECTED_PIECE_VALUE  0.01F
#define VAL_TERRITORY_VALUE  0.005F
#define VAL_ENPRISE_VALUE  0.10F

unsigned int chessMatrix[8][8] = {{WROOK1, WKNIGHT1, WBISHOP1, WQUEEN, WKING, WBISHOP2, WKNIGHT2, WROOK2},
                                   {WPAWN1, WPAWN2, WPAWN3, WPAWN4, WPAWN5, WPAWN6, WPAWN7, WPAWN8},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {BPAWN1, BPAWN2, BPAWN3, BPAWN4, BPAWN5, BPAWN6, BPAWN7, BPAWN8},
                                   {BROOK1, BKNIGHT1, BBISHOP1, BQUEEN, BKING, BBISHOP2, BKNIGHT2, BROOK2}};
/*
unsigned int chessMatrix[8][8] = {{NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WKING},
                                   {BROOK1, NOTHING, NOTHING, BQUEEN, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WPAWN8},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, BPAWN8},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, BPAWN7, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, BKING, NOTHING, NOTHING, NOTHING}};
*/ 

char str[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', '\0'};

unsigned int searchDimension[36] = {4, 8, 4, 8, 8, 4, 8, 4, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 4, 8, 4, 8, 8, 4, 8, 4, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0};
unsigned int ValPcsPos[36] = {5, 3, 3, 9, 18, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 5, 3, 3, 9, 18, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
unsigned int ValPcs[36] = {5, 3, 3, 9, 1000, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 5, 3, 3, 9, 1000, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};

unsigned int previousMovePlay = 0;
unsigned int previousMoveXLoc = 0;
unsigned int previousMoveYLoc = 0;
unsigned int previousMoveDestXLoc = 0;
unsigned int previousMoveDestYLoc = 0;
unsigned int chessMatrixPly1[8][8] = {0};
unsigned int chessMatrixPly2[8][8] = {0};
unsigned int chessMatrixPly3[8][8] = {0};
unsigned int chessMatrixPly4[8][8] = {0};
unsigned int chessMatrixPly5[8][8] = {0};
unsigned int chessMatrixPly6[8][8] = {0};

unsigned int xPositionArray[36] = {0};
unsigned int xPositionArrayBase[36] = {0};
unsigned int xPositionArrayPly1[36] = {0};
unsigned int xPositionArrayPly2[36] = {0};
unsigned int xPositionArrayPly3[36] = {0};
unsigned int xPositionArrayPly4[36] = {0};
unsigned int xPositionArrayPly5[36] = {0};
unsigned int xPositionArrayPly6[36] = {0};
unsigned int yPositionArray[36] = {0};
unsigned int yPositionArrayBase[36] = {0};
unsigned int yPositionArrayPly1[36] = {0};
unsigned int yPositionArrayPly2[36] = {0};
unsigned int yPositionArrayPly3[36] = {0};
unsigned int yPositionArrayPly4[36] = {0};
unsigned int yPositionArrayPly5[36] = {0};
unsigned int yPositionArrayPly6[36] = {0};

unsigned char userMove[10];
unsigned int userPiecePlay;
unsigned int userPieceXLoc;
unsigned int userPieceYLoc;
unsigned int userPieceDestXLoc;
unsigned int userPieceDestYLoc;

unsigned int wRook1PositionalControl[8][8] = {0};
unsigned int wRook2PositionalControl[8][8] = {0};
unsigned int wKnight1PositionalControl[8][8] = {0};
unsigned int wKnight2PositionalControl[8][8] = {0};
unsigned int wBishop1PositionalControl[8][8] = {0};
unsigned int wBishop2PositionalControl[8][8] = {0};
unsigned int wQueenPositionalControl[8][8] = {0};
unsigned int wKingPositionalControl[8][8] = {0};
unsigned int bRook1PositionalControl[8][8] = {0};
unsigned int bRook2PositionalControl[8][8] = {0};
unsigned int bKnight1PositionalControl[8][8] = {0};
unsigned int bKnight2PositionalControl[8][8] = {0};
unsigned int bBishop1PositionalControl[8][8] = {0};
unsigned int bBishop2PositionalControl[8][8] = {0};
unsigned int bQueenPositionalControl[8][8] = {0};
unsigned int bKingPositionalControl[8][8] = {0};

unsigned int wRook1ProtectionMatrix[8][8] = {0};
unsigned int wRook2ProtectionMatrix[8][8] = {0};
unsigned int wKnight1ProtectionMatrix[8][8] = {0};
unsigned int wKnight2ProtectionMatrix[8][8] = {0};
unsigned int wBishop1ProtectionMatrix[8][8] = {0};
unsigned int wBishop2ProtectionMatrix[8][8] = {0};
unsigned int wQueenProtectionMatrix[8][8] = {0};
unsigned int wKingProtectionMatrix[8][8] = {0};
unsigned int bRook1ProtectionMatrix[8][8] = {0};
unsigned int bRook2ProtectionMatrix[8][8] = {0};
unsigned int bKnight1ProtectionMatrix[8][8] = {0};
unsigned int bKnight2ProtectionMatrix[8][8] = {0};
unsigned int bBishop1ProtectionMatrix[8][8] = {0};
unsigned int bBishop2ProtectionMatrix[8][8] = {0};
unsigned int bQueenProtectionMatrix[8][8] = {0};
unsigned int bKingProtectionMatrix[8][8] = {0};

unsigned int wRook1AttackMatrix[8][8] = {0};
unsigned int wRook2AttackMatrix[8][8] = {0};
unsigned int wKnight1AttackMatrix[8][8] = {0};
unsigned int wKnight2AttackMatrix[8][8] = {0};
unsigned int wBishop1AttackMatrix[8][8] = {0};
unsigned int wBishop2AttackMatrix[8][8] = {0};
unsigned int wQueenAttackMatrix[8][8] = {0};
unsigned int wKingAttackMatrix[8][8] = {0};
unsigned int bRook1AttackMatrix[8][8] = {0};
unsigned int bRook2AttackMatrix[8][8] = {0};
unsigned int bKnight1AttackMatrix[8][8] = {0};
unsigned int bKnight2AttackMatrix[8][8] = {0};
unsigned int bBishop1AttackMatrix[8][8] = {0};
unsigned int bBishop2AttackMatrix[8][8] = {0};
unsigned int bQueenAttackMatrix[8][8] = {0};
unsigned int bKingAttackMatrix[8][8] = {0};

unsigned int wPawn1PositionalControl[8][8] = {0};
unsigned int wPawn1ProtectionMatrix[8][8] = {0};
unsigned int wPawn1AttackMatrix[8][8] = {0};
unsigned int wPawn2PositionalControl[8][8] = {0};
unsigned int wPawn2ProtectionMatrix[8][8] = {0};
unsigned int wPawn2AttackMatrix[8][8] = {0};
unsigned int wPawn3PositionalControl[8][8] = {0};
unsigned int wPawn3ProtectionMatrix[8][8] = {0};
unsigned int wPawn3AttackMatrix[8][8] = {0};
unsigned int wPawn4PositionalControl[8][8] = {0};
unsigned int wPawn4ProtectionMatrix[8][8] = {0};
unsigned int wPawn4AttackMatrix[8][8] = {0};
unsigned int wPawn5PositionalControl[8][8] = {0};
unsigned int wPawn5ProtectionMatrix[8][8] = {0};
unsigned int wPawn5AttackMatrix[8][8] = {0};
unsigned int wPawn6PositionalControl[8][8] = {0};
unsigned int wPawn6ProtectionMatrix[8][8] = {0};
unsigned int wPawn6AttackMatrix[8][8] = {0};
unsigned int wPawn7PositionalControl[8][8] = {0};
unsigned int wPawn7ProtectionMatrix[8][8] = {0};
unsigned int wPawn7AttackMatrix[8][8] = {0};
unsigned int wPawn8PositionalControl[8][8] = {0};
unsigned int wPawn8ProtectionMatrix[8][8] = {0};
unsigned int wPawn8AttackMatrix[8][8] = {0};

unsigned int bPawn1PositionalControl[8][8] = {0};
unsigned int bPawn1ProtectionMatrix[8][8] = {0};
unsigned int bPawn1AttackMatrix[8][8] = {0};
unsigned int bPawn2PositionalControl[8][8] = {0};
unsigned int bPawn2ProtectionMatrix[8][8] = {0};
unsigned int bPawn2AttackMatrix[8][8] = {0};
unsigned int bPawn3PositionalControl[8][8] = {0};
unsigned int bPawn3ProtectionMatrix[8][8] = {0};
unsigned int bPawn3AttackMatrix[8][8] = {0};
unsigned int bPawn4PositionalControl[8][8] = {0};
unsigned int bPawn4ProtectionMatrix[8][8] = {0};
unsigned int bPawn4AttackMatrix[8][8] = {0};
unsigned int bPawn5PositionalControl[8][8] = {0};
unsigned int bPawn5ProtectionMatrix[8][8] = {0};
unsigned int bPawn5AttackMatrix[8][8] = {0};
unsigned int bPawn6PositionalControl[8][8] = {0};
unsigned int bPawn6ProtectionMatrix[8][8] = {0};
unsigned int bPawn6AttackMatrix[8][8] = {0};
unsigned int bPawn7PositionalControl[8][8] = {0};
unsigned int bPawn7ProtectionMatrix[8][8] = {0};
unsigned int bPawn7AttackMatrix[8][8] = {0};
unsigned int bPawn8PositionalControl[8][8] = {0};
unsigned int bPawn8ProtectionMatrix[8][8] = {0};
unsigned int bPawn8AttackMatrix[8][8] = {0};

unsigned int wPositionalControl[8][8] = {0};
unsigned int wAttackMatrix[8][8] = {0};
unsigned int wAttackMatrixPly1[8][8] = {0};
unsigned int wAttackMatrixPly2[8][8] = {0};
unsigned int wAttackMatrixPly3[8][8] = {0};
unsigned int wAttackMatrixPly4[8][8] = {0};
unsigned int wAttackMatrixPly5[8][8] = {0};
unsigned int wAttackMatrixPly6[8][8] = {0};

unsigned int wProtectionMatrix[8][8] = {0};
unsigned int bPositionalControl[8][8] = {0};
unsigned int bAttackMatrix[8][8] = {0};
unsigned int bAttackMatrixPly1[8][8] = {0};
unsigned int bAttackMatrixPly2[8][8] = {0};
unsigned int bAttackMatrixPly3[8][8] = {0};
unsigned int bAttackMatrixPly4[8][8] = {0};
unsigned int bAttackMatrixPly5[8][8] = {0};
unsigned int bAttackMatrixPly6[8][8] = {0};
unsigned int bProtectionMatrix[8][8] = {0};

unsigned int ProtectionMapping[36][5] = {0};
unsigned int ProtectionMappingBase[36][5] = {0};
unsigned int ProtectionMappingPly1[36][5] = {0};
unsigned int ProtectionMappingPly2[36][5] = {0};
unsigned int ProtectionMappingPly3[36][5] = {0};
unsigned int ProtectionMappingPly4[36][5] = {0};
unsigned int ProtectionMappingPly5[36][5] = {0};
unsigned int ProtectionMappingPly6[36][5] = {0};
unsigned int AttackMapping[36][5] = {0};
unsigned int AttackMappingBase[36][5] = {0};
unsigned int AttackMappingPly1[36][5] = {0};
unsigned int AttackMappingPly2[36][5] = {0};
unsigned int AttackMappingPly3[36][5] = {0};
unsigned int AttackMappingPly4[36][5] = {0};
unsigned int AttackMappingPly5[36][5] = {0};
unsigned int AttackMappingPly6[36][5] = {0};

unsigned int iterationArrayW[3][100];
unsigned int iterationArrayWPly1[3][100];
unsigned int iterationArrayWPly2[3][100];
unsigned int iterationArrayWPly3[3][100];
unsigned int iterationArrayWPly4[3][100];
unsigned int iterationArrayWPly5[3][100];
unsigned int iterationArrayWPly6[3][100];

unsigned int iterationArrayB[3][100];
unsigned int iterationArrayBPly1[3][100];
unsigned int iterationArrayBPly2[3][100];
unsigned int iterationArrayBPly3[3][100];
unsigned int iterationArrayBPly4[3][100];
unsigned int iterationArrayBPly5[3][100];
unsigned int iterationArrayBPly6[3][100];

float overallEvalArray[6][100];
unsigned int iterationIndexW = 0;
unsigned int iterationIndexWPly1 = 0;
unsigned int iterationIndexWPly2 = 0;
unsigned int iterationIndexWPly3 = 0;
unsigned int iterationIndexWPly4 = 0;
unsigned int iterationIndexWPly5 = 0;
unsigned int iterationIndexWPly6 = 0;
unsigned int iterationIndexB = 0;
unsigned int iterationIndexBPly1 = 0;
unsigned int iterationIndexBPly2 = 0;
unsigned int iterationIndexBPly3 = 0;
unsigned int iterationIndexBPly4 = 0;
unsigned int iterationIndexBPly5 = 0;
unsigned int iterationIndexBPly6 = 0;

unsigned int iterationPieceW = 0;
unsigned int iterationXLocW = 0;
unsigned int iterationYLocW = 0;
unsigned int iterationXOrgLocW = 0;
unsigned int iterationYOrgLocW = 0;
unsigned int kingXLocW;
unsigned int kingXLocB;
unsigned int kingYLocW;
unsigned int kingYLocB;
unsigned int kingUnderAttackW;
unsigned int kingUnderAttackB;
unsigned int kingUnderAttackWPly1;
unsigned int kingUnderAttackWPly2;
unsigned int kingUnderAttackWPly3;
unsigned int kingUnderAttackWPly4;
unsigned int kingUnderAttackWPly5;
unsigned int kingUnderAttackWPly6;
unsigned int kingUnderAttackBPly1;
unsigned int kingUnderAttackBPly2;
unsigned int kingUnderAttackBPly3;
unsigned int kingUnderAttackBPly4;
unsigned int kingUnderAttackBPly5;
unsigned int kingUnderAttackBPly6;

unsigned int iterationPieceB = 0;
unsigned int iterationXLocB = 0;
unsigned int iterationYLocB = 0;
unsigned int iterationXOrgLocB = 0;
unsigned int iterationYOrgLocB = 0;

unsigned int wRook1xPosition;
unsigned int wRook1yPosition;
unsigned int wKnight1xPosition;
unsigned int wKnight1yPosition;
unsigned int wBishop1xPosition;
unsigned int wBishop1yPosition;
unsigned int wQueen1xPosition;
unsigned int wQueen1yPosition;
unsigned int wPawn1xPosition;
unsigned int wPawn1yPosition;
unsigned int wPawn2xPosition;
unsigned int wPawn2yPosition;
unsigned int wPawn3xPosition;
unsigned int wPawn3yPosition;
unsigned int wPawn4xPosition;
unsigned int wPawn4yPosition;
unsigned int wPawn5xPosition;
unsigned int wPawn5yPosition;
unsigned int wPawn6xPosition;
unsigned int wPawn6yPosition;
unsigned int wPawn7xPosition;
unsigned int wPawn7yPosition;
unsigned int wPawn8xPosition;
unsigned int wPawn8yPosition;

unsigned int bRook1xPosition;
unsigned int bRook1yPosition;
unsigned int bKnight1xPosition;
unsigned int bKnight1yPosition;
unsigned int bBishop1xPosition;
unsigned int bQueen1xPosition;
unsigned int bQueen1yPosition;
unsigned int bPawn1xPosition;
unsigned int bPawn1yPosition;
unsigned int bPawn2xPosition;
unsigned int bPawn2yPosition;
unsigned int bPawn3xPosition;
unsigned int bPawn3yPosition;
unsigned int bPawn4xPosition;
unsigned int bPawn4yPosition;
unsigned int bPawn5xPosition;
unsigned int bPawn5yPosition;
unsigned int bPawn6xPosition;
unsigned int bPawn6yPosition;
unsigned int bPawn7xPosition;
unsigned int bPawn7yPosition;
unsigned int bPawn8xPosition;
unsigned int bPawn8yPosition;

unsigned int PiecexPosition;
unsigned int PieceyPosition;

unsigned int territoryIndexW;
unsigned int territoryIndexB;

unsigned int searchIndex = 1;
unsigned int xIndex = 0;
unsigned int yIndex = 0;

unsigned int flgRookPiece = 0;
unsigned int flgKnightPiece = 0;
unsigned int flgBishopPiece = 0;
unsigned int flgQueenPiece = 0;
unsigned int flgKingPiece = 0;
unsigned int flgPawnPiece = 0;
unsigned int flgRangePiece = 0;
unsigned int flgWhitePiece = 0;
unsigned int flgBlackPiece = 0;

unsigned int wTotNumSqControlled = 0;
unsigned int wTotNumPcsProtected = 0;
unsigned int wTotNumPcsAttacked = 0;
unsigned int bTotNumSqControlled = 0;
unsigned int bTotNumPcsProtected = 0;
unsigned int bTotNumPcsAttacked = 0;
unsigned int wTotNumPcsEnPrise = 0;
unsigned int bTotNumPcsEnPrise = 0;
unsigned int wValPcsAttack = 0;
unsigned int bValPcsAttack = 0;
unsigned int wValPcsProtect = 0;
unsigned int bValPcsProtect = 0;

unsigned int wAttackedPiece = 0;
unsigned int bAttackedPiece = 0;

unsigned int ProtectionArray[5] = {0};
unsigned int AttackArray[5] = {0};
unsigned int wNumAttackingPiece = 0;
unsigned int bNumProtectingPiece = 0;
unsigned int bNumAttackingPiece = 0;
unsigned int wNumProtectingPiece = 0;

unsigned int protectionIndex = 0;
unsigned int attackIndex = 0;

int wMaterialGainCapture1 = 0;
int wMaterialGainCapture2 = 0;
int wMaterialGainCapture3 = 0;
int wMaterialGainCapture4 = 0;
int wMaterialGainCapture5 = 0;
int wMaterialGain = 0;
int wMaxMaterialGain = 0;

int wMaterialLossCapture1 = 0;
int wMaterialLossCapture2 = 0;
int wMaterialLossCapture3 = 0;
int wMaterialLossCapture4 = 0;
int wMaterialLossCapture5 = 0;
int wMaterialLoss = 0;
int wMaxMaterialLoss = 0;
int wExchangeGain = 0;
int wExchangeLoss = 0;

float positionEval = 0.0F;
float positionEvalPly1 = 0.0F;
float positionEvalPly2 = 0.0F;
float positionEvalPly3 = 0.0F;
float positionEvalPly4 = 0.0F;
float positionEvalPly5 = 0.0F;
float positionEvalPly6 = 0.0F;
float materialEval = 0.0F;
float materialEvalPly1 = 0.0F;
float materialEvalPly2 = 0.0F;
float materialEvalPly3 = 0.0F;
float materialEvalPly4 = 0.0F;
float materialEvalPly5 = 0.0F;
float materialEvalPly6 = 0.0F;
float overallEval = 0.0F;
float overallEvalPly1 = 0.0F;
float overallEvalPly2 = 0.0F;
float overallEvalPly3 = 0.0F;
float overallEvalPly3Temp = 0.0F;
float overallEvalPly4 = 0.0F;
float overallEvalPly4Temp = 0.0F;
float overallEvalPly4Temp2 = 0.0F;
float overallEvalPly5 = 0.0F;
float overallEvalPly6 = 0.0F;

float whiteBestMoveEval = -1100.0F;
float whiteTempBestMoveEval = -1100.0F;
unsigned int whiteBestMoveIndex;
unsigned int whiteBestMovePieceW;
unsigned int whiteBestMoveXOrgLocW;
unsigned int whiteBestMoveYOrgLocW;
unsigned int whiteBestMoveXLocW;
unsigned int whiteBestMoveYLocW;

unsigned int pawnXLoc;
unsigned int pawnYLoc;

unsigned int wMaterialCount;
unsigned int bMaterialCount;
float wMaterialBalance;

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
        if (piecePlay >= BPAWN1 && piecePlay <= BPAWN8 && pieceDestYLoc == 2 && (pieceDestXLoc - pieceXLoc == 1 || pieceXLoc - pieceDestXLoc == 1))
        {
            (*chessMatrix)[pieceDestYLoc][pieceDestXLoc] = piecePlay;
            (*chessMatrix)[3][pieceDestXLoc] = NOTHING;
            (*chessMatrix)[pieceYLoc][pieceXLoc] = NOTHING;
        }
        else if (piecePlay >= WPAWN1 && piecePlay <= WPAWN8 && pieceDestYLoc == 6 && (pieceDestXLoc - pieceXLoc == 1 || pieceXLoc - pieceDestXLoc == 1))
        {
            (*chessMatrix)[pieceDestYLoc][pieceDestXLoc] = piecePlay;
            (*chessMatrix)[4][pieceDestXLoc] = NOTHING;
            (*chessMatrix)[pieceYLoc][pieceXLoc] = NOTHING;
        }
        else 
        {
            (*chessMatrix)[pieceDestYLoc][pieceDestXLoc] = piecePlay;
            (*chessMatrix)[pieceYLoc][pieceXLoc] = NOTHING;
        }
        
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

void resetIterationArrays(unsigned int (*IterationArray)[3][100])
{
    for (unsigned int j = 0; j < 3; j++)
    {
        for (unsigned int i = 0; i < 300; i++)
        {
            (*IterationArray)[j][i] = 0;
        }
    }
}
void resetOverallEvallArrays(float (*overallEvalArray)[6][100])
{
    for (unsigned int j = 0; j < 6; j++)
    {
        for (unsigned int i = 0; i < 300; i++)
        {
            (*overallEvalArray)[j][i] = -2000.0F;
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

void processPieceActivity(unsigned int chessMatrix[8][8], unsigned int pieces, unsigned int PiecexPosition, unsigned int PieceyPosition, unsigned int (*PositionalControl)[8][8], unsigned int (*ProtectionMatrix)[8][8], unsigned int (*AttackMatrix)[8][8], unsigned int (*ProtectionMapping)[36][5], unsigned int (*AttackMapping)[36][5], unsigned int (*iterationArrayW)[3][100], unsigned int(*iterationIndexW), unsigned int (*iterationArrayB)[3][100], unsigned int(*iterationIndexB))
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

void processBoardPosition(unsigned int chessMatrix[8][8], float(*positionEval), unsigned int (*wAttackMatrix)[8][8], unsigned int (*bAttackMatrix)[8][8], unsigned int (*iterationArrayW)[3][100], unsigned int(*iterationIndexW), unsigned int (*iterationArrayB)[3][100], unsigned int(*iterationIndexB))
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

void amendIterationArray(unsigned int chessMatrix[8][8], unsigned int (*iterationArray)[3][100], unsigned int(*iterationIndex), unsigned int moveWhite, unsigned int AttackMatrix[8][8], unsigned int previousMovePlay, unsigned int previousMoveXLoc, unsigned int previousMoveYLoc, unsigned int previousMoveDestXLoc, unsigned int previousMoveDestYLoc)
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
            if (pawnYLoc == 4 && previousMovePlay >= BPAWN1 && previousMovePlay <= BPAWN8 && previousMoveYLoc == 6 && previousMoveDestYLoc == 4 && (previousMoveDestXLoc - pawnXLoc == 1 || pawnXLoc - previousMoveDestXLoc == 1))
            {
                (*iterationArray)[0][(*iterationIndex)] = pieces;
                (*iterationArray)[1][(*iterationIndex)] = previousMoveDestXLoc;
                (*iterationArray)[2][(*iterationIndex)] = 5;
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
            if (pawnYLoc == 3 && previousMovePlay >= WPAWN1 && previousMovePlay <= WPAWN8 && previousMoveYLoc == 1 && previousMoveDestYLoc == 3 && (previousMoveDestXLoc - pawnXLoc == 1 || pawnXLoc - previousMoveDestXLoc == 1))
            {
                (*iterationArray)[0][(*iterationIndex)] = pieces;
                (*iterationArray)[1][(*iterationIndex)] = previousMoveDestXLoc;
                (*iterationArray)[2][(*iterationIndex)] = 2;
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

void updateOverallEval(float (*overallEvalArray)[6][100], float overallEval, unsigned int movesIndex, unsigned int Ply)
{
    (*overallEvalArray)[(Ply)][movesIndex] = overallEval;
}