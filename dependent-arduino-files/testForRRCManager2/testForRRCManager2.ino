#include <ArduinoUniqueID.h>
#include <EEPROM.h>
#include <stdlib.h>

#define codeUint(y, x) sprintf(y, "%04x", x)
const byte numChars = 64;
const uint8_t symbolSize = 4;
const uint8_t maxValuesNo = 9;
const uint8_t noOfParameters = 21;
char receivedChars[numChars];
char parameterRW = 'N';
char parameterLable[symbolSize+1] = {0}; //table size has to be 1 bigger than longest SYMBOL
uint8_t parameterType;
char parameterValues[maxValuesNo][5] = {0};
char startMarker = '<';
char endMarker = '>';
char sectionMarker[] = "|";

boolean newData = false;
boolean newDataParsed = false;
boolean prevousSerialStatus;

struct Parameter{
  char symbol[symbolSize+1] = {0};
  uint8_t valType; //0 = bool, 1 = uint8_t, 2 = uint16_t, 3 = float
  uint8_t numVal;
} *parameters[noOfParameters];
template<typename T, int numOfVal = 1>
struct ValueParameter : Parameter{
  T values[numOfVal] = {};
};
bool decodeBool(char hexValue[]){
  return bool(atoi(hexValue));
}

uint16_t decodeUint(char hexValue[]){
  return strtoul(hexValue, NULL, 16);
}

float decodeFloat(char hexValue[]){
  unsigned long temp = strtoul(hexValue, NULL, 16);
  float* fp = (float*) &temp;
  float temp2 = *fp;
  fp = NULL;
  return temp2;
}

void codeBool(char* data, bool value){
  if(value)
    return "01";
  else
    return "00";
}

void codeFloat(char* data, float value){
  unsigned long* ul = (unsigned long*) &value;
  sprintf(data, "%lx", *ul);
  ul = NULL;
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;

  char rc;
  if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) {
      rc = Serial.read();
      

      if (recvInProgress == true) {
        if (rc != endMarker) {
          receivedChars[ndx] = rc;
          ndx++;
          if (ndx >= numChars) {
            ndx = numChars - 1;
          }
        }
        else {
          // receivedChars[ndx] = '\0'; // terminate the string
          recvInProgress = false;
          ndx = 0;
          newData = true;
          
        }
      }

      else if (rc == startMarker) {
        recvInProgress = true;
      }
    }
  }
}

void parseMessage(){
  if (newData == true) {
    // split the data into its parts
      newData = false;
    char * strtokIndx; // this is used by strtok() as an index
    parameterRW = receivedChars[0];
    strtokIndx = strtok(receivedChars, sectionMarker);     // get the first part - the string
    strcpy(parameterLable, strtokIndx); // copy it to parameterRW

    strtokIndx = strtok(NULL, sectionMarker); // this continues where the previous call left off
    strcpy(parameterLable, strtokIndx); // copy it to parameterRW
    //integerFromPC = atoi(strtokIndx);     // convert this part to an integer
  
    strtokIndx = strtok(NULL, sectionMarker);
    if(strtokIndx != NULL){
      parameterType = atoi(strtokIndx);     // convert this part to a float
      
      strtokIndx = strtok(NULL, sectionMarker);
      uint8_t i = 0;
      while(strtokIndx != NULL && i < maxValuesNo){
        strcpy(parameterValues[i], strtokIndx);
        strtokIndx = strtok(NULL, sectionMarker);
        ++i; 
      }
    }
    
    newDataParsed = true;
  }
}

