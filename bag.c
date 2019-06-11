/*
 * MAC0323 Algoritmos e Estruturas de Dados II
 * 
 * ADT Bag implementada com lista ligada de itens. 
 *  
 *    https://algs4.cs.princeton.edu/13stacks/
 *    https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/bag.html
 * 
 * ATENÇÃO: por simplicidade Bag contém apenas inteiros (int) não 
 * negativos (>=0) que são 'nomes' de vértices (vertex) de um 
 * digrafo.
 */

/* interface para o uso da funcao deste módulo */
#include "bag.h"  

#include <stdlib.h>  /* free() */
#include <string.h>  /* memcpy() */
#include "util.h"    /* emalloc() */

#undef DEBUG
#ifdef DEBUG
#include <stdio.h>   /* printf(): para debuging */
#endif

/*----------------------------------------------------------*/
/* 
 * Estrutura Básica da Bag
 * 
 * Implementação com listas ligada dos itens.
 */

typedef struct link{
    vertex item;
    struct link *next;
}node;

typedef node *Node;

struct bag {
    Node head;
    Node current;
    int size;
};

/*------------------------------------------------------------*/
/* 
 * Protótipos de funções administrativas: tem modificador 'static'
 * 
 */

/*-----------------------------------------------------------*/

/*  RECEBE um NODE e devolve ao sistema toda a memoria utilizada.*/
void freeNode(Node node);

/*-----------------------------------------------------------*/
/*
 *  newBag()
 *
 *  RETORNA (referência/ponteiro para) uma bag vazia.
 * 
 */
Bag newBag(){
    Bag bag = emalloc(sizeof(*bag));
    bag->head = NULL;
    bag->current = NULL;
    bag->size = 0;
    return bag;
}

/*-----------------------------------------------------------*/
/*
 *  freeBag(BAG)
 *
 *  RECEBE uma Bag BAG e devolve ao sistema toda a memoria 
 *  utilizada.
 *
 */
void freeBag(Bag bag){
    freeNode(bag->head);
    free(bag);
}

/*------------------------------------------------------------*/
/*
 * OPERAÇÕES USUAIS: add(), size(), isEmpty() e itens().
 */

/*-----------------------------------------------------------*/
/*
 *  add(BAG, ITEM, NITEM)
 * 
 *  RECEBE uma bag BAG e um ITEM e insere o ITEM na BAG.
 *  NITEM é o número de bytes de ITEM.
 *
 *  Para criar uma copia/clone de ITEM é usado o seu número de bytes NITEM.
 *
 */
void add(Bag bag, vertex item){
    Node oldfirst = bag->head;
    bag->head = emalloc(sizeof(node));
    bag->head->item = item;
    bag->head->next = oldfirst;
    bag->size++;
}

/*-----------------------------------------------------------*/
/* 
 *  SIZE(BAG)
 *
 *  RECEBE uma bag BAG
 * 
 *  RETORNA o número de itens em BAG.
 */
int size(Bag bag){
    return bag->size;
}

/*-----------------------------------------------------------*/
/* 
 *  ISEMPTY(BAG)
 *
 *  RECEBE uma bag BAG.
 * 
 *  RETORNA TRUE se BAG está vazia e FALSE em caso contrário.
 *
 */
Bool isEmpty(Bag bag){
    return bag->size == 0;
}

/*-----------------------------------------------------------*/
/* 
 *  ITENS(BAG, INIT)
 * 
 *  RECEBE uma bag BAG e um Bool INIT.
 *
 *  Se INIT é TRUE,  ITENS() RETORNA uma cópia/clone do primeiro item na lista de itens na BAG.
 *  Se INIT é FALSE, ITENS() RETORNA uma cópia/clone do item sucessor do último item retornado.
 *  Se BAG está vazia ou não há sucessor do último item retornado, ITENS() RETORNA -1.
 *
 *  Se entre duas chamadas de ITENS() a BAG é alterada, o comportamento é  indefinido. 
 *  
 */
vertex itens(Bag bag, Bool init){
    if (isEmpty(bag)) return -1;
    
    if (init){
        bag->current = bag->head;
    }
    else{
        if (bag->current == NULL || bag->current->next == NULL) return -1;
        bag->current = bag->current->next;
    }
    
    vertex item = bag->current->item;

    return item;
}

/*------------------------------------------------------------*/
/* 
 * Implementaçao de funções administrativas
 */
/*-----------------------------------------------------------*/
/*
 *  freeNode(NODE)
 * 
 *  RECEBE um NODE e devolve ao sistema toda a memoria utilizada.
 *
 */
void freeNode(Node node){
    if(node == NULL) return;
    freeNode(node->next);
    free(node);
}
