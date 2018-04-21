
#ifndef CONSTANTS_H
#define CONSTANTS_H

//these constants are used to be sure that the above values cannot be excessively large
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

//--------------------------------

//in pixels
#define PAGE_MAX_WIDTH 150000
#define PAGE_MAX_HEIGHT 150000

//maximum number of page for a document
#define PAGE_MAX_INDEX 100000

#define VALID_PAGE_WIDTH(width) ((width) > 0 && (width) < (PAGE_MAX_WIDTH))
#define VALID_PAGE_HEIGHT(height) ((height) > 0 && (height) < (PAGE_MAX_HEIGHT))
#define VALID_PAGE_INDEX(index) ((index) < (PAGE_MAX_INDEX))

//--------------------------------

#define WINDOW_MIN_X 0
#define WINDOW_MIN_Y 0
#define WINDOW_MAX_X 15360 //16K screen
#define WINDOW_MAX_Y 8640 //16K screen

#define VALID_WINDOW_SIZE(x0,y0,x1,y1) \
               ((x0) < (x1) && \
                (y0) < (y1) && \
      (WINDOW_MIN_X) <= (x0) && \
                (x1) <= (WINDOW_MAX_X) && \
      (WINDOW_MIN_Y) <= (y0) && \
                (y1) <= (WINDOW_MAX_Y))

//--------------------------------

#define TEST0(expression,message_string) \
    do\
        {\
            if(!(expression)) {\
                std::cerr << message_string << "\n";\
                *(int *)"crash!" = 1;\
            }\
        }\
    while(0)


#endif //CONSTANTS_H
