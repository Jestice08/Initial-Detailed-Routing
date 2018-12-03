#ifndef _GUIDEREADER_H
#define _GUIDEREADER_H

#include "GuideDatabase.h"

class buffer{
public:
  char line[256];
};

void readGuide(std::string const &fileName, GuideDataBase &gdb);

#endif
