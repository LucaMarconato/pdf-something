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
                  -window split screen (a grid inside the window (1x2, 2x1 except for big screens), class Window_split_screen), for each grid position in the (class Window_split_screen_element):
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
    Mediator::load_latest_windows_configuration();
    // std::cout << "Windows_configuration\n";
    // Windows_configuration::print(std::cout);
    
    return 0;
}
