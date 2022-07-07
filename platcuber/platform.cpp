#include "platform.h"

platform::platform()
{

}

Vector3 platform::get_pos() noexcept
{ return m_posit; }

void platform::set_pos(const Vector3 &pos)
{ m_posit = pos; }

void platform::display()
{
  DrawModel(m_model, m_posit, 1.0f, m_color);
}

void platform::set_plane()
{
  m_model = LoadModelFromMesh(GenMeshPlane(m_side, m_side, 100, 100));


}
