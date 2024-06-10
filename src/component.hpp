#ifndef __GE_COMPONENT_HPP__
#define __GE_COMPONENT_HPP__


namespace ge
{
    class GameObject;
    class Component
    {
    private:
        GameObject *owner=nullptr;
    public:
        Component(GameObject *owner);
        virtual ~Component();
        GameObject *get_owner();
    };

    class UpdatableComponent : public Component
    {
    public:
        using Component::Component;
        virtual void update(float dt) = 0;
    };
}


#endif
