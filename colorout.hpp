#ifndef COLORBUFF_C
#define COLORBUFF_C

/* colorout.hpp
 * (c) 2012 Daniel S. Roche, USNA
 *
 * The class colorout below provides the functionality of
 * cout or cerr (depending on the first constructor argument being
 * 1 or 2, respectively). The only difference is that the output
 * is printed in the color corresponding to the second argument.
 * You use it by first calling the constructor to make a new object:
colorout out(1, 'r'); // r is for red
 * and then you can use that just like cout:
out << "This is " << "all red!\n";
 * Note that cout still prints in the default color.
 */

#include <unistd.h> // for isatty
#include <cstdlib>  // for exit
#include <iostream>

class colorbuf : public std::streambuf
{
private:
  int filedes;
  std::streambuf *dest;
  bool tty;
  char magic[7];

public:
  colorbuf(int fd, char color)
  {
    filedes = fd;
    if (filedes == 1)
      dest = std::cout.rdbuf();
    else if (filedes == 2)
      dest = std::cerr.rdbuf();
    else
    {
      std::cerr << "Illegal file descriptor in colorbuf constructor" << std::endl;
      exit(11);
    }
    tty = isatty(filedes);

    int colorcode;
    switch (color)
    {
    case 'b':
      colorcode = 30;
      break; // black
    case 'r':
      colorcode = 31;
      break; // red
    case 'g':
      colorcode = 32;
      break; // green
    case 'y':
      colorcode = 33;
      break; // yellow
    case 'u':
      colorcode = 34;
      break; // blue
    case 'w':
      colorcode = 37;
      break; // white
    default:
      std::cerr << "Illegal color for colorbuf" << std::endl;
      exit(12);
    }

    magic[0] = '\033';
    magic[1] = '[';
    magic[2] = colorcode / 10 + '0';
    magic[3] = colorcode % 10 + '0';
    magic[4] = ';';
    magic[5] = '1';
    magic[6] = 'm';
  }

protected:
  virtual int overflow(int ch)
  {
    if (tty)
      dest->sputn(magic, 7);
    dest->sputc(ch);
    if (tty)
      dest->sputn("\033[0m", 4);
  }
};

class colorout : public std::ostream
{
private:
  colorbuf buf;

public:
  colorout(int fd, int cc)
      : buf(fd, cc), std::ostream(&buf)
  {
  }
};

#endif