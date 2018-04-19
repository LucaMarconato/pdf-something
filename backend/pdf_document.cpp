#include "pdf_document.hpp"

#include <iostream>
#include <set>
#include <list>

#include "uuid.hpp"
#include "datetime.hpp"
#include "database/resources_manager.hpp"
#include "database/mediator.hpp"

#define MAX_WIDTH 150000
#define MAX_HEIGHT 150000
#define MAX_INDEX 100000
#define VALID_WIDTH (this->width > 0 && this->width < MAX_WIDTH)
#define VALID_HEIGHT (this->height > 0 && this->height < MAX_HEIGHT)
#define VALID_INDEX (this->index < MAX_INDEX)
                           
//----------------pdf page----------------
/*
  This constructor is needed by std::map beucase it must be able to create new empty objects.
  If we do not like this constructor to be public we can make this class a friend of std::map
*/

Pdf_page::Pdf_page()
{
    
}

Pdf_page::Pdf_page(std::shared_ptr<Pdf_document> in_document) : in_document(in_document)
{
    this->compute_size();
}

Pdf_page::Pdf_page(const Pdf_page & obj)
{
    this->in_document = obj.in_document;
    this->width = obj.width;
    this->height = obj.height;
    this->index = obj.index;
}

Pdf_page & Pdf_page::operator=(Pdf_page & obj)
{
    Pdf_page to_swap = Pdf_page(obj);
    swap(*this,to_swap);
    return *this;
}

void swap(Pdf_page & obj1, Pdf_page & obj2)
{
    std::swap(obj1.in_document,obj2.in_document);
    std::swap(obj1.width,obj2.width);
    std::swap(obj1.height,obj2.height);
    std::swap(obj1.index,obj2.index);
}

void Pdf_page::compute_size()
{
    std::cout << "TODO: Pdf_page::compute_size() to be implemented, using a fixed choice.\n";
    this->width = 100;
    this->height = 200;
}

inline bool Pdf_page::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->uuid.is_valid();

    if(!VALID_WIDTH || !VALID_HEIGHT || !VALID_INDEX) {
        is_valid = false;
        std::cerr << "warning: this->width = " << this->width << ", this->height = " << this->height << ", this->index = " << this->index << "\n";
    }
    if(!this->in_document) {
        is_valid = false;
        std::cerr << "warning: this->in_doument is not initialized\n";        
    }
    if(!is_valid) {
        std::cerr << "error: Pdf_page, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

// unsigned int Pdf_page::get_index() const
// {
//     if(!VALID_INDEX) {
//         std::cerr << "error: this->index = " << this->index << "\n";
//         exit(1);
//     }
//     return this->index;
// }

std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj)
{
    //obj.initialized is located in the Document superclass
    if(obj.is_valid()) {
        stream << "obj.uuid = " << obj.uuid << "\n";
        stream << "obj.in_docuent:\n";
        stream << obj.in_document << "\n";
        stream << "obj.width = " << obj.width << "\n";
        stream << "obj.height = " << obj.height << "\n";
        stream << "obj.index = " << obj.index;        
    } else {
        stream << "<uninitialized pdf page>";
    }
    return stream;
}

//----------------pdf document----------------
Pdf_document::Pdf_document(json const & j)
{
    // std::cout << "j[\"format\"] = " << j["format"] << "\n";
    this->uuid = Uuid(j["uuid"].get<std::string>());
    this->in_program_directory = j["in_program_directory"].get<std::string>();
    this->name = j["name"].get<std::string>();
    this->latest_opening = Datetime(j["latest_opening"].get<std::string>());
}

