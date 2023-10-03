#include <iostream>
#include <string>

class LugarEstacionamiento
{
private:
    std::string lugar;
    std::string patente;
    bool ocupado;

public:
    // Constructor
    LugarEstacionamiento(std::string lugar = "UNDF", std::string patente = "UNDF", bool ocupado = false)
    {
        this->patente = patente;
        this->patente = patente;
        this->ocupado = ocupado;
    }

    // Setter para Lugar
    void setLugar(const std::string &lugar)
    {
        this->lugar = lugar;
    }

    // Getter para lugar
    std::string getlugar() const
    {
        return lugar;
    }

    // Setter para Patente
    void setPatente(std::string patente)
    {
        this->patente = patente;
    }

    // Getter para Patente
    std::string getPatente() const
    {
        return patente;
    }

    // Setter para Ocupado
    void setOcupado(bool ocupado)
    {
        this->ocupado = ocupado;
    }

    // Getter para Ocupado
    bool estaOcupado() const
    {
        return ocupado;
    }
};
;