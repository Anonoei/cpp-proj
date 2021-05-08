/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "TetrisLogic.h"

void TetrisLogic::Init()
{
	tPROFILE_FUNCTION();
	this->Tetro = nullptr;
	this->IsPolyMoving = false;
	QueueNextArray();
	this->s_Board.Init();
	this->HighestLocation = this->s_Board.GetHeight();
}

int TetrisLogic::Queue()
{
	tPROFILE_FUNCTION();
	this->SpawnIndex++;
	if (SpawnIndex == 7)	//	We need to queue the next array
	{
		int Piece7 = this->SpawnNum[6];
		QueueNextArray();
		return Piece7;
	}
	return this->SpawnNum[this->SpawnIndex - 1];
}

Points TetrisLogic::Spawn()
{
	tPROFILE_FUNCTION();
	int spawn = Queue();
	Tetromino* tetro = new Tetromino;
	this->Tetro = tetro->Spawn(spawn);
	Points locations = GetLocations();
	this->SetIsMoving(true);
	this->floatPoints.clear();
	for (int i = 0; i < locations.Size(); i++)
		this->floatPoints.push_back({ (float)(locations[i].y), (float)(locations[i].x) });
	SetUpdateBoard(true);
	return locations;
}

bool TetrisLogic::Update()
{
	tPROFILE_FUNCTION();
	if (GetUpdateBoard())
	{
		if (IsMoving())
		{
			Points NewLocations = GetLocations();
			Points OldLocations = GetOldPositions();
			if (!OldLocations.IsEmpty())
			{
				s_Board.Erase(OldLocations);
				s_Board.Draw(NewLocations, this->Tetro->GetType());
			}
		}
		this->s_Board.Print(this->GetNextChar());
		this->ActiveGame = this->CheckHeight();
		this->CheckWidth();
		SetUpdateBoard(false);
	}
	return this->ActiveGame;
}
void TetrisLogic::Move(daTimestep ts, Translation direction)
{
	tPROFILE_FUNCTION();
	bool move = false;
	bool ModifyY = true;
	fPoint TranslateValue = { 0.0f, 0.0f };
	if (direction == Translation::Down)
	{
		TranslateValue = { 0.003f , 0.0f };
		ModifyY = true;
	}
	else if (direction == Translation::DownPressed)
	{
		TranslateValue = { 0.005f, 0.0f };
		ModifyY = true;
	}
	else if (direction == Translation::Left)
	{
		TranslateValue = { 0.0f, -0.004f };
		ModifyY = false;
	}
	else if (direction == Translation::Right)
	{
		TranslateValue = { 0.0f, 0.004f };
		ModifyY = false;
	}
	if (ModifyY)
	{
		std::vector<fPoint> oldFloatPoints = this->floatPoints;
		floatPoints.clear();
		for (int i = 0; i < oldFloatPoints.size(); i++)
		{
			floatPoints.push_back({ (oldFloatPoints[i].y + TranslateValue.y * ts), (oldFloatPoints[i].x) });
			if (floatPoints[i].y >= (GetLocations())[i].y + 1)
				move = true;
		}
	}
	else
	{
		std::vector<fPoint> oldFloatPoints = this->floatPoints;
		floatPoints.clear();
		for (int i = 0; i < oldFloatPoints.size(); i++)
		{
			floatPoints.push_back({ (oldFloatPoints[i].y), (oldFloatPoints[i].x + TranslateValue.x * ts) });
			if (direction == Translation::Left)
			{
				if (floatPoints[i].x <= (GetLocations())[i].x - 1)
					move = true;
			}
			else
			{
				if (floatPoints[i].x >= (GetLocations())[i].x + 1)
					move = true;
			}
		}
	}
	if (move)
	{
		if (direction == Translation::DownPressed)
			MoveTetro(Translation::Down);
		else
			MoveTetro(direction);
	}
}

