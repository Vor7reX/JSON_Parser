#include <iostream>
#include <string>
#include <limits>
#include <assert.h>
#include <fstream>
#include <sstream>
struct json_exception {
    std::string msg;
};

class json {
public:
    struct list_iterator; // iteratore per accedere agli elementi di una lista di oggetti json.
    struct dictionary_iterator; //iteratore per accedere alle coppie chiave-valore di un dizionario di oggetti json.
    struct const_list_iterator; //iteratore costante per accedere agli elementi di una lista di oggetti json, che non consente di modificare gli elementi a cui punta.
    struct const_dictionary_iterator; //iteratore costante per accedere alle coppie chiave-valore di un dizionario di oggetti json, che non consente di modificare le coppie a cui punta.

    json(); //costruttore di default
    json(json const&); //Il costruttore copy crea una nuova istanza di json che è una copia dell'oggetto passato come argomento.
    json(json&&); //il costruttore di spostamento (move constructor). Esso viene chiamato quando si crea un nuovo oggetto json passando un altro oggetto json come rvalue reference (riferimento temporaneo). Il costruttore di spostamento "sposta" le risorse dall'oggetto temporaneo all'oggetto appena creato
    ~json(); //distruttore

    json& operator=(json const&);
    json& operator=(json&&);
// FUNZIONI CHE DEVONO RITORNARE UN TRUE O UN FALSE IN BASE A CONDIZIONE
    bool is_list() const; //
    bool is_dictionary() const;
    bool is_string() const;
    bool is_number() const;
    bool is_bool() const;
    bool is_null() const;

    json const& operator[](std::string const&) const;
    json& operator[](std::string const&);

    list_iterator begin_list();
    const_list_iterator begin_list() const; 
    list_iterator end_list();
    const_list_iterator end_list() const;

    dictionary_iterator begin_dictionary();
    const_dictionary_iterator begin_dictionary() const;
    dictionary_iterator end_dictionary();
    const_dictionary_iterator end_dictionary() const;

//FUNZIONI CHE RIOTRNANO UNA REFERENCE AL DETERMINATO VALORE 
    double& get_number();
    double const& get_number() const;

    bool& get_bool();
    bool const& get_bool() const;

    std::string& get_string();
    std::string const& get_string() const;

    void set_string(std::string const&);
    void set_bool(bool);
    void set_number(double);
    void set_null();
    void set_list();
    void set_dictionary();
    void push_front(json const&);
    void push_back(json const&);
    void insert(std::pair<std::string, json> const&);

private:
    struct impl;
    impl* pimpl;
};

std::ostream& operator<<(std::ostream& lhs, json const& rhs);
std::istream& operator>>(std::istream& lhs, json& rhs);
