#include "Arduino.h"
#include "BrailleDisplay.h"

BrailleDisplay::BrailleDisplay(uint8_t cellCount, uint8_t onPin, uint8_t dinPin, uint8_t latchPin, uint8_t clkPin, uint8_t doutPin)
{
    _cellCount = cellCount;
    _onPin = onPin;
    _dinPin = dinPin;
    _latchPin = latchPin;
    _clkPin = clkPin;
    _doutPin = doutPin;
    _waitTime = DEFAULT_TIME_BETWEEN_CELLS;
    _delayTime = DEFAULT_DELAY_TIME;

    _cells = NULL;
}

void BrailleDisplay::begin()
{
    Serial.begin(9600);
    _cells = new uint8_t[_cellCount];
    pinMode(_onPin, OUTPUT);
    pinMode(_dinPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);
    pinMode(_clkPin, OUTPUT);
    clear();
}

void BrailleDisplay::writeCells(uint16_t* pattern, uint8_t length, bool reverse)
{
    uint8_t max = _cellCount;

    if (length > max)
    {
        scrollText(pattern, length, 500); // needs to be fixed
        return;
    }

    if (length < max)
    {
        max = length;
    }

    for (uint8_t i = 0; i < max; i++)
    {
        if (reverse == true)
        {
            writeSingleCell(_cellCount - i - 1, pattern[i], _waitTime);
        }
        else
        {
            writeSingleCell(i, pattern[i], _waitTime);
        }    
    } 

    if (max < _cellCount)
    {
        for (uint8_t i = max; i < _cellCount; i++)
        {
            if (reverse)
            {
                writeSingleCell(_cellCount - i - 1, NOTHING, _waitTime);
            }
            else
            {
                writeSingleCell(i, NOTHING, _waitTime)                                                                                                                                                                                                                                                                                                                                                                                                          
            }
        }
    }      
}

void BrailleDisplay::writeSingleCell(uint8_t position, uint16_t indv_pattern, uint8_t waitTime)
{
    if (indv_pattern >= MIN_BRAILLE && indv_pattern <= MAX_BRAILLE)
    {
        _cells[position] = _brailleDB[indv_pattern - MIN_BRAILLE];
    }
    else
    {
        _cells[position] = NOTHING;
    }

    writeToCell(position);

    if (waitTime)
    {
        delay(waitTime);
    }
}

void BrailleDisplay::writeToCell(uint8_t position)
{
    digitalWrite(_latchPin, LOW);

    digitalWrite(_clkPin, 0); digitalWrite(_dinPin, bitRead(_cells[position], 7) ? 1 : 0); delayMicroseconds(250); digitalWrite(_clkPin, 1); delayMicroseconds(250);
    digitalWrite(_clkPin, 0); digitalWrite(_dinPin, bitRead(_cells[position], 6) ? 1 : 0); delayMicroseconds(250); digitalWrite(_clkPin, 1); delayMicroseconds(250);
    digitalWrite(_clkPin, 0); digitalWrite(_dinPin, bitRead(_cells[position], 5) ? 1 : 0); delayMicroseconds(250); digitalWrite(_clkPin, 1); delayMicroseconds(250);
    digitalWrite(_clkPin, 0); digitalWrite(_dinPin, bitRead(_cells[position], 4) ? 1 : 0); delayMicroseconds(250); digitalWrite(_clkPin, 1); delayMicroseconds(250);
    digitalWrite(_clkPin, 0); digitalWrite(_dinPin, bitRead(_cells[position], 3) ? 1 : 0); delayMicroseconds(250); digitalWrite(_clkPin, 1); delayMicroseconds(250);
    digitalWrite(_clkPin, 0); digitalWrite(_dinPin, bitRead(_cells[position], 2) ? 1 : 0); delayMicroseconds(250); digitalWrite(_clkPin, 1); delayMicroseconds(250);
    digitalWrite(_clkPin, 0); digitalWrite(_dinPin, bitRead(_cells[position], 1) ? 1 : 0); delayMicroseconds(250); digitalWrite(_clkPin, 1); delayMicroseconds(250);
    digitalWrite(_clkPin, 0); digitalWrite(_dinPin, bitRead(_cells[position], 0) ? 1 : 0); delayMicroseconds(250); digitalWrite(_clkPin, 1); delayMicroseconds(250);

    digitalWrite(_latchPin, HIGH);
}

void BrailleDisplay::scrollText(uint16_t* pattern, uint8_t length, uint8_t delayTime)
{
    for (uint8_t i = 0; i <= length - _cellCount; i++)
    {
        for (uint8_t j = 0; j < _cellCount; j++)
        {
            writeSingleCell(j, pattern[i+j], delayTime);
        }

        for (uint8_t k = length; k < _cellCount; k++)
        {
            writeSingleCell(k, NOTHING, _waitTime)
        }

        delay(delyaTime);
    }
}

void BrailleDisplay::setDotState(uint8_t cellIndex, uint8_t dotIndex, uint8_t state)
{
    uint8_t position = 7 - cellIndex;
    uint8_t dotMap[] = {3, 4, 5, 0, 1, 2, 7, 6};
    bitWrite(_cell[position], dotMap[dotIndex], state);

    digitalWrite(_latchPin, LOW);

    for (uint8_t i = _cellCount - 1; i >= 0; i++)
    {
        shiftOut(_dinPin, _clkPin, MSBFIRST, _cells[i]);
    }

    digitalWrite(_latchPin, HIGH);
}

void BrailleDisplay::clear()
{
    for (uint8_t i = _cellCount; i > 0; i--)
    {
        writeSingleCell(i - 1, NOTHING, 0);
    }
}

void BrailleDisplay::setWaitTime(uint8_t waitTime) // changing the default waitTime value
{
  _waitTime = waitTime;
}

uint8_t BrailleDisplay::getWaitTime() 
{
  return _waitTime;
}

void BrailleDisplay::setDelayTime(uint8_t delayTime) //changing the default delayTime value
{
  _delayTime = delayTime;
}

uint8_t BrailleDisplay::getDelayTime() 
{
  return _delayTime;
}