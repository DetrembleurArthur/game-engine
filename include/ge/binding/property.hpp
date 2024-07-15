#ifndef __GE_PROPERTY_HPP__
#define __GE_PROPERTY_HPP__
#include <glm/glm.hpp>
#include <string>
#include <functional>

namespace ge
{

    template <typename T> class Property
    {
    private:
        T value;
        std::function<void(T)> on_change_callback;
    public:
        Property();
        Property(const T& value);
        virtual ~Property();
        virtual void set(const T& value);
        T get();
        void on_change(std::function<void(T)> callback);
    };

    template <typename T> inline ge::Property<T>::Property()
    {

    }

    template <typename T> inline ge::Property<T>::Property(const T& value)
    {
        set(value);
    }

    template <typename T> inline ge::Property<T>::~Property()
    {
        
    }

    template <typename T> inline void ge::Property<T>::set(const T& value)
    {
        this->value = value;
        if(on_change_callback)
            on_change_callback(this->value);
    }

    template <typename T> inline T ge::Property<T>::get()
    {
        return value;
    }

    template <typename T> inline void Property<T>::on_change(std::function<void(T)> callback)
    {
        on_change_callback = callback;
    }

    typedef Property<float> FloatProperty;
    typedef Property<int> IntProperty;
    typedef Property<char> CharProperty;
    typedef Property<short> ShortProperty;
    typedef Property<long> LongProperty;
    typedef Property<unsigned int> UIntProperty;
    typedef Property<unsigned char> UCharProperty;
    typedef Property<unsigned short> UShortProperty;
    typedef Property<unsigned long> ULongProperty;
    typedef Property<double> DoubleProperty;
    typedef Property<bool> BoolProperty;
    typedef Property<glm::vec2> Vec2Property;
    typedef Property<glm::ivec2> IVec2Property;
    typedef Property<glm::uvec2> UVec2Property;
    typedef Property<std::string> StrProperty;
}



#endif
