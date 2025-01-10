#ifndef _QUEST_H_
#define _QUEST_H_

#include <string>


class Quest
{
public:
	std::string questName;
	std::string questDescription;

	Quest(std::string qn, std::string des) : questName{ qn }, questDescription{ des }
	{}
};

#endif
