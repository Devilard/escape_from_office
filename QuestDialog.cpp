#include "QuestDialog.h"

void QuestDialog::init()
{
	text = new sf::Text();
	font = new sf::Font();
	img = new sf::Image();
	texture = new sf::Texture();
	sprite = new sf::Sprite();

	img->loadFromFile("layouts/img/missionbg.png");
	texture->loadFromImage(*img);
	sprite->setTexture(*texture);
	//sprite->setScale(0.5f, 0.5f);

	font->loadFromFile("CyrilicOld.TTF");

	text->setCharacterSize(20);
	text->setFont(*font);
	text->setFillColor(sf::Color::Red);
}

void QuestDialog::show(const NPC* npc, GameView* view)
{
	//Заполняет вектор questList названиями квестов
	if (!npc->questList.empty())
	{
		for (std::vector<sf::String>::const_iterator it = npc->questList.begin(); it != npc->questList.end(); ++it)
		{
			questList.push_back(new sf::Text((*it), *font, 20));
		}
	}
	
	questList.push_back(new sf::Text("tes quest", *font, 20));

	//Устанавливаем позицию спрайта на экране (бэкграунд)
	update(view);
	
	isShowQuestDialog = false;
}

void QuestDialog::high()
{
	
	for (auto it = questList.begin(); it != questList.end(); ++it)
	{
		delete (*it);
	}
	questList.clear();

	isShowQuestDialog = true;
}

void QuestDialog::update(GameView* view)
{
	sprite->setPosition(view->view->getCenter().x + 190.0f, view->view->getCenter().y - 50.0f);
	std::cout << view->view->getCenter().y << " \n";
	std::cout << view->view->getCenter().x << " \n";
	
	int i = 0;
	int h_size = 50;

	for (auto it = questList.begin(); it != questList.end(); ++it)
	{
		(*it)->setFillColor(sf::Color::Red);
		(*it)->setPosition(sprite->getGlobalBounds().left + 100.0f, (sprite->getGlobalBounds().top ) + 50.0f + (h_size * i));
		
		
		
		++i;
	}

}

sf::String QuestDialog::chooseQuest(sf::RenderWindow& window)
{

	for (auto it = questList.begin(); it != questList.end(); ++it)
	{
		sf::IntRect textRect((*it)->getGlobalBounds().left, (*it)->getGlobalBounds().top,
			300, 300);

		//std::cout << sf::Mouse::getPosition(window).x << " ";
		//std::cout << sf::Mouse::getPosition(window).y << "\n";
		//std::cout << textRect.left << " ";
		//std::cout << textRect.top << " ";
		//std::cout << textRect.width << " ";
		//std::cout << textRect.height << " \n";
		if (textRect.contains(sf::Mouse::getPosition(window)))
		{
			
			std::cout << (*it) << "\n";
		}
	}
	return "fsdf";
}