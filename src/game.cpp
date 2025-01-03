#include "game.hpp"

#include <raylib.h>
#include <raymath.h>

#include <fstream>
#include <thread>
#include <algorithm>

#include "ChessAI/ChessAI.hpp"
#include "chessboard/chessboard.hpp"
#include "move/move.hpp"
#include "pieces/models/include.hpp"
#include "resources/audio.hpp"

int cellSize = 100;

enum class GameStatus {
    playing,
    whiteWin,
    blackWin,
    STALEMATE,
    THREEFOLD_REPETITION,
};

Game::Game(StateMachine& sm) :State(sm) {
    LoadSettingsData();
    gameStatus = GameStatus::playing;
    ColorTurn = PieceColor::white;
    chessboard.initPieces();
    InitSounds();
}

Game::~Game() {
    delete move;
    UnloadSounds();
}

void Game::HandleInput() {
    if (AIDoingMove) return;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !move && gameStatus == GameStatus::playing) {
        const int x = GetMouseX() / cellSize;
        const int y = GetMouseY() / cellSize;
        const bool isOwnPieceClick = chessboard.grid[x + y * 8].get() && (chessboard.grid[x + y * 8]->color == ColorTurn);
        const bool isLegalMove = (clickedPiece && std::any_of(clickedPiece->legalMoves.begin(), clickedPiece->legalMoves.end(), [&](auto move) {
            return Vector2Equals(move, {static_cast<float>(x), static_cast<float>(y)});
        }));

        // logic on click
        if (isOwnPieceClick && time>0.1) {
            clickedPiece = chessboard.grid[x + y * 8];
        } else if (clickedPiece && isLegalMove) {
            move = new Move{clickedPiece->position, {static_cast<float>(x), static_cast<float>(y)}, chessboard};
            clickedPiece = nullptr;
        }
    }
    if(IsKeyPressed(KEY_R) && !move && gameStatus == GameStatus::playing && !Move::moveTokens.empty()) {
        if(ai1==nullptr) {
            move = Move::GetUndoMove(chessboard);
        }
        else if(ai2==nullptr){
            move = Move::GetUndoMove(chessboard);
            undoMovevsAi=true;
        }
    }
}

void Game::Update() {
    if (gameStatus != GameStatus::playing) return;

    time += GetFrameTime();

    if (move) {
        move->Update();
        if (move->animationEnd) {
            move->ExecuteMove();
            if (move->winningMove) gameStatus = (ColorTurn == PieceColor::white) ? GameStatus::whiteWin : GameStatus::blackWin;
            if (move->stalematingMove) gameStatus = GameStatus::STALEMATE;
            if (move->stalematingMove && Move::positionHistory.size() >= 3) gameStatus = GameStatus::THREEFOLD_REPETITION;
            delete move;
            move = nullptr;
            if(undoMovevsAi){
                undoMovevsAi=false;
                move = Move::GetUndoMove(chessboard);
                ColorTurn = (ColorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
            }
            else ColorTurn = (ColorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
            clickedPiece = nullptr;
            AIDoingMove = false;
        }
    } else if (!AIDoingMove && ((ai1 && ColorTurn == ai1->colorAI) || ai2)) {
        AIDoingMove = true;
        std::thread aiThread([&](){
            move = ColorTurn == ai1->colorAI ? ai1->GetMove(chessboard) : ai2->GetMove(chessboard);
            if (move->promotion) move->AI_promotion = true;
        });
        aiThread.detach();
    }
}

void Game::Draw() {
    BeginDrawing();

    chessboard.DrawSquares();
    chessboard.DrawPieces();
    if (clickedPiece) chessboard.DrawSelectedPieceDetails(clickedPiece);
    if (move) move->MoveAnimation();
    if (move && move->promotion && !move->AI_promotion) move->PromoteAnimation();
    if (gameStatus != GameStatus::playing) GameOver();

    EndDrawing();
}

void Game::LoadSettingsData() {
    std::ifstream file("../src/GameSettings.txt");
    std::string text;
    while (file >> text) {
        if (text == "PvP") {
            file >> text;
            if (text == "true") {
                ai1 = nullptr;
                ai2 = nullptr;
            }
        } else if (text == "PvAI") {
            file >> text;
            if (text == "true") {
                file >> text >> text;  // skip "ChessAIColor"
                ai1 = std::make_unique<ChessAI>(text == "black" ? PieceColor::black : PieceColor::white);
                ai2 = nullptr;
            }
        } else if (text == "AIvAI") {
            file >> text;
            if (text == "true") {
                ai1 = std::make_unique<ChessAI>(PieceColor::black);
                ai2 = std::make_unique<ChessAI>(PieceColor::white);
            }
        } else if (text == "TargetFPS") {
            int fps;
            file >> fps;
            SetTargetFPS(fps);
        }
    }
    file.close();
}

void Game::GameOver() const {
    std::string resultText;
    switch (gameStatus) {
        case GameStatus::whiteWin:
            resultText = "WHITE WINS";
            break;
        case GameStatus::blackWin:
            resultText = "BLACK WINS";
            break;
        case GameStatus::STALEMATE:
            resultText = "STALEMATE";
            break;
        case GameStatus::THREEFOLD_REPETITION:
            resultText = "THREEFOLD REPETITION";
            break;
        default:
            break;
    }
    
    DrawRectangle(0, 0, 800, 800, Fade(BLACK, 0.8f));
    DrawText("GAME OVER", (800 - MeasureText("GAME OVER", 50)) / 2, 300, 50, WHITE);
    DrawText(resultText.c_str(), (800 - MeasureText(resultText.c_str(), 50)) / 2, 380, 50, WHITE);
}