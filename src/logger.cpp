#include "logger.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

Logger logger;

void Logger::write(char *file, char *log, ... )
{
  va_list va_alist;

  char logbuf[8192] = { 0 };

  FILE * fp = NULL;

  va_start( va_alist, log );

  vsnprintf( logbuf + strlen( logbuf ),
         sizeof( logbuf ) - strlen( logbuf ),
         log, va_alist );

  va_end( va_alist );

  char path[ PATH_MAX ] = { 0 };

  strcat( path, modulePath );
  strcat( path, file );

  fp = fopen( path, "a" );

  if ( fp )
  {
    fprintf( fp, "%s\n", logbuf );
    fclose( fp );
  }
}

char* Logger::dirFile(char* file)
{
  static char path[ PATH_MAX ];
  memset( path, 0, PATH_MAX );
  strcat( path, modulePath );
  strcat( path, file );
  return path;
}
