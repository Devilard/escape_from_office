#ifndef _MISSION_H_
#define _MISSION_H_

#include <string>

int getCurrentMisson(int x)
{
	int mission = 0;


	if ((x > 0) && (x < 600)) { mission = 0; }


	if (x > 400) { mission = 1; }
	if (x > 700) { mission = 2; }
	if (x > 2200) { mission = 3; }

	return mission;
}

std::string getTextMission(int mission)
{
	std::string missionText = "";

	switch(mission)
	{ 
	case 0: missionText = "\nНачальный Этап и \nинструкции к игре"; break;
	case 1: missionText = "\nMission1\nВот первая миссия"; break;
	}

	return missionText;
}

#endif