#include "json.hpp"

//__________________STUDENTE________________//

//struct Studente
//{
//Università Cà Foscari 
//Haddaoui Hakim ٩(◕‿◕｡)۶
//MATRICOLA: 892639
//Progetto di PEL(Programmazione e Laboratorio)
//};

using std::string;
using std::pair;



//<<<<<<<<<<<>>>>>>>>>DATA STRUCTURE<<<<<<<<<<<<<>>>>>>>>>>>>>

//__________________LIST________________//

struct list
{
    json info;
    list *next;
};

//__________________DICTIONARY________________//

struct dictionary
{
    pair<string, json> info;
    dictionary *next;
};

//__________________NOTA BENE________________//

// 0 null, 1 number, 2 string, 3 boolean_value, 4 lista, 5 dictionary

//__________________IMPL________________//

struct json::impl
{

    void default_settings();// Ripristina tutte le impostazioni interne ai valori BASE(info,list,dictionary).
    void reset_list();// Resetta la lista degli elementi JSON.
    void reset_dictionary(); // Resetta il dizionario degli elementi JSON.
    void reset_info();// Resetta le informazioni JSON base.

    ~impl(){
        reset_list();
        reset_dictionary();
    }

    int type; 
    double number;
    string Str;
    bool boolean_value;

    list *head_list;
    list *tail_list;

    dictionary *dicthead;
    dictionary *dictail;
 
  
    
};

//__________________FUNZIONI AUSILIARIE________________//
void json::impl::reset_list()
{
 list *list_temp = nullptr;
    while (head_list) {
        list_temp = head_list;
        head_list = head_list->next;
        delete list_temp;
    }
    head_list = nullptr;
    tail_list = nullptr;
}
void json::impl::reset_dictionary()
{
dictionary *dc = nullptr;
    while (dicthead) {
        dc = dicthead;
        dicthead = dicthead->next;
        delete dc;
    }
    dicthead = nullptr;
    dictail = nullptr;
}
void json::impl::reset_info()
{
    type = 0;
    number = 0;
    Str.clear();
    boolean_value = false;
}
void json::impl::default_settings()
{    
    reset_list();
    reset_dictionary();
    reset_info();
}
//__________________METODI SET________________//

void json::set_null() //0 null
{
    if (pimpl == nullptr) {
        pimpl = new impl{0, 0.0, "", false, nullptr, nullptr, nullptr, nullptr};
    } else {
        pimpl->default_settings();
        pimpl->type = 0;
    }
}

void json::set_number(double value) //1number
{
    if (pimpl == nullptr) {
        pimpl = new impl{1, value, "", false, nullptr, nullptr, nullptr, nullptr};
    } else {
        pimpl->default_settings();
        pimpl->type = 1;
        pimpl->number = value;
    }
}

void json::set_string(const string& value) //2string
{
    if (pimpl == nullptr) {
        pimpl = new impl{2, 0.0, value, false, nullptr, nullptr, nullptr, nullptr};
    } else {
        pimpl->default_settings();
        pimpl->type = 2;
        pimpl->Str = value;
    }
}

void json::set_bool(bool value)//3 bool
{
    if (pimpl == nullptr) {
        pimpl = new impl{3, 0.0, "", value, nullptr, nullptr, nullptr, nullptr};
    } else {
        pimpl->default_settings();
        pimpl->type = 3;
        pimpl->boolean_value = value;
    }
}

void json::set_list() //4 list
{
    if (pimpl == nullptr) {
        pimpl = new impl{4, 0.0, "", false, nullptr, nullptr, nullptr, nullptr};
    } else {
        pimpl->default_settings();
        pimpl->type = 4;
    }
}

void json::set_dictionary() //5 dictionary
{
    if (pimpl == nullptr) {
        pimpl = new impl{5, 0.0, "", false, nullptr, nullptr, nullptr, nullptr};
    } else {
        pimpl->default_settings();
        pimpl->type = 5;
    }
}

//__________________METHOD VERIFY TYPE________________//

