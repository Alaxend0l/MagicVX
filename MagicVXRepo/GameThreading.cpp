#include "GameThreading.h"

GameThreading::GameThreading(void)
{

}

void GameThreading::LaunchThread(bool custom)
{
    if (!custom) game = thread([this] {  this->LaunchNormal(); });
    else  game = thread([this] {  this->LaunchCustom(); });

    game.detach();
}

void GameThreading::LaunchNormal()
{
    manipulator.BootGame(false);
}

void GameThreading::LaunchCustom()
{
    manipulator.BootGame(true);
}

void GameThreading::CloseThread()
{
}
