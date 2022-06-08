#ifndef CHROMATIC_H
#define CHROMATIC_H

#include "raylib.h"


class chromatic
{
private:
  Color m_color
  { 127, 255, 255, 255 };

  int m_intensity
  { m_color.r };

  bool m_up
  { true };

  int m_choice
  { -1 };

public:
  chromatic();

  void pogo();

  void choose();

  Color get_color();
};

#endif // CHROMATIC_H
