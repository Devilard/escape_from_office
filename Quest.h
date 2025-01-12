#ifndef _QUEST_H_
#define _QUEST_H_

#include <string>

enum class statuses { wait, done, wait_execution, taken };

class Quest
{
public:
	std::string questName;
	std::string questDescription;
	
	statuses status;
	
	Quest(std::string qn = "", std::string des = "");
};

#endif
