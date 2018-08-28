#include <stdio.h>
#include <stdlib.h>

int max(int n1, int n2) {
  if (n1 > n2) {
    return n1;
  }
  return n2;
}

int inBounds(int n, int offset, int size) {
  return offset <= n && n < offset+size;
}


int onBoundary(int n, int offset, int size) {
  return n == offset || n == offset+size-1;
}

int onOutline(int x, int y, int x_offset, int y_offset, int size) {
  return inBounds(x, x_offset, size) && onBoundary(y, y_offset, size);
}

// check if EITHER
//    x is less than size1 AND (y is either 0 or size1-1)
// OR
//    y is less than size1 AND (x is either 0 or size1-1)
int onOutline1(int x, int y, int size1) {
  return onOutline(x,y,0,0,size1) || onOutline(y,x,0,0,size1);
}

//check if  EITHER
//    ((x is between x_offset  and x_offset +size2) AND 
//     y is equal to either y_offset OR y_offset + size2 - 1 )
//  OR
//    ((y is between y_offset and y_offset + size2) AND
//     x is equal to either x_offset OR x_offset + size2 -1)
int onOutline2(int x, int y, int x_offset, int y_offset, int size2) {
  return onOutline(x,y,x_offset,y_offset,size2) || onOutline(y,x,y_offset,x_offset,size2);
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, x_offset+size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, y_offset+size2);
  //count from 0 to h. Call the number you count with y
  for (int y=0; y<h; y++) {
    //count from 0 to w. Call the number you count with x
    for (int x=0; x<w; x++) {
      // check if we are on the outline for square 2
      if (onOutline2(x, y, x_offset, y_offset, size2)) {
        // if so, print a *
	printf("*");
      }
      //if not, see if we are on the outline for square 1
      else if (onOutline1(x,y,size1)) {
        //if so, print a #
	printf("#");
      }
      else {
        //else print a space
	printf(" ");
      }
    }
    //when you finish counting x from 0 to w, 
    //print a newline
    printf("\n");
  }
}
