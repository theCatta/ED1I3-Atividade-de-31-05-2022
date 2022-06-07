#include <iostream>
using namespace std;

#define MAX 30

struct No
{
	float dado;
	No *prox;
};

struct PilhaGrupo{
	No *topo;
	int qtd;
};

PilhaGrupo* init(){
	PilhaGrupo *p = new PilhaGrupo;
	p->topo = NULL;
	p->qtd = 0;
	
	return p;
}

int push(PilhaGrupo *p, float v){
	int podeEmpilhar = (p->qtd < MAX);
	if(podeEmpilhar){
		No *no = new No;
		no->dado = v;
		no->prox = p->topo;
		p->topo = no;
		p->qtd++;
	}
	
	return podeEmpilhar;
}

int isEmpty(PilhaGrupo *pImpar, PilhaGrupo *pPar){
	int ret;
	
	if((pImpar->qtd == 0) && (pPar->qtd == 0)){
		ret = 1;
	} else ret = 0;
	
	
	return ret;
}

int count(PilhaGrupo *p){
	int k = 0;
	No *no = p->topo;
	while(no != NULL){
		k++;
		no = no->prox;
	}
	
	return k;
}

float pop(PilhaGrupo *pImpar, PilhaGrupo *pPar){
	float ret;
	
	
	while((count(pImpar) != 0) || (count(pPar) != 0))
	{
		if(pPar->topo > pImpar->topo){
			No *no = pPar->topo;
			ret = no->dado;
			pPar->topo = pPar->topo->prox;
			cout << "Numero apagado: " << ret << endl;
			pPar->qtd--;
			free(no);
		} else{
			No *no = pImpar->topo;
			ret = no->dado;
			pImpar->topo = pImpar->topo->prox;
			cout << "Numero apagado: " << ret << endl;
			pImpar->qtd--;
			free(no);
		}
	}
	
	
	return ret;
}


int main(int argc, char** argv)
{
	PilhaGrupo *pilhaPar;
	pilhaPar = init();
	PilhaGrupo *pilhaImpar;
	pilhaImpar = init();
	
	int i = 0;
	int numAnterior, num;
	
	cout << "Insira " << MAX << " números de forma crescente:" << endl;
	while(i < MAX){
	    cout << i+1 << "° número: ";
		cin >> num;
		
		if(i == 0){
			if(num % 2 == 0){
				push(pilhaPar, num);
			} else{
				push(pilhaImpar, num);
			}
			numAnterior = num;
			i++;
		} else if(num > numAnterior){
			if(num % 2 == 0){
				push(pilhaPar, num);
			} else{
				push(pilhaImpar, num);
			}
			numAnterior = num;
			i++;
		} else {
			cout << "!O número deve ser maior que o anterior!" << endl;
		}
	}

    int imparTotal = count(pilhaImpar);
    int parTotal = count(pilhaPar);
	int total = imparTotal + parTotal;
	
    cout << endl << "-------------Quantidade de números------------" << endl;
    cout << "Quantidade numero par: " << parTotal << endl;
    cout << "Quantidade numero impar: " << imparTotal << endl; 
	cout << "Total: " << total << endl;
	cout << "----------------------------------------------" << endl;
	
	cout << endl << "Pilha está vazia? " << (isEmpty(pilhaImpar, pilhaPar) ? "Sim" : "Nao" ) << endl;

	cout << endl << "Desempilhando..." << endl;
	pop(pilhaImpar, pilhaPar);
	
	cout << endl << "Pilha está vazia? " << (isEmpty(pilhaImpar, pilhaPar) ? "Sim" : "Nao" ) << endl;
	
	return 0;
}