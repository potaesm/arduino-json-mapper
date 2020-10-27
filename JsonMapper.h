#ifndef JsonMapper_h
#define JsonMapper_h
#include "Arduino.h"

class JsonMapper
{
public:
    JsonMapper();
    void setJsonProperty(String key, String value, bool isString = false);
    void setJsonStringProperty(String key, String value);
    void setJsonIntegerProperty(String key, int value);
    void setJsonBooleanProperty(String key, bool value);
    void addArrayValue(String value, bool isString = false);
    void addArrayStringValue(String value);
    void addArrayIntegerValue(int value);
    void addArrayBooleanValue(bool value);
    void setJsonArray(String payload);
    String getJson();
    String getArray();
    String getJsonArrayString();
    String getJsonByIndex(unsigned short index);
    unsigned short getJsonArrayLength();
    unsigned short getJsonChildNumber();

private:
    String jsonString = "{}";
    String jsonArrayString = "";
    String arrayString = "[]";
    unsigned short jsonLen = 0;
    unsigned short jsonChildNum = 0;
    unsigned short objStartBracketIndex[128];
    unsigned short objEndBracketIndex[128];
};

extern String getArrayValue(String payload, unsigned short index);
extern String getJsonProperty(String payload, String key);
extern int parseInteger(String payload);
extern bool parseBoolean(String payload);
extern String parseString(String payload);

#endif