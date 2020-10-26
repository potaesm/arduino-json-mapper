#include "Arduino.h"
#include "JsonMapper.h"

String getValueFromArray(String payload, short index) {
  String data = "";
  short maxIndex = payload.length();
  data = payload.substring(1, maxIndex - 1);
  maxIndex = data.length();
  String filteredData = "";
  for (short i = 0; i <= maxIndex; i++) {
    if (data.charAt(i) != '"') {
      filteredData = filteredData + data.charAt(i);
    }
  }
  short found = 0;
  short strIndex[] = { 0, -1 };
  short filteredMaxIndex = filteredData.length();
  for (short i = 0; i <= filteredMaxIndex && found <= index; i++) {
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
  int maxIndex = payload.length();
  data = payload.substring(1, maxIndex - 1);
  maxIndex = data.length();
  short childSkipCounter = 0;
  short splitIndex = 0;
  String keyValuePair = "";
  String returnValue = "";
  for (int i = 0; i < maxIndex; i++) {
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

String getJsonFromJsonArray(String payload, short index) {
  short objStartIndex[128];
  short objStartIndexCounter = 0;
  short objEndIndex[128];
  short objEndIndexCounter = 0;
  String data = "";
  int maxIndex = payload.length();
  data = payload.substring(1, maxIndex - 1);
  maxIndex = data.length();
  for (int i = 0; i < maxIndex; i++) {
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
  short jsonChildNumber = 1;
  short captureIndex = 0;
  do {
    jsonChildNumber++;
    captureIndex++;
  } while (objStartIndex[captureIndex + 1] < objEndIndex[captureIndex]);
  short jsonLength = objStartIndexCounter / jsonChildNumber;
  String json[jsonLength];
  short jsonCounter = 0;
  do {
    json[jsonCounter] = data.substring(objStartIndex[jsonCounter * jsonChildNumber], objEndIndex[(jsonCounter * jsonChildNumber) + (jsonChildNumber - 1)] + 1);
    jsonCounter++;
  } while (jsonCounter < jsonLength);
  return json[index];
}

String buildJson(String key, String value, String valueType, String json = "{}") {
  String output = "{";
  String modifer = "";
  if (valueType == "string") {
      modifer = "\"";
  }
  String extractedJson = json.substring(1, json.length() - 1);
  if (extractedJson.length() == 0) {
    output += "\"" + key + "\":" + modifer + value + modifer;
  } else {
    output += extractedJson;
    output += ",\"" + key + "\":" + modifer + value + modifer;
  }
  output += "}";
  return output;
}