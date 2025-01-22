#ifndef _QUEST_HANDLER_H_
#define _QUEST_HANDLER_H_

#include <vector>

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <map>
#include <Windows.h>

#include "iconvlite.h"

#include "Quest.h"
#include "QuestStatus.h"

using nlohmann::json;

class QuestHandler
{
private:
	
	std::vector<Quest*> quests;
	
public:
	QuestHandler() {}
	std::string trim(const std::string& source);
	

	statuses changeQuestStatus(std::string questName, statuses newStatus);
	Quest* getQuestByName(std::string questName);

	void readQuestsFromJson();
};

#endif