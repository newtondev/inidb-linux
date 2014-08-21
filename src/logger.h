#ifndef LOGGER_H
#define LOGGER_H

#include <limits.h>

class Logger
{
  public:
    void write(char *file, char *log, ... );
    char* dir(){ return modulePath; }
    char* dirFile(char* file);
  private:
    char modulePath[ PATH_MAX ];
};

extern Logger logger;

#endif
