#ifndef _MISSION_H_
#define _MISSION_H_

#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

#include "Quest.h"

using nlohmann::json;

class Mission
{
	int mission = 0;
	std::vector<Quest*> quests;
public:

	int getCurrentMisson(int x)
	{

		if ((x > 0) && (x < 600)) { mission = 0; }

		if (x > 400) { mission = 1; }
		if (x > 700) { mission = 2; }
		if (x > 2200) { mission = 3; }

		return mission;
	}

	std::string getTextMission(int mission)
	{
		std::string missionText = "";

		switch (mission)
		{
		case 0: missionText = "\nНачальный Этап и \nинструкции к игре"; break;
		case 1: missionText = "\nЗадание первое\nНайти листок и ручку"; break;
		case 2: missionText = "\nЗадание второе\nПомочь пользователю"; break;
		}

		return missionText;
	}

	void readQuestFromJson()
	{
		json jsonQuests;
		std::ifstream file("layouts/json/quest.json");


		try
		{
			jsonQuests = json::parse(file);
			std::string name = jsonQuests["quests"][0]["name"];
			std::string description = jsonQuests["quests"][0]["description"];

			for (auto j : jsonQuests)
			{
				quests.push_back(new Quest(name, description));
			}
		}
		catch (json::parse_error& ex)
		{
			std::cerr << "parse error at byte " << ex.byte << std::endl;
		}

		file.close();
	}
	std::vector<Quest*> getAllQuests()
	{
		return quests;
	}
};





#endif