void Pdf_document::load_all_pages(json const & j)
{
    if(this->pages.size() > 0 || this->numbering.size() > 0) {
        std::cerr << "error: this->pages.size() = " << this->pages.size() << ", this->numbering.size() = " << this->numbering.size() << "\n";
        return;
    }
    
    for(auto && j_page : j["pages"]) {
        Uuid page_uuid(j_page["uuid"].get<std::string>());
        auto & j_highlightings = j_page["highlightings"];
        std::cout << "j_highlightings.size() = " << j_highlightings.size() << "\n";

        std::shared_ptr<Pdf_document> document = std::dynamic_pointer_cast<Pdf_document>(Mediator::document_for_uuid(uuid));
        std::cout << "document.get() = " << document.get() << "\n";
        std::shared_ptr<Pdf_page> page = Mediator::pdf_page_for_uuid(page_uuid, document);
        this->pages.insert(std::make_pair(page_uuid, page));
        for(auto && j_highlighting : j_highlightings) {
            //skipped for the moment
        }        
    }
    /*
      Here I am building a linked list. There are more efficient ways but this is probably the easiesy to type.
      I build also another linked list to check that the .json file was correct.
      In the .json file for each page there are three pieces of information: its uuid, the uuid of the previous page and the uuid of the next pages.
      The pages can be listed in a generic order (because pages can be moved), this is the reason I find useful to use an std::map
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
        exit(1);
    }

    //integrity check 
    if(!first.is_valid() || !last.is_valid()) {
        std::cerr << "error: unable to create the linked list for the page ordering\n";
        exit(1);
    }

    //build the linked lists
    std::list<Uuid> linked_list_forward;    
    std::list<Uuid> linked_list_backward;

    auto build_linked_list_from_map = [](std::map<Uuid,Uuid> & map_linked_list, std::list<Uuid> & linked_list, Uuid & begin, Uuid & end) {
        std::cout << "map_linked_list:\n";
        for(auto && kv: map_linked_list) {
            std::cout << "kv.first = " << kv.first << ", kv.second = " << kv.second << "\n";
        }
        unsigned int max_iterations = map_linked_list.size();
        unsigned int i = 0;
    
        Uuid * current = &begin;
        while(1) {
            linked_list.push_back(*current);
            i++;
            if(i > max_iterations) {
                std::cerr << "error: max_iterations = " << max_iterations << ", i = " << i << "\n";
                exit(1);
            }
            if(*current == end) {
                break;
            }
            if(map_linked_list.find(*current) == map_linked_list.end()) {
                std::cerr << "error: *current = " << *current << " not found in map\n";
                exit(1);
            }
            current = &(map_linked_list[*current]);
        }
    };
    
    build_linked_list_from_map(map_linked_list_forward, linked_list_forward, first, last);
    build_linked_list_from_map(map_linked_list_backward, linked_list_backward, last, first);
    linked_list_backward.reverse();

    //set the page ordering
    auto it = linked_list_forward.begin();
    auto jt = linked_list_backward.begin();
    unsigned int i = 0;
    while(it != linked_list_forward.end() && it != linked_list_backward.end()) {
        Uuid & uuid = *it;
        //integrity check
        if(uuid != *jt) {
            std::cerr << "error: *it = " << *it << ", *jt = " << *jt << "\n";
            exit(1);
        }
        this->numbering.insert( boost::bimap<Uuid, int>::value_type(uuid,i) );
        this->pages[uuid]->index = i;
        it++;
        jt++;
        i++;
    }
    
}

bool Pdf_document::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->Document::is_valid();

    if(this->pages.size() != this->numbering.size()) {
        is_valid = false;
        std::cerr << "error: this->pages.size() = " << this->pages.size() << ", this->numbering.size() = " << this->numbering.size() << "\n";
        exit(1);
    }
    
    if(this->pages.size() == 0) {
        is_valid = false;
        std::cerr << "error: this->pages.size() = " << this->pages.size() << "\n";
    }
    
    std::set<Uuid> uuid0;
    std::set<Uuid> uuid1;
    for(auto && e : this->pages) {
        Uuid & uuid = const_cast<Uuid &>(e.first);
        uuid0.insert(uuid);
        if(!Resources_manager::pdf_page_is_loaded(uuid)) {
            std::cerr << "error: pdf_page is not loaded, uuid = " << uuid << "\n";
            is_valid = false;
        }
    }
    for(auto && e : this->numbering.left) {
        Uuid & uuid = const_cast<Uuid &>(e.first);
        uuid1.insert(uuid);
        if(!Resources_manager::pdf_page_is_loaded(uuid)) {
            std::cerr << "error: pdf_page is not loaded, uuid = " << uuid << "\n";
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
        exit(1);
    }

    if(!is_valid) {
        std::cerr << "error: Pdf_document, is_valid = " << is_valid << "\n";
    }
    
    return is_valid;
}

void Pdf_document::print(std::ostream &stream) const
{
    //call the stream operator in the superclass to see also its content
    this->Document::print(stream);
    std::cout << "\n";
    
    if(this->is_valid()) {
        stream << "this->pages.size() = " << this->pages.size() << "\n";
        stream << "this->pages:\n";
        for(auto && page : this->pages) {
            stream << *(page.second) << "\n";
        }
    } else {
        stream << "<uninitialized pdf document>";
    }

}

std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj)
{
    obj.print(stream);
    return stream;
}

Pdf_document::~Pdf_document()
{
    
}
