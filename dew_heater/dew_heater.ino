//pin for buttons
#define KEYPIN A0
//button constants
#define btnRIGHT 6
#define btnUP 5
#define btnDOWN 4
#define btnLEFT 3
#define btnSELECT 2
#define btnNONE (-1)
#define MOSFETPIN 11 //n-channel- PWM capable
#define THERMPIN A1  //10k thermistor and 10k resistor

#include "idDHT11.h"

int idDHT11pin = 3;       //Digital pin for comunications
int idDHT11intNumber = 1; //interrupt number pin3 uses int.1 on uno
void dht11_wrapper();     // must be declared before the lib initialization
idDHT11 DHT11(idDHT11pin, idDHT11intNumber, dht11_wrapper);

void dht11_wrapper()
{
  DHT11.isrCallback();
}

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //for XC4454 LCD Shield LiquidCrystal lcd(RS, E, b4, b5, b6, b7);
//change normal backlight intensity here:
#define BACKLIGHTINTENSITY 40
#define BACKLIGHTPWMPIN 10

#include <avr/pgmspace.h>
// Big lookup Table (approx 750 entries), subtract 238 from ADC reading to start at 0*C. Entries in 10ths of degree i.e. 242 = 24.2*C Covers 0*C to 150*C For 10k resistor/10k thermistor voltage divider w/ therm on the + side.
const int temps[] PROGMEM = {0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 143, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155, 156, 157, 158, 159, 159, 160, 161, 162, 163, 164, 165, 166, 167, 167, 168, 169, 170, 171, 172, 173, 174, 175, 175, 176, 177, 178, 179, 180, 181, 182, 182, 183, 184, 185, 186, 187, 188, 189, 190, 190, 191, 192, 193, 194, 195, 196, 197, 197, 198, 199, 200, 201, 202, 203, 204, 205, 205, 206, 207, 208, 209, 210, 211, 212, 212, 213, 214, 215, 216, 217, 218, 219, 220, 220, 221, 222, 223, 224, 225, 226, 227, 228, 228, 229, 230, 231, 232, 233, 234, 235, 235, 236, 237, 238, 239, 240, 241, 242, 243, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 255, 256, 257, 258, 259, 260, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 422, 423, 424, 425, 426, 427, 428, 429, 430, 432, 433, 434, 435, 436, 437, 438, 439, 441, 442, 443, 444, 445, 446, 448, 449, 450, 451, 452, 453, 455, 456, 457, 458, 459, 460, 462, 463, 464, 465, 466, 468, 469, 470, 471, 472, 474, 475, 476, 477, 479, 480, 481, 482, 484, 485, 486, 487, 489, 490, 491, 492, 494, 495, 496, 498, 499, 500, 501, 503, 504, 505, 507, 508, 509, 511, 512, 513, 515, 516, 517, 519, 520, 521, 523, 524, 525, 527, 528, 530, 531, 532, 534, 535, 537, 538, 539, 541, 542, 544, 545, 547, 548, 550, 551, 552, 554, 555, 557, 558, 560, 561, 563, 564, 566, 567, 569, 570, 572, 574, 575, 577, 578, 580, 581, 583, 585, 586, 588, 589, 591, 593, 594, 596, 598, 599, 601, 603, 604, 606, 608, 609, 611, 613, 614, 616, 618, 620, 621, 623, 625, 627, 628, 630, 632, 634, 636, 638, 639, 641, 643, 645, 647, 649, 651, 653, 654, 656, 658, 660, 662, 664, 666, 668, 670, 672, 674, 676, 678, 680, 683, 685, 687, 689, 691, 693, 695, 697, 700, 702, 704, 706, 708, 711, 713, 715, 718, 720, 722, 725, 727, 729, 732, 734, 737, 739, 741, 744, 746, 749, 752, 754, 757, 759, 762, 764, 767, 770, 773, 775, 778, 781, 784, 786, 789, 792, 795, 798, 801, 804, 807, 810, 813, 816, 819, 822, 825, 829, 832, 835, 838, 842, 845, 848, 852, 855, 859, 862, 866, 869, 873, 877, 881, 884, 888, 892, 896, 900, 904, 908, 912, 916, 920, 925, 929, 933, 938, 942, 947, 952, 956, 961, 966, 971, 976, 981, 986, 991, 997, 1002, 1007, 1013, 1019, 1024, 1030, 1036, 1042, 1049, 1055, 1061, 1068, 1075, 1082, 1088, 1096, 1103, 1110, 1118, 1126, 1134, 1142, 1150, 1159, 1168, 1177, 1186, 1196, 1206, 1216, 1226, 1237, 1248, 1260, 1272, 1284, 1297, 1310, 1324, 1338, 1353, 1369, 1385, 1402, 1420, 1439, 1459, 1480, 1502};

