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
                  -window split screen (a grid inside the window, 1x2 in the canonical frontend, class Window_split_screen), for each grid position in the grid (class Window_split_screen_element):
                      -the pdf which was opened
                      -page it was opened
                      -crop information for each page (class Page)
                      -highlightings (class Highlighting)
                          highlightings can be semitransparent (normal) or opaque
                          highlightings can be selected (as a result of a previous search)
                          an highlighting is composed by various highlighting components (class Highlighting_component)
                          an highlighting only belongs to a pdf, no page is specified, while for each highlighting component it is specified the page the component belongs to
                      -which pages where bookmarked (this is emphasized in some way in the compass, for instance drawaing the corresponding miniature a bit lower)
  
      The cursor which was used (pen/rubber/highlighter/etc) is not recovered from the last section and it is shared among windows/split screen layouts.
      This because otherwise the user could get confused
    */
    
    /*
      The following line is an advance method, discussed in details asynchronous_loader.hpp. 
      You can ignore it for the moment, look at it when you are familiar with the code.
      Its purpose is to handle the cache better to gain better performance.
    */
    Resources_manager::initialize_resources_caching();

    /*
      Mediator is a "static" class which is used by the frontend to get items from the database (class Database) or from the collection of already loaded elements (class Resources_manager).
    */
    Mediator::load_latest_windows_configuration();
    std::cout << "Windows_configuration\n";
    /* 
       The output uses HTML tags for displaying indentations correctly. 
       To display it just use "make run", which calls (as you can see in CMakeLists.txt), the following:
       "run ./canonical-frontend > output.html && bash put_into_html_body.sh output.html"

       There is no way to overload << for a "static" class, this is the reason why I declared the function print
    */
    // Windows_configuration::print(std::cout);
    
    return 0;
}
