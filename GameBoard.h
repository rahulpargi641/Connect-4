#pragma once
#include <iostream>
#include <memory>

static constexpr int ROWS = 6;
static constexpr int COLS = 7;

struct Coordinate
{
int X, Y;

Coordinate(int x, int y) : X(x), Y(y)
{}
};

enum class EColumnStatus : unsigned char 
{ ECS_Full, ECS_Droppable };

struct ColumnInfo
{
EColumnStatus ColumnStatus;
Coordinate EmptySlot;

ColumnInfo(int colNo) : ColumnStatus(EColumnStatus::ECS_Droppable), EmptySlot({ROWS-1, colNo})
{}
};


class GameBoard
{
private:
std::string m_GameBoard[ROWS][COLS];
std::shared_ptr<ColumnInfo> m_ColumnsInfo[COLS];

public:
GameBoard();

void PrintGameBoard() const;

std::shared_ptr<ColumnInfo> const GetColumnInfo(char userInput) const;

void DropChipNModifyGameBoard(const Coordinate& slotPicked, const std::string& chip);

bool Are4ChipAligned(const std::string& playerChip) const;

private:
void InitializeGameBoard();

void InitializeColumnsInfo();

void UpdateColumnInfo(const Coordinate& nextEmptySlot);

bool IsColumnFull(int rowToDropChip) const;

bool AlignedHorizontally(const std::string& playerChip) const;
bool AlignedVertically(const std::string& playerChip) const;
bool AlignedDiagonallyUpperLeftToBottomRight(const std::string& playerChip) const;
bool AlignedDiagonallyUpperRightToBottomLeft(const std::string& playerChip) const;
};