//for saving startup defaults to eeprom
#include <EEPROM.h>
//eeprom addresses for variables
#define OFFSETMODEADDRESS 0
#define TEMPOFFSETADDRESS 1
#define PWMOUTPUTDEFAULTADDRESS 2

byte DHTdat[5];              //data from DHT11 sensor to be stored in 0.1 humidity% 2.3 degrees C
int tempoffset = 5;          //setpoint offset above dewpoint
byte offsetmode = 'D';       //default to dew point offset
int ambtemp, ambhum, dptemp; //all measured in 1/10's
int pwmoutputdefault = 52;   //10%

void setup()
{
  Serial.begin(9600); //if needed for debugging
  lcd.begin(16, 2);
  lcd.clear();
  int value = EEPROM.read(OFFSETMODEADDRESS);
  if ((value == 'D') || (value == 'A'))
  { //valid eeprom values found
    offsetmode = value;
    tempoffset = EEPROM.read(TEMPOFFSETADDRESS);
    pwmoutputdefault = EEPROM.read(PWMOUTPUTDEFAULTADDRESS);
    lcd.setCursor(0, 0);
    lcd.print("Load EEPROM OK  ");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Invalid EEPROM  ");
  }
  DHT11.acquire(); //start 1st conversion
  delay(500);      //and wait a bit for conversion to finish
  analogWrite(BACKLIGHTPWMPIN, BACKLIGHTINTENSITY);
}

void loop()
{
  int teletemp;       //telescope temperature
  int thermerror = 0; // flag for thermistor error
  teletemp = analogRead(THERMPIN);
  if ((teletemp == 0) | (teletemp > 950))
  {
    thermerror = thermerror | 1;
  } //thermistor error detected
  teletemp = teletemp - 238;
  if (teletemp < 0)
  {
    teletemp = 0;
  } //lookup table won't work if index<0
  teletemp = pgm_read_word(&temps[teletemp]);

  if (DHT11.getStatus() == IDDHTLIB_OK)
  {
    ambtemp = DHT11.getCelsius() * 10;
    ambhum = DHT11.getHumidity() * 10;
    dptemp = DHT11.getDewPointSlow() * 10;
  }
  else
  {
    thermerror = thermerror | 2;
  }

  int key;
  key = read_LCD_buttons();
  if (key == btnLEFT)
  {
    offsetmode = 'D';
  } //offset from dewpoint
  if (key == btnRIGHT)
  {
    offsetmode = 'A';
  } //offset from ambient
  if (key == btnUP)
  {
    tempoffset++;
    if (tempoffset > 9)
    {
      tempoffset = 9;
    }
  }
  if (key == btnDOWN)
  {
    tempoffset--;
    if (tempoffset < 0)
    {
      tempoffset = 0;
    }
  }
  if (key == btnSELECT)
  {
    savetoeeprom();
  } //save to eeprom (load happens on boot)

  int temptarget;
  if (offsetmode == 'D')
  {
    temptarget = dptemp + tempoffset * 10;
  }
  else
  {
    temptarget = ambtemp + tempoffset * 10; //default to (higher) ambient temp if anything but 'D'
  }

  int pwmoutput;
  pwmoutput = constrain(map(temptarget - teletemp, -10, 10, 0, 255), 0, 255);
  if (thermerror)
  {
    pwmoutput = pwmoutputdefault;
  }
  analogWrite(MOSFETPIN, pwmoutput);

  lcd.setCursor(0, 0);
  switch (thermerror)
  {
  case 0:
    LCDtopline();
    break;
  case 1:
    lcd.print("Thermistor fault");
    break;
  case 2:
    lcd.print("DHT11 fault     ");
    break;
  case 3:
    lcd.print("Thrm & DHT11 flt");
    break;
  default:
    lcd.print("Thrm & DHT11 flt");
    break;
  }

  lcd.setCursor(0, 1);
  lcd.print("T:");
  if (teletemp > 99)
  {
    lcd.write((teletemp / 100) % 10 + '0');
  }
  else
  {
    lcd.write(' ');
  }
  lcd.write((teletemp / 10) % 10 + '0');
  lcd.print("C H:");
  pwmoutput = (pwmoutput * 39) / 100; //scale to %
  if (pwmoutput > 9)
  {
    lcd.write((pwmoutput / 10) % 10 + '0');
  }
  else
  {
    lcd.write(' ');
  }
  lcd.write((pwmoutput) % 10 + '0');
  lcd.print("% ");
  lcd.write(offsetmode);
  lcd.print("+");
  lcd.write((tempoffset) % 10 + '0');
  lcd.print("C");
  DHT11.acquire(); //start next conversion
  delay(500);
}

