# BrailleDisplay Arduino Library

## Overview
BrailleDisplay is an Arduino library designed to interface with **P20 Metec** refreshable braille displays. It allows users to send Braille characters to the display, manage scrolling text, and control individual Braille cells with ease.

## Features
- Supports writing single Braille characters to individual cells.
- Displays multiple Braille characters at once.
- Scrolls text when the input exceeds the available cells.
- Allows direct manipulation of Braille dot states.
- Adjustable wait and delay times for smooth operation.
- Compatible with P20 Metec refreshable braille displays.

## Installation

1. Download the repository as a ZIP file or clone it:
   ```sh
   git clone https://github.com/yourusername/BrailleDisplay.git
   ```
2. Copy the **BrailleDisplay** folder into your Arduino `libraries` directory.
3. Restart the Arduino IDE.
4. Include the library in your sketch:
   ```cpp
   #include <BrailleDisplay.h>
   ```

## Usage

### Initialization
```cpp
#include <BrailleDisplay.h>

#define CELL_COUNT <Number Of Cells>
#define ON_PIN <On Pin>
#define DIN_PIN <Data In Pin>
#define LATCH_PIN <STROBE Pin>
#define CLK_PIN <Clock Pin>
#define DOUT_PIN <Data Out Pin>

BrailleDisplay display(CELL_COUNT, ON_PIN, DIN_PIN, LATCH_PIN, CLK_PIN, DOUT_PIN);

void setup()
{
    BrailleDisplay.begin();
}
```

### Writing a Character
```cpp
void setup()
{
    BrailleDisplay.writeCell('A', 0); // Writes 'A' to the first cell
    delay(1000);
    BrailleDisplay.clear(); // Clears the display
}
```

### Writing Full Text
```cpp
#define PATTERN_LENGTH 7

uint16_t pattern[PATTERN_LENGTH] = 
{
    0x283a,  0x2811,  0x2807,  0x2809,  0x2815,  0x280d,  0x2811
  // 0x283a,  0x2811,  0x2807,  0x2809,  0x2815,  0x280d,  0x2811
  //    ⠺         ⠑        ⠇        ⠉       ⠕        ⠍        ⠑ 
  //    W         E        L        C        O        M        E   
};

void setup()
{
  BrailleDisplay.begin();
  BrailleDisplay.writeCells(pattern, PATTERN_LENGTH, false);  // the final boolean argument in the function enables to display the text in reverse order is initialized to true 
}
  
```

### Controlling Individual Dots
```cpp
void setup()
{
  BrailleDisplay.setDotState(0, 0, 0); // sets the first dot of the first cell (from left) to HIGH
  BrailleDisplay.setDotState(3, 2, 1); // sets the fourth dot of the third cell (from left) to LOW
}
```

### Adjusting Wait and Delay Times
- Wait time: Interval between updating two consecutive cells.
- Delay time: Interval between scroll updates when text exceeds available cells.
```cpp
void setup()
{
    BrailleDisplay.setWaitTime(3000);  // Set wait time between cells
    BrailleDisplay.setDelayTime(500); // Set delay time for scrolling
}
```
## API Reference
| Function | Description |
|----------|-------------|
| `begin()` | Initializes the display. |
| `writeCell(char c, uint8_t cellIndex)` | Displays a character in the specified cell. |
| `writeCells(uint16_t* pattern, uint8_t length, bool reverse)` | Displays text on the display. If the length of text is greater than number of cells, then the text is scrolled across display. |
| `setDotState(uint8_t cellIndex, uint8_t dotIndex, uint8_t state, uint8_t* dotMap)` | Sets the state of an individual dot. |
| `setWaitTime(uint8_t waitTime)` | Sets the wait time between two consecutive cells. |
| `getWaitTime()` | Returns the current wait time. |
| `setDelayTime(uint8_t delayTime)` | Sets the delay time between scroll updates. |
| `getDelayTime()` | Returns the current delay time. |
| `clear()` | Clears the display. |

## Hardware Compatibility
This library was developed with **P20 Metec** braille displays in mind. Compatibility with other hardware may require adjustments.

## Contributing
Feel free to contribute by submitting issues and pull requests!

## Authors
Developed at **Sejong University** by **Prithwis Das** under the guidance of **Prof. Luis Arturo Cavazos Quero**.

## License
This project is licensed under the MIT License.


