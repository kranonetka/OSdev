#pragma once

typedef enum { true=1, false=0} bool;

void outb(unsigned short int port, unsigned char value);
unsigned char inb(unsigned short int port);
unsigned short int inw(unsigned short int port);
