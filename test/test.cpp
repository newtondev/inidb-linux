#include "./../src/privateprofile.h"
#include <string>
#include <iostream>

int main()
{
//  char *buffer = new char[200];
//  get_private_profile_string("tsect2", "tkey2_2",
//                               "picard",
//                               buffer, 200,
//                               "testdb.ini");
//  std::cout << buffer << std::endl;


  write_private_profile_string("tsect1", "tkey1_1", "tval1_1", "testdb.ini"); 
  write_private_profile_string("tsect1", "tkey1_2", "tval1_2", "testdb.ini");
  write_private_profile_string("tsect1", "tkey1_3", "tval1_3", "testdb.ini");
  write_private_profile_string("tsect1", "tkey1_4", "tval1_4", "testdb.ini");
  write_private_profile_string("tsect1", "tkey1_5", "tval1_5", "testdb.ini");
  write_private_profile_string("tsect1", "tkey1_6", "tval1_6", "testdb.ini");

  write_private_profile_string("tsect2", "tkey2_1", "tval2_1", "testdb.ini");
  write_private_profile_string("tsect2", "tkey2_2", "tval2_2", "testdb.ini");
  write_private_profile_string("tsect2", "tkey2_3", "tval2_3", "testdb.ini");
  write_private_profile_string("tsect2", "tkey2_4", "tval2_4", "testdb.ini");
  write_private_profile_string("tsect2", "tkey2_5", "tval2_5", "testdb.ini");
//  write_private_profile_string("tsect3", NULL, NULL, "testdb.ini");
  write_private_profile_string("tsect2", "tkey2_6", "tval2_6", "testdb.ini");

  write_private_profile_string("tsect3", "tkey3_1", "tval3_1", "testdb.ini");
  write_private_profile_string("tsect3", "tkey3_2", "tval3_2", "testdb.ini");
  write_private_profile_string("tsect3", "tkey3_3", "tval3_3", "testdb.ini");
  write_private_profile_string("tsect3", "tkey3_4", "tval3_4", "testdb.ini");
  write_private_profile_string("tsect3", "tkey3_5", "tval3_5", "testdb.ini");
  write_private_profile_string("tsect3", "tkey3_6", "tval3_6", "testdb.ini");

  return 0;
}
