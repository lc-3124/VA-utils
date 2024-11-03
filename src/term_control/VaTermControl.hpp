/*
 * THis file includes a class 
 * Be used to control the terminal for tui
 * The name of methods are clear so i would not make a lot of comments
 *
 */
//std
#include <iostream>
#include <cstdio>
#include <cstring>
//sys
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>


/*
 * VatermControl
 * To use it, you should create a instantation
 * e.g.
 * //Create and save the Attributes
 *  VaTermControl *Myterm = new VaTermControl;
 * //use it
 *  Myterm -> disableEcho(); 
 * //release and set the original Attributes
 *  delete Myterm
 *
 */

class VaTermControl {
public:
    VaTermControl();
    ~VaTermControl();

    void getTerminalAttributes();

    void setTerminalAttributes(const termios& newAttrs);

    void enableEcho();

    void disableEcho();

    void enableConsoleBuffering();

    void disableConsoleBuffering();
    
    void getTerminalSize(int& rows, int& cols);

    void setCursorPosition(int row, int col);

    void clearScreen();

    void saveCursorPosition();

    void restoreCursorPosition();

    void setTextColor(int color);

    void setBackgroundColor(int color);

    void fastOutput(const char* str);

    char nonBufferedGetKey();

    const char* getTerminalType();

    bool isTerminalFeatureSupported(const char* feature);

    void setLineBuffering(bool enable);

    void setCharacterDelay(int milliseconds);

    int getInputSpeed();

    void setInputSpeed(int speed);

    int getOutputSpeed();

    void setOutputSpeed(int speed);
    
    //like getch()
    char getCharacter();
    //like kbhit()
    bool keyPressed();

private:
    termios originalAttrs;
    termios currentAttrs;
};
