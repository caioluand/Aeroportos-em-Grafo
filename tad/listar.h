#ifndef LISTAR_H
#define LISTAR_H
#include "meustipos.h"
#include "indice_aeroporto.h"
#include "matriz_voo.h"


boolean hard_code(Raiz *matriz, IndiceAeroporto *vetor);

boolean cadastrar_novo_aeroporto(IndiceAeroporto *vetor, I8 nome[50], I8 sigla[4]);
boolean cadastrar_novo_voo(Raiz *matriz, I16 voo, I16 indice_origem, I16 indice_destino);
boolean remover_aeroporto(Raiz *matriz, IndiceAeroporto *vetor, I8 sigla[4]);
boolean remover_voo(Raiz *matriz, I16 voo);
boolean listar_voos(Raiz *matriz, IndiceAeroporto *vetor);
boolean listar_trajetos(Raiz *matriz, IndiceAeroporto *vetor, I8 sigla_origem[4], I8 sigla_destino[4]);

boolean free_tudo(Raiz *matriz, IndiceAeroporto *vetor);


#endif // LISTAR_H