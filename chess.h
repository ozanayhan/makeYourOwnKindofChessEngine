

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
                                   {WPAWN1, WPAWN2, WPAWN3, WPAWN4, NOTHING, WPAWN6, WPAWN7, WPAWN8},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, WPAWN5, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, BPAWN5, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {BPAWN1, BPAWN2, BPAWN3, BPAWN4, NOTHING, BPAWN6, BPAWN7, BPAWN8},
                                   {BROOK1, BKNIGHT1, BBISHOP1, BQUEEN, BKING, BBISHOP2, BKNIGHT2, BROOK2}};

/*
unsigned int chessMatrix[8][8] = {{NOTHING, NOTHING, WROOK1, NOTHING, WKING, NOTHING, NOTHING, WROOK2},
                                   {WQUEEN, WBISHOP1, WPAWN3, NOTHING, NOTHING, WPAWN6, WBISHOP2, WPAWN8},
                                   {NOTHING, WPAWN2, WKNIGHT1, WPAWN4, NOTHING, WKNIGHT2, WPAWN7, NOTHING},
                                   {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING},
                                   {BPAWN1, NOTHING, NOTHING, BPAWN4, WPAWN5, NOTHING, NOTHING, NOTHING},
                                   {NOTHING, BPAWN2, BKNIGHT1, NOTHING, BPAWN5, NOTHING, BPAWN7, NOTHING},
                                   {NOTHING, BBISHOP1, BPAWN3, BQUEEN, BKNIGHT2, BPAWN6, BBISHOP2, BPAWN8},
                                   {NOTHING, NOTHING, NOTHING, BROOK1, BKING, NOTHING, NOTHING, BROOK2}};
*/ 

unsigned int chessMatrixPly1[8][8] = { 0 };
unsigned int chessMatrixPly2[8][8] = { 0 };
unsigned int chessMatrixPly3[8][8] = { 0 };
unsigned int chessMatrixPly4[8][8] = { 0 };
unsigned int chessMatrixPly5[8][8] = { 0 };
unsigned int chessMatrixPly6[8][8] = { 0 };

unsigned int xPositionArray[36] = { NOTHING };
unsigned int xPositionArrayBase[36] = { NOTHING };
unsigned int xPositionArrayPly1[36] = { NOTHING };
unsigned int xPositionArrayPly2[36] = { NOTHING };
unsigned int xPositionArrayPly3[36] = { NOTHING };
unsigned int xPositionArrayPly4[36] = { NOTHING };
unsigned int xPositionArrayPly5[36] = { NOTHING };
unsigned int xPositionArrayPly6[36] = { NOTHING };
unsigned int yPositionArray[36] = { NOTHING };
unsigned int yPositionArrayBase[36] = { NOTHING };
unsigned int yPositionArrayPly1[36] = { NOTHING };
unsigned int yPositionArrayPly2[36] = { NOTHING };
unsigned int yPositionArrayPly3[36] = { NOTHING };
unsigned int yPositionArrayPly4[36] = { NOTHING };
unsigned int yPositionArrayPly5[36] = { NOTHING };
unsigned int yPositionArrayPly6[36] = { NOTHING };

unsigned char userMove[10];
unsigned int userPiecePlay;
unsigned int userPieceXLoc;
unsigned int userPieceYLoc;
unsigned int userPieceDestXLoc;
unsigned int userPieceDestYLoc;


