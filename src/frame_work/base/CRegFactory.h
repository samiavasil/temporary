#ifndef CREGFACTORY_H
#define CREGFACTORY_H

#include <map>
#include <set>
#include <string>

// Abstract factory from template, register classes at runtime.
template <typename T>
class CRegFactory
{
public:
    typedef T* (*CreateFunc)();

    static void Registrate(const std::string& name, CRegFactory::CreateFunc func)
    {
        if ( GetRegistry().end() == GetRegistry().find(name) )
        {
            GetRegistry()[name] = func;
        }
    }

    static T* CreateInstance(const std::string& name)
    {
        typename std::map<std::string, CRegFactory::CreateFunc>::iterator it = GetRegistry().find(name);
        return it == GetRegistry().end() ? NULL : (it->second)();
    }

    static void GetRegList(std::set<std::string>& outlist)
    {
        outlist.clear();
        typename std::map<std::string, CRegFactory::CreateFunc>::iterator it;
        for ( it = GetRegistry().begin(); it != GetRegistry().end(); it++ )
        {
            outlist.insert(it->first);
        }
    }

    template <typename D>
    struct Registrator
    {
        Registrator(const std::string& name)
        {
            CRegFactory::Registrate(name, D::CreateItem);
        }
    private: // non-copyable
        Registrator(const Registrator&);
        void operator=(const Registrator&);
    };

protected:
    static std::map<std::string, CRegFactory::CreateFunc>& GetRegistry()
    {
        static std::map<std::string, CRegFactory::CreateFunc> s_registry;
        return s_registry;
    }
};

#endif // CREGFACTORY_H
