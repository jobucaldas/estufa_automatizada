
//TCC - Etim - Mecatrônica 2018      Grupo: Óliver Pincelli Westin/ Marcelo Vinicius Teodoro/ Erik Adriano Romanelli/ 
//                                     João Victor Bueno de caldas/ Rafael dos Santos Domingues Costa /                      Estufa Automática 

//***************************************************************************************//*************************************************************************************// 

// Bibliotecas
#include <PCD8544.h>
#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <DS3231.h>
#include <math.h>
#include <EEPROM.h>

// Constantes
#define DHTPIN A5                             // Pino DHT 11 (sensor de tempera)
#define DHTTYPE DHT11                         // DHT 11 (Módulo de temperatura)
#define pino_sinal_analogico A1               //Pino do módulo sensor de umidade
#define pinopot  A3                           //Pino do sensor LDR de luminosidade
#define luzmax 25                              //Pino do relé da lâmpada no máximo
#define luzmin 29                             //Pino do relé da lâmpada no mínimo
#define bomba 33                             //Pino do relé da bomba
#define cooler 37                            //Pino do relé do cooler
#define buzzer 51                            //Pino do buzzer

//Sistema de reuso
#define leituraTan 3
#define leituraRe 5
#define bombinha A7

Time t;

//************************************** Notas Músicais *************************************//

  #define NOTE_B0  31     
  #define NOTE_C1  33     
  #define NOTE_CS1 35     
  #define NOTE_D1  37    
  #define NOTE_DS1 39
  #define NOTE_E1  41    
  #define NOTE_F1  44     
  #define NOTE_FS1 46     
  #define NOTE_G1  49     
  #define NOTE_GS1 52
  #define NOTE_A1  55     
  #define NOTE_AS1 58     
  #define NOTE_B1  62     
  #define NOTE_C2  65    
  #define NOTE_CS2 69
  #define NOTE_D2  73    
  #define NOTE_DS2 78     
  #define NOTE_E2  82    
  #define NOTE_F2  87    
  #define NOTE_FS2 93
  #define NOTE_G2  98     
  #define NOTE_GS2 104   
  #define NOTE_A2  110   
  #define NOTE_AS2 117    
  #define NOTE_B2  123
  #define NOTE_C3  131    
  #define NOTE_CS3 139    
  #define NOTE_D3  147   
  #define NOTE_DS3 156    
  #define NOTE_E3  165
  #define NOTE_F3  175   
  #define NOTE_FS3 185   
  #define NOTE_G3  196   
  #define NOTE_GS3 208   
  #define NOTE_A3  220
  #define NOTE_AS3 233   
  #define NOTE_B3  247    
  #define NOTE_C4  262   
  #define NOTE_CS4 277   
  #define NOTE_D4  294
  #define NOTE_DS4 311    
  #define NOTE_E4  330    
  #define NOTE_F4  349    
  #define NOTE_FS4 370    
  #define NOTE_G4  392
  #define NOTE_GS4 415    
  #define NOTE_A4  440    
  #define NOTE_AS4 466   
  #define NOTE_B4  494    
  #define NOTE_C5  523
  #define NOTE_CS5 554    
  #define NOTE_D5  587   
  #define NOTE_DS5 622   
  #define NOTE_E5  659    
  #define NOTE_F5  698
  #define NOTE_FS5 740   
  #define NOTE_G5  784    
  #define NOTE_GS5 831   
  #define NOTE_A5  880    
  #define NOTE_AS5 932
  #define NOTE_B5  988    
  #define NOTE_C6  1047   
  #define NOTE_CS6 1109   
  #define NOTE_D6  1175  
  #define NOTE_DS6 1245
  #define NOTE_E6  1319   
  #define NOTE_F6  1397   
  #define NOTE_FS6 1480   
  #define NOTE_G6  1568   
  #define NOTE_GS6 1661
  #define NOTE_A6  1760   
  #define NOTE_AS6 1865   
  #define NOTE_B6  1976   
  #define NOTE_C7  2093   
  #define NOTE_CS7 2217
  #define NOTE_D7  2349   
  #define NOTE_DS7 2489   
  #define NOTE_E7  2637  
  #define NOTE_F7  2794   
  #define NOTE_FS7 2960
  #define NOTE_G7  3136   
  #define NOTE_GS7 3322   
  #define NOTE_A7  3520   
  #define NOTE_AS7 3729   
  #define NOTE_B7  3951
  #define NOTE_C8  4186   
  #define NOTE_CS8 4435   
  #define NOTE_D8  4699   
  #define NOTE_DS8 4978  
  #define NO_SOUND 0

//CONFIGURACAO DO DISPLAY MICRO LCD
LCD_SSD1306 lcd;             // para módulo contralado pelo CI SSD1306 OLED
DHT dht(DHTPIN, DHTTYPE);
DS3231  rtc(SDA, SCL);       //Para módulo de tempo


  //****************************Variaveis*********************************//

  // Valores sensores
  int valorpot;                            // Armazena valor lido de 0 até 1023
  float luminosidadelcd = 0;               // Valor luminosidade do lcd 
  int luzambiente;
  int valor_analogico;                     //Valor de umidade lido
  int botao;                               // Lê o estado do botão
  int h;
  int temperature;
  
  //Reuso
  int nivelReuso;
  int nivelTanque;

  // Valores da string do console
  int lastPosRefresh = 0;
  int textPosRefresh = -1;
  int lastPosDate    = 0;
  int textPosDate    = -1;
  int lastPosHour    = 0;
  int textPosHour    = -1;
  int lastPosAnthem  = 0;
  int textPosAnthem  = -1;

  // Valores da string dos dias da semana
  int lastPosSeg    = 0;
  int textPosSeg    = -1;
  int lastPosTer    = 0;
  int textPosTer    = -1;
  int lastPosQua    = 0;
  int textPosQua    = -1;
  int lastPosQui    = 0;
  int textPosQui    = -1;
  int lastPosSex    = 0;
  int textPosSex    = -1;
  int lastPosSab    = 0;
  int textPosSab    = -1;
  int lastPosDom    = 0;
  int textPosDom    = -1;

  int lastPosSegStart    = 0;
  int textPosSegStart    = -1;
  int lastPosTerStart    = 0;
  int textPosTerStart    = -1;
  int lastPosQuaStart    = 0;
  int textPosQuaStart    = -1;
  int lastPosQuiStart    = 0;
  int textPosQuiStart    = -1;
  int lastPosSexStart    = 0;
  int textPosSexStart    = -1;
  int lastPosSabStart    = 0;
  int textPosSabStart    = -1;
  int lastPosDomStart    = 0;
  int textPosDomStart    = -1;

  int lastPosSegFinish   = 0;
  int textPosSegFinish   = -1;
  int lastPosTerFinish   = 0;
  int textPosTerFinish   = -1;
  int lastPosQuaFinish   = 0;
  int textPosQuaFinish   = -1;
  int lastPosQuiFinish   = 0;
  int textPosQuiFinish   = -1;
  int lastPosSexFinish   = 0;
  int textPosSexFinish   = -1;
  int lastPosSabFinish   = 0;
  int textPosSabFinish   = -1;
  int lastPosDomFinish   = 0;
  int textPosDomFinish   = -1;

  // Valores de datas e horas
  int hrClock;
  int minClock;
  int segClock;
  int dayClock;
  int monthClock;
  int yearClock;
  String dowClock;
  int dowClockInt;

  // Dia da semana atual
  String dowNow;

  // Hora dos dias da semana
  int hrSeg;
  int hrTer;
  int hrQua;
  int hrQui;
  int hrSex;
  int hrSab;
  int hrDom;

  //Strings tempo inicio-fim

  String hourSegStart;
  String hourTerStart;
  String hourQuaStart;
  String hourQuiStart;
  String hourSexStart;
  String hourSabStart;
  String hourDomStart;

  String hourSegFinish;
  String hourTerFinish;
  String hourQuaFinish;
  String hourQuiFinish;
  String hourSexFinish;
  String hourSabFinish;
  String hourDomFinish;

  String minSegStart;
  String minTerStart;
  String minQuaStart;
  String minQuiStart;
  String minSexStart;
  String minSabStart;
  String minDomStart;

  String minSegFinish;
  String minTerFinish;
  String minQuaFinish;
  String minQuiFinish;
  String minSexFinish;
  String minSabFinish;
  String minDomFinish;

  // String do texto do console
  String consoleText;

  // Status do funcionamento da bomba
  boolean irrigateStatus = false;

  // Strings de funcionamento da bomba em dias da semana
  String bombSeg;
  String bombTer;
  String bombQua;
  String bombQui;
  String bombSex;
  String bombSab;
  String bombDom;

  String ifTrueSeg;
  String ifTrueTer;
  String ifTrueQua;
  String ifTrueQui;
  String ifTrueSex;
  String ifTrueSab;
  String ifTrueDom;

  // Funcionamento de bombas em int
  int intBombSeg;
  int intBombTer;
  int intBombQua;
  int intBombQui;
  int intBombSex;
  int intBombSab;
  int intBombDom;

  // Valor no EEPROM
  int valueSeg;
  int valueTer;
  int valueQua;
  int valueQui;
  int valueSex;
  int valueSab;
  int valueDom;

  int valueHourSegStart;
  int valueHourTerStart;
  int valueHourQuaStart;
  int valueHourQuiStart;
  int valueHourSexStart;
  int valueHourSabStart;
  int valueHourDomStart;

  int valueMinSegStart;
  int valueMinTerStart;
  int valueMinQuaStart;
  int valueMinQuiStart;
  int valueMinSexStart;
  int valueMinSabStart;
  int valueMinDomStart;

  int valueHourSegFinish;
  int valueHourTerFinish;
  int valueHourQuaFinish;
  int valueHourQuiFinish;
  int valueHourSexFinish;
  int valueHourSabFinish;
  int valueHourDomFinish;

  int valueMinSegFinish;
  int valueMinTerFinish;
  int valueMinQuaFinish;
  int valueMinQuiFinish;
  int valueMinSexFinish;
  int valueMinSabFinish;
  int valueMinDomFinish;

  // Posição da variavel no eeprom
  int addrSeg = 0;
  int addrTer = 1;
  int addrQua = 2;
  int addrQui = 3;
  int addrSex = 4;
  int addrSab = 5;
  int addrDom = 6;
  
  int addrHourSegStart = 7;
  int addrHourTerStart = 8;
  int addrHourQuaStart = 9;
  int addrHourQuiStart = 10;
  int addrHourSexStart = 11;
  int addrHourSabStart = 12;
  int addrHourDomStart = 13;
  
  int addrMinSegStart = 14;
  int addrMinTerStart = 15;
  int addrMinQuaStart = 16;
  int addrMinQuiStart = 17;
  int addrMinSexStart = 18;
  int addrMinSabStart = 19;
  int addrMinDomStart = 20;

  int addrHourSegFinish = 21;
  int addrHourTerFinish = 22;
  int addrHourQuaFinish = 23;
  int addrHourQuiFinish = 24;
  int addrHourSexFinish = 25;
  int addrHourSabFinish = 26;
  int addrHourDomFinish = 27;

  int addrMinSegFinish = 28;
  int addrMinTerFinish = 29;
  int addrMinQuaFinish = 30;
  int addrMinQuiFinish = 31;
  int addrMinSexFinish = 32;
  int addrMinSabFinish = 33;
  int addrMinDomFinish = 34;

