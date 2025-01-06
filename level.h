#pragma once
#include <SFML/Graphics.hpp>
#include "./libs/tinyxml2/tinyxml2.h"
#include <iostream>
#include <cctype>

class Object
{
public:
	Object(float x, float y, float width, float height) : rect(x, y, width, height)
	{
		
	}
	int         GetPropertyInt(const std::string& name);
	float       GetPropertyFloat(const std::string& name);
	std::string GetPropertyString(const std::string& name);
	std::string name;
	std::string type;
	std::map<std::string, std::string> properties;
	sf::FloatRect rect;
	int id;
};

class TileMap : public sf::Drawable
{
public:
	~TileMap();
	bool load(const std::string& tmx_file_path);
	Object               getObject(const std::string& name);
	std::vector<Object>  getObjectsByName(const std::string& name);
	std::vector<Object>  getObjectsByType(const std::string& type);
	std::vector<Object>& getAllObjects();
	Object				 getObjectById(const int id);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture* texture;
	std::vector<sf::VertexArray> tile_layers;
	std::vector<Object>          objects;
};
TileMap::~TileMap()
{
	if (texture)
		delete texture;
}
bool TileMap::load(const std::string& tmx_file_path)
{
	tinyxml2::XMLDocument document;
	if (document.LoadFile(tmx_file_path.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Loading file " << tmx_file_path << " failed..." << std::endl;
		return false;
	}
	// получаем все данные тайлсета
	tinyxml2::XMLElement* root_element = document.FirstChildElement("map");
	const size_t tile_width = std::stoul(root_element->Attribute("tilewidth"));
	const size_t tile_height = std::stoul(root_element->Attribute("tileheight"));
	auto tileset = root_element->FirstChildElement("tileset");
	//Моя доработка
	std::string path_to_tileset = tileset->Attribute("source");
	path_to_tileset = "tiled_prod/" + path_to_tileset;
	tinyxml2::XMLDocument document2;
	if (document2.LoadFile(path_to_tileset.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Loading file " << path_to_tileset << " failed..." << std::endl;
		return false;
	}
	tinyxml2::XMLElement* tileset_root_element = document2.FirstChildElement("tileset");
	
	const size_t tile_count = std::stoul(tileset_root_element->Attribute("tilecount"));
	const size_t columns = std::stoul(tileset_root_element->Attribute("columns"));
	// получаем путь до файла
	auto image = tileset_root_element->FirstChildElement("image");
	std::string path = image->Attribute("source");
	while (!isalpha(path.front())) // если путь редактор записал, например, так : "../textures/Tiles.png"
		path.erase(0, 1);          // то убираем все лишние символы в начале строки ( ../ ), чтобы избежать сбоя загрузки
	texture = new sf::Texture();
	if (!texture->loadFromFile(path))
		return false;
	// создаём сетку, где индекс каждого тайла зависит от его координат в текстуре
	// Например, если ширина тайла 32 пикселя, координаты в текстуре : 
	// первого тайла (0, 0), второго (32, 0), третьего (64, 0) и так далее
	std::vector<sf::Vector2f> texture_grid;
	texture_grid.reserve(tile_count);
	size_t rows = tile_count / columns; //64 / 8 = 8
	for (size_t y = 0u; y < rows; ++y)
		for (size_t x = 0u; x < columns; ++x)
			texture_grid.emplace_back(sf::Vector2f((float)x * tile_width, (float)y * tile_height));
	// обрабатываем csv-массивы 
	for (auto layer = root_element->FirstChildElement("layer");
		layer != nullptr;
		layer = layer->NextSiblingElement("layer"))
	{
		/*if (!layer)
		{
		std::cerr << "Bad map. No layer information found." << std::endl;
		return false;
		}*/
		// Ширина и высота слоя в тайлах
		const size_t width = std::stoul(layer->Attribute("width"));
		const size_t height = std::stoul(layer->Attribute("height"));
		// переводим слой в вектор целых чисел, где каждое число - номер тайла в тайлсете
		tinyxml2::XMLElement* data = layer->FirstChildElement("data");
		std::string dirty_string = data->GetText(), buffer;
		std::vector<size_t> csv_array;
		csv_array.reserve(dirty_string.size());
		for (auto& character : dirty_string)
		{
			if (isdigit(character))
				buffer += character;
			else
				if (!buffer.empty())
				{
					csv_array.push_back(std::stoi(buffer));
					buffer.clear();
				}
		}
		csv_array.shrink_to_fit();
		// создаём массив вершин
		sf::VertexArray vertices;
		vertices.setPrimitiveType(sf::Quads);
		for (size_t y = 0u, index = 0u; y < height; ++y) //height 60
		{
			for (size_t x = 0u; x < width; ++x, ++index) //width 80
			{
				size_t tile_num = csv_array[index];
				// если номер тайла больше нуля, то есть место не пусто - записываем тайл в массив вершин
				if (tile_num)
				{   // обходим по часовой стрелке
					sf::Vertex leftTop;     // Вевый верхний угол тайла
					sf::Vertex rightTop;    // Верхний правый 
					sf::Vertex rightBottom; // Нижний правый 
					sf::Vertex leftBottom;  // Нижний левый
					// Устанавливаем тайл в позицию на карте
					leftTop.position = sf::Vector2f((float)x * tile_width, (float)y * tile_height);
					rightTop.position = sf::Vector2f(((float)x + 1) * tile_width, (float)y * tile_height);
					rightBottom.position = sf::Vector2f(((float)x + 1) * tile_width, (float)(y + 1) * tile_height);
					leftBottom.position = sf::Vector2f((float)x * tile_width, (float)(y + 1) * tile_height);
					//	определяем его текстурные координаты
					leftTop.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x, texture_grid[tile_num - 1].y);
					rightTop.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x + tile_width, texture_grid[tile_num - 1].y);
					rightBottom.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x + tile_width, texture_grid[tile_num - 1].y + tile_height);
					leftBottom.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x, texture_grid[tile_num - 1].y + tile_height);
					vertices.append(leftTop);
					vertices.append(rightTop);
					vertices.append(rightBottom);
					vertices.append(leftBottom);
				}
			}
		}
		tile_layers.push_back(std::move(vertices));
	}
	// загружаем объекты, если есть
	for (auto object_group = root_element->FirstChildElement("objectgroup");
		object_group != nullptr;
		object_group = object_group->NextSiblingElement("objectgroup"))
	{// получаем все данные - тип, имя, позиция, etc
		for (auto object = object_group->FirstChildElement("object");
			object != nullptr;
			object = object->NextSiblingElement("object"))
		{
			std::string object_name;
			if (object->Attribute("name"))
				object_name = object->Attribute("name");
			std::string object_type;
			if (object->Attribute("type"))
				object_type = object->Attribute("type");
			float x = std::stof(object->Attribute("x"));
			float y = std::stof(object->Attribute("y"));
			int object_id = std::stoi(object->Attribute("id"));
			float width{}, height{};
			if (object->Attribute("width") && object->Attribute("height"))
			{
				width = std::stof(object->Attribute("width"));
				height = std::stof(object->Attribute("height"));
			}
			Object new_object(x, y, width, height);
			new_object.name = object_name;
			new_object.type = object_type;
			new_object.id = object_id;
			auto properties = object->FirstChildElement("properties");
			if (properties)
			{
				for (auto property = properties->FirstChildElement("property");
					property != nullptr;
					property = property->NextSiblingElement("property"))
				{
					std::string name, value;
					if (property->Attribute("name"))
						name = property->Attribute("name");
					if (property->Attribute("value"))
						value = property->Attribute("value");
					new_object.properties[name] = value;
				}
			}
			objects.emplace_back(std::move(new_object));
		}
	}
	return true;
}
// Только первый объект с заданным именем
Object TileMap::getObject(const std::string& name)
{
	auto found = std::find_if(objects.begin(), objects.end(), [&](const Object& obj)
		{
			return obj.name == name;
		});
	return *found;
}
// Все объекты с заданным именем
std::vector<Object> TileMap::getObjectsByName(const std::string& name)
{
	std::vector<Object> objects_by_name;
	std::copy_if(objects.begin(), objects.end(), std::back_inserter(objects_by_name), [&](const Object& obj)
		{
			return obj.name == name;
		});
	return objects_by_name;
}
// Все объекты с заданным именем
std::vector<Object> TileMap::getObjectsByType(const std::string& type)
{
	std::vector<Object> objects_by_type;
	std::copy_if(objects.begin(), objects.end(), std::back_inserter(objects_by_type), [&](const Object& obj)
		{
			return obj.type == type;
		});
	return objects_by_type;
}

Object TileMap::getObjectById(const int id)
{
	auto found = std::find_if(objects.begin(), objects.end(), [&](const Object& obj)
		{
			return obj.id == id;
		});
	return *found;

}
std::vector<Object>& TileMap::getAllObjects()
{
	return objects;
}
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& layer : tile_layers)
		target.draw(layer, texture);
}
int Object::GetPropertyInt(const std::string& name)
{
	return std::stoi(properties[name]);
}
float Object::GetPropertyFloat(const std::string& name)
{
	return std::stof(properties[name]);
}
std::string Object::GetPropertyString(const std::string& name)
{
	return properties[name];
}