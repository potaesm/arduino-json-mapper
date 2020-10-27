#include "Arduino.h"
#include "JsonMapper.h"

String getValueFromArray(String payload, unsigned short index) {
  String data = "";
  unsigned short maxIndex = payload.length();
  data = payload.substring(1, maxIndex - 1);
  maxIndex = data.length();
  String filteredData = data;
  // for (unsigned short i = 0; i <= maxIndex; i++) {
  //   if (data.charAt(i) != '"') {
  //     filteredData = filteredData + data.charAt(i);
  //   }
  // }
  unsigned short found = 0;
  unsigned short strIndex[] = { 0, -1 };
  unsigned short filteredMaxIndex = filteredData.length();
  for (unsigned short i = 0; i <= filteredMaxIndex && found <= index; i++) {
    if (filteredData.charAt(i) == ',' || i == filteredMaxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == filteredMaxIndex) ? i + 1 : i;
    }
  }
  return found > index ? filteredData.substring(strIndex[0], strIndex[1]) : "";
}

String getValueFromJson(String payload, String key) {
  String data = "";
  unsigned short maxIndex = payload.length();
  data = payload.substring(1, maxIndex - 1);
  maxIndex = data.length();
  unsigned short childSkipCounter = 0;
  unsigned short splitIndex = 0;
  String keyValuePair = "";
  String returnValue = "";
  for (unsigned short i = 0; i < maxIndex; i++) {
    if (data.charAt(i) == '{' || data.charAt(i) == '[') {
      childSkipCounter++;
    }
    if (data.charAt(i) == '}' || data.charAt(i) == ']') {
      childSkipCounter--;
    }
    if (childSkipCounter == 0 && data.charAt(i) == ',') {
      if (splitIndex == 0) {
        keyValuePair = data.substring(splitIndex, i);
      } else {
        keyValuePair = data.substring(splitIndex + 1, i);
      }
      splitIndex = i;
    }
    if (i == maxIndex - 1) {
      keyValuePair = data.substring(splitIndex + 1, maxIndex);
    }
    if (keyValuePair.substring(1, keyValuePair.indexOf(':') - 1) == key) {
      returnValue = keyValuePair.substring(keyValuePair.indexOf(':') + 1, keyValuePair.length());
    }
  }
  return returnValue;
}

String getJsonFromJsonArray(String payload, unsigned short index) {
  unsigned short objStartIndex[128];
  unsigned short objStartIndexCounter = 0;
  unsigned short objEndIndex[128];
  unsigned short objEndIndexCounter = 0;
  String data = "";
  unsigned short maxIndex = payload.length();
  data = payload.substring(1, maxIndex - 1);
  maxIndex = data.length();
  for (unsigned short i = 0; i < maxIndex; i++) {
    if (data.charAt(i) == '{') {
      objStartIndex[objStartIndexCounter] = i;
      objStartIndexCounter++;
    }
    if (data.charAt(i) == '}') {
      objEndIndex[objEndIndexCounter] = i;
      objEndIndexCounter++;
    }
  }
  if (objStartIndexCounter != objEndIndexCounter) {
    return "";
  }
  unsigned short jsonChildNumber = 1;
  unsigned short captureIndex = 0;
  do {
    jsonChildNumber++;
    captureIndex++;
  } while (objStartIndex[captureIndex + 1] < objEndIndex[captureIndex]);
  unsigned short jsonLength = objStartIndexCounter / jsonChildNumber;
  String json[jsonLength];
  unsigned short jsonCounter = 0;
  do {
    json[jsonCounter] = data.substring(objStartIndex[jsonCounter * jsonChildNumber], objEndIndex[(jsonCounter * jsonChildNumber) + (jsonChildNumber - 1)] + 1);
    jsonCounter++;
  } while (jsonCounter < jsonLength);
  return json[index];
}

int parseInt(String payload) {
  return payload.toInt();
}

bool parseBool(String payload) {
  String lowerCasePayload = payload;
  lowerCasePayload.toLowerCase();
  if (lowerCasePayload == "true") {
    return true;
  } else {
    return false;
  }
}

String parseString(String payload) {
  return payload.substring(1, payload.length() - 1);
}

JsonMapper::JsonMapper() {
  jsonString = "{}";
  arrayString = "[]";
}

void JsonMapper::addProperty(String key, String value, bool isString) {
  String output = "{";
  String modifer = "";
  if (isString) {
      modifer = "\"";
  }
  String extractedJson = jsonString.substring(1, jsonString.length() - 1);
  if (extractedJson.length() == 0) {
    output += "\"" + key + "\":" + modifer + value + modifer;
  } else {
    output += extractedJson;
    output += ",\"" + key + "\":" + modifer + value + modifer;
  }
  output += "}";
  jsonString = output;
}

void JsonMapper::addStringProperty(String key, String value) {
  JsonMapper::addProperty(key, value, true);
}

void JsonMapper::addIntProperty(String key, int value) {
  JsonMapper::addProperty(key, String(value), false);
}

void JsonMapper::addBoolProperty(String key, bool value) {
  if (value) {
    JsonMapper::addProperty(key, "true", false);
  } else {
    JsonMapper::addProperty(key, "false", false);
  }
}

void JsonMapper::addValue(String value, bool isString) {
  String output = "[";
  String modifer = "";
  if (isString) {
      modifer = "\"";
  }
  String extractedArray = arrayString.substring(1, arrayString.length() - 1);
  if (extractedArray.length() == 0) {
    output += modifer + value + modifer;
  } else {
    output += extractedArray;
    output += "," + modifer + value + modifer;
  }
  output += "]";
  arrayString = output;
}

void JsonMapper::addStringValue(String value) {
  JsonMapper::addValue(value, true);
}

void JsonMapper::addIntValue(int value) {
  JsonMapper::addValue(String(value), false);
}

void JsonMapper::addBoolValue(bool value) {
  if (value) {
    JsonMapper::addValue("true", false);
  } else {
    JsonMapper::addValue("false", false);
  }
}

String JsonMapper::getJson() {
  return jsonString;
}

String JsonMapper::getArray() {
  return arrayString;
}