//*************************************************************************//*********************************************************************************//
    
const unsigned char PROGMEM agua [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xE0,
0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFB, 0xFE, 0xFC, 0xF0, 0xE0, 0xC0,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFE, 0xFC, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F,
0x07, 0x0F, 0x3F, 0x7D, 0xCB, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x3F, 0x7F, 0xFF, 0xFF,
0xFE, 0xFC, 0xF8, 0xF8, 0xF8, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char PROGMEM logo [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0,
0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFC, 0x30, 0x1C, 0x0F, 0x1F, 0x3B, 0x7D,
0xFE, 0xFE, 0xFE, 0xFC, 0xF9, 0xF3, 0xC7, 0x1F, 0xFF, 0xFF, 0xFC, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0x78, 0x38, 0xB8, 0xB8, 0xB8, 0x78, 0xF0, 0xE0,
0xC0, 0x00, 0x80, 0xE0, 0xF0, 0xF8, 0x1F, 0x1F, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x3F, 0x7F, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00,
0x00, 0x7C, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0xF9, 0xFC, 0x7F, 0x7F, 0x7F, 0x7F, 0x3E, 0x3E, 0x1F,
0x0F, 0x06, 0x1F, 0x3F, 0xFF, 0xF8, 0xC0, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0x70, 0x78, 0x78,
0x78, 0xF8, 0xF8, 0xF8, 0xF8, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0x0F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFE, 0x86, 0x07, 0x0F, 0x3E, 0x7E, 0x7F, 0xFF, 0xFF,
0xFF, 0xFE, 0xFE, 0xFD, 0xFB, 0xFB, 0x7B, 0x3B, 0x3F, 0x3E, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char PROGMEM relogio [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0xA0, 0xA0,
0xD0, 0xD0, 0xD0, 0xE8, 0xE8, 0xE8, 0xE8, 0x68, 0x68, 0xE8, 0xE8, 0xE8, 0xE8, 0xD0, 0xD0, 0xD0,
0xA0, 0xA0, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x98, 0xEC, 0xF6, 0xFB, 0xFD, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFD, 0xFB, 0xF6, 0xEC, 0x98, 0x70, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xF8, 0x07, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x1F, 0x8F, 0xC7, 0xE3, 0xF1, 0xF9, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF1, 0x0F, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x0F, 0x70, 0x8F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xC7, 0x78, 0x0F, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0C, 0x1B, 0x37, 0x6F, 0xDF, 0xBF, 0x7F, 0x7F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0x7F, 0x7F, 0xBF, 0xDF, 0x6F, 0x37, 0x1B, 0x0C, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02,
0x05, 0x05, 0x05, 0x0D, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0D, 0x05, 0x05, 0x05,
0x02, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


const unsigned char PROGMEM calendario [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x01, 0xFE, 0x01, 0x01, 0x01, 0x09, 0x09,
0x09, 0x01, 0x19, 0x45, 0x49, 0x39, 0x05, 0x05, 0x01, 0x49, 0x49, 0x49, 0x39, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x82, 0x42, 0x22, 0xE2, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x02, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x43, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0xC0, 0xC0, 0xE1, 0x22, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



const unsigned char PROGMEM termometro [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
0x20, 0x20, 0x60, 0x00, 0x80, 0x40, 0xA0, 0xA0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x70,
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x08, 0x08, 0x08,
0x08, 0x00, 0xFE, 0x01, 0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0x88, 0x88, 0x89, 0xFE, 0x00, 0x00, 0x04,
0x06, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x88, 0x88, 0x88, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x40, 0x20, 0x1F, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xE8, 0xC8, 0x88, 0x1F, 0x20, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
0x30, 0x40, 0x8F, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x8F, 0x40, 0x30, 0x0F,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char PROGMEM luz [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x80, 0x40, 0x40, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0xCC, 0x32, 0x0D, 0x02,
0x02, 0x01, 0x01, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x01, 0x01, 0x02, 0x02, 0x0D, 0x32,
0xCC, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x60, 0x9F, 0x60, 0x80, 0x00,
0x00, 0x02, 0x07, 0x04, 0x04, 0xFF, 0x00, 0xFF, 0x04, 0x04, 0x07, 0x02, 0x00, 0x00, 0x80, 0x60,
0x9F, 0x60, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x05, 0x1A,
0x24, 0xE8, 0x18, 0xF0, 0x20, 0xFF, 0xE0, 0xFF, 0x20, 0xF0, 0x18, 0xE8, 0x24, 0x1A, 0x05, 0x02,
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xCC, 0x73, 0x3E, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0x3E, 0x73, 0xCC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//********************************************************************//************************************************************************//
 //Sistema de reuso
void reuso(){  
  nivelTanque = digitalRead(leituraTan);
  
  
  if(!nivelTanque){   
    nivelReuso = digitalRead(leituraRe);


    Serial.print("Reuso: ");
    Serial.println(nivelReuso);
    Serial.print("Tanque: ");
    Serial.println(nivelTanque);
    
    if(!nivelReuso && !nivelTanque){

      titulo();
      setFont();
      lcd.setCursor(42,4);
      lcd.setFontSize(FONT_SIZE_XLARGE);
      lcd.print("Bombeando");
      
      analogWrite (bombinha, 1023);
      digitalWrite (buzzer, HIGH);
      delay (1000);
      analogWrite (bombinha, 0);
      digitalWrite (buzzer, LOW);    
    }
  }
}

void SerialReadDOW(){  
    // Pega posição do checkbox
    textPosSeg = consoleText.lastIndexOf("Seg:", lastPosSeg);
    lastPosSeg = textPosSeg;

    // Se mandou checkbox, muda informações
    if(textPosSeg != -1){
      textPosSeg = -1;

      // Lê valor recebido
      bombSeg   = consoleText.substring(lastPosSeg + 5, lastPosSeg + 10);
      ifTrueSeg = consoleText.substring(lastPosSeg + 5, lastPosSeg + 9);
      
      // Coloca valor em int
      if(ifTrueSeg.equals("true")){
        intBombSeg = 1;
      }
      else if(bombSeg.equals("false")){
        intBombSeg = 0;
      }

      Serial.print(bombSeg);
      Serial.print("\n");
      Serial.print(ifTrueSeg);

      // Insere valor em int no eeprom
      if((ifTrueSeg.equals("true")) || (bombSeg.equals("false"))){
        EEPROM.update(addrSeg, intBombSeg); 
      }
      
    }

    // Pega posição do checkbox
    textPosTer = consoleText.lastIndexOf("Ter:", lastPosTer);
    lastPosTer = textPosTer;

    // Se mandou checkbox, muda informações
    if(textPosTer != -1){
      textPosTer = -1;

      bombTer   = consoleText.substring(lastPosTer + 5, lastPosTer + 10);
      ifTrueTer = consoleText.substring(lastPosTer + 5, lastPosTer + 9);

      // Coloca valor em int
      if(ifTrueTer.equals("true")){
        intBombTer = 1;
      }
      else if(bombTer.equals("false")){
        intBombTer = 0;
      }

      // Insere valor em int no eeprom
      if((ifTrueTer.equals("true")) || (bombTer.equals("false"))){
        EEPROM.update(addrTer, intBombTer); 
      }
      
    }

    // Pega posição do checkbox
    textPosQua = consoleText.lastIndexOf("Qua:", lastPosQua);
    lastPosQua = textPosQua;

    // Se mandou checkbox, muda informações
    if(textPosQua != -1){
      textPosQua = -1;

      bombQua   = consoleText.substring(lastPosQua + 5, lastPosQua + 10);
      ifTrueQua = consoleText.substring(lastPosQua + 5, lastPosQua + 9);

      // Coloca valor em int
      if(ifTrueQua.equals("true")){
        intBombQua = 1;
      }
      else if(bombQua.equals("false")){
        intBombQua = 0;
      }

      // Insere valor em int no eeprom
      if((ifTrueQua.equals("true")) || (bombQua.equals("false"))){
        EEPROM.update(addrQua, intBombQua); 
      }
      
    }

    // Pega posição do checkbox
    textPosQui = consoleText.lastIndexOf("Qui:", lastPosQui);
    lastPosQui = textPosQui;

    // Se mandou checkbox, muda informações
    if(textPosQui != -1){
      textPosQui = -1;

      bombQui   = consoleText.substring(lastPosQui + 5, lastPosQui + 10);
      ifTrueQui = consoleText.substring(lastPosQui + 5, lastPosQui + 9);

      // Coloca valor em int
      if(ifTrueQui.equals("true")){
        intBombQui = 1;
      }
      else if(bombQui.equals("false")){
        intBombQui = 0;
      }

      // Insere valor em int no eeprom
      if((ifTrueQui.equals("true")) || (bombQui.equals("false"))){
        EEPROM.update(addrQui, intBombQui); 
      }
      
    }

    // Pega posição do checkbox
    textPosSex = consoleText.lastIndexOf("Sex:", lastPosSex);
    lastPosSex = textPosSex;

    // Se mandou checkbox, muda informações
    if(textPosSex != -1){
      textPosSex = -1;

      bombSex   = consoleText.substring(lastPosSex + 5, lastPosSex + 10);
      ifTrueSex = consoleText.substring(lastPosSex + 5, lastPosSex + 9);

      // Coloca valor em int
      if(ifTrueSex.equals("true")){
        intBombSex = 1;
      }
      else if(bombSex.equals("false")){
        intBombSex = 0;
      }

      // Insere valor em int no eeprom
      if((ifTrueSex.equals("true")) || (bombSex.equals("false"))){
        EEPROM.update(addrSex, intBombSex); 
      }
      
    }

    // Pega posição do checkbox
    textPosSab = consoleText.lastIndexOf("Sab:", lastPosSab);
    lastPosSab = textPosSab;

    // Se mandou checkbox, muda informações
    if(textPosSab != -1){
      textPosSab = -1;

      bombSab   = consoleText.substring(lastPosSab + 5, lastPosSab + 10);
      ifTrueSab = consoleText.substring(lastPosSab + 5, lastPosSab + 9);

      // Coloca valor em int
      if(ifTrueSab.equals("true")){
        intBombSab = 1;
      }
      else if(bombSab.equals("false")){
        intBombSab = 0;
      }

      // Insere valor em int no eeprom
      if((ifTrueSab.equals("true")) || (bombSab.equals("false"))){
        EEPROM.update(addrSab, intBombSab); 
      }
      
    }

    // Pega posição do checkbox
    textPosDom = consoleText.lastIndexOf("Dom:", lastPosDom);
    lastPosDom = textPosDom;

    // Se mandou checkbox, muda informações
    if(textPosDom != -1){
      textPosDom = -1;

      bombDom   = consoleText.substring(lastPosDom + 5, lastPosDom + 10);
      ifTrueDom = consoleText.substring(lastPosDom + 5, lastPosDom + 9);

      // Coloca valor em int
      if(ifTrueDom.equals("true")){
        intBombDom = 1;
      }
      else if(bombDom.equals("false")){
        intBombDom = 0;
      }

      // Insere valor em int no eeprom
      if((ifTrueDom.equals("true")) || (bombDom.equals("false"))){
        EEPROM.update(addrDom, intBombDom); 
      }
      
    }

//**********************************************************************************************************************************************************************//

    // Pega posição do checkbox
    textPosSegStart = consoleText.lastIndexOf("Seg Start:", lastPosSegStart);
    lastPosSegStart = textPosSegStart;

    // Se mandou checkbox, muda informações
    if(textPosSegStart != -1){
      textPosSegStart = -1;

      // Lê valor recebido
      hourSegStart   = consoleText.substring(lastPosSegStart + 11, lastPosSegStart + 13);
      minSegStart   = consoleText.substring(lastPosSegStart + 14, lastPosSegStart + 16);
      
      Serial.print(hourSegStart);
      Serial.print("\n");
      Serial.print(minSegStart);
      Serial.print("\n");

      EEPROM.update(addrHourSegStart, hourSegStart.toInt());
      EEPROM.update(addrMinSegStart,  minSegStart.toInt());      
    }

    // Pega posição do checkbox
    textPosTerStart = consoleText.lastIndexOf("Ter Start:", lastPosTerStart);
    lastPosTerStart = textPosTerStart;

    // Se mandou checkbox, muda informações
    if(textPosTerStart != -1){
      textPosTerStart = -1;

      // Lê valor recebido
      hourTerStart   = consoleText.substring(lastPosTerStart + 11, lastPosTerStart + 13);
      minTerStart   = consoleText.substring(lastPosTerStart + 14, lastPosTerStart + 16);

      EEPROM.update(addrHourTerStart, hourTerStart.toInt());
      EEPROM.update(addrMinTerStart,  minTerStart.toInt());      
    }

    // Pega posição do checkbox
    textPosQuaStart = consoleText.lastIndexOf("Qua Start:", lastPosQuaStart);
    lastPosQuaStart = textPosQuaStart;

    // Se mandou checkbox, muda informações
    if(textPosQuaStart != -1){
      textPosQuaStart = -1;

      // Lê valor recebido
      hourQuaStart   = consoleText.substring(lastPosQuaStart + 11, lastPosQuaStart + 13);
      minQuaStart   = consoleText.substring(lastPosQuaStart + 14, lastPosQuaStart + 16);

      EEPROM.update(addrHourQuaStart, hourQuaStart.toInt());
      EEPROM.update(addrMinQuaStart,  minQuaStart.toInt());      
    }

    // Pega posição do checkbox
    textPosQuiStart = consoleText.lastIndexOf("Qui Start:", lastPosQuiStart);
    lastPosQuiStart = textPosQuiStart;

    // Se mandou checkbox, muda informações
    if(textPosQuiStart != -1){
      textPosQuiStart = -1;

      // Lê valor recebido
      hourQuiStart   = consoleText.substring(lastPosQuiStart + 11, lastPosQuiStart + 13);
      minQuiStart   = consoleText.substring(lastPosQuiStart + 14, lastPosQuiStart + 16);

      EEPROM.update(addrHourQuiStart, hourQuiStart.toInt());
      EEPROM.update(addrMinQuiStart,  minQuiStart.toInt());      
    }

    // Pega posição do checkbox
    textPosSexStart = consoleText.lastIndexOf("Sex Start:", lastPosSexStart);
    lastPosSexStart = textPosSexStart;

    // Se mandou checkbox, muda informações
    if(textPosSexStart != -1){
      textPosSexStart = -1;

      // Lê valor recebido
      hourSexStart   = consoleText.substring(lastPosSexStart + 11, lastPosSexStart + 13);
      minSexStart   = consoleText.substring(lastPosSexStart + 14, lastPosSexStart + 16);

      EEPROM.update(addrHourSexStart, hourSexStart.toInt());
      EEPROM.update(addrMinSexStart,  minSexStart.toInt());      
    }

    // Pega posição do checkbox
    textPosSabStart = consoleText.lastIndexOf("Sab Start:", lastPosSabStart);
    lastPosSabStart = textPosSabStart;

    // Se mandou checkbox, muda informações
    if(textPosSabStart != -1){
      textPosSabStart = -1;

      // Lê valor recebido
      hourSabStart   = consoleText.substring(lastPosSabStart + 11, lastPosSabStart + 13);
      minSabStart   = consoleText.substring(lastPosSabStart + 14, lastPosSabStart + 16);

      EEPROM.update(addrHourSabStart, hourSabStart.toInt());
      EEPROM.update(addrMinSabStart,  minSabStart.toInt());      
    }

    // Pega posição do checkbox
    textPosDomStart = consoleText.lastIndexOf("Dom Start:", lastPosDomStart);
    lastPosDomStart = textPosDomStart;

    // Se mandou checkbox, muda informações
    if(textPosDomStart != -1){
      textPosDomStart = -1;

      // Lê valor recebido
      hourDomStart   = consoleText.substring(lastPosDomStart + 11, lastPosDomStart + 13);
      minDomStart   = consoleText.substring(lastPosDomStart + 14, lastPosDomStart + 16);

      EEPROM.update(addrHourDomStart, hourDomStart.toInt());
      EEPROM.update(addrMinDomStart,  minDomStart.toInt());      
    }

//**********************************************************************************************************************************************************************************//

    // Pega posição do checkbox
    textPosSegFinish = consoleText.lastIndexOf("Seg Finish:", lastPosSegFinish);
    lastPosSegFinish = textPosSegFinish;

    // Se mandou checkbox, muda informações
    if(textPosSegFinish != -1){
      textPosSegFinish = -1;

      // Lê valor recebido
      hourSegFinish   = consoleText.substring(lastPosSegFinish + 12, lastPosSegFinish + 14);
      minSegFinish   = consoleText.substring(lastPosSegFinish + 15, lastPosSegFinish + 17);
      
      Serial.print(hourSegFinish);
      Serial.print("\n");
      Serial.print(minSegFinish);
      Serial.print("\n");

      EEPROM.update(addrHourSegFinish, hourSegFinish.toInt());
      EEPROM.update(addrMinSegFinish,  minSegFinish.toInt());      
    }

    // Pega posição do checkbox
    textPosTerFinish = consoleText.lastIndexOf("Ter Finish:", lastPosTerFinish);
    lastPosTerFinish = textPosTerFinish;

    // Se mandou checkbox, muda informações
    if(textPosTerFinish != -1){
      textPosTerFinish = -1;

      // Lê valor recebido
      hourTerFinish   = consoleText.substring(lastPosTerFinish + 12, lastPosTerFinish + 14);
      minTerFinish   = consoleText.substring(lastPosTerFinish + 15, lastPosTerFinish + 17);

      EEPROM.update(addrHourTerFinish, hourTerFinish.toInt());
      EEPROM.update(addrMinTerFinish,  minTerFinish.toInt());      
    }

    // Pega posição do checkbox
    textPosQuaFinish = consoleText.lastIndexOf("Qua Finish:", lastPosQuaFinish);
    lastPosQuaFinish = textPosQuaFinish;

    // Se mandou checkbox, muda informações
    if(textPosQuaFinish != -1){
      textPosQuaFinish = -1;

      // Lê valor recebido
      hourQuaFinish   = consoleText.substring(lastPosQuaFinish + 12, lastPosQuaFinish + 14);
      minQuaFinish   = consoleText.substring(lastPosQuaFinish + 15, lastPosQuaFinish + 17);

      EEPROM.update(addrHourQuaFinish, hourQuaFinish.toInt());
      EEPROM.update(addrMinQuaFinish,  minQuaFinish.toInt());      
    }

    // Pega posição do checkbox
    textPosQuiFinish = consoleText.lastIndexOf("Qui Finish:", lastPosQuiFinish);
    lastPosQuiFinish = textPosQuiFinish;

    // Se mandou checkbox, muda informações
    if(textPosQuiFinish != -1){
      textPosQuiFinish = -1;

      // Lê valor recebido
      hourQuiFinish   = consoleText.substring(lastPosQuiFinish + 12, lastPosQuiFinish + 14);
      minQuiFinish   = consoleText.substring(lastPosQuiFinish + 15, lastPosQuiFinish + 17);

      EEPROM.update(addrHourQuiFinish, hourQuiFinish.toInt());
      EEPROM.update(addrMinQuiFinish,  minQuiFinish.toInt());      
    }

    // Pega posição do checkbox
    textPosSexFinish = consoleText.lastIndexOf("Sex Finish:", lastPosSexFinish);
    lastPosSexFinish = textPosSexFinish;

    // Se mandou checkbox, muda informações
    if(textPosSexFinish != -1){
      textPosSexFinish = -1;

      // Lê valor recebido
      hourSexFinish   = consoleText.substring(lastPosSexFinish + 12, lastPosSexFinish + 14);
      minSexFinish   = consoleText.substring(lastPosSexFinish + 15, lastPosSexFinish + 17);

      EEPROM.update(addrHourSexFinish, hourSexFinish.toInt());
      EEPROM.update(addrMinSexFinish,  minSexFinish.toInt());      
    }

    // Pega posição do checkbox
    textPosSabFinish = consoleText.lastIndexOf("Sab Finish:", lastPosSabFinish);
    lastPosSabFinish = textPosSabFinish;

    // Se mandou checkbox, muda informações
    if(textPosSabFinish != -1){
      textPosSabFinish = -1;

      // Lê valor recebido
      hourSabFinish   = consoleText.substring(lastPosSabFinish + 12, lastPosSabFinish + 14);
      minSabFinish   = consoleText.substring(lastPosSabFinish + 15, lastPosSabFinish + 17);

      EEPROM.update(addrHourSabFinish, hourSabFinish.toInt());
      EEPROM.update(addrMinSabFinish,  minSabFinish.toInt());      
    }

    // Pega posição do checkbox
    textPosDomFinish = consoleText.lastIndexOf("Dom Finish:", lastPosDomFinish);
    lastPosDomFinish = textPosDomFinish;

    // Se mandou checkbox, muda informações
    if(textPosDomFinish != -1){
      textPosDomFinish = -1;

      // Lê valor recebido
      hourDomFinish   = consoleText.substring(lastPosDomFinish + 12, lastPosDomFinish + 14);
      minDomFinish   = consoleText.substring(lastPosDomFinish + 15, lastPosDomFinish + 17);

      EEPROM.update(addrHourDomFinish, hourDomFinish.toInt());
      EEPROM.update(addrMinDomFinish,  minDomFinish.toInt());      
    }
    

}

void TemperatureSensor(){
  //Temperatura
  
  h = dht.readHumidity();                //Valor da umidade relativa do ar
  temperature = dht.readTemperature();   //Valor da temperatura
  
  if (temperature <= 25)
  {
    digitalWrite (cooler, HIGH);             // Com temperatura >= 25 °C ==> Liga o Cooler
  }
    
  else
  {                         
     digitalWrite (cooler, LOW);             //Com temperatura < 25°C ==> Desliga o Cooler
  }
}

void SetArduinoUp(){
  // Inicia porta
  Serial.begin(115200);

  // Abre lcd
  lcd.begin();

  // Inicia porta
  Serial.begin(9600);

  // Seta entradas
  pinMode (pino_sinal_analogico, INPUT);        //Declarando pinos de entrada e saída
  pinMode (44, OUTPUT);                         //Error 44 -> Sensor fora do solo
  pinMode (pinopot, INPUT);                    //Porta ligada ao sensor LDR

  // Entradas dos sensores
  pinMode (49, OUTPUT);
  pinMode (luzmax, OUTPUT);                        //Relé lâmpada 1   (Luminosidade)
  pinMode (luzmin, OUTPUT);                        //Relé lâmpada 2    (Luminosidade)
  pinMode (bomba, OUTPUT);                         //Relé Bomba         (Umidade do solo)
  pinMode (cooler, OUTPUT);                        //Relé Cooler         (Temperatura)
  pinMode (buzzer, OUTPUT);                        //Buzzer
 
  pinMode (7, INPUT_PULLUP);                   //Botão (liga display)

  //Sistema de reuso
  pinMode (leituraTan, INPUT);
  pinMode (leituraRe, INPUT);
  pinMode (bombinha, OUTPUT);

  // Printa titulo
  Serial.println("TCC - Estufa");

  // Inicialização do RTC e DHT
  rtc.begin();
  dht.begin();

  // Plantinha Logo TCC  
  lcd.setCursor(40,1);
  lcd.draw(logo,48,48);
  delay(4000);
  lcd.clear();
}

void SetDOWStrings(){
  // Seta strings de dia da semana atual
  if(rtc.getDOWStr(FORMAT_SHORT) == "Mon"){
    dowNow = "seg";
  }
  else if(rtc.getDOWStr(FORMAT_SHORT) == "Tue"){
    dowNow = "ter";
  }
  else if(rtc.getDOWStr(FORMAT_SHORT) == "Wed"){
    dowNow = "qua";
  }
  else if(rtc.getDOWStr(FORMAT_SHORT) == "Thu"){
    dowNow = "qui";
  }
  else if(rtc.getDOWStr(FORMAT_SHORT) == "Fri"){
    dowNow = "sex";
  }
  else if(rtc.getDOWStr(FORMAT_SHORT) == "Sat"){
    dowNow = "sab";
  }
  else if(rtc.getDOWStr(FORMAT_SHORT) == "Sun"){
    dowNow = "dom";
  }
}

void titulo(){
  //Mostra o titulo pra quando a tela for limpa
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.setFontSize(FONT_SIZE_XLARGE);
  lcd.println("TCC - Estufa");
}

void setFont(){
  //Define fonte como tamanho pequeno
  lcd.setCursor(52,4);
  lcd.setFontSize(FONT_SIZE_SMALL);
}

void setFont2(){
  //Define a fonte como tamanho médio
  lcd.setCursor(52,4);
  lcd.setFontSize(FONT_SIZE_LARGE);
}

void pula(){
  //Pula da linha 4 para a 5
  lcd.setCursor(80,5);
  lcd.setFontSize(FONT_SIZE_SMALL);
}
void irrigacaoConcluida (){
  // Mostra no display que a irrigação foi finalizada
  titulo();
  lcd.setCursor(0, 2);            
  lcd.draw(agua,48,48);
  setFont();
  lcd.setCursor(51,4);
  lcd.print("Solo irrigado");                                
  delay(3000);
  lcd.clear();                                           
  titulo();
  lcd.setCursor(0, 2);            
  lcd.draw(agua,48,48);
  setFont();
  lcd.print("Umidade em:");
  pula();
  lcd.print(valor_analogico);
  lcd.print("%");
  delay(3000);  
}

void LedTest(){
  // Testa LEDS
  digitalWrite (luzmax, HIGH);
  delay (1000);
  digitalWrite (luzmax, LOW);
  delay (1000);

  digitalWrite (luzmin, HIGH);
  delay (1000);
  digitalWrite (luzmin, LOW);
  delay (1000);
  
  digitalWrite (bomba, HIGH);
  delay (1000);
  digitalWrite (bomba, LOW);
  delay (1000);

  digitalWrite (cooler, HIGH);
  delay (1000);
  digitalWrite (cooler, LOW);
  delay (1000);
  
  digitalWrite (buzzer, HIGH);
  delay (200);
  digitalWrite (buzzer, LOW);
  delay (1000);

  digitalWrite (luzmax, HIGH);
  digitalWrite (luzmin, HIGH);
  digitalWrite (bomba, HIGH);
  digitalWrite (cooler, HIGH);
  delay (1000);
  
  digitalWrite (44, HIGH);
  delay (1000);
  digitalWrite (44, LOW);
  delay (1000);

}

void SerialReadHour(){
  // Pega posição da hora
  textPosHour = consoleText.lastIndexOf("New Hour:", lastPosHour);
  lastPosHour = textPosHour;

  // Se mandou hora, muda informações no clock interno
  if(textPosHour != -1){
    textPosHour = -1;

    // Seta int dos horários
    hrClock  = consoleText.substring(lastPosHour + 10, lastPosHour + 12).toInt();
    minClock = consoleText.substring(lastPosHour + 13, lastPosHour + 15).toInt();
    segClock = consoleText.substring(lastPosHour + 16, lastPosHour + 18).toInt();
  
    // Ajustes do relógio
    rtc.setTime(hrClock, minClock, segClock);
  }
}

void DateArduinoShow(){
  // Escreve data no LCD
  titulo();
  lcd.setCursor(0, 2);
  lcd.draw(calendario,48,48);
  setFont();
  lcd.println(rtc.getDateStr());
  delay(3000);
}

void HourArduinoShow(){
  // Escreve horário no LCD
  titulo();
  lcd.setCursor(0, 2);
  lcd.draw(relogio,48,48);
  lcd.setCursor(70,4);
  lcd.setFontSize(FONT_SIZE_LARGE);
  lcd.print(t.hour,DEC);
  lcd.print(":");
  if(t.min<10){ lcd.print("0"); }
  lcd.print(t.min, DEC);
  delay(3000); 
}

void LightArduinoShow(){
  // Escreve luminosidade no LCD
  
  luzambiente = map(valorpot, 0, 1023, 0, 100);
  titulo();
  lcd.setCursor(0,2);
  lcd.draw(luz,48,48);
  lcd.setCursor(45,4);
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.print(" Luminosidade:");
  pula();
  lcd.print(luzambiente);
  lcd.print("%");
  delay(3000);
}

void HumidityArduinoShow(){
  // Escreve umidade do solo no LCD

  titulo();
  lcd.setCursor(0, 2);        //Gota no display
  lcd.draw(agua,48,48);     
  setFont();
 
  if (valor_analogico > 70 && valor_analogico <= 100)
  {  
    lcd.setCursor(78,4);
    lcd.setFontSize(FONT_SIZE_SMALL);
    lcd.print("Umido");                            // solo umido
    pula();
    lcd.print(valor_analogico);
    lcd.print("%");
    delay(3000);
  }
 
  if (valor_analogico > 30 && valor_analogico < 69)
  {  
    setFont(); 
    lcd.print("Equilibrado");                                
    pula();                                           // solo equilibrado
    lcd.print(valor_analogico);
    lcd.print("%");
    delay(3000);
  }

  if (valor_analogico >= 15 && valor_analogico < 29)
  {
    setFont();  
    lcd.print("Solo seco");                                // solo seco
    pula();
    lcd.print(valor_analogico);
    lcd.print("%");
    delay(3000);
  }

  if (valor_analogico >= 0 && valor_analogico < 2)   
  {
    lcd.print("Sensor fora");
    pula();
    lcd.print("do solo!");
    digitalWrite (44, HIGH);
    delay (3000);                                          // sensor fora do solo
    digitalWrite (44, LOW);
  }

  // Seta display com icones e texto 
  titulo();
  lcd.setCursor(0, 2);        //Gota no display
  lcd.draw(agua,48,48);     
  setFont();

  // Variavel de umidade do ar
  h = dht.readHumidity();            //Valor da umidade relativa do ar

  // Printa valores da variavel
  lcd.print("Umidade ar: ");
  pula();
  lcd.print(h);
  lcd.print("%");
  delay(3000);
  
}

void TemperatureArduinoShow(){
  // Escreve temperatura no LCD
  
  titulo();
  lcd.setCursor(0, 2);
  lcd.draw(termometro,48,48);
  setFont();

  // String de temperatura
  temperature = dht.readTemperature();         //Valor da temperatura

  // Se não for um numero escreve erro
  if (isnan(temperature)) 
  {
    lcd.print("Falha ao ler");
    pula();
    lcd.print("DHT");
  } 
  else 
  {
    lcd.print("Temperatura:");
    pula();
    lcd.print(temperature);
    lcd.print("'C");
  }
  delay(3000); 
  lcd.clear();
}


void HinoNacional(){
    
   int melodia[] = {
    NOTE_C4, NOTE_F4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_AS4, NOTE_B4,NOTE_C5,NOTE_F4,NOTE_C4, NOTE_F4,NOTE_E4,NOTE_G4,NOTE_F4,NOTE_A4,NOTE_G4,NOTE_AS4,NOTE_A4, NOTE_FS4,NOTE_G4,NO_SOUND,NO_SOUND,NOTE_C4, NOTE_G4,NOTE_FS4,NOTE_G4,NOTE_A4,NOTE_AS4,NOTE_A4,NOTE_AS4,NOTE_B4,
    NOTE_CS5,NOTE_D5,NOTE_G4,NOTE_C4, NOTE_G4,NOTE_F4,NOTE_A4,NOTE_G4,NOTE_AS4,NOTE_A4,NOTE_B4,NOTE_AS4, NOTE_GS4,NOTE_A4,NO_SOUND,NOTE_A4,NOTE_A4, NOTE_AS4,NOTE_A4,NO_SOUND,NOTE_A4,NOTE_AS4,NOTE_A4, NOTE_A4,NOTE_D5,NOTE_C5,NOTE_AS4, NOTE_AS4,NOTE_A4,NOTE_A4,NOTE_G4,NOTE_G4,NOTE_F4,NOTE_F4,NOTE_E4,
    NOTE_E4,NOTE_D4,NO_SOUND,NOTE_G4,NOTE_G4, NOTE_A4,NOTE_G4,NO_SOUND,NOTE_G4,NOTE_A4,NOTE_G4, NOTE_G4,NOTE_C5,NOTE_B4,NOTE_A4, NOTE_A4,NOTE_G4,NOTE_G4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_D4, NOTE_D4,NOTE_C4,NO_SOUND,NOTE_C4,NOTE_E4,NOTE_G4, NOTE_AS4,NOTE_C4,NOTE_E4,NOTE_G4,NOTE_AS4,NOTE_C4,NOTE_E4,NOTE_G4,
    NOTE_AS4,NOTE_AS4,NOTE_C4, NOTE_F4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_AS4, NOTE_B4,NOTE_C5,NOTE_F4,NOTE_C4, NOTE_F4,NOTE_E4,NOTE_G4,NOTE_F4,NOTE_A4,NOTE_G4,NOTE_AS4,NOTE_A4, NOTE_FS4,NOTE_G4,NO_SOUND,NOTE_C4, NOTE_G4,NOTE_FS4,NOTE_G4,NOTE_A4,NOTE_AS4,NOTE_A4,NOTE_AS4,NOTE_B4,
    NOTE_CS5,NOTE_D5,NOTE_G4,NOTE_C4, NOTE_G4,NOTE_FS4,NOTE_A4,NOTE_G4,NOTE_AS4,NOTE_A4,NOTE_C5,NOTE_AS4, NOTE_GS4,NOTE_A4,NO_SOUND,NO_SOUND,NOTE_F4, NOTE_G4,NOTE_F4,NOTE_E4,NOTE_F4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_F4, NOTE_F4,NOTE_AS4,NOTE_AS4,NO_SOUND,NOTE_G4, NOTE_A4,NOTE_G4,NOTE_FS4,NOTE_G4,NOTE_FS4,NOTE_G4,NOTE_A4,NOTE_G4,
    NOTE_G4,NOTE_C5,NOTE_C5,NO_SOUND,NOTE_A4, NOTE_AS4,NOTE_A4,NOTE_GS4,NOTE_A4,NOTE_GS4,NOTE_A4,NOTE_AS4,NOTE_A4, NOTE_A4,NOTE_D5,NOTE_C5,NOTE_AS4,NOTE_G4, NOTE_G4,NOTE_F4,NO_SOUND,NOTE_E4,NOTE_F4,NOTE_G4, NOTE_AS4,NOTE_A4,NOTE_E4,NOTE_F4,NOTE_CS4,NOTE_D4,NOTE_AS4,NOTE_G4, NOTE_G4,NOTE_F4,NO_SOUND,NOTE_G4,NOTE_A4,NOTE_AS4,
    NOTE_B4,NOTE_C5,NOTE_A4,NOTE_F4,NOTE_D4,NOTE_AS4, NOTE_A4,NOTE_F4,NOTE_D4,NOTE_C4,NOTE_D4,NOTE_E4,
    NOTE_F4
    };
   int tempoNotas[] = {
    4,
    6,16,6,16,6,16,6,16,
    3,8,4,4,
    6,16,6,16,6,16,6,16,
    4,4,4,16,8,
    6,16,6,16,6,16,6,16,
    3,8,4,4,
    6,16,6,16,6,16,6,16,
    4,4,4,6,16,
    4,4,8,8,6,16,
    4,2,8,8,
    8,8,8,8,8,8,8,8,
    4,4,4,6,16,
    4,4,8,8,6,16,
    4,2,8,8,
    8,8,8,8,8,8,8,8,
    4,4,8,8,8,8,
    8,8,8,8,8,8,8,8,
    2,4,4,
    6,16,6,16,6,16,6,16,
    3,8,4,4,
    6,16,6,16,6,16,6,16,
    4,4,4,4,
    6,16,6,16,6,16,6,16,
    3,8,4,4,
    6,16,6,16,6,16,6,16,
    4,4,4,8,16,
    6,16,6,16,6,16,6,16,
    3,8,4,8,8,
    6,16,6,16,6,16,6,16,
    3,8,4,8,8,
    6,16,6,16,6,16,6,16,
    4,3,8,8,8,
    4,4,8,8,8,8,  
    8,8,8,8,8,8,8,8,
    4,4,8,8,8,8,
    8,8,8,8,4,4,
    4,6,16,4,6,16,
    2
    };
    const int compasso = 1500;
    
    for (int Nota = 0; Nota < 230; Nota++) {
    int tempo = compasso/tempoNotas[Nota];
    tone(buzzer, melodia[Nota],tempo);
    delay(tempo*1.2);
    }
  }

void RefreshData(){
  // Pega posição do refresh
  textPosRefresh = consoleText.lastIndexOf("Refresh Data", lastPosRefresh);
  lastPosRefresh = textPosRefresh;

  // Se houve refresh, manda informações
  if(textPosRefresh != -1){
    textPosRefresh = -1;

    digitalWrite(44, HIGH);
    delay(500);
    digitalWrite(44, LOW);
    
    // Informacoes seriais
    // Data
    Serial.println("    ");
    Serial.print("  Data: ");
    Serial.println(rtc.getDateStr());
  
    // Horario
    Serial.print("  Horario: ");
    Serial.println(rtc.getTimeStr());
    
    // Semana
    Serial.print("  Dia da semana: ");
    Serial.println(rtc.getDOWStr(FORMAT_SHORT));

    // Luminosidade
    valorpot = analogRead(pinopot);

    luminosidadelcd = map(valorpot, 0, 1023, 0, 255);
    Serial.print("  Valor lido do LDR : ");
    Serial.println(valorpot);

    luzambiente = map(valorpot, 0, 1023, 0, 100);
    Serial.print("  Luminosidade : ");
    Serial.print(map(valorpot, 0, 1023, 0, 100));
    Serial.println("%");
  
    // Sensor de umidade do solo
    valor_analogico = analogRead(pino_sinal_analogico);           //Le o valor do pino A1 do sensor
    valor_analogico = map(valor_analogico, 1023, 0, 0, 100);

    //Mostra o valor da porta analogica no serial monitor
    Serial.print("  Umidade solo: ");
    Serial.print(valor_analogico);
    Serial.println("%");
  
    if (valor_analogico > 70 && valor_analogico <= 100)
    {
      Serial.println("  Status: Solo umido");
    }
    if (valor_analogico > 30 && valor_analogico < 69)
    {
      Serial.println("  Status: Umidade moderada");
    }
    if (valor_analogico >= 15 && valor_analogico < 29)
    {
      Serial.println("  Status: Solo seco");
    }
  
    // Temperatura
    h           = dht.readHumidity();            //Valor da umidade relativa do ar
    temperature = dht.readTemperature();         //Valor da temperatura
  
    if (isnan(temperature) || isnan(h)) 
    {
      Serial.println("  Falha ao ler DHT");
    }
    else 
    {
      Serial.print("  Umidade do AR: ");
      Serial.print(h);
      Serial.println("% ");                                    //Monitor serial
      Serial.print("  Temperatura: ");
      Serial.print(temperature);
      Serial.print(" °C");
      Serial.println("          ");
    }

    //***********************DOW**************************//

    Serial.print("  Seg DOW: ");
    Serial.println(EEPROM.read(addrSeg));

    Serial.print("  Ter DOW: ");
    Serial.println(EEPROM.read(addrTer));

    Serial.print("  Qua DOW: ");
    Serial.println(EEPROM.read(addrQua));

    Serial.print("  Qui DOW: ");
    Serial.println(EEPROM.read(addrQui));

    Serial.print("  Sex DOW: ");
    Serial.println(EEPROM.read(addrSex));

    Serial.print("  Sab DOW: ");
    Serial.println(EEPROM.read(addrSab));

    Serial.print("  Dom DOW: ");
    Serial.println(EEPROM.read(addrDom));

    //*************************************************************************************************************************************************************************//

    Serial.print("  Seg Start Time: ");
    Serial.print(EEPROM.read(addrHourSegStart));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinSegStart));

    Serial.print("  Seg Finish Time: ");
    Serial.print(EEPROM.read(addrHourSegFinish));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinSegFinish));

    Serial.print("  Ter Start Time: ");
    Serial.print(EEPROM.read(addrHourTerStart));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinTerStart));

    Serial.print("  Ter Finish Time: ");
    Serial.print(EEPROM.read(addrHourTerFinish));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinTerFinish));

    Serial.print("  Qua Start Time: ");
    Serial.print(EEPROM.read(addrHourQuaStart));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinQuaStart));

    Serial.print("  Qua Finish Time: ");
    Serial.print(EEPROM.read(addrHourQuaFinish));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinQuaFinish));

    Serial.print("  Qui Start Time: ");
    Serial.print(EEPROM.read(addrHourQuiStart));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinQuiStart));

    Serial.print("  Qui Finish Time: ");
    Serial.print(EEPROM.read(addrHourQuiFinish));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinQuiFinish));

    Serial.print("  Sex Start Time: ");
    Serial.print(EEPROM.read(addrHourSexStart));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinSexStart));

    Serial.print("  Sex Finish Time: ");
    Serial.print(EEPROM.read(addrHourSexFinish));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinSexFinish));

    Serial.print("  Sab Start Time: ");
    Serial.print(EEPROM.read(addrHourSabStart));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinSabStart));

    Serial.print("  Sab Finish Time: ");
    Serial.print(EEPROM.read(addrHourSabFinish));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinSabFinish));

    Serial.print("  Dom Start Time: ");
    Serial.print(EEPROM.read(addrHourDomStart));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinDomStart));

    Serial.print("  Dom Finish Time: ");
    Serial.print(EEPROM.read(addrHourDomFinish));
    Serial.print(":");
    Serial.println(EEPROM.read(addrMinDomFinish));
  }
}

