#ifndef __GE_NODE_HPP__
#define __GE_NODE_HPP__
#include <ge/entity/drawable.hpp>

namespace ge
{
    struct RefNode
    {
        bool anchored=false;
        glm::vec2 delta_pos;
        float rotation=0;
    };

    class Node : public GameObject
    {
    private:
        bool kill_enabled=false;
        bool dirty_drawing_cache=false;
        bool *dirty_child_drawing_cache=nullptr;
        std::vector<std::pair<GameObject *, RefNode>> sub_objects;
        std::vector<Drawable *> drawable_cache_objects;
    public:
        using GameObject::GameObject;
        virtual ~Node();
        void as_child(Node *master);
        virtual void update(float dt) override;
        void add(GameObject *go, bool anchored=false);
        void kill(GameObject *go);
        std::vector<Drawable *>& get_drawable_cache();
        int count();
        glm::vec2 get_drawable_size();
    };
}


#endif
