#include "QuestHandler.h"

statuses QuestHandler::changeQuestStatus(std::string questName, statuses newStatus)
{
	getQuestByName(questName)->status = newStatus;
	return newStatus;
}

Quest* QuestHandler::getQuestByName(std::string questName)
{
	bool isFind = false;
	for (auto it = this->quests.begin(); it != this->quests.end(); it++)
	{
		if ((*it)->questName == questName)
		{
			isFind = true;
			return (*it);
		}
	}

	if (isFind == false)
		return nullptr;
}

void QuestHandler::readQuestsFromJson()
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
			Quest* qtemp = new Quest(name, description);
			this->quests.push_back(qtemp);

			
		}
	}
	catch (json::parse_error& ex)
	{
		std::cerr << "parse error at byte " << ex.byte << std::endl;
	}

	file.close();
}

std::string QuestHandler::trim(const std::string& source) {
	std::string s(source);
	s.erase(0, s.find_first_not_of(" \n\r\t"));
	s.erase(s.find_last_not_of(" \n\r\t") + 1);
	return s;
}