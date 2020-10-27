#ifndef JsonMapper_h
#define JsonMapper_h
#include "Arduino.h"

class JsonMapper {
    public:
        JsonMapper();
        void addProperty(String key, String value, bool isString);
        void addStringProperty(String key, String value);
        void addIntProperty(String key, int value);
        void addBoolProperty(String key, bool value);
        void addValue(String value, bool isString);
        void addStringValue(String value);
        void addIntValue(int value);
        void addBoolValue(bool value);
        String getJson();
        String getArray();
    private:
        String jsonString = "{}";
        String arrayString = "[]";
};

extern String getJsonFromJsonArray(String payload, unsigned short index);
extern String getValueFromArray(String payload, unsigned short index);
extern String getValueFromJson(String payload, String key);
extern int parseInt(String payload);
extern bool parseBool(String payload);
extern String parseString(String payload);

#endif