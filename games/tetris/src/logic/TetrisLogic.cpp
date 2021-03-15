#include "TetrisLogic.h"

void TetrisLogic::Init()
{
	this->Tetro = nullptr;
	this->IsPolyMoving = false;
	this->SpawnNum = rand() % 6 + 1;
	this->NextSpawnNum = rand() % 6 + 1;
	this->s_Board.Init();
	this->HighestLocation = this->s_Board.GetHeight();
}

int TetrisLogic::Queue()
{
	this->SpawnNum = this->NextSpawnNum;
	this->NextSpawnNum = rand() % 6 + 1;
	return this->SpawnNum;
}

Points TetrisLogic::Spawn()
{
	Queue();
	Tetromino* tetro = new Tetromino;
	this->Tetro = tetro->Spawn(SpawnNum);
	Points locations = GetLocations();
	this->SetIsMoving(true);
	return locations;
}

void TetrisLogic::Update()
{
	if (IsMoving())
	{
		Points NewLocations = GetLocations();
		Points OldLocations = GetOldPositions();
		if (!OldLocations.IsEmpty())
		{
			s_Board.Erase(OldLocations);
			s_Board.Draw(NewLocations);
		}
	}
	this->s_Board.Print(this->GetNextChar());
	this->CheckHeight();
}

