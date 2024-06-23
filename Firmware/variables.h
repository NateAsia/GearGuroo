/*****************************************
 *  PUBLIC VARIABLES / OBJECTS - GearGuroo
 ******************************************/

#define EEPROM_SIZE 8   // Change later to save user configurations    [t#, dif#, size#, numGears, calibrationA#(4B)]
#define BUZZZER_PIN  33 // Buzzer
#define LEDPIN 32       // Status LED
#define HS_PIN 2        // Halleffect Sensor 
#define SD_CS_PIN 5    // SD Card "CS" Pin
  
#define sDELAY 50       // Software Spacing for Sensors

#define mRUN_TIME esp_timer_get_time()/1000

int SDOFF = 1;
#define WIFIOFF 1

// DISPLAY Parameters
NexNumber nMPH    = NexNumber(0,  3, "nMPH");
NexNumber nGear   = NexNumber(0,  7, "nGear");
NexText nAngle    = NexText(  0,  6, "tAngle");
NexSlider sProg   = NexSlider(2,  2,  "j0");
NexText tFile     = NexText(  0,  8, "tFile");

NexButton bSET  = NexButton(0 ,9, "b0"); // this is the settings button
NexButton bSIZE = NexButton(3, 5, "b1"); // Wheel Size
NexButton bCAL  = NexButton(3, 4, "b0"); // Angle Offset
NexButton bDIF  = NexButton(3, 6, "b2"); // DIFFICULLTY
NexButton bGEAR = NexButton(3, 10, "b4"); // Gear Number
NexButton bSAVE = NexButton(3, 7, "b3"); // SAVE SETTINGS

NexPicture p0   = NexPicture(0, 1, "p0"); // Background
 


// Configuration Inputs
double calibrationA   = 0.0;  // DONE: USER INPUT 
int numGears          = 9;    // DONE: USER INPUT *******
int Diameter          = 1;   // DONE: USER INPUT
int userDiff          = 1;    // DONE: USER INPUT


// Initialize Moving AVG
movingAvg angleAvg(20); 
movingAvg mphAvg(50);

MPU6050 mpu6050(Wire);

// Developer Configurations (SDCARD Settings)
//File myFile;
int fileNumber=0;
char fileName[13] = "/test000.txt";
char filen[12] = "test000.txt";
char text[16];


long timer    = 0; 
//int Val1      = 0;
//int Val2      = 0;

long timerLast   = 0;
long timerNew    = 0;

long t        = 0;
long RPM      = 0;
double MPH      = 0;
double curAngle = 0;

uint32_t counter   = 0;

int avgAngle;
int avgMPH;
int recGear = 1;
int prevGear=0;

bool setPres    = false;
bool sizePres   = false;
bool calPres    = false;
bool difPres    = false;
bool savePres   = false;
bool gearPres   = false;

float angleAvg1 = 0; 
float speedAvg1 = 0; 
int newRec;
float output;


bool changedPic = false;

int melody[] = {
  NOTE_C4, NOTE_G3
};

int noteDurations[] = {
  8,8
};

struct Sensor {
  const uint8_t PIN;
  uint32_t numberOfDetections;
  bool pressed;
  
};

Sensor hall = {HS_PIN,0,false};  // OBJECT

//AsyncWebServer server(80);
//const char* ssid = "Iphone13_n";          // Your WiFi SSID
//const char* password = "NGRAD2020";       // Your WiFi Password

NexTouch *home_nex_list[] = 
{
    &bSET,
    NULL
};

NexTouch *settings_nex_list[] = 
{
    &bCAL,
    &bSIZE,
    &bDIF,
    &bSAVE,
    &bGEAR,
    NULL
};

// Reccome
int lastTime = 0;
int currRec = 0; 
float data1[300][2];
int numPts = 0;
long curTime   = 0;
