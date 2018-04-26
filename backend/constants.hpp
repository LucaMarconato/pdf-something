#ifndef CONSTANTS_H
#define CONSTANTS_H

// when cropping or when adding highlighting we will not exceed this relative coordinates
#define PAGE_EXTRA_BORDER 2.0
#define PAGE_MIN_X 0.0 - PAGE_EXTRA_BORDER
#define PAGE_MIN_Y 0.0 - PAGE_EXTRA_BORDER
#define PAGE_MAX_X 1.0 + PAGE_EXTRA_BORDER
#define PAGE_MAX_Y 1.0 + PAGE_EXTRA_BORDER

#define VALID_PAGE_COORDINATES(x0,y0,x1,y1) \
             ((x0) < (x1) && \
              (y0) < (y1) && \
      (PAGE_MIN_X) <= (x0) && \
              (x1) <= (PAGE_MAX_X) && \
      (PAGE_MIN_Y) <= (y0) && \
              (y1) <= PAGE_MAX_Y)

// --------------------------------

// in pixels
#define PAGE_MAX_WIDTH 150000
#define PAGE_MAX_HEIGHT 150000

// maximum number of page for a document
#define PAGE_MAX_INDEX 100000

#define VALID_PAGE_WIDTH(width) ((width) > 0 && (width) < (PAGE_MAX_WIDTH))
#define VALID_PAGE_HEIGHT(height) ((height) > 0 && (height) < (PAGE_MAX_HEIGHT))
#define VALID_PAGE_INDEX(index) ((index) < (PAGE_MAX_INDEX))

// --------------------------------

// 8K screen
#define WINDOW_MAX_W 7680
#define WINDOW_MAX_H 4320
// extreme coordinates for a maximized window in 8K screen, moved outside the screen
#define WINDOW_MIN_X (-1*(WINDOW_MAX_W))
#define WINDOW_MIN_Y (-1*(WINDOW_MAX_H))
#define WINDOW_MAX_X (2*(WINDOW_MAX_W))
#define WINDOW_MAX_Y (2*(WINDOW_MAX_H))

#define VALID_WINDOW_SIZE(x0,y0,x1,y1) \
               ((x0) < (x1) && \
                (y0) < (y1) && \
      (WINDOW_MIN_X) <= (x0) && \
                (x1) <= (WINDOW_MAX_X) && \
      (WINDOW_MIN_Y) <= (y0) && \
                (y1) <= (WINDOW_MAX_Y) && \
         (x1) - (x0) <= (WINDOW_MAX_W) && \
         (y1) - (y0) <= (WINDOW_MAX_H))

// --------------------------------

// some pdf viewers show a single page for a document, or maybe two or three, we show this huge grid
#define GRID_LAYOUT_MAX_ROWS 6
#define GRID_LAYOUT_MAX_COLUMNS 6

#define VALID_GRID_LAYOUT(rows,columns) ((rows) > 0 && (rows) <= (GRID_LAYOUT_MAX_ROWS) && (columns) > 0 && (columns) <= (GRID_LAYOUT_MAX_COLUMNS))

// --------------------------------

/*
  This function is usefull in Visual Studio Code because when the code crash in this way we are able to navigate in the stack trace and see what happened before the crash.
  We cannot do it with the assertion of <cassert>

  One case in which this macro was useful was inside the various is_valid() methods, like in highlighting.cpp, to understand which was the test making the variable is_valid false.
*/

#define MY_ASSERT(expression) \
    do {\
    	if(!(expression)) {\
        	std::cerr << "error: MY_ASSERTION failed\n";\
        	*(int *)"crash!" = true;\
        }\
    } while(0)

// --------------------------------

#endif //CONSTANTS_H
