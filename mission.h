#ifndef _MISSION_H_
#define _MISSION_H_

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>
#include "iconvlite.h"

#include "Quest.h"

using nlohmann::json;

class Mission
{
public:
	int getCurrentMisson(int x);
	std::string getTextMission(int mission);
	void readQuestFromJson();
	Quest getQuestByName(std::string questName);
	std::map<std::string, Quest*> getAllQuests() { return quests; }

private:
	int mission = 0;

	std::map<std::string, Quest*> quests;
	std::string trim(const std::string& source);
};

#endif