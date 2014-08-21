#include "privateprofile.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#define MAX_LINE_LENGTH	512

int read_line(FILE *fp, char *bp)
{
  char c =  '\0';
  int i = 0;
  while ( (c = getc(fp)) != '\n')
  {
    if ( c == EOF )
      return (0);
    if (c != '\r')
      bp[i++] = c;
  }
  bp[i] = '\0';
  return (1);
}

/***************************************************************************
 * Function:	get_private_profile_int()
 * Arguments:	<char *> section - the name of the section to search for
 *              <char *> entry - the name of the entry to find the value of
 *              <int> def - the default value in the event of a failed read
 *              <char *> file_name - the name of the .ini file to read from
 * Returns:	the value located at entry
 ***************************************************************************/
int get_private_profile_int(const char *section,
    const char *entry, int def, const char *file_name)
{
  FILE *fp = fopen(file_name, "r");
  if (!fp) return (0);

  char buff[MAX_LINE_LENGTH];
  char *ep;
  char t_section[MAX_LINE_LENGTH];
  char value[6];
  int len = strlen(entry);
  int i;

  sprintf(t_section, "[%s]", section);
  /* Move through the file 1 line at a time until a section is matched or EOF */
  do
  {
    if ( !read_line(fp, buff) )
    {
      fclose(fp);
      return (def);
    }
  } while ( strcmp(buff, t_section) );

  /* Now that the section has been found, find the entry.
   * Stop searching upon leaving the section's area. */
  do
  {
    if ( !read_line(fp, buff) || buff[0] == '[' )
    {
      fclose(fp);
      return (def);
    }
  } while ( strncmp(buff, entry, len) );

  ep = strrchr(buff, '='); 	// parse out the equal sign
  ep++;
  if ( !strlen(ep) )		// no setting?
    return (def);

  /* Copy only numbers fail on characters */
  for (i = 0; isdigit(ep[i]); i++)
    value[i] = ep[i];
  value[i] = '\0';
  fclose(fp);			// clean up and return the value

  return (atoi(value));
}

/*******************************************************************************
 * Function: 	get_private_profile_string()
 * Arguments:	<char *> section - the name of the section to search for
 *		<char *> entry - the name of the entry to find the value of
 *		<char *> def - the default string in the event of a failed read
 *		<char *> buffer - a pointer to the buffer to copy into
 *		<int> buffer_len - the max number of characters to copy
 *		<char *> file_name - the name of the .ini file to read from
 * Returns:	the number of characters copied into the supplied buffer
 *******************************************************************************/
int get_private_profile_string(const char *section, const char *entry,
                               const char *def,
                               char *buffer, int buffer_len,
                               const char *file_name)
{
  FILE *fp = fopen(file_name, "r");
  if (!fp) return (0);

  char buff[MAX_LINE_LENGTH];
  char *ep;
  char t_section[MAX_LINE_LENGTH];
  // entry == NULL means copy the whole section
  int len = (entry != NULL) ? strlen(entry) : 0;

  sprintf(t_section, "[%s]", section);	// format the section name

  /* Move through the file 1 line at a time until a section is matched or EOF */
  do
  {
    if (!read_line(fp, buff))
    {
        fclose(fp);
        strncpy(buffer, def, buffer_len);
        return (strlen(buffer));
    }
  }
  while (strcmp(buff, t_section));

  /* Now that the section has been found, find the entry.
   * Stop searching upon leaving the section's area. */
  do
  {
    if (!read_line(fp, buff) || buff[0] == '[')
    {
      fclose(fp);
      strncpy(buffer, def, buffer_len);
      return (strlen(buffer));
    }
  }
  while ((len == 0) || strncmp(buff, entry, len));

  if (len > 0) {
    ep = strrchr(buff, '=');	// parse out the equal sign
    ep++;
    /* Copy up to buffer_len chars to buffer */
    strncpy(buffer, ep, buffer_len - 1);
  }

  buffer[buffer_len - 1] = '\0';
  fclose(fp);	// Clean up and return the amount copied

  return (strlen(buffer));
}

/*******************************************************************************
 * Function:	write_private_profile_string()
 * Arguments:	<char *> section - the name of the section to search for
 *		<char *> entry - the name of the entry to find the value of
 *		<char *> buffer - pointer to the buffer that holds the string
 *		<char *> file_name - the name of the .ini file to read from
 * Returns:	TRUE if successful, otherwise FALSE
 *******************************************************************************/
int write_private_profile_string(const char *section, const char *entry,
                                 const char *buffer, const char *file_name)
{
  FILE *rfp, *wfp;

  char tmp_name[15] = "PRIVPROFXXXXXX";
  char buff[MAX_LINE_LENGTH];
  char t_section[MAX_LINE_LENGTH];
  int len = strlen(entry);
  int tmpfd = mkstemp(tmp_name);	// Get a temporary file name to copy to

  sprintf(t_section, "[%s]", section);	// Format the section name

  if (!(rfp = fopen(file_name, "r")) )	// If the .ini file doesn't exist
  {
    if (!(wfp = fopen(file_name, "r"))) // then make one
      return (0);
    fprintf(wfp, "%s\n", t_section);
    fprintf(wfp, "%s=%s\n", entry, buffer);
    fclose(wfp);
    return (1);
  }
  if (!(wfp = fdopen(tmpfd, "w")))
  {
    fclose(rfp);
    return (0);
  }

  /* Move through the file one line at a time until a section is 
   * matched or until EOF. Copy to temp file as it is read. */
  do
  {
    if (!read_line(rfp, buff))
    {
      /* Failed to find section, so add one to the end */
      fprintf(wfp, "\n%s\n", t_section);
      fprintf(wfp, "%s=%s\n", entry, buffer);
      /* Clean up and rename */
      fclose(rfp);
      fclose(wfp);
      remove(file_name);
      rename(tmp_name, file_name);
      return (1);
    }
    fprintf(wfp, "%s\n", buff);
  }
  while (strcmp(buff, t_section));

  /* Now that the section has been found, find the entry. Stop searching
   * upon leaving the section's area. Copy the file as it is read
   * and create an entry if one is not found. */
  while (1)
  {
    if (!read_line(rfp, buff))
    {
      /* EOF without an entry so make one */
      fprintf(wfp, "%s=%s\n", entry, buffer);
      /* Clean up and rename */
      fclose(rfp);
      fclose(wfp);
      remove(file_name);
      rename(tmp_name, file_name);
      return (1);
    }

    if (!strncmp(buff, entry, len) || buff[0] == '\0')
      break;
    fprintf(wfp, "%s\n", buff);
  }

  if (buff[0] == '\0')
  {
    fprintf(wfp, "%s=%s\n", entry, buffer);
    do
    {
      fprintf(wfp, "%s\n", buff);
    }
    while (read_line(rfp, buff));
  }
  else
  {
    fprintf(wfp, "%s=%s\n", entry, buffer);
    while (read_line(rfp, buff))
    {
      fprintf(wfp, "%s\n", buff);
    }
  }

  /* Clean up and rename */
  fclose(wfp);
  fclose(rfp);
  remove(file_name);
  rename(tmp_name, file_name);
  return (1);
}

#undef MAX_LINE_LENGTH