void SerialReadAnthem(){
  // Pega posição do hino
  textPosAnthem = consoleText.lastIndexOf("Anthem Play", lastPosAnthem);
  lastPosAnthem = textPosAnthem;
  
  // Se mandou hino, toca
  if(textPosAnthem != -1){
    textPosAnthem = -1;

    HinoNacional();    
  }
}

void SerialReadDate(){
  // Pega posição da data
  textPosDate = consoleText.lastIndexOf("New Date:", lastPosDate);
  lastPosDate = textPosDate;
  
  // Se mandou data, muda informações no clock interno
  if(textPosDate != -1){
    textPosDate = -1;

    dayClock   = consoleText.substring(lastPosDate + 10, lastPosDate + 12).toInt();
    monthClock = consoleText.substring(lastPosDate + 13, lastPosDate + 15).toInt();
    yearClock  = consoleText.substring(lastPosDate + 16, lastPosDate + 20).toInt();
    dowClock   = consoleText.substring(lastPosDate + 22, lastPosDate + 25);

    // Deixa dia em int pra colocar no clock
    if(dowClock.equals("seg")){
      dowClockInt = 1;
    }else if(dowClock.equals("ter")){
      dowClockInt = 2;
    }else if(dowClock.equals("qua")){
      dowClockInt = 3;
    }else if(dowClock.equals("qui")){
      dowClockInt = 4;
    }else if(dowClock.equals("sex")){
      dowClockInt = 5;
    }else if(dowClock.equals("sab")){
      dowClockInt = 6;
    }else if(dowClock.equals("dom")){
      dowClockInt = 7;
    }
  
    // Ajustes da data
    rtc.setDate(dayClock, monthClock, yearClock);
    if((dowClockInt >= 1) || (dowClockInt <=7)){
      rtc.setDOW(dowClockInt);
    }
  }
}

