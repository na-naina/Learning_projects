#pragma once
#include <iostream>
#include <vector>


class NxN
{
private:
	int Size, WinCondition, Move;
	std::vector<char> Field;
	std::vector<char> Players;

	bool RowHit() 
	{
		int Combo = 1;
		for (int i = 0; i < Size; i++)
			for (int j = 0; j < Size - 1; j++)
				if ((Field[i * Size + j] == Field[i * Size + j + 1]) && (Field[i * Size + j] != '_'))
				{
					Combo++;
					if (Combo == WinCondition) return 1;
				}
				else
					Combo = 1;

		return 0;
	}

	bool ColumnHit()
	{
		int Combo = 1;

		for(int i = 0; i < Size; i++)
			for(int j = 0; j < Size - 1; j++)
				if ((Field[j * Size + i] == Field[(j + 1) * Size + i]) && (Field[j * Size + i] != '_'))
				{
					Combo++;
					if (Combo == WinCondition) return 1;
				}
				else
					Combo = 1;


		return 0;
	}

	bool DiagonalHit() 
	{
		int Combo = 1;

		for (int d = 0; d < Size; d++) 
		{
			for (int i = d, j = 0; i < Size - 1 && j < Size - 1; i++, j++)
				if ((Field[i * Size + j] == Field[(i + 1) * Size + j + 1]) && (Field[i * Size + j] != '_')) 
				{	
					Combo++;
					if (Combo == WinCondition) return 1;
				}
				else
					Combo = 1;

			for (int i = 0, j = d; i < Size - 1 && j < Size - 1; i++, j++)
				if ((Field[i * Size + j] == Field[(i + 1) * Size + j + 1]) && (Field[i * Size + j] != '_')) 
				{	
					Combo++;
					if (Combo == WinCondition) return 1;
				}
				else
					Combo = 1;
		}


		for (int d = 0; d < Size; d++) 
		{
			for (int i = 0, j = Size - d - 1; (i < Size - 1) && (j > 0); i++, j--)
				if ((Field[i * Size + j] == Field[(i + 1) * Size + j - 1]) && (Field[i * Size + j] != '_')) 
				{
					Combo++;
					if (Combo == WinCondition) return 1;
				}
				else
					Combo = 1;

			for (int i = d, j = Size - 1; (i < Size - 1)&&(j > 0); i++, j--)
				if ((Field[i * Size + j] == Field[(i + 1) * Size + j - 1]) && (Field[i * Size + j] != '_')) 
				{
					Combo++;
					if (Combo == WinCondition) return 1;
				}
				else
					Combo = 1;
		}


		return 0;
	}

public:

	NxN()
		: Size(0), WinCondition(0), Move(0)
	{
	}

	NxN(int S, int W)
		: Size(S), WinCondition(W), Move(0)
	{
		Field.reserve(S);

		for (int i = 0; i < S; i++)
			for (int j = 0; j < S; j++)
				Field.push_back('_');

	}

	void SetPlayerNumber(unsigned Pn)
	{
		Players.clear();
		for (unsigned i = 0; i < Pn; i++)
			Players.push_back('a' + i);
	}

	void LogGameState()
	{
		std::cout << Size << ' ' << WinCondition << '\n';

		for (unsigned i = 0; i < Players.size(); i++)
			std::cout << Players[i] << ' ';

		std::cout << "Move:" << Move << '\n';

		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++)
				std::cout << Field[i*Size+j] << ' ';
			std::cout << '\n';
		}
	}

	void LogField() 
	{
		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++)
				std::cout << Field[i*Size + j] << ' ';
			std::cout << '\n';
		}
	}

	void SetValue(int a, int b, const char c) {
		Field[(b-1)*Size + a - 1] = c;
	}

	void NextMove(int a, int b) {
		if (Field[(a - 1) + (b - 1) * Size] == '_') {
			this->SetValue(a, b, Players[(Move) % Players.size()]);
			Move++;
		}
	}

	bool Winner() {
		if (RowHit() || ColumnHit() || DiagonalHit())
			return 1;
		else return 0;
	}

	int GetSize() {
		return Size;
	}

	std::vector<char> GetField() {
		return Field;
	}

	int GameFinished() {
		if (Winner())
			if ((Move) % Players.size() != 0)
				return ((Move) % Players.size());
			else
				return Players.size();
		else if(Move == Size*Size)
			return 0;

		return -1;
	}

};

