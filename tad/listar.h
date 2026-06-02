#ifndef LISTAR_H
#define LISTAR_H
#include "meustipos.h"
#include "indice_aeroporto.h"
#include "matriz_voo.h"

boolean cadastrar_novo_aeroporto(I8 nome, I8 sigla);
boolean cadastrar_novo_voo(I16 voo);
boolean remover_aeroporto(I8 sigla);
boolean remover_voo(I16 voo);
boolean listar_aeroportos();
boolean listar_voos();
boolean listar_trajetos(I8 sigla, I8 sigla2);

//Raiz *matriz, IndiceAeroporto *vetor

#endif // LISTAR_H