int findParameter(){
  if(newDataParsed){
    //newDataParsed = false;
    for(uint8_t i = 0; i < noOfParameters; ++i){
      boolean eqTest = true;
      for(uint8_t j = 0; j < symbolSize; ++j){
        if(parameters[i]->symbol[j] != parameterLable[j]){
          eqTest = false;
        }
      }
      if(eqTest){
          return i;  
      }
    }
  }
  return -1; //error handler
}
void updateParameter(uint8_t id){
  if(parameters[id]->numVal != 0){//can not update command that are not having value
    switch(parameters[id]->valType){
      case 0:
        for(uint8_t i = 0; i < parameters[id]->numVal; ++i){
          ((ValueParameter<bool>*)parameters[id])->values[i] = decodeBool(parameterValues[i]);
        }
        break;
      case 1:
        for(uint8_t i = 0; i < parameters[id]->numVal; ++i){
          ((ValueParameter<uint8_t>*)parameters[id])->values[i] = uint8_t(decodeUint(parameterValues[i]));
        }
        break; 
      case 2:
        for(uint8_t i = 0; i < parameters[id]->numVal; ++i){
          ((ValueParameter<uint16_t>*)parameters[id])->values[i] = decodeUint(parameterValues[i]);
        }
        break;
      case 3:
        for(uint8_t i = 0; i < parameters[id]->numVal; ++i){
          ((ValueParameter<float>*)parameters[id])->values[i] = decodeFloat(parameterValues[i]);
        }
        break;
    };
  }
}

void readParameter(uint8_t id){
  if(parameters[id]->numVal != 0){//can not read command without value
    Serial.print("<");
    Serial.print(parameters[id]->symbol);
    Serial.print("|");
    
    //Serial.print("("); Serial.print(parameters[id]->valType); Serial.print(")");
    if(parameters[id]->valType == 0){
      Serial.print("0");
        Serial.print("|");
        for(uint8_t i = 0; i < parameters[id]->numVal; ++i){
          if(((ValueParameter<bool>*)parameters[id])->values[i]){
            Serial.print("01");
          }
          else{
            Serial.print("00");
          }
          //codeBool(temp, ((ValueParameter<bool>*)parameters[id])->values[i]);
          //Serial.print(temp);
          if(i < parameters[id]->numVal - 1){
            Serial.print("|");
          }
        }
        Serial.println(">");
    }
    else if(parameters[id]->valType == 1){
      char temp[5] = {0};
      Serial.print("1");
        Serial.print("|");     
        for(uint8_t i = 0; i < parameters[id]->numVal; ++i){
          codeUint(temp, ((ValueParameter<uint8_t>*)parameters[id])->values[i]);
          Serial.print(temp);
          if(i < parameters[id]->numVal - 1){
            Serial.print("|");
          }
        }
        Serial.println(">");
    }
    else if(parameters[id]->valType == 2){
      char temp[5] = {0};
      Serial.print("1");
        Serial.print("|");
        for(uint8_t i = 0; i < parameters[id]->numVal; ++i){
          codeUint(temp, ((ValueParameter<uint16_t>*)parameters[id])->values[i]);
          Serial.print(temp);
          if(i < parameters[id]->numVal - 1){
            Serial.print("|");
          }
        }
        Serial.println(">");
    }
    else if(parameters[id]->valType == 3){
      char temp[5] = {0};
        Serial.print("2");
        Serial.print("|");
        for(uint8_t i = 0; i < parameters[id]->numVal; ++i){
          codeFloat(temp, ((ValueParameter<float>*)parameters[id])->values[i]);
          temp[4] = '\0';
          Serial.print(temp);
          if(i < parameters[id]->numVal - 1){
            Serial.print("|");
          }
        }
        Serial.println(">");  
    }
  }
}

void readAll(){
  for(uint8_t i = 0; i < noOfParameters; ++i){
        readParameter(i);
      delay(100);
    }
}


void selectAction(uint8_t id){
  if(newDataParsed){
    if(id == 7){
      Serial.println("readAll");
      readAll();
    }
    else if(parameterRW == '?'){
      Serial.println("readParameter");
      readParameter(id);
    }
    else if(parameterRW == '!'){
      Serial.println("updateParameter");
      updateParameter(id);
    }
  }
}

