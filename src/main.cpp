#include <iostream>
#include <time.h>
#include "listEnc.h"
#include "listDEnc.h"
#include "listCirc.h"
#include "tadEsp.h"
#include "delivery.h"

void fechaCaixa(TListaDE<Pedido> pedidosConcluidos){
    TElementoDE<Pedido>* nav = pedidosConcluidos.primeiro;
    TElementoDE<Pedido>* nav2 = pedidosConcluidos.primeiro;
    double primeiraContagem, segundaContagem;
    for(primeiraContagem = 0; nav != NULL; nav = nav->proximo){
        primeiraContagem += nav->conteudo.preco;
        nav2 = nav->anterior;
    }
    //nav2 = nav2->proximo;
    for(segundaContagem = 0; nav2 != NULL; nav2 = nav2->anterior){
        segundaContagem += nav2->conteudo.preco;
    }
    if(abs(primeiraContagem == segundaContagem) < 0.001){
        std::cout << "O caixa foi fechado corretamente,\n";
        std::cout << "Foi arrecadado o valor de " << primeiraContagem << " reais. \n";
        std::cout << "Foram realizados " << tamanho(pedidosConcluidos) << " pedidos.\n";
    } else {
        std::cerr <<" Foi encontrada uma divegência de " << abs(primeiraContagem - segundaContagem) << " reais no fechamento de caixa!";
    }
}

int main(){
    srand(time(NULL));
    //Declaração de variáveis, cardapio, lista de pedidos, entregadores, preços, etc...
    TListaEnc<Item> cardapio;
    inicializaLista(cardapio);
    preencheCardapio(cardapio);

    TListaDE<Pedido> pedidosPendentes; //"Para estimar o tempo de entrega [...] deve ser percorrida do final até o início"
    inicializaLista(pedidosPendentes);

    TListaDE<Pedido> pedidosConcluidos;
    inicializaLista(pedidosConcluidos);

    TListaC<Entregador> listaEntregadores;
    inicializaLista(listaEntregadores);
    preencheListaEntregadores(listaEntregadores, 5);
    imprimeLista(listaEntregadores);
    
    int numeroDeCozinheiros = 3;
    TElementoC<Entregador>* entregadorAtual = listaEntregadores.primeiro;

    for(int tempoAtual = 1; tempoAtual <= 300 || tamanho(pedidosPendentes) > 0; tempoAtual++){ //O período de atendimento do restaurante é 5 horas. 
        std::cout << "Minuto Atual: " << tempoAtual << ".\n";
        if(tempoAtual % 2 == 0 && tempoAtual <= 300){ //A cada 2 minutos, uma nova compra é efetuada.
            criaPedido(cardapio, pedidosPendentes);
        }
        entregaPedido(pedidosPendentes, pedidosConcluidos, listaEntregadores, entregadorAtual);
        contrataOuDemiteEntregador(listaEntregadores, entregadorAtual);
        decrementaTempoPedidos(pedidosPendentes, numeroDeCozinheiros);
        decrementaTempoEntregadores(listaEntregadores);
        std::cout << "\n--------------------------------------------------------------\n";
    }
    //imprimeLista(listaEntregadores);
    imprimeLista(pedidosPendentes);
    imprimeLista(pedidosConcluidos);
    fechaCaixa(pedidosConcluidos);
    
}

//Calculo de caixa, dupla verifiação, etc...