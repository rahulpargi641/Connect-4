#include "GameManager.h"

GameManager::GameManager()
{
  m_CurrentPlayerChip = GenerateRandomPlayerTurn();
  m_GameBoard = std::make_shared<GameBoard>();
}

void GameManager::GameIntroduction() const
{
  const std::string infoText = 
  R"(🔴🔵 WELCOME TO CONNECT 4! A two-player turn-based game 🔴🔵
  
  How to Play:
  - Select a column between A-G to drop the chip when the turn is yours.
  - Column will be filled from bottom to top.

  Win Condition:
  - A player will win if he aligns 4 chips horizontally, vertically, or diagonally.
  )";

  std::cout << infoText << std::endl;
}

void GameManager::StartGameLoop()
{
  m_GameBoard->PrintGameBoard();
  
  while (m_GameState == EGameState::EGS_Gameplay) 
  { //Making player enter columns between A-Z or a-z 
    ReadValidateAndCaptureInput();
    //Successfully user entered the correct column, now perform actions
    DropChipAndModifyGameBoard();
    //After dropping the chip check Win or tie and update the game state
    CheckIfWinOrTie();
    //Switch turn
    m_CurrentPlayerChip = m_CurrentPlayerChip == "🔴" ? "🔵" : "🔴";
  }
}

char GameManager::ReadInput() const
{
  std::cout << "\nPlayer " << m_CurrentPlayerChip << " turn. Pick a Column (A-G): ";
  char userInput;
  std::cin >> userInput;
  return userInput;
}

bool GameManager::IsInputValid(char userInput) const
{
  if((userInput >= 'A' && userInput <= 'G') || (userInput >= 'a' && userInput <= 'g'))
    return true;
  else
    return false;
}

void GameManager::ReadValidateAndCaptureInput()
{
  char userInput = ReadInput();
  if(! IsInputValid(userInput))
  {
    std::cout << "\nINVALID INPUT!, Choose the correct column." << std::endl;
    ReadValidateAndCaptureInput();
  }
  else
  { m_ValidUserInput = userInput; }
}

void GameManager::DropChipAndModifyGameBoard()
{ //Getting information about the column picked by the user
  const std::shared_ptr<ColumnInfo> pickedColumnInfo = m_GameBoard->GetColumnInfo(m_ValidUserInput);
  //If the picked column status is FULL means there's no empty slot available
  if(pickedColumnInfo->ColumnStatus == EColumnStatus::ECS_Full)
  {
    std::cout << "\nCOLUMN IS FULL, Choose the empty column." << std::endl;
    ReadValidateAndCaptureInput();
  } 
  //If the picked column status is Droppable means there's an empty slot available
  else if(pickedColumnInfo->ColumnStatus == EColumnStatus::ECS_Droppable)
  {//Getting coordinates of the empty slot to drop the chip
    Coordinate emptySlot = pickedColumnInfo->EmptySlot;  
    //Dropping the chip and modifying the Game Board
    m_GameBoard->DropChipNModifyGameBoard(emptySlot, m_CurrentPlayerChip);
    m_GameBoard->PrintGameBoard();
    m_Moves++;
  }
}

void GameManager::CheckIfWinOrTie()
{
  if(m_GameBoard->Are4ChipAligned(m_CurrentPlayerChip))
  {
    std::cout << "\nGame over " << m_CurrentPlayerChip << " wins! 🎉 Thank you for playing :)" << std::endl; 
    m_GameState = EGameState::EGS_Gameover; 
  }

  if(IsGameTie())
  {
    std::cout << "\nThe game is a tie. Thank you for playing :)\n";
    m_GameState = EGameState::EGS_Gameover;
  }
}

bool GameManager::IsGameTie() const
{
  if(m_Moves == (ROWS * COLS))
    return true;
  else
    return false;
}

std::string GameManager::GenerateRandomPlayerTurn() const
{
  srand(static_cast<unsigned int>(time(nullptr)));
  int turn = rand() % 2 + 1;
  return turn == 1 ? "🔴" : "🔵";
}


