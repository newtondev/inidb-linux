#include "ini.h"
#include "privateprofile.h"

bool Ini::Read(char* file, char* section, char* key, char* defaultValue, char* output, size_t outputSize)
{
	if (get_private_profile_string(section, key, defaultValue, output, outputSize, file) == 0)
	{
		return false;
	}

	return true;
}

bool Ini::Write(char* file, char* section, char* key, char* value)
{
	if(write_private_profile_string(section, key, value, file) == 0)
	{
		return false;
	}

	return true;
}

bool Ini::Deletesection(char* file, char* section)
{
   if(write_private_profile_string(section, NULL, NULL, file) == 0)
   {
	   return false;
   }
   return true;
}

bool Ini::Deletekey(char* file, char* section, char* key)
{
   if(write_private_profile_string(section, key, NULL, file) == 0)
   {
	   return false;
   }
   return true;
}

