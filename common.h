#pragma once

typedef enum { true=1, false=0} bool;

void outb(const unsigned short int port, const unsigned char value);
unsigned char inb(const unsigned short int port);
unsigned short int inw(const unsigned short int port);

unsigned int malloc(unsigned int size);
void free(unsigned int ptr);
