#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

typedef struct no bigInt;
typedef no* pBigInt;
    
struct no{
    int valor;
    pBigInt proximo;
    pBigInt anterior;
};
    
int tamanho(char* x){
    int i = 0;
    while(*x){
        i++;
        x++;
    }
    return i;
}

void percorre(pBigInt L){    
    while(L){
        printf(" %d ", L->valor);
         if(L->anterior){
             L=L->anterior;
         }
         else 
             break;
    }
    printf("\n");
     while(L){
        printf(" %d ", L->valor);
        if(L->proximo)
          L=L->proximo;
        else
            break;
    }
    printf("\n");
}


    
pBigInt converte(char* numero) {
    pBigInt L = NULL;
    pBigInt aux = NULL;
    char pnum = numero[0];
    char str[1];
    int TAM = tamanho(numero);
    if(pnum == '-'){
        for(*numero++; *numero; *numero++){
            pBigInt L = (pBigInt) malloc(sizeof(no));
            L->anterior = aux;
            if(aux)
                aux->proximo = L;
            str[0] = *numero;
            if(atoi(str) > 9)//gambiarra
                L->valor = (atoi(str)/10)*-1;
            else
                L->valor = atoi(str)*-1;
            aux = L;
         }
    }
    else{
        for(;*numero; *numero++){
            pBigInt L = (pBigInt) malloc(sizeof(no));
            L->anterior = aux;
            if(aux)
                aux->proximo = L;
            str[0] = *numero;
            if(atoi(str) > 9)//gambiarra
                L->valor = atoi(str)/10;
            else
                L->valor = atoi(str);
            aux = L;              
        };
    }
     aux->proximo = NULL;     
    return aux;
} 

pBigInt maiorAbs(pBigInt x, pBigInt y){
   
    pBigInt comx = x;
    pBigInt comy = y;
    while(x->anterior){
       x = x->anterior;
       y = y->anterior;
    }
 
    while(abs(x->valor) == abs(y->valor)){
        //printf("oi");
       if(x->proximo){
          x = x->proximo;
          y = y->proximo;
        }else{
            return comx;
        }
    }
    
    if(abs(x->valor) > abs(y->valor))
        return comx;
        else
            return comy;
}

pBigInt menorAbs(pBigInt x, pBigInt y){
    pBigInt comx = x;
    pBigInt comy = y;
    while(x->anterior){
       x = x->anterior;
       y = y->anterior;
    }
    while(abs(x->valor) == abs(y->valor)){
        if(x->proximo){
          x = x->proximo;
          y = y->proximo;
        }else{
            return comy;
        }
    }
    
    if(abs(x->valor) > abs(y->valor))
        return comy;
        else
            return comx;
}

void printBigInt(pBigInt L){
    while(L){
         if(L->anterior){
             L=L->anterior;
         }
         else 
             break;
    }
    while(L->valor == 0 && L->proximo){
        L= L->proximo;
    }
    printf("%d", L->valor);
    L=L->proximo;
    while(L){
        if(L->valor < 0)
            printf("%d", L->valor*-1);
        else
            printf("%d", L->valor);
        if(L->proximo)
          L=L->proximo;
        else
            break;
    }
}


