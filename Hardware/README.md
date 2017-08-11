# Hardware
The user interface is a 4x20 LCD character display, with 8 buttons and 4 knobs to interact with. These are driven by the MSP430FR45969 microcontroller which will be on a PCB referenced in the project as the "Front Panel". The front panel only deals with the user inteface and it connects to another PCB called the "Main Board" that handles all the signal processing. Signal processing is done by the C5535 DSP with the AIC3204 audio codec handling audio IO. The front panel and main board are connected by board-to-board connectors carrying 3.3v power, ground, and an SPI bus for the FR5969 and C5535 to communicate.

# CAD
Both the front panel and main board are designed using kicad which is a free PCB design suite (http://kicad-pcb.org/). Each board folder contains standard kicad project files as well as a Component Library for the custom components i've made. In each folder is also a pdf show the latest version of the schematic.
