#include <string>

const unsigned int INVALID_UNFIROM_LOCATION = 0xffffffff;

#define GLCheckError() (glGetError() == 0)

bool ReadFile(const char* pFileName, std::string& outFile);

long long GetCurrentTimeMillis();