//	This function preforms all of the error checking or... logic, and the tetromino executes it
void TetrisLogic::MoveTetro(Translation direction)
{
	tPROFILE_FUNCTION();
	Point value;
	Points& PreviousLocations = GetLocations();
	Points NewLocations;
	bool ValidMove = true;
	bool ModifyY = true;
	int TranslateValue = 0;
	if (direction == Translation::Down)
	{
		TranslateValue = 1;	//	Move down 1 
		ModifyY = true;
	}
	else if (direction == Translation::Left)
	{
		TranslateValue = -1;	//	Move left 1
		ModifyY = false;
	}
	else if (direction == Translation::Right)
	{
		TranslateValue = 1;		//	Move right 1
		ModifyY = false;
	}
	for (int i = 0; i < PreviousLocations.Size(); i++)
	{
		value = PreviousLocations.Get(i);
		if (ModifyY)
		{
			// GetMaxHeight stores the value of y at a specific x
			if (((value.y + TranslateValue) < this->s_Board.GetMaxHeight(value.x)) || ((value.y + TranslateValue < this->s_Board.GetHeight()) && (this->s_Board.IsLocationClear(PreviousLocations, value.y + TranslateValue, value.x))))	//	Height
				this->Tetro->Translate(direction, value);
			else
				ValidMove = false;
		}
		else
		{
			if (((value.x + TranslateValue) < (this->s_Board.GetWidth())) && ((value.x + TranslateValue) >= 0) && (this->s_Board.IsLocationClear(PreviousLocations, value.y, value.x + TranslateValue )))	//	Width
				this->Tetro->Translate(direction, value);
			else	//	Move is not valid, revert to previous state
				ValidMove = false;
		}
		NewLocations.Add(value);
	}
	if (ValidMove)
	{
		this->Tetro->SetLocations(NewLocations);
		floatPoints.clear();
		for (int i = 0; i < NewLocations.Size(); i++)
			floatPoints.push_back({ (float)(NewLocations[i].y), (float)(NewLocations[i].x) });
		SetUpdateBoard(true);
	}
	else
	{
		if (direction != Translation::Down)
			return;
		else
		{
			//	The piece has hit the bottom
			this->Tetro->SetPieceMoving(false);
			this->SetIsMoving(false);
		}

		for (int i = 0; i < NewLocations.Size(); i++)
		{
			value = NewLocations.Get(i);
			if (value.y < this->s_Board.GetMaxHeight(value.x))
				this->s_Board.SetMaxHeight(value);	//	Update the max heights to the location of the piece;
		}
	}
}
void TetrisLogic::Rotate(daTimestep ts, Rotation direction)	//	This also needs to error check the values
{
	tPROFILE_FUNCTION();
	this->RotateTimer += 0.002f * ts;
	if (this->RotateTimer >= 1.0f)
	{
		RotateTetro(direction);
		this->RotateTimer = 0.0f;
	}
}

void TetrisLogic::RotateTetro(Rotation direction)
{
	tPROFILE_FUNCTION();
	bool RotateClockwise = true;
	short int NormalValues[4][4] = { 0 };	//	We're rotating a 4x4 matrix
	short int RotatedValues[4][4] = { 0 };

	Point value;
	Points& PreviousLocations = GetLocations();
	Points NewLocations;
	bool ValidMove = false;
	Point Origin = GetOrigin();
	Point NormalOriginLocation;
	Point RotatedOriginLocation;
	for (int i = 0; i < PreviousLocations.Size(); i++)
	{
		value = PreviousLocations.Get(i);
		value = { value.y - Origin.y, value.x - Origin.x };
		if (value.x == 0 && value.y == 0)	//	This is the origin
		{
			NormalValues[value.y + 1][value.x + 1] = 2;
			NormalOriginLocation = { value.y + 1, value.x + 1 };
		}
		else
			NormalValues[value.y + 1][value.x + 1] = 1;
	}

	if (this->GetOrientation() == Rotation::Up)	//	The piece is in the default position (left/right are authorized)
	{
		if (direction == Rotation::Left)
		{
			this->Tetro->SetRotation(Rotation::Left);
			RotateClockwise = false;
		}
		else if (direction == Rotation::Right)
		{
			this->Tetro->SetRotation(Rotation::Right);
			RotateClockwise = true;
		}
	}
	else if (this->GetOrientation() == Rotation::Right)	//	Piece is facing right
	{
		if (direction == Rotation::Left)
		{
			this->Tetro->SetRotation(Rotation::Up);
			RotateClockwise = false;
		}
		else if (direction == Rotation::Right)
		{
			this->Tetro->SetRotation(Rotation::Down);
			RotateClockwise = true;
		}
	}
	else if (this->GetOrientation() == Rotation::Down)	//	Piece is facing down
	{
		if (direction == Rotation::Left)
		{
			this->Tetro->SetRotation(Rotation::Right);
			RotateClockwise = false;
		}
		else if (direction == Rotation::Right)
		{
			this->Tetro->SetRotation(Rotation::Left);
			RotateClockwise = true;
		}
	}
	else if (this->GetOrientation() == Rotation::Left)	//	Piece is facing left
	{
		if (direction == Rotation::Left)
		{
			this->Tetro->SetRotation(Rotation::Down);
			RotateClockwise = false;
		}
		else if (direction == Rotation::Right)
		{
			this->Tetro->SetRotation(Rotation::Up);
			RotateClockwise = true;
		}
	}

	if (RotateClockwise)
	{
		tPROFILE_SCOPE("Rotate-Clockwise");
		for (int height = 0; height < PreviousLocations.Size(); height++)
		{
			for (int width = 0; width < PreviousLocations.Size(); width++)
			{
				//RotatedValues[height][width] = NormalValues[width][3 - height];
			}
		}
	}
	else
	{
		tPROFILE_SCOPE("Rotate-CounterClockwise");
		int OriginIndex = 0;
		int ValidLocations = 0;
		for (int height = 0; height < PreviousLocations.Size(); height++)
		{
			for (int width = 0; width < PreviousLocations.Size(); width++)
			{
				if (NormalValues[width][3 - height] != 0)
				{
					if (NormalValues[width][3 - height] == 2)
					{
						OriginIndex = ValidLocations;
						RotatedOriginLocation = { height, width };
					}
					RotatedValues[height][width] = NormalValues[width][3 - height];
					ValidLocations++;
				}
			}
		}
		this->Tetro->SetOriginIndex(OriginIndex + 1);
	}	//	Now our RotatedValues array is populated, convert it back to our Board array values
	Point OriginDifference = { 0,0 };
	OriginDifference.x = NormalOriginLocation.x - RotatedOriginLocation.x;
	OriginDifference.y = NormalOriginLocation.y - RotatedOriginLocation.y;
	
	Point ValidityTranslation = { 0, 0 };

	for (int height = 0; height < 4; height++)
	{
		for (int width = 0; width < 4; width++)
		{
			if (RotatedValues[height][width] != 0)
			{
				bool ValidX = false, ValidY = false;
				Point newLocation = { ((height - 1) + Origin.y) + OriginDifference.y, ((width - 1) + Origin.x) + OriginDifference.x };
				while (!ValidMove)
				{
					//	Check height
					if (!ValidY)
					{
						if (newLocation.y + ValidityTranslation.y < this->s_Board.GetMaxHeight(newLocation.x + ValidityTranslation.x))
							ValidY = true;
						else
							ValidityTranslation.y++;
					}

					//	Check Width
					if (!ValidX)
					{
						if (((newLocation.x + ValidityTranslation.x) < (this->s_Board.GetWidth())) && ((newLocation.x + ValidityTranslation.x) >= 0) && (this->s_Board.IsLocationClear(PreviousLocations, newLocation.y + ValidityTranslation.y, newLocation.x + ValidityTranslation.x)))
							ValidX = true;
						else
						{
							if (this->s_Board.IsLocationClear(PreviousLocations, newLocation.y + ValidityTranslation.y, newLocation.x + ValidityTranslation.x))
								if (this->s_Board.IsLocationClear(PreviousLocations, newLocation.y + ValidityTranslation.y, (newLocation.x + ValidityTranslation.x) + 1))
									ValidityTranslation.x += 1;
								else if (newLocation.x + ValidityTranslation.x > 0 && this->s_Board.IsLocationClear(PreviousLocations, newLocation.y + ValidityTranslation.y, (newLocation.x + ValidityTranslation.x) - 1))
									ValidityTranslation.x -= 1;
							else if (newLocation.x + 1 + ValidityTranslation.x > this->s_Board.GetWidth())
									ValidityTranslation.x -= 1;
							else if ((newLocation.x + ValidityTranslation.x) - 1 < 0)
									ValidityTranslation.x += 1;
						}
					}
					if (ValidX && ValidY)
						ValidMove = true;
					else
					{
						if (ValidityTranslation.y + newLocation.y > this->s_Board.GetHeight() || ValidityTranslation.y + newLocation.y < 0)
							break;
						else if (ValidityTranslation.x + newLocation.x > this->s_Board.GetWidth() || ValidityTranslation.x + newLocation.x < 0)
							break;
					}
				}
				NewLocations.Add({ (newLocation.y + ValidityTranslation.y), (newLocation.x + ValidityTranslation.x) });
			}
		}
	}

	if (ValidMove)
	{
		this->Tetro->SetLocations(NewLocations);
		floatPoints.clear();
		for (int i = 0; i < NewLocations.Size(); i++)
			floatPoints.push_back({ (float)(NewLocations[i].y), (float)(NewLocations[i].x) });
		SetUpdateBoard(true);
	}
}

