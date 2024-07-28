#include "ge/level/map.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

ge::Map::Map(const std::string filename, glm::vec2 element_size) : filename(filename), element_size(element_size)
{
}

void ge::Map::load()
{
    elements.clear();
    std::ifstream file(filename);
    if(file.is_open())
    {
        std::string buffer = "";
        while(std::getline(file, buffer))
        {
            std::istringstream stream(buffer);
            std::vector<int> line_elements;
            std::string element;
            while(stream >> element)
            {
                line_elements.push_back(std::atoi(element.c_str()));
            }
            elements.push_back(line_elements);
        }
    }
}

void ge::Map::foreach (std::function<void(int type, glm::vec2 position, glm::vec2 size)> callback, glm::vec2 origin)
{
    glm::vec2 pos = origin;
    for(const std::vector<int>& line : elements)
    {
        for(int element : line)
        {
            callback(element, pos, element_size);
            pos.x += element_size.x;
        }
        pos.y += element_size.y;
        pos.x = 0;
    }
}

