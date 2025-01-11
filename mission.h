#ifndef _MISSION_H_
#define _MISSION_H_

#include <string>
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
	int mission = 0;
	std::map<std::string, Quest*> quests;
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
			
			for (int i = 0; i < jsonQuests["quests"].size(); i++)
			{
				
				std::string name = trim(jsonQuests["quests"][i]["name"]);
				name = utf2cp(name);
			
				std::string description = trim(jsonQuests["quests"][i]["description"]);
				description = utf2cp(description);
				quests[name] = new Quest(name, description);
			}
		}
		catch (json::parse_error& ex)
		{
			std::cerr << "parse error at byte " << ex.byte << std::endl;
		}

		file.close();
	}

	Quest getQuestByName(std::string questName)
	{
		if (quests.contains(questName))
		{
			return *quests[questName];
		}
		else
		{
			return Quest();
		}
		
	}

	std::map<std::string, Quest*> getAllQuests()
	{
		return quests;
	}
private:

	std::string trim(const std::string& source) {
		std::string s(source);
		s.erase(0, s.find_first_not_of(" \n\r\t"));
		s.erase(s.find_last_not_of(" \n\r\t") + 1);
		return s;
	}


};





#endif