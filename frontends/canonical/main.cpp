#include <iostream>
#include <string>
#include <backend.hpp>

int main(int argc, char * argv[])
{
    /*
      The application, as first thing, will load the previous session.
      The information needed to restore the session are listed here, in a hierarchical description.
  
      Information about:
          -windows which were open (class Window), for every window:
              -monitor (class Monitor) and virtual screen (class Virtual_screen) they where located
              -position and size (or fullscreen)
              -for each window:
                  -window split layout (a grid inside the window, class Window_layout), for each grid position in the layout (class Window_layout_element):
                      -the pdf which was open
                      -page it was opened
                      -zoom information
                      -highlightings (class Highlighting)
                          highlightings can be semitransparent (normal) or opaque
                          highlightings can be selected (as a result of a previous search)
                          an highlighting is composed by various highlighting components (class Highlighting_component).
                          an highlighting only belongs to a pdf, no page is specified, while for each highlighting component it is specified the page the component belongs to
                      -which pages where bookmarked (this is emphasized in some way in the compass, for instance drawaing the corresponding miniature a bit lower)
  
      The cursor which was used (pen/rubber/highlighter/etc) is not recovered from the last section and it is shared among windows/split screen layouts.
      This because otherwise the user could get confused
    */

    //here I show some classes as an example.
    Uuid uuid;
    std::cout << uuid << "\n\n";

    Color my_color = Color::orange();
    std::cout << my_color << "\n\n";

    Datetime datetime = Datetime::now();
    std::cout << datetime << "\n\n";

    Document document;
    std::cout << document << "\n\n";

    Highlighting highlighting(document);
    std::cout << highlighting << "\n\n";

    Pdf_document pdf_document;
    std::cout << pdf_document << "\n\n";

    Pdf_page pdf_page(pdf_document);
    std::cout << pdf_page << "\n\n";
    
    Highlighting_component highlighting_component(highlighting,pdf_page,0.5,0.5,0.6,0.6);
    std::cout << highlighting_component << "\n\n";

    Virtual_screen virtual_screen;
    std::cout << virtual_screen << "\n\n";
    
    Monitor monitor;
    std::cout << monitor << "\n\n";

    Window window(0,0,1200,800);
    window.virtual_screen = &virtual_screen;
    window.monitor = &monitor;
    std::cout << window << "\n\n";

    Window_layout window_layout;
    unsigned int rows = 2, columns = 3;
    window_layout.set_layout(rows,columns);
    std::tie(rows, columns) = window_layout.size();
    for(unsigned int i = 0; i < rows; i++) {
        for(unsigned int j = 0; j < columns; j++) {
            Window_layout_element e(&document);
            window_layout.set_layout_element(e,i,j);
        }
    }
    std::cout << window_layout << "\n\n";
    return 0;
}
