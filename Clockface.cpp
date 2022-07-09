#include "Clockface.h"

const byte CLOCK_POINTER_SIZE = 10;
const byte CLOCK_POINTER_POSX = 32;
const byte CLOCK_POINTER_POSY = 28;

unsigned long lastMillis = 0;

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
 
  if (millis() - lastMillis >= 1000) { 
    float hourAngle = (((_dateTime->getHour()*-30)+180) * 3.14) / 180;
    float minAngle = (((_dateTime->getMinute()*-6)+180) * 3.14) / 180;

    
    drawClockPointer(lastMinAngle, CLOCK_POINTER_SIZE, 0x00E1);
    drawClockPointer(lastHourAngle, CLOCK_POINTER_SIZE-2, 0x00E1);
    
    drawClockPointer(minAngle, CLOCK_POINTER_SIZE, 0xB58C);
    drawClockPointer(hourAngle, CLOCK_POINTER_SIZE-2, 0x8DAC);

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


void Clockface::updateClock() 
{
  Locator::getDisplay()->drawRGBBitmap(0, 0, _CLOCK_TOWER, 64, 64);
}
