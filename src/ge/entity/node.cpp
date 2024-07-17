#include "ge/entity/node.hpp"
#include <algorithm>

ge::Node::~Node()
{
    for(auto& go : sub_objects)
    {
        if(go.first)
            delete go.first;
    }
}

void ge::Node::as_child(Node *master)
{
    dirty_child_drawing_cache = &master->dirty_drawing_cache;
}

void ge::Node::update(float dt)
{
    if(kill_enabled)
    {
        sub_objects.erase(std::remove_if(sub_objects.begin(), sub_objects.end(), [](std::pair<GameObject *, RefNode>& go) {
            bool to_kill = go.first->get_flags().killed;
            if(to_kill)
                delete go.first;
            return to_kill;
        }));
        kill_enabled = false;
    }
    GameObject::update(dt);
    for(auto& go : sub_objects)
    {
        RefNode& ref = go.second;
        if(ref.anchored)
        {
            float rot = ref.rotation;
            ge::Transform& tr = get_transform();
            glm::vec2 pos = ref.delta_pos - tr.get_origin();
            float angle = glm::radians(tr.get_rotation());
            pos = glm::vec2(pos.x * cos(angle) - pos.y * sin(angle), pos.x * sin(angle) + pos.y * cos(angle));
            pos += tr.get_position();
            go.first->get_transform().set_position(pos);
            go.first->get_transform().set_rotation(tr.get_rotation() + rot + go.first->get_transform().get_rotation());
        }
        go.first->update(dt);
    }
}
void ge::Node::add(GameObject *go, bool anchored)
{
    std::pair<GameObject *, RefNode> pair = {go, RefNode()};
    RefNode& ref = pair.second;
    ref.anchored = anchored;
    if(anchored)
    {
        ref.delta_pos = go->get_transform().get_position() - get_transform().get_center_position();
        ref.rotation = go->get_transform().get_rotation();
    }
    sub_objects.push_back(pair);
    if(dynamic_cast<Drawable *>(go) || dynamic_cast<Node *>(go))
    {
        if(dynamic_cast<Node *>(go))
            dynamic_cast<Node *>(go)->as_child(this);
        dirty_drawing_cache = true;
        if(dirty_child_drawing_cache)
            *dirty_child_drawing_cache = true;
    }
}

void ge::Node::kill(GameObject *go)
{
    if(go)
    {
        kill_enabled = go->get_flags().killed = true;
        if(dynamic_cast<Drawable *>(go) || dynamic_cast<Node *>(go))
        {
            dirty_drawing_cache = true;
            if(dirty_child_drawing_cache)
                *dirty_child_drawing_cache = true;
        }
    }
}

std::vector<ge::Drawable *> &ge::Node::get_drawable_cache()
{
    if(dirty_drawing_cache)
    {
        drawable_cache_objects.clear();
        for(auto& go : sub_objects)
        {
            if(dynamic_cast<Drawable *>(go.first))
            {
                drawable_cache_objects.push_back(dynamic_cast<Drawable *>(go.first));
            }
            else if(dynamic_cast<Node *>(go.first))
            {
                std::vector<ge::Drawable *>& cache = dynamic_cast<Node *>(go.first)->get_drawable_cache();
                drawable_cache_objects.insert(drawable_cache_objects.end(), cache.begin(), cache.end());
                cache.clear();
            }
        }
        dirty_drawing_cache = false;
    }
    return drawable_cache_objects;
}

int ge::Node::count()
{
    return drawable_cache_objects.size();
}

#include <limits>
glm::vec2 ge::Node::get_drawable_size()
{
    glm::vec2 size(0, 0);
    float min_x=std::numeric_limits<float>::max(), min_y=std::numeric_limits<float>::max();
    float max_x=std::numeric_limits<float>::min(), max_y=std::numeric_limits<float>::min();
    auto& drawables = get_drawable_cache();
    for(Drawable *dr : drawables)
    {
        auto&& min_pos = dr->get_transform().get_tl_position();
        auto&& max_pos = dr->get_transform().get_br_position();
        min_x = std::min(min_x, min_pos.x);
        min_y = std::min(min_y, min_pos.y);
        max_x = std::max(max_x, max_pos.x);
        max_y = std::max(max_y, max_pos.y);
    }
    size.x = max_x - min_x;
    size.y = max_y - min_y;
    return size;
}

