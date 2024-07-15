#ifndef __GE_NOTIFY_PROPERTY_HPP__
#define __GE_NOTIFY_PROPERTY_HPP__
#include <ge/binding/property.hpp>
#include <functional>
#include <vector>

namespace ge
{
    template <typename T> class NotifyProperty : public Property<T>
    {
    private:
        bool notifying=false;
        std::vector<std::pair<void *, std::function<void()>>> callbacks;
    public:
        using Property<T>::Property;
        void set(const T& value) override;
        void notify();
        template <typename U> void link(Property<U> *other);
        template <typename U> void bilink(NotifyProperty<U> *other);
        template <typename U> void link(Property<U> *other, std::function<U(const T&)> converter);
        template <typename U> void link(NotifyProperty<U> *other, std::function<U(const T&)> converter, std::function<T(const U&)> inv_converter);
        template <typename U> void rm_link(Property<U> *other, bool bidirectional=false);
    };

    template <typename T> inline void NotifyProperty<T>::set(const T &value)
    {
        if(!notifying)
        {
            Property<T>::set(value);
            notify();
        }
    }

    template <typename T> inline void NotifyProperty<T>::notify()
    {
        notifying = true;
        for(std::pair<void *, std::function<void()>>& pair : callbacks)
        {
            pair.second();
        }
        notifying = false;
    }

    template <typename T> template <typename U> inline void NotifyProperty<T>::link(Property<U> *other)
    {
        std::pair<void *, std::function<void()>> pair;
        pair.first = static_cast<void *>(other);
        pair.second = [this, other]() {
            other->set(this->get());
        };
        callbacks.push_back(pair);
    }

    template <typename T> template <typename U> inline void NotifyProperty<T>::bilink(NotifyProperty<U> *other)
    {
        link(other);
        other->link(this);
    }

    template <typename T> template <typename U> inline void NotifyProperty<T>::link(Property<U> *other, std::function<U(const T &)> converter)
    {
        std::pair<void *, std::function<void()>> pair;
        pair.first = static_cast<void *>(other);
        pair.second = [this, other, converter]() {
            other->set(converter(this->get()));
        };
        callbacks.push_back(pair);
    }
    
    template <typename T> template <typename U> inline void NotifyProperty<T>::link(NotifyProperty<U> *other, std::function<U(const T &)> converter, std::function<T(const U &)> inv_converter)
    {
        link(other, converter);
        other->link(this, inv_converter);
    }
    
    template <typename T> template <typename U> inline void NotifyProperty<T>::rm_link(Property<U> *other, bool bidirectional)
    {
        auto it = std::remove_if(callbacks.begin(), callbacks.end(), [other](std::pair<void *, std::function<void ()>>& pair) {
            return pair.first == other;
        });
        callbacks.erase(it, callbacks.end());
        if(bidirectional && dynamic_cast<NotifyProperty<U> *>(other))
        {
            dynamic_cast<NotifyProperty<U> *>(other)->rm_link(this);
        }
    }

    typedef NotifyProperty<float> FloatNotifyProperty;
    typedef NotifyProperty<int> IntNotifyProperty;
    typedef NotifyProperty<char> CharNotifyProperty;
    typedef NotifyProperty<short> ShortNotifyProperty;
    typedef NotifyProperty<long> LongNotifyProperty;
    typedef NotifyProperty<unsigned int> UIntNotifyProperty;
    typedef NotifyProperty<unsigned char> UCharNotifyProperty;
    typedef NotifyProperty<unsigned short> UShortNotifyProperty;
    typedef NotifyProperty<unsigned long> ULongNotifyProperty;
    typedef NotifyProperty<double> DoubleNotifyProperty;
    typedef NotifyProperty<bool> BoolNotifyProperty;
    typedef NotifyProperty<glm::vec2> Vec2NotifyProperty;
    typedef NotifyProperty<glm::ivec2> IVec2NotifyProperty;
    typedef NotifyProperty<glm::uvec2> UVec2NotifyProperty;
    typedef NotifyProperty<std::string> StrNotifyProperty;
    typedef NotifyProperty<Color> ColorNotifyProperty;
}

#endif
