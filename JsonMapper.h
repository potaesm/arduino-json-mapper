#ifndef JsonMapper_h
#define JsonMapper_h
#include "Arduino.h"

extern String getValueFromArray(String payload, short index);
extern String getValueFromJson(String payload, String key);
extern String getJsonFromJsonArray(String payload, short index);
extern String buildJson(String key, String value, String valueType, String json);

#endif