bool json::is_null() const
{
return pimpl->type == 0; // 0 indica il tipo "null" nella struttura di implementazione
}
bool json::is_number() const
{
return pimpl->type == 1; // 1 indica il tipo "numero" nella struttura di implementazione
}
bool json::is_string() const
{
return pimpl->type == 2; // 2 indica il tipo "stringa" nella struttura di implementazione
}
bool json::is_bool() const
{
return pimpl->type == 3; // 3 indica il tipo "booleano" nella struttura di implementazione
}
bool json::is_list() const
{
return pimpl->type == 4; // 4 indica il tipo "lista" nella struttura di implementazione
}
bool json::is_dictionary() const
{
return pimpl->type == 5; // 5 indica il tipo "dictionary" nella struttura di implementazione
}

//__________________METODI GET________________//

double &json::get_number()
{
    if (is_number()) return pimpl->number;
    
    else throw json_exception { "è stata chiamata la funzione get_number su un oggetto che non è un numero" };
}
bool &json::get_bool()
{
    if (is_bool()) return pimpl->boolean_value;
    
    else throw json_exception { "è stata chiamata la funzione get_bool su un oggetto che non è un booleano" };
    
}
std::string &json::get_string()
{
    if (is_string()) return pimpl->Str;
    
    else throw json_exception { "è stata chiamata la funzione get_string su un oggetto che non è una stringa" };
    
}
double const &json::get_number() const
{
  if (is_number()) return pimpl->number;
    
    else throw json_exception { "è stata chiamata la funzione get_number const su un oggetto che non è un numero" };
   
}
bool const &json::get_bool() const
{
   if (is_bool()) return pimpl->boolean_value;
    
    else throw json_exception { "è stata chiamata la funzione get_bool const su un oggetto che non è un booleano" };
}
std::string const &json::get_string() const
{
   if (is_string()) return pimpl->Str;
    
    else throw json_exception { "è stata chiamata la funzione get_string const su un oggetto che non è una stringa" };
    
}

//__________________IMPL COSTRUTTORE, DISTRUTTORE, METODI________________//

json::json() : pimpl(new impl())// Costruttore crea json
{
    pimpl->type = 0;
    pimpl->number = 0;
    pimpl->Str = "";
    pimpl->boolean_value = false;

    pimpl->head_list = nullptr;
    pimpl->tail_list = nullptr;
    pimpl->dicthead = nullptr;
    pimpl->dictail = nullptr;
}
json::json(json const &other) : pimpl(new impl())// Costruttore di copia
{
    *this = other;
}
json::json(json &&other) : pimpl(other.pimpl)// Costruttore di spostamento
{
    other.pimpl = nullptr;
}
json::~json()//distruttore
{
if (pimpl){
    delete pimpl;
}
}
json &json::operator=(json const &other)// Operatore di assegnazione di copia

{
   if (this != &other)
    {
        pimpl->default_settings();
        switch (other.pimpl->type)
        { 
        case 0:{ 
            set_null();
            break;
        }
        case 1:{
            set_number(other.pimpl->number);
            break;
        }
        case 2:{
            set_string(other.pimpl->Str);
            break;
        }
        case 3:{
            set_bool(other.pimpl->boolean_value);
            break;
        }
        case 4:{
            set_list();
            list *list_temp = other.pimpl->head_list;
            while (list_temp)
            {
                push_back(list_temp->info);
                list_temp = list_temp->next;
            }
            break;
        }
        case 5:{
            set_dictionary();
            dictionary *dict_pc = other.pimpl->dicthead;
            while (dict_pc)
            {
                insert(dict_pc->info);
                dict_pc = dict_pc->next;
            }
            break;
        }
        }
    }
    return *this;
}
json &json::operator=(json &&other)// Operatore di assegnazione di spostamento
{
    if (this != &other)
    {
        delete pimpl;
        pimpl = other.pimpl;
        other.pimpl = nullptr;
    }
    return *this;
}

//__________________FUNZIONI DI INSERIMENTO________________//

