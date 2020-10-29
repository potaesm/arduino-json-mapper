#ifndef JsonMapper_h
#define JsonMapper_h
#include "Arduino.h"

class Json
{
public:
    Json();
    void addProperty(String key, String value, bool isString = false);
    void addStringProperty(String key, String value);
    void addIntegerProperty(String key, int value);
    void addBooleanProperty(String key, bool value);
    String getJson();

private:
    String jsonString = "{}";
};

class List
{
public:
    List();
    void addValue(String value, bool isString = false);
    void addStringValue(String value);
    void addIntegerValue(int value);
    void addBooleanValue(bool value);
    String getList();

private:
    String listString = "[]";
};

class JsonList
{
public:
    JsonList();
    void setJsonList(String payload);
    String getJsonList();
    String getJson(unsigned short index);
    unsigned short length();

private:
    String jsonListString = "";
    unsigned short jsonLength = 0;
    ::std::vector<String> jsonList;
};

extern String editValue(String payload, unsigned short index, String key, String value, bool isSetByIndex, bool isString);
extern String getListValue(String payload, unsigned short index);
extern String getJsonProperty(String payload, String key);
extern int parseInteger(String payload);
extern bool parseBoolean(String payload);
extern String parseString(String payload);

#endif