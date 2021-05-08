#pragma once

struct String
{
    unsigned char length;   // Defines the length of the String in bytes
    char* addr;             // The addres where the String is saved
};

typedef struct String str;

str *testStr;

str constructStr(char *s);