void json::push_front(const json& item) { //Classic Push_Front
    if (is_list()) {
        list* list_temp = new list {item};
        list_temp->next = pimpl->head_list;
        pimpl->head_list = list_temp;
        if (!pimpl->tail_list) {
            pimpl->tail_list = list_temp;
        }
    } else {
        throw json_exception { "è stata chiamata la funzione push_front su un oggetto che non è una lista" };
    } 
}
void json::push_back(const json& item) {  //Classic Push_Back
    if (is_list()) {
        list* list_temp = new list {item, nullptr};

        if (pimpl->head_list == nullptr) {
            pimpl->head_list = list_temp;
            pimpl->tail_list = list_temp;
        } else {
            pimpl->tail_list->next = list_temp;
            pimpl->tail_list = list_temp;
        }
    } else {
        throw json_exception { "è stata chiamata la funzione push_back su un oggetto che non è una lista" };
    }
}
void json::insert(const std::pair<std::string, json>& item) { //Metodo Insert for Dictionary
    if (!is_dictionary()) {
    throw json_exception { "è stata chiamata la funzione insert su un oggetto che non è un dizionario" };
    }
    dictionary* dict_temp = new dictionary {item, nullptr};
     if (pimpl->dicthead == nullptr){
      
        pimpl->dicthead = dict_temp;
    }  
    else
        pimpl->dictail->next = dict_temp;
        pimpl->dictail = dict_temp;
} 

//<<<<<<<<<<<>>>>>>>>>ITERATOR<<<<<<<<<<<<<>>>>>>>>>>>>>()

//__________________LIST_ITERATOR________________//

struct json::list_iterator
{
public:
    list_iterator(list *ptr) : list_temp(ptr){};
    json &operator*() const;
    json *operator->() const;
    list_iterator &operator++();
    list_iterator operator++(int);
    bool operator==(list_iterator const &) const;
    bool operator!=(list_iterator const &) const;

private:
    list *list_temp;
};

//__________________LIST_ITERATOR METODI________________//

json &json::list_iterator::operator*() const
{

    return list_temp->info;
}
json *json::list_iterator::operator->() const
{

    return &(list_temp->info);
}
json::list_iterator &json::list_iterator::operator++()
{

    list_temp = list_temp->next;
    return *this;
}
json::list_iterator json::list_iterator::operator++(int)
{

    list_iterator prev_pc {list_temp};
    list_temp = list_temp->next;
    return prev_pc;
}
bool json::list_iterator::operator==(list_iterator const &dic) const
{

    return list_temp == dic.list_temp;
}
bool json::list_iterator::operator!=(list_iterator const &dic) const
{

    return list_temp != dic.list_temp;
}

//__________________CONST_LIST_ITERATOR________________//

struct json::const_list_iterator
{
public:
    const_list_iterator(const list *ptr) : list_temp(ptr){};

    const json &operator*() const;
    const json *operator->() const;
    const_list_iterator& operator++();
    const_list_iterator operator++(int);
    bool operator==(const_list_iterator const &) const;
    bool operator!=(const_list_iterator const &) const;

private:
    const list *list_temp;
};

//__________________CONST_LIST_ITERATOR METODI________________//

const json &json::const_list_iterator::operator*() const
{
    return list_temp->info;
}
const json *json::const_list_iterator::operator->() const
{
    return &(list_temp->info);
}
json::const_list_iterator &json::const_list_iterator::operator++()
{
    list_temp = list_temp->next;
    return *this;
}
json::const_list_iterator json::const_list_iterator::operator++(int)
{
    const_list_iterator prev_pc {list_temp};
    list_temp = list_temp->next;
    return prev_pc;
}
bool json::const_list_iterator::operator==(const_list_iterator const &dic) const
{
    return list_temp == dic.list_temp;
}
bool json::const_list_iterator::operator!=(const_list_iterator const &dic) const
{
    return list_temp != dic.list_temp;
}

//__________________DICTIONARY_ITERATOR________________//

struct json::dictionary_iterator
{
public:
    dictionary_iterator(dictionary *ptr) : list_temp(ptr){};
    std::pair<std::string, json> &operator*() const;
    std::pair<std::string, json> *operator->() const;
    dictionary_iterator &operator++();
    dictionary_iterator operator++(int);
    bool operator==(dictionary_iterator const &) const;
    bool operator!=(dictionary_iterator const &) const;

private:
    dictionary *list_temp;
};

//__________________DICTIONARY_ITERATOR METODI________________//

std::pair<std::string, json> &json::dictionary_iterator::operator*() const
{
    return list_temp->info;
}
std::pair<std::string, json> *json::dictionary_iterator::operator->() const
{
    return &(list_temp->info);
}
json::dictionary_iterator &json::dictionary_iterator::operator++()
{
    list_temp = list_temp->next;
    return *this;
}
json::dictionary_iterator json::dictionary_iterator::operator++(int)
{
    dictionary_iterator prev_pc {list_temp};
    list_temp = list_temp->next;
    return prev_pc;
}
bool json::dictionary_iterator::operator==(dictionary_iterator const &dic) const
{
    return list_temp == dic.list_temp;
}
bool json::dictionary_iterator::operator!=(dictionary_iterator const &dic) const
{
    return list_temp != dic.list_temp;
}

