#ifndef JsonMapper_h
#define JsonMapper_h
#include "Arduino.h"

class JsonMapper {
    public:
        JsonMapper();
        void addProperty(String key, String value, bool isString);
        void addStringProperty(String key, String value);
        void addIntegerProperty(String key, int value);
        void addBooleanProperty(String key, bool value);
        void addValue(String value, bool isString);
        void addStringValue(String value);
        void addIntegerValue(int value);
        void addBooleanValue(bool value);
        String getJson();
        String getArray();
    private:
        String jsonString = "{}";
        String arrayString = "[]";
};

extern String getJsonFromJsonArray(String payload, unsigned short index);
extern String getValueFromArray(String payload, unsigned short index);
extern String getValueFromJson(String payload, String key);
extern int parseInteger(String payload);
extern bool parseBoolean(String payload);
extern String parseString(String payload);

#endif