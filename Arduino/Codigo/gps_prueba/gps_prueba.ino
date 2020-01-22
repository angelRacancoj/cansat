#include <SoftwareSerial.h>

#include <TinyGPS.h>


#define N 32
/* Pines: 11(rx) and 10(tx)
   baud serial: 9600
   Voltaje necesario: 3.3v
*/

TinyGPS gps;
SoftwareSerial ss(4, 3);

static void smartdelay(unsigned long ms);
float print_float(float val, float invalid, int len, int prec);
int print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);

void setup()
{
  Serial.begin(115200);
  
  Serial.print("Testing TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
  Serial.println("Sats HDOP Latitude  Longitude  Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum");
  Serial.println("          (deg)     (deg)      Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail");
  Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");

  ss.begin(9600);
}

void loop()
{
  float flat, flon;
  unsigned long age, date, chars = 0;
  unsigned short sentences = 0, failed = 0;
  
  gps.f_get_position(&flat, &flon, &age);
  Serial.print("latitud:");
  float latitude =  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  Serial.print("longitud");
  float longitude = print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  Serial.print("fecha-Hora");
  print_date(gps);
  Serial.print("Altitud:");
  float altitud = print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 7, 2);
  Serial.println("");
  delay(1000);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

float print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
    return 0;
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  return val;
  smartdelay(0);
}

int print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  char anho[N], mes[N], dia[N], hora[N], minuto[N], segundo[N];
  String an, ms, da, hr, mt, sg;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    char sz[32];
    ms = sprintf(mes, "%02d", month);
    da = sprintf(dia, "%02d", day);
    hr = sprintf(hora, "%02d", hour);
    mt = sprintf(minuto, "%02d", minute);
    sg = sprintf(segundo, "%02d", second);
    
    //sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
    //    month, day, year, hour, minute, second);
    Serial.print(sz);
  }
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  smartdelay(0);
}



static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartdelay(0);
}
