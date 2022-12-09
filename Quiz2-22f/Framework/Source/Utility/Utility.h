#pragma once

namespace fw {

double GetHighPrecisionTime();
void OutputMessage(const char* message, ...);
char* LoadCompleteFile(const char* filename, long* length);

}
