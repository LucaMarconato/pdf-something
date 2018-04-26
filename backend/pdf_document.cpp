#include "pdf_document.hpp"

#include <iostream>
#include <set>
#include <list>

#include "uuid.hpp"
#include "datetime.hpp"
#include "pdf_page.hpp"
#include "database/resources_manager.hpp"
#include "database/mediator.hpp"
#include "timer.hpp"
#include "constants.hpp"

Pdf_document::Pdf_document(json const & j)
{
    this->uuid = Uuid(j["uuid"].get<std::string>());
    this->in_program_directory = j["in_program_directory"].get<std::string>();
    this->name = j["name"].get<std::string>();
    this->latest_opening = Datetime(j["latest_opening"].get<std::string>());
    this->index = j["current_index"].get<unsigned int>();
    auto & j_grid_layout = j["grid_layout"];
    unsigned int number_of_rows = j_grid_layout["rows"].get<unsigned int>();
    unsigned int number_of_columns = j_grid_layout["columns"].get<unsigned int>();
    Grid_layout grid_layout(number_of_rows, number_of_columns);
    this->grid_layout = grid_layout;    
}

void Pdf_document::load_all_pages(json const & j)
{    
    if(this->pages.size() > 0 || this->numbering.size() > 0) {
        std::cerr << "the document has already been loaded, this->pages.size() = " << this->pages.size() << ", this->numbering.size() = " << this->numbering.size() << "\n";
        MY_ASSERT(false);
        exit(1);
    }
    // --------allocating the pages and the highlighting components, putting them into the pages--------
    for(auto && j_page : j["pages"]) {
        Uuid page_uuid(j_page["uuid"].get<std::string>());
        Pdf_page * page = Mediator::pdf_page_for_uuid(page_uuid);
        page->compute_size();
        page->in_document = this;
        /*
          This is the real index of the page in the .pdf file.
          The page ordering shown to the user does not depend on this but on Page::index.
          Page::index_in_pdf is used for rendering the Page.
          Using two indexes we can swap two pages with virtually no cost.
        */
        page->index_in_pdf = j_page["index_in_pdf"];
        this->pages.insert(std::make_pair(page_uuid, page));

        auto & j_highlighting_components_in_page = j_page["highlighting_components"];

        for(auto && j_highlighting_component : j_highlighting_components_in_page) {
            Uuid highlighting_component_uuid(j_highlighting_component.get<std::string>());
            Highlighting_component * highlighting_component = Mediator::highlighting_component_for_uuid(highlighting_component_uuid);
            highlighting_component->in_page = page;
            page->highlighting_components.push_back(highlighting_component);
        }
        auto & j_crop = j_page["crop"]; 
        page->x0_crop = j_crop["x0"].get<double>(); 
        page->y0_crop = j_crop["y0"].get<double>(); 
        page->x1_crop = j_crop["x1"].get<double>(); 
        page->y1_crop = j_crop["y1"].get<double>();
    }

    // --------giving pages the correct number--------
    /*
      Here I am building a linked list. There are more efficient ways but this is probably the easiest to type.
      I build also another linked list to check that the .json file has not corrupted information about the page ordering.
      In the .json file for each page there are three pieces of information: its uuid, the uuid of the previous page and the uuid of the next pagen.
      The pages can be listed in a generic order (because pages can be moved), this is the reason I find useful to use an std::map as an intermediate step for building the linked list
    */
    std::map<Uuid,Uuid> map_linked_list_forward;
    std::map<Uuid,Uuid> map_linked_list_backward;
    Uuid first;
    Uuid last;
    for(auto && j_page_ordering : j["pages_ordering"]) {
        Uuid page_uuid(j_page_ordering["uuid"].get<std::string>());
        auto & j_ordering = j_page_ordering["ordering"];
        std::string prev = j_ordering["prev"].get<std::string>();
        std::string next = j_ordering["next"].get<std::string>();
        if(next == "") {
            last = Uuid(page_uuid);
            map_linked_list_forward[page_uuid] = Uuid();
        } else {
            map_linked_list_forward[page_uuid] = Uuid(next);
        }
        if(prev == "") {
            first = Uuid(page_uuid);
            map_linked_list_backward[page_uuid] = Uuid();
        } else {
            map_linked_list_backward[page_uuid] = Uuid(prev);
        }
    }
    if(map_linked_list_forward.size() != map_linked_list_backward.size()) {
        std::cerr << "error: map_linked_list_forward.size() = " << map_linked_list_forward.size() << ", map_linked_list_backward.size() = " << map_linked_list_backward.size() << "\n";
        MY_ASSERT(false); exit(1);
    }

    // integrity check 
    if(!first.is_valid() || !last.is_valid()) {
        std::cerr << "error: unable to create the linked list for the page ordering\n";
        MY_ASSERT(false); exit(1);
    }

    // builds the linked lists using the maps
    std::list<Uuid> linked_list_forward;    
    std::list<Uuid> linked_list_backward;

    auto build_linked_list_from_map = [](std::map<Uuid,Uuid> & map_linked_list, std::list<Uuid> & linked_list, Uuid & begin, Uuid & end) {
        // std::cout << "map_linked_list:\n";
        // for(auto && kv: map_linked_list) {
        //     std::cout << "kv.first = " << kv.first << ", kv.second = " << kv.second << "\n";
        // }
        unsigned int max_iterations = map_linked_list.size();
        unsigned int i = 0;
    
        Uuid * current = &begin;
        while(1) {
            linked_list.push_back(*current);
            i++;
            if(i > max_iterations) {
                std::cerr << "error: max_iterations = " << max_iterations << ", i = " << i << "\n";
                MY_ASSERT(false); exit(1);
            }
            if(*current == end) {
                break;
            }
            if(map_linked_list.find(*current) == map_linked_list.end()) {
                std::cerr << "error: *current = " << *current << " not found in map\n";
                MY_ASSERT(false); exit(1);
            }
            current = &(map_linked_list[*current]);
        }
    };
    
    build_linked_list_from_map(map_linked_list_forward, linked_list_forward, first, last);
    build_linked_list_from_map(map_linked_list_backward, linked_list_backward, last, first);
    linked_list_backward.reverse();

    // sets the page ordering
    auto it = linked_list_forward.begin();
    auto jt = linked_list_backward.begin();
    unsigned int i = 0;
    while(it != linked_list_forward.end() && it != linked_list_backward.end()) {
        Uuid & uuid = *it;
        // integrity check
        if(uuid != *jt) {
            std::cerr << "error: *it = " << *it << ", *jt = " << *jt << "\n";
            MY_ASSERT(false); exit(1);
        }
        this->numbering.insert( boost::bimap<Uuid, int>::value_type(uuid,i) );
        this->pages[uuid]->index = i;
        it++;
        jt++;
        i++;
    }
    
    // --------loading the highlightings--------
    for(auto && j_highlighting : j["highlightings"]) {
        Uuid highlighting_uuid(j_highlighting["uuid"].get<std::string>());
        Highlighting * highlighting = Mediator::highlighting_for_uuid(highlighting_uuid);
        highlighting->in_document = this;        
        highlighting->color = Color::from_string(j_highlighting["color"].get<std::string>());
        highlighting->text = j_highlighting["text"].get<std::string>();
    }
    
    // --------loading the highlighting components--------
    for(auto && j_highlighting_component : j["highlighting_components"]) {
        Uuid highlighting_component_uuid(j_highlighting_component["uuid"].get<std::string>());
        Uuid parent_highlighting_uuid(j_highlighting_component["parent_highlighting"].get<std::string>());
        double x0 = j_highlighting_component["x0"].get<double>();
        double x1 = j_highlighting_component["x1"].get<double>();
        double y0 = j_highlighting_component["y0"].get<double>();
        double y1 = j_highlighting_component["y1"].get<double>();
        Highlighting_component * highlighting_component = Mediator::highlighting_component_for_uuid(highlighting_component_uuid);
        Highlighting * highlighting = Mediator::highlighting_for_uuid(parent_highlighting_uuid);
        highlighting->highlighting_components.push_back(highlighting_component);
        highlighting_component->parent_highlighting = highlighting;
        highlighting_component->x0 = x0;
        highlighting_component->x1 = x1;
        highlighting_component->y0 = y0;
        highlighting_component->y1 = y1;
    }
    if(!this->is_valid()) {
        std::cerr << "error: failed to load all pages\n";
        exit(1);
    }
}

