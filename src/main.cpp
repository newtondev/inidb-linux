#include <iostream>
#include <stdio.h>
#include <string.h>
#include "md5.h"
#include "base64.h"
#include "crc32.h"
#include "ini.h"
#include "logger.h"

#define INIDB_VERSION_NUMBER "1.5"

extern "C" void RVExtension(char *output, int outputSize, const char *function)
    {
        outputSize -= 1;

        if(strcmp(function, "version") == 0) {
			strncpy(output, INIDB_VERSION_NUMBER, outputSize);
		} else	{
			char* params = new char[strlen(function)];
                        strcpy(params, function);
			char* func = strtok(params, ";");

			if(func) {
				if(strcmp(func, "read") == 0) {

					char* file = strtok(NULL, ";");
					char* sec = strtok(NULL, ";");
					char* key = strtok(NULL, ";");

					if(file != NULL && sec != NULL && key != NULL) {
						char realFile[PATH_MAX] = {0};
						sprintf(realFile, "db/%s.ini", file);
						char trueValue[8192] = {0};
                                                std::string seed_str = "c0f916b469c17e0f967c6774e0d837fac0f916b469c17e0f967c6774e0d837fa";
                                                char *seed_val = const_cast<char*> (seed_str.c_str());
						if(Ini::Read(logger.dirFile(realFile), sec, key, seed_val, trueValue, 8192)){
							if(strcmp(trueValue, "c0f916b469c17e0f967c6774e0d837fac0f916b469c17e0f967c6774e0d837fa") == 0){
								strncpy(output, "[false];", outputSize);
							} else {
								sprintf(output, "[true, '%s'];", trueValue);
							}
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "write") == 0)	{

					char* file = strtok(NULL, ";");
					char* sec = strtok(NULL, ";");
					char* key = strtok(NULL, ";");
					char* val = strtok(NULL, ";");

					if(file != NULL && sec != NULL && key != NULL && val != NULL) {

						char realFile[PATH_MAX] = {0};
						sprintf(realFile, "db/%s.ini", file);

						if(Ini::Write(logger.dirFile(realFile), sec, key, val))	{
							strncpy(output, "[true];", outputSize);
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "deletesection") == 0)	{

					char* file = strtok(NULL, ";");
					char* sec = strtok(NULL, ";");

					if(file != NULL && sec != NULL) {
						char realFile[PATH_MAX] = {0};
						sprintf(realFile, "db/%s.ini", file);

						if(Ini::Deletesection(logger.dirFile(realFile), sec))	{
							strncpy(output, "[true];", outputSize);
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "deletekey") == 0)	{

					char* file = strtok(NULL, ";");
					char* sec = strtok(NULL, ";");
					char* key = strtok(NULL, ";");

					if(file != NULL && sec != NULL) {
						char realFile[PATH_MAX] = {0};
						sprintf(realFile, "db/%s.ini", file);

						if(Ini::Deletekey(logger.dirFile(realFile), sec, key))	{
							strncpy(output, "[true];", outputSize);
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "exists") == 0) {
					char* file = strtok(NULL, ";");

					if(file != NULL) {
						char realFile[PATH_MAX] = {0};

						sprintf(realFile, "db/%s.ini", file);
						FILE* fp = fopen(logger.dirFile(realFile), "r");

						if(fp) {
							fclose(fp);
							strncpy(output, "[true, true];", outputSize);
						} else {
							strncpy(output, "[true, false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "delete") == 0) {
					char* file = strtok(NULL, ";");

					if(file != NULL) {
						char realFile[PATH_MAX] = {0};

						sprintf(realFile, "db/%s.ini", file);

						if(remove(logger.dirFile(realFile)) == 0) {
							strncpy(output, "[true];", outputSize);
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "crc") == 0) {
					char* toHash = strtok(NULL, ";");

					if(toHash != NULL) {
						sprintf(output, "[true, '%X'];", crc32(toHash, strlen(toHash)));
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "md5") == 0) {
					char* toHash = strtok(NULL, ";");

					if(toHash != NULL) {
						unsigned char digest[16];

						MD5_CTX context;
						MD5_Init(&context);
						MD5_Update(&context, toHash, strlen(toHash));
						MD5_Final(digest, &context);

						sprintf(output, "[true, '%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x'];",
							digest[0], digest[1], digest[2], digest[3], digest[4], digest[5], digest[6],
							digest[7], digest[8], digest[9], digest[10], digest[11], digest[12], digest[13],
							digest[14], digest[15]);
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "b64_enc") == 0) {
					char* toHash = strtok(NULL, ";");

					if(toHash != NULL) {
						sprintf(output, "[true, '%s'];", base64_encode((unsigned char*)toHash, strlen(toHash)).c_str());
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(strcmp(func, "b64_dec") == 0) {
					char* toHash = strtok(NULL, ";");

					if(toHash != NULL) {
						sprintf(output, "[true, '%s'];", base64_decode(toHash).c_str());
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else {
					strncpy(output, "[false];", outputSize);
				}
			} else {
				strncpy(output, "[false];", outputSize);
			}
		}
		return;
}