//	This function preforms all of the error checking or... logic, and the tetromino executes it
void TetrisLogic::Move(Translation direction)
{
	Point value;
	Points& PreviousLocations = GetLocations();
	Points NewLocations;
	bool ValidMove = true;

	if (direction == Translation::Down)
	{
		for (int i = 0; i < PreviousLocations.Size(); i++)
		{
			value = PreviousLocations.Get(i);
			if ((value.y + 1) < this->s_Board.GetMaxHeight(value.x))	//	Height
				this->Tetro->Translate(direction, value);
			else
				ValidMove = false;
			NewLocations.Add(value);
			//	This needs to be rewritten to determine the lowest y for each x, and check each of them
		}
	}
	else if (direction == Translation::DownPressed)
	{
		for (int i = 0; i < PreviousLocations.Size(); i++)
		{
			value = PreviousLocations.Get(i);
			if ((value.y + 2) < this->s_Board.GetMaxHeight(value.x))	//	Height
				this->Tetro->Translate(direction, value);
			else
			{
				value.y -= 1;
				this->Tetro->Translate(Translation::Down, value);
				ValidMove = false;
			}
			NewLocations.Add(value);
			//	This needs to be rewritten to determine the lowest y for each x, and check each of them
		}
	}
	else if (direction == Translation::Left)
	{
		for (int i = 0; i < PreviousLocations.Size(); i++)
		{
			value = PreviousLocations.Get(i);
			if ((value.x - 1) >= 0)	//	Left side
				this->Tetro->Translate(direction, value);
			else	//	Move is not valid, revert to previous state
				ValidMove = false;
			NewLocations.Add(value);
		}
	}
	else if (direction == Translation::Right)
	{
		for (int i = 0; i < PreviousLocations.Size(); i++)
		{
			value = PreviousLocations.Get(i);
			if ((value.x + 1) < this->s_Board.GetWidth())	//	Right side (width)
				this->Tetro->Translate(direction, value);
			else	//	Move is not valid, revert to previous state
				ValidMove = false;
			NewLocations.Add(value);
		}
	}
	if (ValidMove)
	{
		this->Tetro->SetLocations(NewLocations);
	}
	else
	{
		if (direction == Translation::Down)
		{
			//	The piece has hit the bottom
			this->Tetro->SetPieceMoving(false);
			this->SetIsMoving(false);
		}
		else if (direction == Translation::DownPressed)
		{
			this->Tetro->SetLocations(NewLocations);
			//	The piece has hit the bottom
			this->Tetro->SetPieceMoving(false);
			this->SetIsMoving(false);
		}
		else
		{
			return;
		}
		for (int i = 0; i < NewLocations.Size(); i++)
		{
			value = NewLocations.Get(i);
			if (value.y < this->s_Board.GetMaxHeight(value.x))
				this->s_Board.SetMaxHeight(value);	//	Update the max heights to the location of the piece;
		}
	}
}
void TetrisLogic::Rotate(Rotation direction)	//	This also needs to error check the values
{
	Point value;
	Points& PreviousLocations = GetLocations();
	Points NewLocations;
	bool ValidMove = true;

	if (this->GetOrientation() == Rotation::Up)	//	The piece is in the default position (left/right are authorized)
	{
		if (direction == Rotation::Left)
		{
			for (int i = 0; i < PreviousLocations.Size(); i++)
			{
				value = PreviousLocations.Get(i);
				this->Tetro->Rotate(Rotation::CounterClockwise, value, i);
				this->Tetro->SetRotation(Rotation::Left);
				NewLocations.Add(value);
			}
		}
		else if (direction == Rotation::Right)
		{
			for (int i = 0; i < PreviousLocations.Size(); i++)
			{
				value = PreviousLocations.Get(i);
				this->Tetro->Rotate(Rotation::Clockwise, value, i);
				this->Tetro->SetRotation(Rotation::Right);
				NewLocations.Add(value);
			}
		}
	}
	else if (this->GetOrientation() == Rotation::Right)	//	Piece is facing right
	{
		if (direction == Rotation::Left)
		{
			for (int i = 0; i < PreviousLocations.Size(); i++)
			{
				value = PreviousLocations.Get(i);
				this->Tetro->Rotate(Rotation::CounterClockwise, value, i);
				this->Tetro->SetRotation(Rotation::Up);
				NewLocations.Add(value);
			}
		}
		else if (direction == Rotation::Right)
		{
			for (int i = 0; i < PreviousLocations.Size(); i++)
			{
				value = PreviousLocations.Get(i);
				this->Tetro->Rotate(Rotation::Clockwise, value, i);
				this->Tetro->SetRotation(Rotation::Down);
				NewLocations.Add(value);
			}
		}
	}
	else if (this->GetOrientation() == Rotation::Down)	//	Piece is facing down
	{
		if (direction == Rotation::Left)
		{
			for (int i = 0; i < PreviousLocations.Size(); i++)
			{
				value = PreviousLocations.Get(i);
				this->Tetro->Rotate(Rotation::CounterClockwise, value, i);
				this->Tetro->SetRotation(Rotation::Right);
				NewLocations.Add(value);
			}
		}
		else if (direction == Rotation::Right)
		{
			for (int i = 0; i < PreviousLocations.Size(); i++)
			{
				value = PreviousLocations.Get(i);
				this->Tetro->Rotate(Rotation::Clockwise, value, i);
				this->Tetro->SetRotation(Rotation::Left);
				NewLocations.Add(value);
			}
		}
	}
	else if (this->GetOrientation() == Rotation::Left)	//	Piece is facing left
	{
		if (direction == Rotation::Left)
		{
			for (int i = 0; i < PreviousLocations.Size(); i++)
			{
				value = PreviousLocations.Get(i);
				this->Tetro->Rotate(Rotation::CounterClockwise, value, i);
				this->Tetro->SetRotation(Rotation::Down);
				NewLocations.Add(value);
			}
		}
		else if (direction == Rotation::Right)
		{
			for (int i = 0; i < PreviousLocations.Size(); i++)
			{
				value = PreviousLocations.Get(i);
				this->Tetro->Rotate(Rotation::Clockwise, value, i);
				this->Tetro->SetRotation(Rotation::Up);
				NewLocations.Add(value);
			}
		}
	}
	if (ValidMove)
	{
		this->Tetro->SetLocations(NewLocations);
	}
}

////////////////////////////////////////////////////////
//  --------------  Private Functions  -------------  //
////////////////////////////////////////////////////////

void TetrisLogic::CheckHeight()
{
	for (int i = 0; i < this->s_Board.GetWidth(); i++)
	{
		if (this->HighestLocation > this->s_Board.GetMaxHeight(i))
			this->HighestLocation = this->s_Board.GetMaxHeight(i);
	}
	if (this->HighestLocation == 0)
		GameOver();
}

void TetrisLogic::GameOver()
{
	tLOG(Level::Info, "Game Over!");
	while (true)
	{

	}
}