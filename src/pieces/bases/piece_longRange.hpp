#pragma once 
#include "piece.hpp"

class LongRangePiece : public Piece {
   public:
    void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) override;
    bool SetAtackedPools(std::shared_ptr<Piece> grid[][8], bool atackedPools[8][8]) override;

   protected:
    LongRangePiece(float column, float row, const std::string& pieceName, std::vector<Vector2> moveDirections, PieceColor color) : Piece(column, row, pieceName, color), moveDirections(moveDirections){};
    virtual ~LongRangePiece() = default;
    std::vector<Vector2> moveDirections;
};