#ifndef JsonMapper_h
#define JsonMapper_h
#include "Arduino.h"

class Json
{
public:
    Json();
    void setJsonProperty(String key, String value, bool isString = false);
    void setJsonStringProperty(String key, String value);
    void setJsonIntegerProperty(String key, int value);
    void setJsonBooleanProperty(String key, bool value);
    String getJson();

private:
    String jsonString = "{}";
};

class List
{
public:
    List();
    void addListValue(String value, bool isString = false);
    void addListStringValue(String value);
    void addListIntegerValue(int value);
    void addListBooleanValue(bool value);
    String getList();

private:
    String listString = "[]";
};

class JsonList
{
public:
    JsonList();
    void setJsonList(String payload);
    String getJsonListString();
    String getJsonByIndex(unsigned short index);
    unsigned short getJsonListLength();
    unsigned short getJsonChildNumber();

private:
    String jsonListString = "";
    unsigned short jsonLen = 0;
    unsigned short jsonChildNum = 0;
    unsigned short objStartBracketIndex[128];
    unsigned short objEndBracketIndex[128];
};

extern String getListValue(String payload, unsigned short index);
extern String getJsonProperty(String payload, String key);
extern int parseInteger(String payload);
extern bool parseBoolean(String payload);
extern String parseString(String payload);

#endif