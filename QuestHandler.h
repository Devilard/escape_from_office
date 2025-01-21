#ifndef _QUEST_HANDLER_H_
#define _QUEST_HANDLER_H_

#include <vector>
#include <string>

#include "Quest.h"


class QuestHandler
{
private:
	
public:
	QuestHandler() {}
	std::vector<Quest*> questList;
	statuses changeQuestStatus(std::string questName, statuses newStatus);
	Quest* getQuestByName(std::string questName);
};

#endif