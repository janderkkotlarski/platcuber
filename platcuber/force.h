#ifndef FORCE_H
#define FORCE_H

enum class force_type
{
  none, gravity, repulse,
  spring_line, spring_plane, spring_space
};

class force
{
private:
  const force_type m_type
  { force_type::none };
public:
  force();
};



#endif // FORCE_H
