#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct bst{
    struct noBst* raiz;
    int tam;
};

struct noBst{
    int val;
    struct noBst* dir;
    struct noBst* esq;
};

struct bst* alocarBst(){
    struct bst* bstaloc = (struct bst*)malloc(sizeof(struct bst));
    bstaloc->raiz = NULL;
    bstaloc->tam = 0;
    return bstaloc;
}

struct noBst* alocarNovoNo(int val){
    struct noBst* novoNo = (struct noBst*)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    return novoNo;
}

void inserirNoRec(struct noBst* raiz, struct noBst* novoNo){
    if(novoNo->val <= raiz->val){
       if(raiz->esq == NULL){
          raiz->esq = novoNo;
       }
       else{
          inserirNoRec(raiz->esq, novoNo);
       }
    }
    else if(novoNo->val > raiz->val){
       if(raiz->dir == NULL){
          raiz->dir = novoNo;
       }
       else{
          inserirNoRec(raiz->dir, novoNo);
       }
    }
}

void inserirNoIt(struct noBst* raiz, struct noBst* novoNo){
    struct noBst* aux = raiz;
    while(raiz != NULL){
       if(novoNo->val <= raiz->val){
          aux = raiz;
          raiz = raiz->esq;
       }
       else if(novoNo->val > raiz->val){
          aux = raiz;
          raiz = raiz->dir;
       }
    }
    if(novoNo->val <= aux->val){
       aux->esq = novoNo;
    }
    else{
       aux->dir = novoNo;
    }
}

void inserir(struct bst* bst, int val, bool rec){
    struct noBst* novoNo = alocarNovoNo(val);
    if(bst->raiz == NULL){
       bst->raiz = novoNo;
    }
    else if(rec){
       inserirNoRec(bst->raiz, novoNo);
    }
    else{
       inserirNoIt(bst->raiz, novoNo);
    }
    bst->tam++;
}

bool buscarRec(struct noBst* raiz, int val){
    if(raiz != NULL){
       if(raiz->val == val){
          return true;
       }
       else{
          if(val < raiz->val){
             buscarRec(raiz->esq, val);
          }
          else{
             buscarRec(raiz->dir, val);
          }
       }
    }
    else{
	    return false;
    }
}

bool buscarIt(struct noBst* raiz, int val){
    while(raiz != NULL){
       if(val < raiz->val){
          raiz = raiz->esq;
       }
       else if(val > raiz->val){
          raiz = raiz->dir;
       }
       else{
          return true;
       }
    }
    return false;
}

bool buscar(struct bst* bst, int val, bool rec){
    if(bst->raiz == NULL){
       return false;
    }
    else if(rec){
       return buscarRec(bst->raiz, val);
    }
    else{
       return buscarIt(bst->raiz, val);
    }
}

void navEmOrdem(struct noBst* raiz){
    if(raiz != NULL){
       navEmOrdem(raiz->esq);
       printf("%d ", raiz->val);
       navEmOrdem(raiz->dir);
    }
}

void navPreOrdem(struct noBst* raiz){
    if(raiz != NULL){
       printf("%d ", raiz->val);
       navPreOrdem(raiz->esq);
       navPreOrdem(raiz->dir);
    }
}

void navPosOrdem(struct noBst* raiz){
    if(raiz != NULL){
       navPosOrdem(raiz->esq);
       navPosOrdem(raiz->dir);
       printf("% d", raiz->val);
    }
}

int min(struct noBst* raiz){
    if(raiz == NULL){
       return NULL;
    }
    if(raiz->esq != NULL){
       return min(raiz->esq);
    }
    else{
       return raiz->val;
    }
}

int max(struct noBst* raiz){
    if(raiz == NULL){
       return NULL;
    }
    if(raiz->dir != NULL){
       return max(raiz->dir);
    }
    else{
       return raiz->val;
    }
}

int altura(struct noBst* raiz) {
    int altesq;
    int altdir; 

    if(raiz == NULL){
       return 0;
    }
    else{
       int nesq = raiz->esq == NULL ? 1 : 0;
       int ndir = raiz->dir == NULL ? 1 : 0;
       altesq = altura(raiz->esq) - nesq;
       altdir = altura(raiz->dir) - ndir;

       if(altesq < altdir){
          return altdir+1;
       }
       else{
          return altesq+1;
       }
    }
}

struct noBst* removerRec(struct noBst* raiz , int val) {
    if(raiz == NULL){
       return NULL;
    }
    else{ 
       if(raiz->val == val){ 
          if(raiz->esq == NULL && raiz->dir == NULL){ 
             free(raiz);
             return NULL;
          }
          else{
             if(raiz->esq != NULL && raiz->dir != NULL){
                struct noBst* aux = raiz->esq;
                while(aux->dir != NULL){
                   aux = aux-> dir;
                }
                raiz->val = aux->val;
                aux->val = val;
                raiz->esq = removerRec(raiz->esq,val);
                return raiz;
             }
             else{
                struct noBst* aux;
                if(raiz->esq != NULL){
                   aux = raiz->esq;
                }
                else{
                   aux = raiz->dir;
                }
                   free(raiz);
                   return aux;
             }
          }
       }
       else{
          if(val < raiz->val){
             raiz->esq = removerRec(raiz->esq , val);
          }
          else{
             raiz->dir = removerRec(raiz->dir , val);
          }
          return raiz;
       }
    }
}

void remover(struct bst* bst, int val) {
    if(bst->raiz != NULL){
       struct noBst* no = removerRec(bst->raiz, val);
       bst->tam--;
    }
}
