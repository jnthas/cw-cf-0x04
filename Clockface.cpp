#include "Clockface.h"

const byte CLOCK_POINTER_SIZE = 10;
const byte CLOCK_POINTER_POSX = 32;
const byte CLOCK_POINTER_POSY = 28;

const uint16_t BG_COLOR = 0x00E1;
const uint16_t POINTER_COLOR = 0xB58C;

const int HOUR_OFFSET = -30;
const int MIN_OFFSET = -6;

unsigned long lastMillis = millis() + 60000;

float clock_x1 = CLOCK_POINTER_POSX;
float clock_y1 = CLOCK_POINTER_POSY;

float lastHourAngle = 0;
float lastMinAngle = 0;

Clockface::Clockface(Adafruit_GFX* display) {
  _display = display;
  Locator::provide(display);
}

void Clockface::setup(CWDateTime *dateTime) {
  this->_dateTime = dateTime;
  Locator::getDisplay()->fillRect(0, 0, 64, 64, 0x0000);  
  updateClock();
}

void Clockface::update()
{ 
  if (millis() - lastMillis >= 60000) { 
    float additional_offset = (HOUR_OFFSET * _dateTime->getMinute())/60;

    float hourAngle = degreesToRadians((_dateTime->getHour()*HOUR_OFFSET)+180+additional_offset);
    float minAngle = degreesToRadians((_dateTime->getMinute()*MIN_OFFSET)+180);

    drawClockPointer(lastMinAngle, CLOCK_POINTER_SIZE, BG_COLOR);
    drawClockPointer(lastHourAngle, CLOCK_POINTER_SIZE-3, BG_COLOR);
    
    drawClockPointer(minAngle, CLOCK_POINTER_SIZE, POINTER_COLOR);
    drawClockPointer(hourAngle, CLOCK_POINTER_SIZE-3, POINTER_COLOR);

    lastHourAngle = hourAngle;
    lastMinAngle = minAngle;
    lastMillis = millis();
  }
}

void Clockface::drawClockPointer(float angle, byte pointerSize, uint16_t color) 
{
    clock_x1 = CLOCK_POINTER_POSX + (sin(angle) * pointerSize);
    clock_y1 = CLOCK_POINTER_POSY + (cos(angle) * pointerSize);
   
    Locator::getDisplay()->drawLine(CLOCK_POINTER_POSX,CLOCK_POINTER_POSY,clock_x1,clock_y1,color);
}

float Clockface::degreesToRadians(float degrees)
{
    return (degrees * 3.14) / 180;
}

void Clockface::updateClock() 
{
  Locator::getDisplay()->drawRGBBitmap(0, 0, _CLOCK_TOWER, 64, 64);
}