void setup() {
  parameters[0] = new ValueParameter<uint8_t, 5>;
  parameters[0]->symbol[0] = 'S';
  parameters[0]->symbol[1] = 'N';
  parameters[0]->symbol[2] = '\0';
  parameters[0]->symbol[3] = '\0';
  parameters[0]->valType = 1;
  parameters[0]->numVal = 5;

  parameters[1] = new ValueParameter<uint8_t, 5>;
  parameters[1]->symbol[0] = 'S';
  parameters[1]->symbol[1] = 'V';
  parameters[1]->symbol[2] = '\0';
  parameters[1]->symbol[3] = '\0';
  parameters[1]->valType = 1;
  parameters[1]->numVal = 5;

  parameters[2] = new ValueParameter<uint8_t, 3>;
  parameters[2]->symbol[0] = 'L';
  parameters[2]->symbol[1] = 'U';
  parameters[2]->symbol[2] = '\0';
  parameters[2]->symbol[3] = '\0';
  parameters[2]->valType = 1;
  parameters[2]->numVal = 3;

  parameters[3] = new ValueParameter<uint16_t, 1>;
  parameters[3]->symbol[0] = 'A';
  parameters[3]->symbol[1] = 'U';
  parameters[3]->symbol[2] = '\0';
  parameters[3]->symbol[3] = '\0';
  parameters[3]->valType = 2;
  parameters[3]->numVal = 1;

  parameters[4] = new ValueParameter<uint8_t, 1>;
  parameters[4]->symbol[0] = 'R';
  parameters[4]->symbol[1] = 'S';
  parameters[4]->symbol[2] = '4';
  parameters[4]->symbol[3] = '\0';
  parameters[4]->valType = 1;
  parameters[4]->numVal = 1;
  //memset(((ValueParameter<uint8_t, 1>*)parameters[4])->values,0,sizeof(((ValueParameter<uint8_t, 1>*)parameters[4])->values));

  parameters[5] = new ValueParameter<uint8_t, 3>;
  parameters[5]->symbol[0] = 'C';
  parameters[5]->symbol[1] = 'H';
  parameters[5]->symbol[2] = 'I';
  parameters[5]->symbol[3] = 'D';
  parameters[5]->valType = 1;
  parameters[5]->numVal = 3;
  ((ValueParameter<uint8_t, 3>*)parameters[5])->values[0] = 0x1e;
  ((ValueParameter<uint8_t, 3>*)parameters[5])->values[1] = 0x95;
  ((ValueParameter<uint8_t, 3>*)parameters[5])->values[2] = 0x0f;

  parameters[6] = new ValueParameter<uint8_t, 9>;
  parameters[6]->symbol[0] = 'C';
  parameters[6]->symbol[1] = 'H';
  parameters[6]->symbol[2] = 'S';
  parameters[6]->symbol[3] = 'N';
  parameters[6]->valType = 1;
  parameters[6]->numVal = 9;
  for(size_t i = 0; i < UniqueIDsize; i++)
  ((ValueParameter<uint8_t, 9>*)parameters[6])->values[i] = UniqueID[i];

  parameters[7] = new Parameter;
  parameters[7]->symbol[0] = 'A';
  parameters[7]->symbol[1] = 'L';
  parameters[7]->symbol[2] = 'L';
  parameters[7]->symbol[3] = '\0';
  parameters[7]->valType = 0;
  parameters[7]->numVal = 0;

  parameters[8] = new Parameter;
  parameters[8]->symbol[0] = 'C';
  parameters[8]->symbol[1] = 'H';
  parameters[8]->symbol[2] = 'A';
  parameters[8]->symbol[3] = 'U';
  parameters[8]->valType = 0;
  parameters[8]->numVal = 0;

  parameters[9] = new ValueParameter<bool, 1>;
  parameters[9]->symbol[0] = 'M';
  parameters[9]->symbol[1] = 'O';
  parameters[9]->symbol[2] = 'D';
  parameters[9]->symbol[3] = 'E';
  parameters[9]->valType = 0;
  parameters[9]->numVal = 1;

  parameters[10] = new ValueParameter<uint16_t, 1>;
  parameters[10]->symbol[0] = 'F';
  parameters[10]->symbol[1] = 'P';
  parameters[10]->symbol[2] = 'D';
  parameters[10]->symbol[3] = '\0';
  parameters[10]->valType = 2;
  parameters[10]->numVal = 1;

  parameters[11] = new ValueParameter<uint16_t, 1>;
  parameters[11]->symbol[0] = 'T';
  parameters[11]->symbol[1] = 'F';
  parameters[11]->symbol[2] = 'D';
  parameters[11]->symbol[3] = '\0';
  parameters[11]->valType = 2;
  parameters[11]->numVal = 1;

  parameters[12] = new ValueParameter<uint16_t, 1>;
  parameters[12]->symbol[0] = 'M';
  parameters[12]->symbol[1] = 'T';
  parameters[12]->symbol[2] = 'F';
  parameters[12]->symbol[3] = 'D';
  parameters[12]->valType = 2;
  parameters[12]->numVal = 1;

  parameters[13] = new ValueParameter<uint8_t, 1>;
  parameters[13]->symbol[0] = 'G';
  parameters[13]->symbol[1] = 'D';
  parameters[13]->symbol[2] = 'D';
  parameters[13]->symbol[3] = '\0';
  parameters[13]->valType = 1;
  parameters[13]->numVal = 1;

  parameters[14] = new ValueParameter<uint8_t, 1>;
  parameters[14]->symbol[0] = 'A';
  parameters[14]->symbol[1] = 'I';
  parameters[14]->symbol[2] = 'N';
  parameters[14]->symbol[3] = '\0';
  parameters[14]->valType = 1;
  parameters[14]->numVal = 1;

  parameters[15] = new ValueParameter<uint8_t, 1>;
  parameters[15]->symbol[0] = 'A';
  parameters[15]->symbol[1] = 'C';
  parameters[15]->symbol[2] = 'I';
  parameters[15]->symbol[3] = 'N';
  parameters[15]->valType = 1;
  parameters[15]->numVal = 1;

  parameters[16] = new ValueParameter<uint8_t, 1>;
  parameters[16]->symbol[0] = 'D';
  parameters[16]->symbol[1] = 'C';
  parameters[16]->symbol[2] = 'I';
  parameters[16]->symbol[3] = 'N';
  parameters[16]->valType = 1;
  parameters[16]->numVal = 1;

  parameters[17] = new ValueParameter<uint8_t, 1>;
  parameters[17]->symbol[0] = 'M';
  parameters[17]->symbol[1] = 'I';
  parameters[17]->symbol[2] = 'N';
  parameters[17]->symbol[3] = '\0';
  parameters[17]->valType = 1;
  parameters[17]->numVal = 1;

  parameters[18] = new ValueParameter<uint8_t, 1>;
  parameters[18]->symbol[0] = 'A';
  parameters[18]->symbol[1] = 'I';
  parameters[18]->symbol[2] = 'N';
  parameters[18]->symbol[3] = 'S';
  parameters[18]->valType = 1;
  parameters[18]->numVal = 1;

  parameters[19] = new ValueParameter<uint8_t, 6>;
  parameters[19]->symbol[0] = 'I';
  parameters[19]->symbol[1] = 'N';
  parameters[19]->symbol[2] = 'A';
  parameters[19]->symbol[3] = 'D';
  parameters[19]->valType = 1;
  parameters[19]->numVal = 6;

  parameters[20] = new ValueParameter<uint8_t, 6>;
  parameters[20]->symbol[0] = 'I';
  parameters[20]->symbol[1] = 'N';
  parameters[20]->symbol[2] = 'D';
  parameters[20]->symbol[3] = 'D';
  parameters[20]->valType = 1;
  parameters[20]->numVal = 6;



  Serial.begin(57600);
  while (!Serial) {
    delay(1); // wait for serial port to connect-> Needed for native USB port only
  }
  delay(1000);
  Serial.println("ready");
  char temp[4];
  for(uint8_t i = 0; i < 4 ;++i)
      temp[i] = parameters[5]->symbol[i];
//  Serial.print(temp);
//  Serial.println();
//  Serial.println("juz po");
//  for(uint8_t i = 0; i < 9; ++i){
//    Serial.print(((ValueParameter<uint8_t>*)parameters[6])->values[i], HEX);
//    Serial.print("\t");
//  }
//  Serial.println();


}

void loop() {
  if(Serial){
    recvWithStartEndMarkers();
  } 
  parseMessage();   
  if(newDataParsed){
    Serial.println(findParameter());
    Serial.println(parameterRW);
    Serial.println(parameterLable);
    Serial.println(parameterType);

    selectAction(findParameter());
    newDataParsed = false;
    memset(receivedChars, '\0', sizeof(receivedChars));
  }

//  int i = 0; 
//  while(Serial.available() > 0){
//    receivedChars[i%64] = Serial.read();
//    ++i;
//  }
//  if(i != 0)
//    Serial.println(receivedChars);


}
