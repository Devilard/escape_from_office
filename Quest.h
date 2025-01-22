#ifndef _QUEST_H_
#define _QUEST_H_

#include <string>

#include "QuestStatus.h"

class Quest
{
public:
	std::string questName;
	std::string questDescription;
	
	statuses status;
	
	Quest(std::string qn = "", std::string des = "", statuses s = statuses::no_taken);
};

#endif
