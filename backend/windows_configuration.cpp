#include "windows_configuration.hpp"

#include "window_split_screen.hpp"
#include "database/mediator.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

bool Windows_configuration::already_initialized = false;
std::list<Window> Windows_configuration::windows = std::list<Window>();

void Windows_configuration::parse(char * file_content)
{
    if(Windows_configuration::already_initialized) {
        std::cerr << "error: Windows_configuration already initalized\n";
        MY_ASSERT(false); exit(1);
    }
    Windows_configuration::already_initialized = true;
    auto j = json::parse(file_content);
    for(auto && j_window : j["windows"]) {
        bool fullscreen = (j_window["fullscreen"].get<std::string>() == "true");
        double x0, x1, y0, y1;
        Window window;
        if(fullscreen) {
            window.set_dimentions(fullscreen);
        } else {
            x0 = j_window["x0"].get<double>();
            x1 = j_window["x1"].get<double>();
            y0 = j_window["y0"].get<double>();
            y1 = j_window["y1"].get<double>();
            window.set_dimentions(x0,y0,x1,y1);
        }
        // unused for the moment
        Virtual_screen virtual_screen;
        //unused for the moment
        Monitor monitor;
        window.monitor = monitor;
        window.virtual_screen = virtual_screen;
        
        auto & j_window_split_screen = j_window["window_split_screen"];
        unsigned int split_screen_number_of_rows = j_window_split_screen["number_of_rows"].get<unsigned int>();
        unsigned int split_screen_number_of_columns = j_window_split_screen["number_of_columns"].get<unsigned int>();        
        auto & j_window_split_screen_elements = j_window_split_screen["window_split_screen_elements"];

        if(split_screen_number_of_rows * split_screen_number_of_columns != j_window_split_screen_elements.size()) {
            std::cerr << "error: split_screen_number_of_rows = " << split_screen_number_of_rows << ", split_screen_number_of_columns = " << split_screen_number_of_columns << "\n";
            MY_ASSERT(false); exit(1);
        }
        
        Window_split_screen window_split_screen;
        window_split_screen.set_split_screen_layout(split_screen_number_of_rows,split_screen_number_of_columns);
        unsigned int j = 0; // the previous j variable is masked
        unsigned int i = 0;
        for(auto && j_window_split_screen_element : j_window_split_screen_elements) {
            Uuid document_uuid(j_window_split_screen_element["document"].get<std::string>());
            Document * document = Mediator::document_for_uuid(document_uuid);
            Window_split_screen_element window_split_screen_element(document);
            window_split_screen.set_split_screen_element(window_split_screen_element,i,j);
            j++;
            if(j == split_screen_number_of_columns) {
                j = 0;
                i++;
            }
        }
        window.window_split_screen = window_split_screen;
        Windows_configuration::windows.push_back(window);
    }
}

bool Windows_configuration::is_valid()
{
    bool is_valid = true;
    is_valid = is_valid && Windows_configuration::already_initialized;
    is_valid = is_valid && Windows_configuration::windows.size() > 0;

    if(!is_valid) {
        std::cerr << "error: Windows_configuration, is_valid = " << is_valid << "\n";
        MY_ASSERT(false); exit(1);
    }
    return is_valid;
}

void Windows_configuration::print(std::ostream & stream)
{    
    stream << "Windows_configuration::windows:<BR>";
    for(auto & window: Windows_configuration::windows) {
        stream << "-window:";
        stream << "<blockquote>";
        stream << window;
        stream << "</blockquote>";
    }
}
