#include "Mission.h"

int Mission::getCurrentMisson(int x)
{

	if ((x > 0) && (x < 600)) { mission = 0; }

	if (x > 400) { mission = 1; }
	if (x > 700) { mission = 2; }
	if (x > 2200) { mission = 3; }

	return mission;
}

std::string Mission::getTextMission(int mission)
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

void Mission::readQuestFromJson()
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

Quest Mission::getQuestByName(std::string questName)
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

std::string Mission::trim(const std::string& source) {
	std::string s(source);
	s.erase(0, s.find_first_not_of(" \n\r\t"));
	s.erase(s.find_last_not_of(" \n\r\t") + 1);
	return s;
}