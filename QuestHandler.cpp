#include "QuestHandler.h"

statuses QuestHandler::changeQuestStatus(std::string questName, statuses newStatus)
{
	getQuestByName(questName)->status == newStatus;
	return newStatus;
}

Quest* QuestHandler::getQuestByName(std::string questName)
{
	for (auto it = this->questList.begin(); it != this->questList.end(); it++)
	{
		if ((*it)->questName == questName)
		{
			return (*it);
		}
	}
}