int read_LCD_buttons()
{
  int adc_key_in = 0;
  adc_key_in = analogRead(KEYPIN);           // read the value from the sensor
  delay(5);                                  //switch debounce delay. Increase this delay if incorrect switch selections are returned.
  int k = (analogRead(KEYPIN) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
  if (5 < abs(k))
    return btnNONE; // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000)
    return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)
    return btnRIGHT;
  if (adc_key_in < 195)
    return btnUP;
  if (adc_key_in < 380)
    return btnDOWN;
  if (adc_key_in < 555)
    return btnLEFT;
  if (adc_key_in < 790)
    return btnSELECT;
  return btnNONE; // when all others fail, return this...
}

void LCDtopline()
{
  lcd.print("A:");
  if (ambtemp > 99)
  {
    lcd.write((ambtemp / 100) % 10 + '0');
  }
  else
  {
    lcd.write(' ');
  }
  lcd.write((ambtemp / 10) % 10 + '0');
  lcd.print("C ");
  if (ambhum > 99)
  {
    lcd.write((ambhum / 100) % 10 + '0');
  }
  else
  {
    lcd.write(' ');
  }
  lcd.write((ambhum / 10) % 10 + '0');
  lcd.print("% DP ");
  if (dptemp > 99)
  {
    lcd.write((dptemp / 100) % 10 + '0');
  }
  else
  {
    lcd.write(' ');
  }
  lcd.write((dptemp / 10) % 10 + '0');
  lcd.print("C ");
}

void savetoeeprom()
{
  int htr = 0;
  int key;
  analogWrite(MOSFETPIN, 0); //shut down heater in case button is stuck
  lcd.setCursor(0, 0);
  lcd.print("Choose value for");
  lcd.setCursor(0, 1);
  lcd.print("Heater backup:");
  while (read_LCD_buttons() == btnSELECT)
  { //cycle while select held down
    htr = htr + 5;
    if (htr > 99)
    {
      htr = 0;
    }
    lcd.setCursor(14, 1);
    if (htr > 9)
    {
      lcd.write((htr / 10) % 10 + '0');
    }
    else
    {
      lcd.write(' ');
    }
    lcd.write((htr) % 10 + '0');
    delay(500);
  }
  lcd.setCursor(0, 0);
  lcd.print("Saving EEPROM...");
  EEPROM.write(OFFSETMODEADDRESS, offsetmode);
  EEPROM.write(TEMPOFFSETADDRESS, tempoffset);
  EEPROM.write(PWMOUTPUTDEFAULTADDRESS, (htr + 1) * 100 / 39);
  delay(500);
}