void HumiditySensor(){
  t = rtc.getTime();
  
  // Sensor de umidade do solo

   valor_analogico = analogRead(pino_sinal_analogico);           //Le o valor do pino A1 do sensor
   valor_analogico = map(valor_analogico, 1023, 0, 0, 100);

   //Seta valores do EEPROM em variaveis
   valueSeg = EEPROM.read(addrSeg);
   valueTer = EEPROM.read(addrTer);
   valueQua = EEPROM.read(addrQua);
   valueQui = EEPROM.read(addrQui);
   valueSex = EEPROM.read(addrSex);
   valueSab = EEPROM.read(addrSab);
   valueDom = EEPROM.read(addrDom);

  bool working = false;
  bool dayIsTrue = false;
  bool timeIsTrue = false;
  String trueDOW;

  if(dowNow.equals("seg") &&  (valueSeg == 1)){
    dayIsTrue = true;
    trueDOW = "seg";
  }
  else if(dowNow.equals("ter") &&  (valueTer == 1)){
    dayIsTrue = true;
    trueDOW = "ter";
  }
  else if(dowNow.equals("qua") &&  (valueQua == 1)){
    dayIsTrue = true;
    trueDOW = "qua";
  }
  else if(dowNow.equals("qui") &&  (valueQui == 1)){
    dayIsTrue = true;
    trueDOW = "qui";
  }
  else if(dowNow.equals("sex") &&  (valueSex == 1)){
    dayIsTrue = true;
    trueDOW = "sex";
  }
  else if(dowNow.equals("sab") &&  (valueSab == 1)){
    dayIsTrue = true;
    trueDOW = "sab";
  }
  else if(dowNow.equals("dom") &&  (valueDom == 1)){ 
    dayIsTrue = true;   
    trueDOW = "dom";
  }  

  if(trueDOW.equals("seg") && (t.hour >= EEPROM.read(addrHourSegStart)) && (t.hour <= EEPROM.read(addrHourSegFinish))
  && (t.min >= EEPROM.read(addrMinSegStart)) || (t.min <= EEPROM.read(addrMinSegFinish))){
    timeIsTrue = true;
  }
  else if(trueDOW.equals("ter") && (t.hour >= EEPROM.read(addrHourTerStart)) && (t.hour <= EEPROM.read(addrHourTerFinish))
  && (t.min >= EEPROM.read(addrMinTerStart)) || (t.min <= EEPROM.read(addrMinTerFinish))){
    timeIsTrue = true;
  }
  else if(trueDOW.equals("qua") && (t.hour >= EEPROM.read(addrHourQuaStart)) && (t.hour <= EEPROM.read(addrHourQuaFinish))
  && (t.min >= EEPROM.read(addrMinQuaStart)) || (t.min <= EEPROM.read(addrMinQuaFinish))){
    timeIsTrue = true;
  }
  else if(trueDOW.equals("qui") && (t.hour >= EEPROM.read(addrHourQuiStart)) && (t.hour <= EEPROM.read(addrHourQuiFinish))
  && (t.min >= EEPROM.read(addrMinQuiStart)) || (t.min <= EEPROM.read(addrMinQuiFinish))){
    timeIsTrue = true;
  }
  else if(trueDOW.equals("sex") && (t.hour >= EEPROM.read(addrHourSexStart)) && (t.hour <= EEPROM.read(addrHourSexFinish))
  && (t.min >= EEPROM.read(addrMinSexStart)) || (t.min <= EEPROM.read(addrMinSexFinish))){
    timeIsTrue = true;
  }
  else if(trueDOW.equals("sab") && (t.hour >= EEPROM.read(addrHourSabStart)) && (t.hour <= EEPROM.read(addrHourSabFinish))
  && (t.min >= EEPROM.read(addrMinSabStart)) || (t.min <= EEPROM.read(addrMinSabFinish))){
    timeIsTrue = true;
  }
  else if(trueDOW.equals("dom") && (t.hour >= EEPROM.read(addrHourDomStart)) && (t.hour <= EEPROM.read(addrHourDomFinish))
  && (t.min >= EEPROM.read(addrMinDomStart)) || (t.min <= EEPROM.read(addrMinDomFinish))){
    timeIsTrue = true;
  }

  if(dayIsTrue && timeIsTrue)
  {
    t = rtc.getTime();
    
    if (valor_analogico < 40);{

      while (valor_analogico >= 0 && valor_analogico <= 50){

        digitalWrite (luzmin, HIGH);
        digitalWrite (luzmax, HIGH);
        digitalWrite (cooler, HIGH);
        digitalWrite (buzzer, HIGH);
        delay (1000);
        digitalWrite (buzzer, LOW);
        digitalWrite (bomba, LOW);          // Ativa a irrigação  
        
     
        titulo();
        lcd.setCursor(0, 2);            //Gota no display
        lcd.draw(agua,48,48);
        setFont();
        lcd.setCursor(51,4);
        lcd.print("Bomba ligada");

//****************************************************************************************************************************************************************************
        
        // Ler sensor de luminosidade
        LightSensor();

        // Ler sensor de umidade
        HumiditySensor();

        // Ler sensor de temperatura    
        TemperatureSensor();

//**********************************************************************************//**********************************************************************************************//

        // Lê console
        consoleText = Serial.readString();

        // Escreve no serial
        RefreshData();

        // Lê informações de data
        SerialReadDate();

        // Lê informações de hora
        SerialReadHour();

        // Lê informações do dia da semana
        SerialReadDOW();

        // Lê hino nacional
        SerialReadAnthem();

//*****************************************************************************************************************************************************************************

        delay (3000);
        digitalWrite (bomba, HIGH);
  
        valor_analogico = analogRead(pino_sinal_analogico);           //Le o valor do pino A1 do sensor novamente
        valor_analogico = map(valor_analogico, 1023, 0, 0, 100);

        if (valor_analogico > 50 && valor_analogico <= 100){          // se o solo estiver umido 
  
          irrigacaoConcluida();              //Void Irrigação Concluída
          lcd.print(valor_analogico);

          digitalWrite (bomba, HIGH);
          break;
           
        } 
        break;
      }
    }
  }

  if (valor_analogico >= 50 && valor_analogico <= 100);{
    digitalWrite(bomba, HIGH);
    lcd.clear();
  }
  
  if (valor_analogico >= 0 && valor_analogico < 2)   // sensor fora do solo
  {
    digitalWrite (49, HIGH);
    delay (100);                                          
    digitalWrite (49, LOW);
  }
}