//__________________CONST_DICTIONARY_ITERATOR________________//

struct json::const_dictionary_iterator
{
public:
    const_dictionary_iterator(const dictionary *ptr) : list_temp(ptr){};
    const std::pair<std::string, json> &operator*() const;
    const std::pair<std::string, json> *operator->() const;
    const_dictionary_iterator &operator++();
    const_dictionary_iterator operator++(int);
    bool operator==(const_dictionary_iterator const &) const;
    bool operator!=(const_dictionary_iterator const &) const;

private:
    const dictionary *list_temp;
};

//__________________CONST_DICTIONARY_ITERATOR METODI________________//

const std::pair<std::string, json> &json::const_dictionary_iterator::operator*() const
{
    return list_temp->info;
}
const std::pair<std::string, json> *json::const_dictionary_iterator::operator->() const
{
    return &(list_temp->info);
}
json::const_dictionary_iterator &json::const_dictionary_iterator::operator++()
{
    list_temp = list_temp->next;
    return *this;
}
json::const_dictionary_iterator json::const_dictionary_iterator::operator++(int)
{
    const_dictionary_iterator prev_pc{list_temp};
    list_temp = list_temp->next;
    return prev_pc;
}
bool json::const_dictionary_iterator::operator==(const_dictionary_iterator const &dic) const
{
    return list_temp == dic.list_temp;
}
bool json::const_dictionary_iterator::operator!=(const_dictionary_iterator const &dic) const
{
    return list_temp != dic.list_temp;
}

//__________________GESTIONE_ITERATOR METODI________________//

json::list_iterator json::begin_list()
{
    if (is_list()) return list_iterator {json::pimpl->head_list};

    else throw json_exception { "è stata chiamata la funzione begin_list su un oggetto che non è una lista" };  
}
json::const_list_iterator json::begin_list() const
{
    if (is_list()) return const_list_iterator {json::pimpl->head_list};

    else throw json_exception { "è stata chiamata la funzione begin_list const su un oggetto che non è una lista" };
}
json::list_iterator json::end_list()
{
    if (is_list()) return {nullptr};
    
    else throw json_exception { "è stata chiamata la funzione end_list su un oggetto che non è una lista" };
    
}
json::const_list_iterator json::end_list() const
{
    if (is_list()) return {nullptr};
    
    else throw json_exception { "è stata chiamata la funzione end_list const su un oggetto che non è una lista" };   
}

//__________________GESTIONE_DICTIONARY METODI________________//

json::dictionary_iterator json::begin_dictionary()
{
    if (is_dictionary()) return dictionary_iterator{json::pimpl->dicthead};
    
    else throw json_exception { "è stata chiamata la funzione begin_dictionary su un oggetto che non è un dizionario" };
}
json::const_dictionary_iterator json::begin_dictionary() const
{
    if (is_dictionary()) return const_dictionary_iterator{json::pimpl->dicthead};
    
    else throw json_exception { "è stata chiamata la funzione begin_dictionary const su un oggetto che non è un dizionario" };
    
}
json::dictionary_iterator json::end_dictionary()
{
    if (is_dictionary()) return {nullptr};
    
    else throw json_exception { "è stata chiamata la funzione end_dictionary su un oggetto che non è un dizionario" };
}
json::const_dictionary_iterator json::end_dictionary() const
{
    if (is_dictionary()) return {nullptr};
    
    else throw json_exception { "è stata chiamata la funzione end_dictionary const su un oggetto che non è un dizionario" };
    
}

//__________________OPERATOR[]________________//

json& json::operator[](std::string const& key)
{
    if (!is_dictionary()){
        throw json_exception {"è stata chiamata la funzione operator[] su un oggetto che non è un dizionario"};
}
    for (dictionary_iterator dic = pimpl->dicthead; dic != end_dictionary(); ++dic)
    {
        if (key == dic->first)
            return dic->second;
    }

    json value {};
    std::pair<std::string,json> key_value {key, value};

    insert(key_value);

    return pimpl->dictail->info.second;
}
json const& json::operator[](std::string const& key) const
{
    if (!is_dictionary()){
        throw json_exception {"è stata chiamata la funzione operator[] const su un oggetto che non è un dizionario"};
}
    for (const_dictionary_iterator dic = pimpl->dicthead; dic != end_dictionary(); ++dic)
    {
        if (key == dic->first)
            return dic->second;
    }

    throw json_exception {"è stata chiamata la funzione operator[] const chiave non trovata"};
}

