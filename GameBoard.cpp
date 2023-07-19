#include "GameBoard.h"

GameBoard::GameBoard()
{
  InitializeGameBoard();
  InitializeColumnsInfo();
}

void GameBoard::InitializeGameBoard()
{
  for(int i = 0; i < ROWS; i++)
    for(int j = 0; j < COLS; j++)
      m_GameBoard[i][j] = "";
}

void GameBoard::InitializeColumnsInfo()
{
  for(int j = 0; j < COLS; j++)
    m_ColumnsInfo[j] = std::make_shared<ColumnInfo>(j);
}

void GameBoard::PrintGameBoard() const
{
  std::cout << "\n     A    B    C    D    E    F    G    ";
  for(int i = 0; i < ROWS; i++)
    {
      std::cout << "\n   +----+----+----+----+----+----+----+\n";
      std::cout << i << "  |";
      for(int j = 0; j < COLS; j++)
        {
          if(m_GameBoard[i][j] == "🔵")
            std::cout << " 🔵 |";
          else if(m_GameBoard[i][j] == "🔴")
            std::cout << " 🔴 |";
          else
          std::cout << "    |";
        }
    }
  std::cout << "\n   +----+----+----+----+----+----+----+\n";
  std::cout << "____________________________________________\n";
}

std::shared_ptr<ColumnInfo> const GameBoard::GetColumnInfo(char userInput) const
{
    int columnIdx;
    if(userInput >= 'A' && userInput <= 'G')
      columnIdx = userInput - 'A';
    else
      columnIdx = userInput - 'a';

    return m_ColumnsInfo[columnIdx];
}

void GameBoard::DropChipNModifyGameBoard(const Coordinate& slotPicked, const std::string& chip)
{
  m_GameBoard[slotPicked.X][slotPicked.Y] = chip;
  UpdateColumnInfo({slotPicked.X - 1, slotPicked.Y});
}

bool GameBoard::Are4ChipAligned(const std::string& playerChip) const
{
  return AlignedHorizontally(playerChip) || AlignedVertically(playerChip) || AlignedDiagonallyUpperLeftToBottomRight(playerChip) || AlignedDiagonallyUpperRightToBottomLeft(playerChip);
}

void GameBoard::UpdateColumnInfo(const Coordinate& nextEmptySlot)
{
  const int columnToUpdate = nextEmptySlot.Y;
  const int rowToDropChip = nextEmptySlot.X;
  
  bool columnFull = IsColumnFull(rowToDropChip);
  if(columnFull)
    m_ColumnsInfo[columnToUpdate]->ColumnStatus = EColumnStatus::ECS_Full;
  else
    m_ColumnsInfo[columnToUpdate]->EmptySlot = nextEmptySlot;
}

bool GameBoard::IsColumnFull(int rowToDropChip) const
{
  if(rowToDropChip == -1)
    return true;
  else
    return false;
}

bool GameBoard::AlignedHorizontally(const std::string& playerChip) const
{
  for (int y = 0; y < ROWS; y++)
  {
    for (int x = 0; x < COLS - 3; x++)
    {
      // Check if horizontally aligned
      if (x + 3 < COLS && m_GameBoard[x][y] == playerChip && m_GameBoard[x+1][y] == playerChip && m_GameBoard[x+2][y] == playerChip && m_GameBoard[x+3][y] == playerChip)
        return true;
    }
  }
  return false;
}

bool GameBoard::AlignedVertically(const std::string& playerChip) const
{
  for (int x = 0; x < ROWS; x++)
  {
    for (int y = 0; y < COLS - 3; y++)
    {
      // Check if vertically aligned
      if (y + 3 < COLS && m_GameBoard[x][y] == playerChip && m_GameBoard[x][y+1] == playerChip && m_GameBoard[x][y+2] == playerChip && m_GameBoard[x][y+3] == playerChip)
        return true;
    }
  }
  return false;
}

bool GameBoard::AlignedDiagonallyUpperLeftToBottomRight(const std::string& playerChip) const
{
  for (int x = 0; x < ROWS - 3; x++)
  {
    for (int y = 0; y < COLS - 3; y++)
    {
      // check if upper left to bottom right diagonally alinged
      if (x + 3 < ROWS && y + 3 < COLS && m_GameBoard[x][y] == playerChip && m_GameBoard[x+1][y+1] == playerChip && m_GameBoard[x+2][y+2] == playerChip && m_GameBoard[x+3][y+3] == playerChip)
        return true;
    }
  }
  return false;
}

bool GameBoard::AlignedDiagonallyUpperRightToBottomLeft(const std::string& playerChip) const
{
  for (int x = 0; x < ROWS - 3; x++)
  {
    for (int y = 3; y < COLS; y++)
    {
      // Check if upper right to bottom left diagonally aligned
      if (x + 3 < ROWS && y - 3 >= 0 && m_GameBoard[x][y] == playerChip && m_GameBoard[x+1][y-1] == playerChip && m_GameBoard[x+2][y-2] == playerChip && m_GameBoard[x+3][y-3] == playerChip)
        return true;
    }
   }
  return false;
}
