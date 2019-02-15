#pragma once
#define PANIC(err_msg) PANIC_FUNC(err_msg, __FILE__, __LINE__)

void PANIC_FUNC(const char* err_msg, const char* filename, const int line);
