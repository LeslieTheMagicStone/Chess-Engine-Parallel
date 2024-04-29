#include "piece.hpp"

extern int cellSize;

// ### KING ### //

class King : public Piece {
   public:
    King(float column, float row) : Piece(column, row){};
    virtual ~King() = default;
    void Move() override {}
    int getValue() override { return 20; }
};

class KingBlack : public King {
   public:
    KingBlack(float column, float row) : King(column, row) {
        Image image = LoadImage("Graphics/kingBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~KingBlack() { UnloadTexture(texture); }
};

class KingWhite : public King {
   public:
    KingWhite(float column, float row) : King(column, row) {
        Image image = LoadImage("Graphics/kingWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~KingWhite() { UnloadTexture(texture); }
};

// ### QUEEN ### //

class Queen : public Piece {
   public:
    Queen(float column, float row) : Piece(column, row){};
    virtual ~Queen() = default;
    void Move() override {}
    int getValue() override { return 10; }
};

class QueenBlack : public Queen {
   public:
    QueenBlack(float column, float row) : Queen(column, row) {
        Image image = LoadImage("Graphics/QueenBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~QueenBlack() { UnloadTexture(texture); }
};

class QueenWhite : public Queen {
   public:
    QueenWhite(float column, float row) : Queen(column, row) {
        Image image = LoadImage("Graphics/QueenWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~QueenWhite() { UnloadTexture(texture); }
};

// ### ROOK ### //

class Rook : public Piece {
   public:
    Rook(float column, float row) : Piece(column, row){};
    virtual ~Rook() = default;
    void Move() override {}
    int getValue() override { return 5; }
};

class RookBlack : public Rook {
   public:
    RookBlack(float column, float row) : Rook(column, row) {
        Image image = LoadImage("Graphics/RookBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~RookBlack() { UnloadTexture(texture); }
};

class RookWhite : public Rook {
   public:
    RookWhite(float column, float row) : Rook(column, row) {
        Image image = LoadImage("Graphics/RookWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~RookWhite() { UnloadTexture(texture); }
};

// ### HORSE ###//

class Horse : public Piece {
   public:
    Horse(float column, float row) : Piece(column, row){};
    virtual ~Horse() = default;
    void Move() override {}
    int getValue() override { return 3; }
};

class HorseBlack : public Horse {
   public:
    HorseBlack(float column, float row) : Horse(column, row) {
        Image image = LoadImage("Graphics/HorseBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~HorseBlack() { UnloadTexture(texture); }
};

class HorseWhite : public Horse {
   public:
    HorseWhite(float column, float row) : Horse(column, row) {
        Image image = LoadImage("Graphics/HorseWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~HorseWhite() { UnloadTexture(texture); }
};

// ### BISHOP ### //

class Bishop : public Piece {
   public:
    Bishop(float column, float row) : Piece(column, row){};
    virtual ~Bishop() = default;
    void Move() override {}
    int getValue() override { return 3; }
};

class BishopBlack : public Bishop {
   public:
    BishopBlack(float column, float row) : Bishop(column, row) {
        Image image = LoadImage("Graphics/BishopBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~BishopBlack() { UnloadTexture(texture); }
};

class BishopWhite : public Bishop {
   public:
    BishopWhite(float column, float row) : Bishop(column, row) {
        Image image = LoadImage("Graphics/BishopWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~BishopWhite() { UnloadTexture(texture); }
};

// ### PAWN ### //

class Pawn : public Piece {
   public:
    Pawn(float column, float row) : Piece(column, row){};
    virtual ~Pawn() = default;
    int getValue() override { return 1; }
};

class PawnBlack : public Pawn {
   public:
    PawnBlack(float column, float row) : Pawn(column, row) {
        Image image = LoadImage("Graphics/pawnBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    void Move() override {}
    ~PawnBlack() { UnloadTexture(texture); }
};

class PawnWhite : public Pawn {
   public:
    PawnWhite(float column, float row) : Pawn(column, row) {
        Image image = LoadImage("Graphics/pawnWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    void Move() override {}
    ~PawnWhite() { UnloadTexture(texture); }
};