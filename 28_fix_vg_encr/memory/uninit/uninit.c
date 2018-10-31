#include <stdio.h>
#include <stdlib.h>

void f(int x) {
  int y;
  int z = x + y;
  printf("%d\n", z);
}

int main(void) {
  f(4);
}
/*
 * the initialization problem was picked up by the compiler as shown below:
 *
gcc -ggdb3 -Wall -Werror -std=gnu99 -pedantic -o uninit uninit.c
uninit.c: In function ‘f’:
uninit.c:6:7: error: ‘y’ is used uninitialized in this function [-Werror=uninitialized]
   int z = x + y;
       ^
cc1: all warnings being treated as errors
Makefile:3: recipe for target 'uninit' failed
make: *** [uninit] Error 1
*/
/* The code compiles using gcc without -Wall -Werror.
 * This allowed me to run the program with valgrind
 *
 * valgrind ./uninit
 *
A complaint is issued only when your program attempts to make use 
of uninitialised data in a way that might affect your program's 
externally-visible behaviour. In this example, y is uninitialised. 
Memcheck observes the value being passed to printf and thence to 
vfprintf, but makes no comment. However, vfprintf has to examine 
the value of y so it can turn it into the corresponding ASCII string, 
and it is at this point that Memcheck complains.

Use --track-origins=yes to see where uninitialised values come from

 *
 * Below is the output from valgrind.
 * 529 is the process id.
 *
==529== Memcheck, a memory error detector
==529== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==529== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==529== Command: ./uninit
==529==
==529== error calling PR_SET_PTRACER, vgdb might block
==529== Conditional jump or move depends on uninitialised value(s)
==529==    at 0x4E988DA: vfprintf (vfprintf.c:1642)
==529==    by 0x4EA0F25: printf (printf.c:33)
==529==    by 0x108675: f (uninit.c:7)
==529==    by 0x108686: main (uninit.c:11)
==529==
==529== Use of uninitialised value of size 8
==529==    at 0x4E9486B: _itoa_word (_itoa.c:179)
==529==    by 0x4E97F0D: vfprintf (vfprintf.c:1642)
==529==    by 0x4EA0F25: printf (printf.c:33)
==529==    by 0x108675: f (uninit.c:7)
==529==    by 0x108686: main (uninit.c:11)
==529==
==529== Conditional jump or move depends on uninitialised value(s)
==529==    at 0x4E94875: _itoa_word (_itoa.c:179)
==529==    by 0x4E97F0D: vfprintf (vfprintf.c:1642)
==529==    by 0x4EA0F25: printf (printf.c:33)
==529==    by 0x108675: f (uninit.c:7)
==529==    by 0x108686: main (uninit.c:11)
==529==
==529== Conditional jump or move depends on uninitialised value(s)
==529==    at 0x4E98014: vfprintf (vfprintf.c:1642)
==529==    by 0x4EA0F25: printf (printf.c:33)
==529==    by 0x108675: f (uninit.c:7)
==529==    by 0x108686: main (uninit.c:11)
==529==
==529== Conditional jump or move depends on uninitialised value(s)
==529==    at 0x4E98B4C: vfprintf (vfprintf.c:1642)
==529==    by 0x4EA0F25: printf (printf.c:33)
==529==    by 0x108675: f (uninit.c:7)
==529==    by 0x108686: main (uninit.c:11)
==529==
1082692
==529==
==529== HEAP SUMMARY:
==529==     in use at exit: 0 bytes in 0 blocks
==529==   total heap usage: 1 allocs, 1 frees, 512 bytes allocated
==529==
==529== All heap blocks were freed -- no leaks are possible
==529==
==529== For counts of detected and suppressed errors, rerun with: -v
==529== Use --track-origins=yes to see where uninitialised values come from
==529== ERROR SUMMARY: 17 errors from 5 contexts (suppressed: 0 from 0)
*/