pBigInt somaBigInt(pBigInt x, pBigInt y){
    pBigInt s = NULL;
    pBigInt z = x;
    pBigInt w = y;
    pBigInt aux = NULL;
    int umneg = 0;
    int doisneg = 0;
    int tamx = 0, tamy = 0;
    int vai = 0;


    while(x->anterior){
        tamx++;
        x = x->anterior;
    }
    
    while(y->anterior){
        tamy++;
        y = y->anterior;
    }
    
       
    if(x->valor < 0 || y->valor < 0)
        umneg = 1;
    if(x->valor <= 0 && y->valor <= 0){
        umneg = 0;
        doisneg = 1;
    }
        
        
    if(tamx > tamy)
        for(int i = tamy; i < tamx; i++){
            s = converte("0");
            y->anterior = s;
            s->proximo = y;
            y = y->anterior;
        }
    
    else if (tamx < tamy)
        for(int i = tamx; i < tamy; i++){
            s = converte("0");
            x->anterior = s;
            s->proximo = x;
            x = x->anterior;
        }
    
    x = z;
    y = w;
    s = NULL;
    z = maiorAbs(x,y);
    w = menorAbs(x,y);        
    int a = 0;
    int b = 0;
    
    if(!umneg || doisneg){
        while(z || vai != 0){
            if(z){
                a = z->valor;
                b = w->valor;
            }
            else{
                a = 0;
                b = 0;
            }
            s = (pBigInt) malloc(sizeof(no));
            if (aux)
               aux->anterior = s;
            s->proximo = aux;
            aux = s;
            s->valor = a + b + vai;
            vai = 0;
            if(s->valor > 9){
                s->valor = s->valor - 10;
                vai = 1;
            }
            if(s->valor < -9){
                 s->valor = s->valor + 10;
                 vai = -1;
            }
        
            if (z)
                z = z->anterior;
            if (w)
                w = w->anterior;            
        }
    } else {
           int zsinal = 0;
           pBigInt p = z;
           while(!p->valor)
              p = p->anterior;
           zsinal = p->valor;
           while(z || vai != 0){
               if(z){
                    a = z->valor;
                    b = w->valor;
               }
                else{
                    a = 0;
                    b = 0;
                }
              s = (pBigInt) malloc(sizeof(no));
              if (aux)
                 aux->anterior = s;
              s->proximo = aux; 
              aux = s;
              s->valor = a + b + vai;
              if(a == 0 && vai != 0){
                  a = -10;
                  if (zsinal >= 0)
                      a = 10;
              }
              if((abs(b)) > abs(a)){
                  if(zsinal < 0){
                      s->valor = (a-10) + b + vai;
                      vai = 1;
                  }
                  else{
                      s->valor = (a+10) + b + vai;
                      vai = -1;
                  }
                  //+a
              } else{
                  s->valor = a + b + vai;
                  vai = 0;
                  if(a == 10)
                      vai = -1;
                  if(a == -10)
                      vai = 1;
              }
              if(z)
                  z = z->anterior;
              if(w)
                  w = w->anterior;
           }      
        } 
   
    s->anterior = NULL; 
    while(s->valor == 0){
        if(s->proximo){
           s = s->proximo;
           s->anterior = NULL;
        } else
            break;
    }
    while(s->proximo){
        s = s->proximo;
    }
    return s;
}



pBigInt subtBigInt(pBigInt x, pBigInt y){   
    pBigInt s = x;
    pBigInt r = y;     
    while(r){ 
        r->valor = (r->valor)*-1;
        r = r->anterior;
    }
    return somaBigInt(x,y);
    
}


pBigInt adcionaZero(pBigInt L, int count){
    pBigInt aux = L;
    for(; count>0; count--){
        L->proximo = converte("0");
        L = L->proximo;
        L->anterior = aux;
        aux = L;
    }
    L->proximo = NULL;
    return L;
}

pBigInt multBigInt(pBigInt x,pBigInt y){
    int count = 0;
    pBigInt z = converte("0"); 
    pBigInt s = converte("0");
    pBigInt w = y;
    pBigInt p = x;
    while(x->anterior && x->valor == 0)
        x = x->anterior;
    while(x->anterior && y->valor == 0)
        y = y->anterior;

    while(p){
        for(int i = abs(p->valor); i > 0; i--)
            z = somaBigInt(z, w);
        z = adcionaZero(z, count);
        if(p)
          p = p->anterior;
        count++;
        s = somaBigInt(z,s);
        z = converte("0");
    }
    z = s;
    if(x->valor < 0 || (x->valor < 0 && y->valor < 0)){
        while(s){
            s->valor = s->valor*-1;
            if(s)
                s = s->anterior;
            else
                break;
        }
        
    }
    return z;
}

pBigInt expo(pBigInt x, int y) {
    pBigInt a = converte("1");
    while (y > 0) {
        a = multBigInt(x, a);
        y--;
    }
    return a;
}

int compara(pBigInt x, pBigInt y){
    pBigInt z = x;
    pBigInt w = y;
    pBigInt s = NULL;
    int tamx = 0, tamy = 0;
    
    while(x->anterior){
        tamx++;
        x = x->anterior;
    }
    
    while(y->anterior){
        tamy++;
        y = y->anterior;
    }
        
    if(tamx > tamy)
        for(int i = tamy; i < tamx; i++){
            s = converte("0");
            y->anterior = s;
            s->proximo = y;
            y = y->anterior;
        }
    
    else if (tamx < tamy)
        for(int i = tamx; i < tamy; i++){
            s = converte("0");
            x->anterior = s;
            s->proximo = x;
            x = x->anterior;
        }
    
    x = z;
    y = w;
    s = converte("0");
    z = maiorAbs(x,y);
    w = menorAbs(x,y);     
  
    int ret;
    if(z != x)
        ret = -1;
    if(maiorAbs(x,y) == menorAbs(y,x))
        ret =  0;
    if(z == x)
        ret = 1;
    return ret;
 
    
}


