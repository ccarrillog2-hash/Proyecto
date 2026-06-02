#include "validaciones.h"
#include <cctype>

bool esNumeroPositivo(const std::string& s){
    if(s.empty()) return false;
    for(char c : s){
        if(!isdigit(c))
            return false;
    }
    return true;
}

bool esPrecioValido(const std::string& s){
    if(s.empty()) return false;
    int puntos = 0;
    for(char c : s){
        if(c == '.'){
            puntos++;
            if(puntos > 1) return false;
        }
        else if(!isdigit(c)){
            return false;
        }
    }
    return true;
}