//__________________PARSING________________//

void parseNullValue(std::istream& inputStream, json& jsonValue);
void parseBooleanValue(std::istream& inputStream, json& jsonValue);
void parseNumberValue(std::istream& inputStream, json& jsonValue);
void parseStringValue(std::istream& inputStream, json& jsonValue);
void parseList(std::istream& inputStream, json& jsonValue);
void parseDictionary(std::istream& inputStream, json& jsonValue);

/////////////////////////////////////////////////////////////////IMPLEMENTAZIONE PARSING

void parseNullValue(std::istream& inputStream, json& jsonValue) {

    char expectedChars[] = "null";
    char character;

    for (int i = 0; i < 4; i++) {
        inputStream >> character;
        if (character != expectedChars[i]) {
            throw json_exception {"Errore nella lettura del valore null"};
        }
    }

    jsonValue.set_null();
}
   
void parseBooleanValue(std::istream& inputStream, json& jsonValue) {
    string expectedChars;
    bool expectedValue;

    
    char character;
    inputStream >> character;

    if (character == 't') {
        // Si prevede "true"
        expectedChars = "rue";
        expectedValue = true;
    } else if (character == 'f') {
        // Si prevede "false"
        expectedChars = "alse";
        expectedValue = false;
    } else {
        throw json_exception {"Errore nella lettura del valore booleano"};
    }

    // Verifica
    for (int i = 0; i < ( (expectedValue==true) ? 3 : 4 ); i++) {
        inputStream >> character;
        if (character != expectedChars[i]) {
            throw json_exception {"Errore nella lettura del valore booleano"};
        }
    }

    jsonValue.set_bool(expectedValue);
}

void parseNumberValue(std::istream& inputStream, json& jsonValue) {

    double token {};

    inputStream >> token;

    jsonValue.set_number(token);
}

void parseStringValue(std::istream& inputStream, json& jsonValue) {

    std::string token;
    char character;
    inputStream >> character;  // Leggi l'apice di apertura "c\"o"

    while (inputStream.get(character)) {
        if (character == '\\') {
            // Carattere di escape, leggi il carattere successivo
            token += character;
            if (inputStream.get(character)) {
                token += character;
            } else {
                throw json_exception{"Errore nella lettura della stringa: carattere di escape senza seguito"};
            }
        } else if (character == '"') {
            // Apice di chiusura, fine della stringa
            break;
        } else {

            token += character;
        }
    }

    jsonValue.set_string(token);
}

void parseList(std::istream& inputStream, json& jsonValue) {
    char character;

    while (true) {
        while (std::isspace(inputStream.peek())) {
            inputStream.get();
        }

        json temp;
        inputStream >> temp;

        jsonValue.push_back(temp);

        while (std::isspace(inputStream.peek())) {
            inputStream.get();
        }

        inputStream >> character;

        if (character == ',') {
            // Continua la lettura della lista
        } else if (character == ']') {
            break;  // Fine della lista
        } else {
            throw json_exception {"Errore nella lettura della lista"};
        }
    }


}

void parseDictionary(std::istream& inputStream, json& jsonValue) {
    char character;

    //prendo chiave
    auto take_key = [](std::istream& inputStream) {
        

        std::string key;
        char character;
        inputStream >> character;  // Leggi l'apice di apertura "c\"o"

        while (inputStream.get(character)) {
            if (character == '\\') {
                key += character;
                if (inputStream.get(character)) {
                    key += character;
                } else {
                    throw json_exception{"Errore nella lettura della stringa: carattere di escape senza seguito"};
                }
            } else if (character == '"') {
                // Apice di chiusura, fine della stringa
                break;
            } else {
                // Altro carattere, aggiungilo
                key += character;
            }
        }
        return key;
    };

    while (true) {

        while (inputStream.peek() == ' ' || inputStream.peek() == '\t' || inputStream.peek() == '\n' || inputStream.peek() == '\r') {
            inputStream.get();
        }

        std::pair<std::string, json> keyvalue {};

        keyvalue.first = take_key(inputStream);

        inputStream >> character;
        if (character != ':') {
            throw json_exception {"Errore nella lettura del dizionario"};
        }

        keyvalue.second = json();
        inputStream >> keyvalue.second;

        jsonValue.insert(keyvalue);

        inputStream >> character;
        if (character == ',') {

        } else if (character == '}') {
            break;
        } else {
            throw json_exception {"Errore nella lettura del dizionario"};
        }
    }
}


