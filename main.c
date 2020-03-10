#include <stdio.h>
#include "dados.h"
#include "interface.h"
#include "logica.h"

ESTADO * inicializar_estado();

int main () {
        ESTADO *  estado;
        estado = inicializar_estado();
        mostrar_tabuleiro (estado);
        return 0;
}