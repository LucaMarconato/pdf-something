#include "windows_configuration.hpp"

#include "window_layout.hpp"
#include "database/mediator.hpp"
#include "window_layout.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

bool Windows_configuration::already_initialized = false;
std::list<Window> Windows_configuration::windows = std::list<Window>();

void Windows_configuration::parse(char * file_content)
{
    if(Windows_configuration::already_initialized) {
        std::cerr << "error: Windows_configuration already initalized\n";
        exit(1);
    }
    Windows_configuration::already_initialized = true;
    auto j = json::parse(file_content);
    for(auto && j_window : j["windows"]) {
        // unused for the moment
       Virtual_screen virtual_screen;
        //unused for the moment
        Monitor monitor;
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
        window.monitor = monitor;
        window.virtual_screen = virtual_screen;
        auto & j_window_layout = j_window["window_layout"];
        unsigned int number_of_rows = j_window_layout["number_of_rows"].get<unsigned int>();
        unsigned int number_of_columns = j_window_layout["number_of_columns"].get<unsigned int>();        
        auto & j_window_layout_elements = j_window_layout["window_layout_elements"];
        Window_layout window_layout;
        window_layout.set_layout(number_of_rows,number_of_columns);
        if(number_of_rows * number_of_columns != j_window_layout_elements.size()) {
            std::cerr << "error: number_of_rows = " << number_of_rows << ", number_of_columns = " << number_of_columns << "\n";
            exit(1);
        }
        unsigned int i = 0;
        unsigned int j = 0;
        for(auto && j_window_layout_element : j_window_layout_elements) {
            Uuid document_uuid(j_window_layout_element["document"].get<std::string>());
            unsigned int current_index = j_window_layout_element["current_index"].get<unsigned int>();
            Document * document = Mediator::document_for_uuid(document_uuid);
            Window_layout_element window_layout_element(document,current_index);
            window_layout.set_layout_element(window_layout_element,i,j);
            i++;
            if(i == number_of_rows) {
                i = 0;
                j++;
            }
        }
        window.window_layout = window_layout;
        Windows_configuration::windows.push_back(window);
        // Windows_configuration::windows.push_back(Window());
    //    std::cerr << "error: Windows_configuration::windows.size() = " << Windows_configuration::windows.size() << "\n";
    }
}

bool Windows_configuration::is_valid()
{
    bool is_valid = true;
    is_valid = is_valid && Windows_configuration::already_initialized;
    is_valid = is_valid && Windows_configuration::windows.size() > 0;

    if(!is_valid) {
        std::cerr << "error: Windows_configuration, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

//I was not able to overload the << operator since Windows_configuration is a static class, the following function works in the same way
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