void LightSensor(){
  //Linha da Luminosidade
  //Luminosidade ==> CMD

  valorpot = analogRead(pinopot);
  luzambiente = map(valorpot, 0, 1023, 0, 100);

  // Reação da leitura

  if ((map(valorpot,0,1023, 0, 100)) < 20){
    digitalWrite(luzmin, LOW);    
    digitalWrite(luzmax, HIGH);    
  }

  else if ((map(valorpot,0,1023, 0, 100)) > 20){
    digitalWrite(luzmin, LOW);}
  
  valorpot = analogRead(pinopot);
 
  if ((map(valorpot,0,1023, 0, 100)) < 65){
    digitalWrite(luzmin, LOW);
    digitalWrite(luzmax, HIGH); 
  }
  
  else if ((map(valorpot,0,1023, 0, 100)) > 65){
    digitalWrite(luzmax, LOW);
    digitalWrite(luzmin, HIGH);}
 
  if ((map(valorpot,0,1023, 0, 100)) < 90){
    digitalWrite(luzmin, LOW);
    digitalWrite(luzmax, HIGH); 
  }
  
  else if ((map(valorpot,0,1023, 0, 100)) > 90){
    digitalWrite(luzmax, HIGH);
    digitalWrite(luzmin, HIGH);}
}

 
void setup() {

  SetArduinoUp();

  SetDOWStrings();

  /* Teste de leds*/
  //LedTest();

  

}

