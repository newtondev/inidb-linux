#ifndef WRITEPRIVATEPROFILESTRING_H
#define WRITEPRIVATEPROFILESTRING_H

int get_private_profile_int(const char *section, const char *entry, 
                            int def, const char *file_name);

int get_private_profile_string(const char *section, const char *entry, 
                               const char *def, 
                               char *buffer, int buffer_len, 
                               const char *file_name);

int write_private_profile_string(const char *section, const char *entry, 
                                 const char *buffer, const char *file_name);

#endif // WRITEPRIVATEPROFILESTRING_H
