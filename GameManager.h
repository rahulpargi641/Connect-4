#pragma once
#include <cstdlib>
#include "GameBoard.h"

class GameManager
{
private:
enum class EGameState : unsigned char
{ EGS_Gameplay, EGS_Gameover };

EGameState m_GameState = EGameState::EGS_Gameplay;
unsigned int m_Moves = 0;
std::string m_CurrentPlayerChip;
char m_ValidUserInput;
std::shared_ptr<GameBoard> m_GameBoard;

public:
GameManager();

void GameIntroduction() const;

void StartGameLoop();

private:
char ReadInput() const;

bool IsInputValid(char userInput) const;

void ReadValidateAndCaptureInput();

void DropChipAndModifyGameBoard();

void CheckIfWinOrTie();

bool IsGameTie() const;

std::string GenerateRandomPlayerTurn() const;
};
