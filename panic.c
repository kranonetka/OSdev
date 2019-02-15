#include "panic.h"
#include "string.h"
#include "video.h"

void PANIC_FUNC(const char* err_msg, const char* filename, const int line)
{
	print(">>>PANIC: ");
	print(filename);
	print(":");
	print(itoa(line, 10));
	print(": error: ");
	print(err_msg);
	print("<<<\n");
	while (1);
}
