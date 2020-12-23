#include <map>
#include <string>
#include <vector>

template <typename T /*DBname*/> class RegObserver
{
public:
    virtual void field_changed(T & source, const std::string & module_name, const std::string & register_name) = 0;

    virtual void field_changed(T & source, const std::string & module_name, const std::string & register_name,
                               int addr) = 0;
};

template <typename T /*DBname*/> class RegObservable
{
public:
    void notify(const std::string & module_name, const std::string & config_name)
    {
        for (auto observer : observers)
        {
            observer->field_changed(*this, module_name, config_name);
        }
    }
    void notify(const std::string & module_name, const std::string & config_name, int addr)
    {
        for (auto observer : observers)
        {
            observer->field_changed(*this, module_name, config_name, addr);
        }
    }
    void subscribe(Observer<T> * observer, std::string module_name) { observers[module_name].push_back(observer); }
    void unsubscribe(Observer<T> * observer, std::string module_name)
    {
        if (observers.count(module_name) > 0)
        {
            observers.erase(std::remove(observers[module_name].begin(), observers[module_name].end(), observer),
                            observers[module_name].end());
        }
    }

private:
    std::map<std::string /*module name*/, std::vector<RegObserver<T> *> > observers;
};
