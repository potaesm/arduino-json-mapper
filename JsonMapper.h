#ifndef JsonMapper_h
#define JsonMapper_h
#include "Arduino.h"

class Json
{
public:
    Json();
    void setJson(String payload);
    void addProperty(String key, String value, bool isString = false);
    void addStringProperty(String key, String value);
    void addIntegerProperty(String key, int value);
    void addBooleanProperty(String key, bool value);
    void patchProperty(String key, String value, bool isString = false);
    void patchStringProperty(String key, String value);
    void patchIntegerProperty(String key, int value);
    void patchBooleanProperty(String key, bool value);
    void removeProperty(String key);
    String getJson();

private:
    String jsonString = "{}";
};

class List
{
public:
    List();
    void setList(String payload);
    void addValue(String value, bool isString = false);
    void addStringValue(String value);
    void addIntegerValue(int value);
    void addBooleanValue(bool value);
    void patchValue(unsigned short index, String value, bool isString = false);
    void patchStringValue(unsigned short index, String value);
    void patchIntegerValue(unsigned short index, int value);
    void patchBooleanValue(unsigned short index, bool value);
    void removeValue(unsigned short index);
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

extern String patchListValue(String payload, unsigned short index, String value, bool isString);
extern String patchListIntegerValue(String payload, unsigned short index, int value);
extern String patchListBooleanValue(String payload, unsigned short index, bool value);
extern String patchListStringValue(String payload, unsigned short index, String value);
extern String patchJsonProperty(String payload, String key, String value, bool isString);
extern String patchJsonIntegerProperty(String payload, String key, int value);
extern String patchJsonBooleanProperty(String payload, String key, bool value);
extern String patchJsonStringProperty(String payload, String key, String value);
extern String removeListValue(String payload, unsigned short index);
extern String removeJsonProperty(String payload, String key);
extern String getListValue(String payload, unsigned short index);
extern String getJsonProperty(String payload, String key);
extern int parseInteger(String payload);
extern bool parseBoolean(String payload);
extern String parseString(String payload);

#endif