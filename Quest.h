#ifndef _QUEST_H_
#define _QUEST_H_

#include <string>


class Quest
{
public:
	std::string questName;
	std::string questDescription;
	enum class statuses {wait, done, wait_execution, taken};
	statuses status;
	
	Quest(std::string qn = "", std::string des = "");
};

#endif