pBigInt div(pBigInt x, pBigInt y){
    pBigInt z = x;
    pBigInt w = y;
    pBigInt s = NULL;
    int tamx = 0, tamy = 0;
    int temndiferentedezero = 0;
    
    while(x->anterior){
        tamx++;
        x = x->anterior;
    }
    
    while(y->anterior){
        if(y->valor > 0 || y->valor < 0)
           temndiferentedezero = 1;
        tamy++;
        y = y->anterior; 
    }
    if(y->valor == 0 && !temndiferentedezero){
        printf("\nDivisao por zero nao existe!\n");
        return NULL;
    }   
        
    if(tamx > tamy)
        for(int i = tamy; i < tamx; i++){
            s = converte("0");
            y->anterior = s;
            s->proximo = y;
            y = y->anterior;
        }
    
    else if (tamx < tamy)
        for(int i = tamx; i < tamy; i++){
            s = converte("0");
            x->anterior = s;
            s->proximo = x;
            x = x->anterior;
        }
    
    x = z;
    y = w;
    s = converte("0"); 
    int TAM = max(tamx, tamy) - 1;
    pBigInt cont;

    s = somaBigInt(s,converte("1"));
    if(tamy == 0 && y->valor == 1)
        return z;
    if(tamy == 0 && y->valor == -1)
        return subtBigInt(0,z);
    if(TAM == -1){
        cont = converte("1");
        while(compara(z, multBigInt(s, w)) > 0)
             s = somaBigInt(s,cont);
    }else
        while(TAM > -1){
            cont = converte("1");
            cont = adcionaZero(cont, TAM);
            while(compara(z, multBigInt(s, w)) > 0)
                 s = somaBigInt(s,cont);
            while(compara(z, multBigInt(s, w)) == -1)
                 s = subtBigInt(s, cont);
            TAM--;
        }
    
    z = s;
    
    while(x->valor == 0)
        if(x->anterior)
            x = x->anterior;
     while(y->valor == 0)
        if(y->anterior)
            y = x->anterior;
    
    if((x->valor < 0 || y->valor < 0) && !(x->valor < 0 && y->valor < 0)){
        while(s){
            s->valor = s->valor*-1;
            if(s)
                s = s->anterior;
            else
                break;
        }
        
    }
    return z;

    
}


int main(int argc, char** argv) {
    int escolha = 0;
    int on = 1;
    char pnum[200], snum[200];
    char operacao [15];
    pBigInt a = NULL;
    pBigInt b = NULL;
    int exp = 0;
    pBigInt c = NULL;
    while(on){
        
        printf("\tCalculo de BigInts!\n");
        printf("Escolha um modulo de operacao:\n");
        printf("1.Soma 2.Subtracao 3.Multiplicacao 4.Divisao 5.Exponenciacao\n");
        cin >> escolha;
        printf("\nDigite o primeiro numero:\n");
        cin >> pnum;
        printf("\nDigite o segundo numero:\n");
        a = converte(pnum);
        if(escolha != 5){
            cin >> snum;
            b = converte(snum);
        } else{
          cin >> exp;
        }
        printf("%d", exp);
        switch (escolha){                       
                case 1:
                    c = somaBigInt(a,b);
                    strcpy(operacao, "soma");
                    break;
                case 2:
                    c = subtBigInt(a,b);
                    strcpy(operacao, "subtracao");
                    break;
                case 3:
                    c = multBigInt(a,b);
                    strcpy(operacao, "multiplicacao");
                    break;
                case 4:
                    c = div(a,b);
                    strcpy(operacao, "divisao");
                    break;
                case 5:
                    c = expo(a,exp);
                    strcpy(operacao, "exponenciacao");
                    break;
                default:
                    return 0;
       }
    if(c){
        printf("\n O resultado da %s entre ", operacao);
        printBigInt(a);
        printf(" e ");
        if(b)
          printBigInt(b);
        else
            printf("%d", exp);
        printf(" eh: ");
        printBigInt(c);
        printf(" !\n\n");
        }
    }
    return 0;
}