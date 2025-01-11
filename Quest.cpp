#include "Quest.h"

Quest::Quest(std::string qn, std::string des) : questName{ qn }, questDescription{ des }, status{ statuses::wait }
{}