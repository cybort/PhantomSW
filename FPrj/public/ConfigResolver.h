#ifndef _CONFIG_RESOLVER_H_
#define _CONFIG_RESOLVER_H_
#include <minIni.h>
#include <iostream>
class ConfigResolver
{
public:
    ConfigResolver():inifile("config.ini"){}
    ConfigResolver(const std::string& s):inifile(s){}
    static ConfigResolver& GetInstance() 
    {
        static ConfigResolver instance;
        return instance;
    }
    int get_int(const char* section, const char* key, int default_value = 0)
    {
        return ini_getl(section, key, default_value, inifile.c_str());
    }
    
    std::string get_string(const char* section, const char* key, const char* default_value = "")
    {
        char s[200];
        ini_gets(section, key, default_value, s, (sizeof(s) / sizeof((s)[0])), inifile.c_str());
        return std::string(s);
    }
    
    bool get_bool(const char* section, const char* key, bool default_value = false)
    {
        return ini_getbool(section, key, default_value==true?1:0, inifile.c_str())==1?true:false;
    }
    
    void set_int(const char* section, const char* key, int value)
    {
        ini_putl(section, key, value, inifile.c_str());
    }
    
    void set_string(const char* section, const char* key, std::string s)
    {
        ini_puts(section, key, s.c_str(), inifile.c_str());
    }
    
    void set_string(const char* section, const char* key, const char* s)
    {
        ini_puts(section, key, s, inifile.c_str());
    }
    
private:
    std::string inifile;
    
};
#endif