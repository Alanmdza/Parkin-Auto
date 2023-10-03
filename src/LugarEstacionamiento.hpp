#include <iostream>
#include <string>

class LugarEstacionamiento
{
private:
    std::string lugar;
    int patente;
    bool ocupado;

public:
    // Constructor
    LugarEstacionamiento(std::string lugar = "UNDF", int patente = 999, bool ocupado = false)
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
    void setPatente(int patente)
    {
        this->patente = patente;
    }

    // Getter para Patente
    int getPatente() const
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