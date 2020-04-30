#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "interface.h"
#include "logica.h"



int main () {
 
        ESTADO *  estado;
        estado = inicializar_estado();
        interpretador(estado);
        free(estado);   
        return 0;
}