//__________________METODI OUTPUT________________//

void print_null(std::ostream& lhs);
void print_number(std::ostream& lhs, json const& rhs);
void print_bool(std::ostream& lhs, json const& rhs);
void print_string(std::ostream& lhs, json const& rhs);
void print_list(std::ostream& lhs, json const& rhs);
void print_dictionary(std::ostream& lhs, json const& rhs);

/////////////////////////////////////////////////////////////////IMPLEMENTAZIONE PRINT

void print_null(std::ostream& lhs)
{
    lhs << "null";
}
void print_number(std::ostream& lhs, json const& rhs)
{
    lhs << rhs.get_number();
}
void print_bool(std::ostream& lhs, json const& rhs)
{
    lhs << (rhs.get_bool() ? "true" : "false");
}
void print_string(std::ostream& lhs, json const& rhs)
{
    lhs << '"' << rhs.get_string() << '"';
}
void print_list(std::ostream& lhs, json const& rhs)
{
    lhs << "[";
        bool first = true;
        for (auto list_it = rhs.begin_list(); list_it != rhs.end_list(); ++list_it)
        {
            if (!first)
                lhs << ",";

            lhs << *list_it;
            first = false;
        }
        lhs << "]";
}
void print_dictionary(std::ostream& lhs, json const& rhs)
{
    lhs << "{";

    bool end = false;

    json::const_dictionary_iterator dic_temp = rhs.begin_dictionary();

    while(!end)
    {
        if(dic_temp != rhs.end_dictionary())
        {
            lhs << "\"" << (*dic_temp).first << "\"" << " : " << (*dic_temp).second;
            dic_temp++;
        }

        if(dic_temp == rhs.end_dictionary())
        {
            lhs << "}";
            end = true;
        }

        else
            lhs << ", ";
    } 
}

//__________________INPUT STREAM________________//

std::istream& operator>>(std::istream& lhs, json& rhs)
{
    lhs >> std::ws; 

    if (lhs.eof())
        return lhs;
    

    char character = lhs.peek(); 

    if (character == 'n') {
        parseNullValue(lhs, rhs);
    }
    else if (character == 'f' || character == 't') {
        parseBooleanValue(lhs, rhs);
    }
    else if (std::isdigit(character) || character == '-') {
        parseNumberValue(lhs, rhs);
    }
    else if (character == '"') {
        parseStringValue(lhs, rhs);
    }
    else if (character == '[') {
        lhs >> character;
        rhs.set_list();
        lhs >> character;
        if (character != ']') {
            lhs.putback(character);
            parseList(lhs, rhs); 
        }
    }
    else if (character == '{') {
        lhs >> character;
        rhs.set_dictionary();
        lhs >> character;
        if (character != '}') {
            lhs.putback(character);
            parseDictionary(lhs, rhs);
        }
    }
    else {
        throw json_exception {"errore nella lettura del file json"};
    }

    return lhs;
}

//__________________OUTPUT STREAM________________//

std::ostream& operator<<(std::ostream& lhs, json const& rhs)
{
    if (rhs.is_null()) {
        print_null(lhs);
    }
    else if (rhs.is_bool()) {
        print_bool(lhs, rhs);
    }
    else if (rhs.is_number()) {
        print_number(lhs, rhs);
    }
    else if (rhs.is_string()) {
        print_string(lhs, rhs);

    }
    else if (rhs.is_list()) {
        print_list(lhs, rhs);
    }
    else if (rhs.is_dictionary()) {
        print_dictionary(lhs, rhs);
    }
    else {
        throw json_exception {"errore riscontrato nella stampa json"};
    }

    return lhs;
}








///////////////////////////////////////////////////////////////////////////////////////
//__________________END OF FILE________________//
///////////////////////////////////////////////////////////////////////////////////////


