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

void Json::setProperty(String key, String value, bool isString)
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

void Json::setStringProperty(String key, String value)
{
  Json::setProperty(key, value, true);
}

void Json::setIntegerProperty(String key, int value)
{
  Json::setProperty(key, String(value), false);
}

void Json::setBooleanProperty(String key, bool value)
{
  if (value)
  {
    Json::setProperty(key, "true", false);
  }
  else
  {
    Json::setProperty(key, "false", false);
  }
}

String Json::getJson()
{
  return jsonString;
}

void List::addValue(String value, bool isString)
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

void List::addStringValue(String value)
{
  List::addValue(value, true);
}

void List::addIntegerValue(int value)
{
  List::addValue(String(value), false);
}

void List::addBooleanValue(bool value)
{
  if (value)
  {
    List::addValue("true", false);
  }
  else
  {
    List::addValue("false", false);
  }
}

String List::getList()
{
  return listString;
}

void JsonList::setJsonList(String payload)
{
  unsigned short childSkipCounter = 0;
  unsigned short indexCounter = 0;
  unsigned short splitIndex = 0;
  String data = "";
  unsigned short dataLength = payload.length();
  if (dataLength != 0)
  {
    jsonListString = payload;
    data = payload.substring(1, dataLength - 1);
    dataLength = data.length();
  }
  else
  {
    jsonListString = "";
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
        jsonList.push_back(data.substring(splitIndex, i));
      }
      else
      {
        jsonList.push_back(data.substring(splitIndex + 1, i));
      }
      splitIndex = i;
      indexCounter++;
    }
    if (i == dataLength - 1)
    {
      jsonList.push_back(data.substring(splitIndex + 1, dataLength));
      indexCounter++;
    }
  }
  jsonLength = indexCounter;
}

String JsonList::getJsonList()
{
  return jsonListString;
}

String JsonList::getJson(unsigned short index)
{
  if (index < jsonLength)
  {
    return jsonList[index];
  }
  else
  {
    return "";
  }
}

unsigned short JsonList::length()
{
  return jsonLength;
}