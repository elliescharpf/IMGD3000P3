#ifndef __COLOR_H__
#define __COLOR_H__

namespace df {

/// Colors Dragonfly recognizes.
enum Color {
  UNDEFINED_COLOR = -1,
  BLACK = 0,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  CUSTOM,
};

/// If color not specified, use default
const Color COLOR_DEFAULT = WHITE;

} 
#endif //__COLOR_H__
