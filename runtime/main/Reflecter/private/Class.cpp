#include"Class.h"
#include"Property.h"

namespace HARMONY
{
    Class::Class(std::string name, std::size_t size)
    :Class::Type(name,size)
    {
        _nameIndexMapper[name] = _classes.size();
    }

    Class& Class::GetClassByName(std::string name)
    {
        int index = _nameIndexMapper[name];
        return *_classes[index].get();
    }

    Property& Class::GetPropertyByName(std::string name)
    {
        for (auto& vec : _properties)
        {
            if (vec->GetPropertyName() == name)
            {
                return *vec;
            }
        }
    }

    Class::~Class()
    {
        
    }
    std::vector<Property*> Class::GetProperties()
    {
        return _properties;
    }
}