//****************************************************************************************//************************************************************************************//

void loop() {

  botao = digitalRead (7);
  t = rtc.getTime();

  if (botao){

    // Testa a ordem dos relés
    // LedTest();

    // Mostra data no lcd
    DateArduinoShow();

    // Mostra hora no lcd
    HourArduinoShow(); 

    // Mostra luminosidade no lcd
    LightArduinoShow();

    // Mostra umidade no lcd
    HumidityArduinoShow();
    
    // Mostra temperatura no lcd
    TemperatureArduinoShow();
  
  }

//********************************************************************************//**********************************************************************************************//
//*******************************************************************************//***********************************************************************************************//

  else (botao);{
     
     //Sistema de reuso
     reuso();

    // Ler sensor de luminosidade
    LightSensor();

    // Ler sensor de umidade
    HumiditySensor();

    // Ler sensor de temperatura    
    TemperatureSensor();

//**********************************************************************************//**********************************************************************************************//

    // Lê console
    consoleText = Serial.readString();

    // Escreve no serial
    RefreshData();

    // Lê informações de data
    SerialReadDate();

    // Lê informações de hora
    SerialReadHour();

    // Lê informações do dia da semana
    SerialReadDOW();

    // Lê hino nacional
    SerialReadAnthem();


  }
}

//****************************************************************************************************************************************************************************
