#include "chromatic.h"

chromatic::chromatic()
{

}

void chromatic::pogo()
{
  if (m_up)
  {
    ++m_intensity;

    if (m_intensity >= 255)
    {
      m_intensity = 255;

      m_up = false;

      if (m_choice < 0)
      { m_choice = 0; }
      else if (m_choice == 0)
      { m_choice = 1; }
      else
      { m_choice = -1; }
    }
  }
  else
  {
    --m_intensity;

    if (m_intensity <= 127)
    {
      m_intensity = 127;

      m_up = true;
    }
  }
}

void chromatic::choose()
{
  if (m_choice < 0)
  { m_color.r = m_intensity; }

  if (m_choice == 0)
  { m_color.g = m_intensity; }

  if (m_choice > 0)
  { m_color.b = m_intensity; }
}

Color chromatic::get_color()
{ return m_color; }