unsigned int searchDimension[36] = {4, 8, 4, 8, 8, 4, 8, 4, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 4, 8, 4, 8, 8, 4, 8, 4, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0};
unsigned int ValPcsPos[36] = {5, 3, 3, 9, 18, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 5, 3, 3, 9, 18, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
unsigned int ValPcs[36] = {5, 3, 3, 9, 1000, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 5, 3, 3, 9, 1000, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};

char str[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h','\0'};

unsigned int wRook1PositionalControl[8][8] = { 0 };
unsigned int wRook2PositionalControl[8][8] = { 0 };
unsigned int wKnight1PositionalControl[8][8] = { 0 };
unsigned int wKnight2PositionalControl[8][8] = { 0 };
unsigned int wBishop1PositionalControl[8][8] = { 0 };
unsigned int wBishop2PositionalControl[8][8] = { 0 };
unsigned int wQueenPositionalControl[8][8] = { 0 };
unsigned int wKingPositionalControl[8][8] = { 0 };
unsigned int bRook1PositionalControl[8][8] = { 0 };
unsigned int bRook2PositionalControl[8][8] = { 0 };
unsigned int bKnight1PositionalControl[8][8] = { 0 };
unsigned int bKnight2PositionalControl[8][8] = { 0 };
unsigned int bBishop1PositionalControl[8][8] = { 0 };
unsigned int bBishop2PositionalControl[8][8] = { 0 };
unsigned int bQueenPositionalControl[8][8] = { 0 };
unsigned int bKingPositionalControl[8][8] = { 0 };

unsigned int wRook1ProtectionMatrix[8][8] = { 0 };
unsigned int wRook2ProtectionMatrix[8][8] = { 0 };
unsigned int wKnight1ProtectionMatrix[8][8] = { 0 };
unsigned int wKnight2ProtectionMatrix[8][8] = { 0 };
unsigned int wBishop1ProtectionMatrix[8][8] = { 0 };
unsigned int wBishop2ProtectionMatrix[8][8] = { 0 };
unsigned int wQueenProtectionMatrix[8][8] = { 0 };
unsigned int wKingProtectionMatrix[8][8] = { 0 };
unsigned int bRook1ProtectionMatrix[8][8] = { 0 };
unsigned int bRook2ProtectionMatrix[8][8] = { 0 };
unsigned int bKnight1ProtectionMatrix[8][8] = { 0 };
unsigned int bKnight2ProtectionMatrix[8][8] = { 0 };
unsigned int bBishop1ProtectionMatrix[8][8] = { 0 };
unsigned int bBishop2ProtectionMatrix[8][8] = { 0 };
unsigned int bQueenProtectionMatrix[8][8] = { 0 };
unsigned int bKingProtectionMatrix[8][8] = { 0 };

unsigned int wRook1AttackMatrix[8][8] = { 0 };
unsigned int wRook2AttackMatrix[8][8] = { 0 };
unsigned int wKnight1AttackMatrix[8][8] = { 0 };
unsigned int wKnight2AttackMatrix[8][8] = { 0 };
unsigned int wBishop1AttackMatrix[8][8] = { 0 };
unsigned int wBishop2AttackMatrix[8][8] = { 0 };
unsigned int wQueenAttackMatrix[8][8] = { 0 };
unsigned int wKingAttackMatrix[8][8] = { 0 };
unsigned int bRook1AttackMatrix[8][8] = { 0 };
unsigned int bRook2AttackMatrix[8][8] = { 0 };
unsigned int bKnight1AttackMatrix[8][8] = { 0 };
unsigned int bKnight2AttackMatrix[8][8] = { 0 };
unsigned int bBishop1AttackMatrix[8][8] = { 0 };
unsigned int bBishop2AttackMatrix[8][8] = { 0 };
unsigned int bQueenAttackMatrix[8][8] = { 0 };
unsigned int bKingAttackMatrix[8][8] = { 0 };

unsigned int wPawn1PositionalControl[8][8] = { 0 };
unsigned int wPawn1ProtectionMatrix[8][8] = { 0 };
unsigned int wPawn1AttackMatrix[8][8] = { 0 };
unsigned int wPawn2PositionalControl[8][8] = { 0 };
unsigned int wPawn2ProtectionMatrix[8][8] = { 0 };
unsigned int wPawn2AttackMatrix[8][8] = { 0 };
unsigned int wPawn3PositionalControl[8][8] = { 0 };
unsigned int wPawn3ProtectionMatrix[8][8] = { 0 };
unsigned int wPawn3AttackMatrix[8][8] = { 0 };
unsigned int wPawn4PositionalControl[8][8] = { 0 };
unsigned int wPawn4ProtectionMatrix[8][8] = { 0 };
unsigned int wPawn4AttackMatrix[8][8] = { 0 };
unsigned int wPawn5PositionalControl[8][8] = { 0 };
unsigned int wPawn5ProtectionMatrix[8][8] = { 0 };
unsigned int wPawn5AttackMatrix[8][8] = { 0 };
unsigned int wPawn6PositionalControl[8][8] = { 0 };
unsigned int wPawn6ProtectionMatrix[8][8] = { 0 };
unsigned int wPawn6AttackMatrix[8][8] = { 0 };
unsigned int wPawn7PositionalControl[8][8] = { 0 };
unsigned int wPawn7ProtectionMatrix[8][8] = { 0 };
unsigned int wPawn7AttackMatrix[8][8] = { 0 };
unsigned int wPawn8PositionalControl[8][8] = { 0 };
unsigned int wPawn8ProtectionMatrix[8][8] = { 0 };
unsigned int wPawn8AttackMatrix[8][8] = { 0 };

unsigned int bPawn1PositionalControl[8][8] = { 0 };
unsigned int bPawn1ProtectionMatrix[8][8] = { 0 };
unsigned int bPawn1AttackMatrix[8][8] = { 0 };
unsigned int bPawn2PositionalControl[8][8] = { 0 };
unsigned int bPawn2ProtectionMatrix[8][8] = { 0 };
unsigned int bPawn2AttackMatrix[8][8] = { 0 };
unsigned int bPawn3PositionalControl[8][8] = { 0 };
unsigned int bPawn3ProtectionMatrix[8][8] = { 0 };
unsigned int bPawn3AttackMatrix[8][8] = { 0 };
unsigned int bPawn4PositionalControl[8][8] = { 0 };
unsigned int bPawn4ProtectionMatrix[8][8] = { 0 };
unsigned int bPawn4AttackMatrix[8][8] = { 0 };
unsigned int bPawn5PositionalControl[8][8] = { 0 };
unsigned int bPawn5ProtectionMatrix[8][8] = { 0 };
unsigned int bPawn5AttackMatrix[8][8] = { 0 };
unsigned int bPawn6PositionalControl[8][8] = { 0 };
unsigned int bPawn6ProtectionMatrix[8][8] = { 0 };
unsigned int bPawn6AttackMatrix[8][8] = { 0 };
unsigned int bPawn7PositionalControl[8][8] = { 0 };
unsigned int bPawn7ProtectionMatrix[8][8] = { 0 };
unsigned int bPawn7AttackMatrix[8][8] = { 0 };
unsigned int bPawn8PositionalControl[8][8] = { 0 };
unsigned int bPawn8ProtectionMatrix[8][8] = { 0 };
unsigned int bPawn8AttackMatrix[8][8] = { 0 };

unsigned int wPositionalControl[8][8] = { 0 };
unsigned int wAttackMatrix[8][8] = { 0 };
unsigned int wAttackMatrixPly1[8][8] = { 0 };
unsigned int wAttackMatrixPly2[8][8] = { 0 };
unsigned int wAttackMatrixPly3[8][8] = { 0 };
unsigned int wAttackMatrixPly4[8][8] = { 0 };
unsigned int wAttackMatrixPly5[8][8] = { 0 };
unsigned int wAttackMatrixPly6[8][8] = { 0 };

unsigned int wProtectionMatrix[8][8] = { 0 };
unsigned int bPositionalControl[8][8] = { 0 };
unsigned int bAttackMatrix[8][8] = { 0 };
unsigned int bAttackMatrixPly1[8][8] = { 0 };
unsigned int bAttackMatrixPly2[8][8] = { 0 };
unsigned int bAttackMatrixPly3[8][8] = { 0 };
unsigned int bAttackMatrixPly4[8][8] = { 0 };
unsigned int bAttackMatrixPly5[8][8] = { 0 };
unsigned int bAttackMatrixPly6[8][8] = { 0 };
unsigned int bProtectionMatrix[8][8] = { 0 };

unsigned int ProtectionMapping[36][5] = { 0 };
unsigned int ProtectionMappingBase[36][5] = { 0 };
unsigned int ProtectionMappingPly1[36][5] = { 0 };
unsigned int ProtectionMappingPly2[36][5] = { 0 };
unsigned int ProtectionMappingPly3[36][5] = { 0 };
unsigned int ProtectionMappingPly4[36][5] = { 0 };
unsigned int ProtectionMappingPly5[36][5] = { 0 };
unsigned int ProtectionMappingPly6[36][5] = { 0 };
unsigned int AttackMapping[36][5] = { 0 };
unsigned int AttackMappingBase[36][5] = { 0 };
unsigned int AttackMappingPly1[36][5] = { 0 };
unsigned int AttackMappingPly2[36][5] = { 0 };
unsigned int AttackMappingPly3[36][5] = { 0 };
unsigned int AttackMappingPly4[36][5] = { 0 };
unsigned int AttackMappingPly5[36][5] = { 0 };
unsigned int AttackMappingPly6[36][5] = { 0 };

unsigned int iterationArrayW[3][300];
unsigned int iterationArrayWPly1[3][300];
unsigned int iterationArrayWPly2[3][300];
unsigned int iterationArrayWPly3[3][300];
unsigned int iterationArrayWPly4[3][300];
unsigned int iterationArrayWPly5[3][300];
unsigned int iterationArrayWPly6[3][300];

unsigned int iterationArrayB[3][300];
unsigned int iterationArrayBPly1[3][300];
unsigned int iterationArrayBPly2[3][300];
unsigned int iterationArrayBPly3[3][300];
unsigned int iterationArrayBPly4[3][300];
unsigned int iterationArrayBPly5[3][300];
unsigned int iterationArrayBPly6[3][300];

float overallEvalArray[6][300];
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

unsigned int ProtectionArray[5] = { 0 };
unsigned int AttackArray[5] = { 0 };
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