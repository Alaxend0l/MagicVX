#include "GamePlayer.h"


GamePlayer::GamePlayer()
{
	Active = false;
}

GamePlayer::GamePlayer(int startAddress)
{
	Active = true;
	Address = startAddress;
}
