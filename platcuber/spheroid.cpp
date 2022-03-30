#include "spheroid.h"

spheroid::spheroid()
{

}

void spheroid::display()
{ DrawSphere(m_posit, 0.5f*m_side, m_color); }

void spheroid::set_shading(const Shader &shade)
{
  // m_model.materials[0].shader = shader;
}
