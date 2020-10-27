#include "Arduino.h"
#include "JsonMapper.h"

String getValue(String payload, unsigned short index, String key, bool isFindByIndex)
{
  unsigned short childSkipCounter = 0;
  unsigned short indexCounter = 0;
  unsigned short splitIndex = 0;
  String returnValue = "";
  String data = "";
  unsigned short dataLength = payload.length();
  if (dataLength != 0)
  {
    data = payload.substring(1, dataLength - 1);
    dataLength = data.length();
  }
  else
  {
    return returnValue;
  }
  for (unsigned short i = 0; i < dataLength; i++)
  {
    char currentChar = data.charAt(i);
    if (currentChar == '{' || currentChar == '[')
    {
      childSkipCounter++;
    }
    if (currentChar == '}' || currentChar == ']')
    {
      childSkipCounter--;
    }
    if (childSkipCounter == 0 && currentChar == ',')
    {
      if (splitIndex == 0)
      {
        returnValue = data.substring(splitIndex, i);
      }
      else
      {
        returnValue = data.substring(splitIndex + 1, i);
      }
      splitIndex = i;
      indexCounter++;
    }
    if (i == dataLength - 1)
    {
      returnValue = data.substring(splitIndex + 1, dataLength);
    }
    if (isFindByIndex)
    {
      if (indexCounter > index)
      {
        break;
      }
      if ((i == dataLength - 1) && (indexCounter < index))
      {
        returnValue = "";
        break;
      }
    }
    else
    {
      if (returnValue.substring(1, returnValue.indexOf(':') - 1) == key)
      {
        returnValue = returnValue.substring(returnValue.indexOf(':') + 1, returnValue.length());
        break;
      }
      else if (i == dataLength - 1)
      {
        returnValue = "";
        break;
      }
    }
  }
  return returnValue;
}

String getListValue(String payload, unsigned short index)
{
  return getValue(payload, index, "", true);
}

String getJsonProperty(String payload, String key)
{
  return getValue(payload, 0, key, false);
}

int parseInteger(String payload)
{
  return payload.toInt();
}

bool parseBoolean(String payload)
{
  String lowerCasePayload = payload;
  lowerCasePayload.toLowerCase();
  if (lowerCasePayload == "true")
  {
    return true;
  }
  else
  {
    return false;
  }
}

String parseString(String payload)
{
  return payload.substring(1, payload.length() - 1);
}

Json::Json()
{
}

List::List()
{
}

JsonList::JsonList()
{
}

void Json::setJsonProperty(String key, String value, bool isString)
{
  String output = "{";
  String modifer = "";
  if (isString)
  {
    modifer = "\"";
  }
  String extractedJson = jsonString.substring(1, jsonString.length() - 1);
  if (extractedJson.length() == 0)
  {
    output += "\"" + key + "\":" + modifer + value + modifer;
  }
  else
  {
    output += extractedJson;
    output += ",\"" + key + "\":" + modifer + value + modifer;
  }
  output += "}";
  jsonString = output;
}

void Json::setJsonStringProperty(String key, String value)
{
  Json::setJsonProperty(key, value, true);
}

void Json::setJsonIntegerProperty(String key, int value)
{
  Json::setJsonProperty(key, String(value), false);
}

void Json::setJsonBooleanProperty(String key, bool value)
{
  if (value)
  {
    Json::setJsonProperty(key, "true", false);
  }
  else
  {
    Json::setJsonProperty(key, "false", false);
  }
}

String Json::getJson()
{
  return jsonString;
}

void List::addListValue(String value, bool isString)
{
  String output = "[";
  String modifer = "";
  if (isString)
  {
    modifer = "\"";
  }
  String extractedList = listString.substring(1, listString.length() - 1);
  if (extractedList.length() == 0)
  {
    output += modifer + value + modifer;
  }
  else
  {
    output += extractedList;
    output += "," + modifer + value + modifer;
  }
  output += "]";
  listString = output;
}

void List::addListStringValue(String value)
{
  List::addListValue(value, true);
}

void List::addListIntegerValue(int value)
{
  List::addListValue(String(value), false);
}

void List::addListBooleanValue(bool value)
{
  if (value)
  {
    List::addListValue("true", false);
  }
  else
  {
    List::addListValue("false", false);
  }
}

String List::getList()
{
  return listString;
}

void JsonList::setJsonList(String payload)
{
  unsigned short objStartIndexCounter = 0;
  unsigned short objEndIndexCounter = 0;
  String data = "";
  unsigned short dataLength = payload.length();
  data = payload.substring(1, dataLength - 1);
  dataLength = data.length();
  for (unsigned short i = 0; i < dataLength; i++)
  {
    char currentChar = data.charAt(i);
    if (currentChar == '{')
    {
      objStartBracketIndex[objStartIndexCounter] = i;
      objStartIndexCounter++;
    }
    if (currentChar == '}')
    {
      objEndBracketIndex[objEndIndexCounter] = i;
      objEndIndexCounter++;
    }
  }
  if (objStartIndexCounter != objEndIndexCounter)
  {
    Serial.println("Warning: Incorrect format of json list");
  }
  unsigned short jsonChildNumber = 1;
  unsigned short captureIndex = 0;
  do
  {
    jsonChildNumber++;
    captureIndex++;
  } while (objStartBracketIndex[captureIndex + 1] < objEndBracketIndex[captureIndex]);
  jsonLen = objStartIndexCounter / jsonChildNumber;
  jsonChildNum = jsonChildNumber;
  jsonListString = payload;
}

String JsonList::getJsonListString()
{
  return jsonListString;
}

String JsonList::getJsonByIndex(unsigned short index)
{
  if (index < jsonLen)
  {
    return jsonListString.substring(1, jsonListString.length() - 1).substring(objStartBracketIndex[index * jsonChildNum], objEndBracketIndex[(index * jsonChildNum) + (jsonChildNum - 1)] + 1);
  }
  else
  {
    return "";
  }
}

unsigned short JsonList::getJsonListLength()
{
  return jsonLen;
}

unsigned short JsonList::getJsonChildNumber()
{
  return jsonChildNum;
}