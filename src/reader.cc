/*
 This is an open source non-commercial project. Dear PVS-Studio, please check
 it. PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
 http://www.viva64.com
*/

#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace BGPSim {
void Reader::ReadString(std::string s) { ReadString(s.c_str()); }

void Reader::ReadFile(std::string filename) { ReadFile(filename.c_str()); }

void Reader::ReadString(const char *s) {
  char *copy = strdup(s);
  char *saveptr = NULL;
  char *token;

  token = strtok_r(copy, "\r\n", &saveptr);
  while (token != NULL) {
    if (!skipcomments_ || token[0] != commentchar_) {
      ParseLine(token);
    }

    token = strtok_r(NULL, "\r\n", &saveptr);
  }

  free(copy);
}

void Reader::ReadFile(const char *filename) {
  FILE *file = fopen(filename, "rb");
  char *buffer = new char[maxlinelength_];

  if (!file) {
    perror("Cannot open file");
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, maxlinelength_, file) != NULL) {
    if (skipcomments_ && buffer[0] == commentchar_) {
      continue;
    }

    ParseLine(buffer);
  }

  fclose(file);
  delete[] buffer;
}

void Reader::SkipComments(bool enabled) { skipcomments_ = enabled; }

void Reader::SetMaxLineLength(size_t length) { maxlinelength_ = length; }

}  // namespace BGPSim