////////////////////////////////////////////////////////
//  --------------  Private Functions  -------------  //
////////////////////////////////////////////////////////
void TetrisLogic::QueueNextArray()
{
	std::vector<int> UsedPieces;
	bool validPiece = false;
	bool NotValidPiece = true;
	for (int i = 0; i < 7; i++)
	{
		NotValidPiece = true;
		int value = rand() % 7;
		while (NotValidPiece)
		{
			validPiece = true;
			for (int j = 0; j < UsedPieces.size(); j++)
			{
				if (value == UsedPieces[j])
					validPiece = false;
			}
			if (!validPiece)
				value = rand() % 7;
			else
				NotValidPiece = false;
		}

		UsedPieces.push_back(value);
		this->SpawnNum[i] = value;
	}
	this->SpawnIndex = 0;
}

bool TetrisLogic::CheckHeight()
{
	tPROFILE_FUNCTION();
	for (int i = 0; i < this->s_Board.GetWidth(); i++)
	{
		if (this->HighestLocation > this->s_Board.GetMaxHeight(i))
			this->HighestLocation = this->s_Board.GetMaxHeight(i);
	}
	if (this->HighestLocation == 0)
		return false;
	return true;
}

void TetrisLogic::CheckWidth()
{
	tPROFILE_FUNCTION();
	for (int i = 0; i < this->s_Board.GetHeight(); i++)
	{
		if (this->s_Board.GetFullRow(i))	//	The row is full
			this->RemoveRows.push_back(i);
	}
}

void TetrisLogic::EraseRows()
{
	tPROFILE_FUNCTION();
	for (int i = 0; i < this->RemoveRows.size(); i++)
	{

	}
}