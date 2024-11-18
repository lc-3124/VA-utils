#include "VaTermControl.hpp"

VaTermControl::VaTermControl() {
  tcgetattr(STDIN_FILENO, &originalAttrs);
  currentAttrs = originalAttrs;
}

VaTermControl::~VaTermControl() {
  tcsetattr(STDIN_FILENO, TCSANOW, &originalAttrs);
}

void VaTermControl::getTerminalAttributes() {
  tcgetattr(STDIN_FILENO, &currentAttrs);
}

void VaTermControl::setTerminalAttributes(const termios &newAttrs) {
  currentAttrs = newAttrs;
  tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
}

void VaTermControl::enableEcho() {
  currentAttrs.c_lflag |= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
}

void VaTermControl::disableEcho() {
  currentAttrs.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
}

void VaTermControl::enableConsoleBuffering() {
  int flags = fcntl(STDIN_FILENO, F_GETFL);
  fcntl(STDIN_FILENO, F_SETFL, flags & ~O_SYNC);
}

void VaTermControl::disableConsoleBuffering() {
  int flags = fcntl(STDIN_FILENO, F_GETFL);
  fcntl(STDIN_FILENO, F_SETFL, flags | O_SYNC);
}

void VaTermControl::getTerminalSize(int &rows, int &cols) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  rows = w.ws_row;
  cols = w.ws_col;
}

void VaTermControl::setCursorPosition(int row, int col) {
  std::cout << "\033[" << row << ";" << col << "H";
}

void VaTermControl::saveCursorPosition() { std::cout << "\033[s"; }

void VaTermControl::restoreCursorPosition() { std::cout << "\033[u"; }

void VaTermControl::fastOutput(const char *str) {
  write(STDOUT_FILENO, str, strlen(str));
}

char VaTermControl::nonBufferedGetKey() {
  struct termios oldt, newt;
  char c;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  read(STDIN_FILENO, &c, 1);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

const char *VaTermControl::getTerminalType() { return std::getenv("TERM"); }

bool VaTermControl::isTerminalFeatureSupported(const char *feature) {
  // to do
  return 0;
}

void VaTermControl::setLineBuffering(bool enable) {
  if (enable) {
    currentAttrs.c_lflag |= ICANON;
  } else {
    currentAttrs.c_lflag &= ~ICANON;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
}

void VaTermControl::setCharacterDelay(int milliseconds) {
  // to do
}

int VaTermControl::getInputSpeed() {
  // to do
  return 0;
}

void VaTermControl::setInputSpeed(int speed) {
  // to do
}

void VaTermControl::setOutputSpeed(int speed) {
  // to do
}

char VaTermControl::getCharacter() {
  disableEcho();
  char c = nonBufferedGetKey();
  enableEcho();
  return c;
}

int VaTermControl::keyPressed() {
  struct termios oldt, newt;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  char c;
  int res = read(STDIN_FILENO, &c, 1);
  if (res > 0) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    return c;
  } else {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    return -1;
  }
}
