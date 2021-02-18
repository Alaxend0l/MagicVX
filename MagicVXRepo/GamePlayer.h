#pragma once


class GamePlayer
{
public:
	//This is an object representing a player in HWVX. It applies to both human players and AI.
	bool Active = false; //Represents whether the player is currently active.
	int Address = 0x0; //This is the base address of a player.
	int Updates = 0; //Every frame, this variable is checked. If changes are made to the player, this number increases, so in-game changes are necessary.

	//TEMP: This is mostly here just to ensure this stuff works.

	int StuntPoints = 0;
	int Kills = 0;

	GamePlayer();

	GamePlayer(int);

};