std::string Pdf_document::serialize_to_json()
{
    std::cerr << "error: not yet implemented\n";
    MY_ASSERT(false); exit(1);
}

bool Pdf_document::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->Document::is_valid();
    is_valid = is_valid && this->pages.size() == this->numbering.size();
    is_valid = is_valid && VALID_PAGE_INDEX(this->pages.size()-1);

    // checks that this->pages and this->numbering are using the same set of uuids
    std::set<Uuid> uuid0;
    std::set<Uuid> uuid1;
    for(auto && e : this->pages) {
        Uuid & uuid = const_cast<Uuid &>(e.first);
        uuid0.insert(uuid);
        if(!Mediator::pdf_page_is_loaded(uuid)) {
            std::cerr << "error: (pages), pdf_page is not loaded, uuid = " << uuid << "\n";
            is_valid = false;
        }
    }
    for(auto && e : this->numbering.left) {
        Uuid & uuid = const_cast<Uuid &>(e.first);
        uuid1.insert(uuid);
        if(!Mediator::pdf_page_is_loaded(uuid)) {
            std::cerr << "error: (numbering.left), pdf_page is not loaded, uuid = " << uuid << "\n";
            is_valid = false;
        }
    }
    
    if(uuid0 != uuid1) {
        is_valid = false;
        std::cerr << "error: uuid0 != uuid1\n";
        for(auto && e : uuid0) {
            std::cout << "e = " << e << "\n";
        }
        for(auto && e : uuid1) {
            std::cout << "e = " << e << "\n";
        }
        MY_ASSERT(false); exit(1);
    }

    if(!is_valid) {
        std::cerr << "error: Pdf_document, is_valid = " << is_valid << "\n";
        MY_ASSERT(false); exit(1);
    }
    
    return is_valid;
}

void Pdf_document::print(std::ostream &stream) const
{
    //call the stream operator in the superclass to see also its content
    this->Document::print(stream);
    std::cout << "<BR>";
    
    if(this->is_valid()) {
        stream << "this->pages.size() = " << this->pages.size() << "<BR>";
        stream << "this->pages:<BR>";
        for(auto && page : this->pages) {
            stream << "-page:<BR>";
            stream << "<blockquote>";
            stream << *(page.second);
            stream << "</blockquote>";
        }
    } else {
        stream << "[uninitialized pdf document]";
    }

}

std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj)
{
    obj.print(stream);
    return stream;
}
