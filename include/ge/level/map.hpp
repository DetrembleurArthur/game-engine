#ifndef __GE_MAP_HPP__
#define __GE_MAP_HPP__
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <functional>

namespace ge
{
    class Map
    {
    private:
        std::string filename;
        glm::vec2 element_size;
        std::vector<std::vector<int>> elements;
    public:
        Map(const std::string filename, glm::vec2 element_size);
        void load();
        void foreach(std::function<void(int type, glm::vec2 position, glm::vec2 size)> callback, glm::vec2 origin=glm::vec2(0));
    };
}

#endif
