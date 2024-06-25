/* Filipe Resendes 96859 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 65535

typedef struct node {
	char *caminho;
	char *valor;
	struct node *next;
} * link;                     /* Tabela de caminhos  */ 

void *malloc(size_t size);

/*
Liberta a memoria de uma dada string
*/
void free_char(char *any){
	any = NULL;
	free(any);
}


/*
Imprime todos os caminhos e valores
*/
void print(link head){
	int i;
	link t, x;
	char *tabela[];
	for (t = head, i = 0; t != NULL; t=t->next, i++);
		tabela[i] = t->caminho;
	while (i < 0){
		printf("%s\n", tabela[i]);
		i--;
	}
}


/*
Proucura o node de um dado valor
*/
link lookup_val(link head, char *in_valor){
	link t;
	for (t = head; t != NULL; t = t->next)
		if (t->valor != NULL)
			if (strcmp(t->valor, in_valor) == 0)
				return t;
	return NULL;
}


/*
Procura o node de um dado caminho
*/
link lookup(link head, char *in_caminho){
	link t;
	for (t = head; t != NULL; t = t->next)
		if (strcmp(t->caminho, in_caminho) == 0)
			return t;
	return NULL;
}


/*
Reserva memoria e coloca um caminho
*/
link NEW(char *sub){
	link new = (link) malloc(sizeof(link));
	new->caminho = (char*)malloc(sizeof(char)*(strlen(sub)+1));
	strcpy(new->caminho, sub);
	new->next = NULL;
	return new;
}


/*
Insere um novo caminho
*/
link insert(char *sub, link head){
	link x;
	if(head == NULL)
		return NEW(sub);
	for (x = head; x->next != NULL; x = x->next);
	x->next = NEW(sub);
	return head;
}


/*
Liberta memoria e apaga todos os caminhos
*/
link delete_all(link head){
	link t;
	for (t = head; t != NULL; t = t->next){
		free_char(t->caminho);
		free_char(t->valor);
		head = t->next;
		free(t);
	}
	return head;
}


/*
Apaga todos os caminhos de um sub-caminho
*/
link delete_path(char *in_caminho, link head){
	link t, prev;
	for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){
		if (strncmp(t->caminho, in_caminho, strlen(in_caminho) -1) == 0) {
			if (t == head)
				head = t->next;
			else
				prev->next = t->next;
		if (t->valor != NULL)
			free(t->valor);
		free(t->caminho);
		free(t);
		}
	}
	return head;
}


/*
Apaga todos os caminhos de um sub-caminho ou todos os armazenados
*/
link delete(char *comando, link head){
	int i, f = 0;
	char *in_caminho;
	link x;
	in_caminho = (char*)malloc(sizeof(char)*(strlen(comando)+1));
	if (strcmp(comando, "delete") == 0)
		 head = delete_all(head);
	else{
		for (i = 7, in_caminho[f++] = '/'; comando[i] != '\0'; i++)
			in_caminho[f++] = comando[i];
		if ((x = lookup(head, in_caminho)) == NULL)
			printf("not found\n");
		head = delete_path(in_caminho, head);
	}
	free_char(in_caminho);
	return head;
}


/*
Verifica se eh um componente
*/
int eh_comp(char *cam){
	int i;
	for(i = 1; cam[i] != '\0'; i++)
		if (cam[i] == '/')
			return 0;
	return 1;
}


/*
Lista todos os caminhos
*/
void list_all(link head){
	link t;
	for (t = head; t != NULL; t = t->next)
		if (t->caminho != NULL && eh_comp(t->caminho))
			printf("%s\n", t->caminho+1);
}


/*
Verifica se o caminho existe
*/
void check_comp(char *comando, link head){
	int i, f = 0;
	char *in_caminho;
	link x;
	in_caminho = (char*)malloc(sizeof(char)*(strlen(comando)+1));
	if (comando[0] != '/')
		in_caminho[f++] = '/';
	for (i = 5; comando[i] != '\0'; i++)
		in_caminho[f++] = comando[i];
	if ((x = lookup(head, in_caminho)) == NULL)
		printf("not found\n");
	free_char(in_caminho);
}


/*
Lista todos os componentes imediatos de um sub-caminho
*/
void list(char *comando, link head){
	if (strcmp(comando, "list") == 0)
		list_all(head);
	else {
		check_comp(comando, head);
	}
}


/*
Proucura o caminho de um valor
*/
void search(char *comando, link head){
	int i, f = 0;
	char *in_valor;
	link x;
	in_valor = (char*)malloc(sizeof(char)*(strlen(comando)+1));
	for (i = 7; comando[i] != '\0'; i++)
		in_valor[f++] = comando[i];
	if ((x = lookup_val(head, in_valor)) == NULL)
		printf("not found\n");
	else
		printf("%s\n", x->caminho);
	free_char(in_valor);
}


/*
Imprime o valor armazenado de um caminho
*/
void find(char *comando, link head){
	int i, f = 0;
	char *in_caminho;
	link x;
	in_caminho = (char*)malloc(sizeof(char)*(strlen(comando)+1));
	for (i = 5, in_caminho[f++] = '/'; comando[i] != '\0'; i++)
		in_caminho[f++] = comando[i];
	x = lookup(head, in_caminho);
	if (x == NULL)
		printf("not found\n");
	else {
		if (x->valor == NULL)
			printf("no data\n");
		else
			printf("%s\n", x->valor);
	}
	free_char(in_caminho);
}


/*
Obtem o valor dado
*/
void get_path_val(char *comando, char *in_caminho, char *in_valor){
	int i, f = 0, c = 0;
	for (i = 4; comando[i] != ' '; i++)
		in_caminho[f++] = comando[i];
	in_caminho[f] = '\0';
	while (comando[++i] != '\0')
		in_valor[c++] = comando[i];
}


/*
Adiciona o valor ao sistema
*/
void add_val(link x, char *in_valor){
	x->valor = (char*)malloc(sizeof(char)*(strlen(in_valor)+1));
	strcpy(x->valor, in_valor);
}


/*
Adiciona os caminhos e valor
*/
link add_link(char *in_caminho, char *in_valor, link head, link x){
	int i = 0, v = 0;
	char *sub;
	sub = (char*)malloc(sizeof(char)*(strlen(in_caminho)+1));
	if (in_caminho[0] != '/')
		sub[v++] = '/';
	for (i = 0; in_caminho[i] != '\0'; i++){
		if (in_caminho[i] == '/')
			if (lookup(head, sub) == NULL)
				head = insert(sub, head);
		sub[v++] = in_caminho[i];
	}
	head = insert(sub, head);
	x = lookup(head, sub);
	if (in_valor != NULL){
		x->valor = (char*)malloc(sizeof(char)*(strlen(in_valor)+1));
		strcpy(x->valor, in_valor);
	}
	else
		free_char(in_valor);
	free_char(sub);
	return head;
}


/*
Adiciona ou modifica o valor a armazenar
*/
link set(char *comando, link head){
	char *in_caminho, *in_valor;
	link x;
	in_caminho = (char*)malloc(sizeof(char)*(strlen(comando)+1));
	in_valor = (char*)malloc(sizeof(char)*(strlen(comando)+1));
	get_path_val(comando, in_caminho, in_valor);
	if ((x = lookup(head, in_caminho)) != NULL && in_valor != NULL)
		add_val(x, in_valor);
	else
		head = add_link(in_caminho, in_valor, head, x);
	free_char(in_caminho);
	free_char(in_valor);
	return head;
}


/*
Imprime os comandos disponiveis
*/
void help(){
	printf("help: Imprime os comandos disponíveis.\n");
	printf("quit: Termina o programa.\n");
	printf("set: Adiciona ou modifica o valor a armazenar.\n");
	printf("print: Imprime todos os caminhos e valores.\n");
	printf("find: Imprime o valor armazenado.\n");
	printf("list: Lista todos os componentes imediatos de um sub-caminho.\n");
	printf("search: Procura o caminho dado um valor.\n");
	printf("delete: Apaga um caminho e todos os subcaminhos.\n");
}


int main(){
	int i, c, run = 1;
	char *comando;
	link head = NULL;
	comando = (char*)malloc(MAX*sizeof(char));
	while (run){
		for (i = 0; (c = getchar()) != '\n';)
			comando[i++] = c;
		comando[i] = '\0';
		if (i >= MAX){
			printf("No memory\n");
			break;
		}
		if (strcmp(comando, "help") == 0)
			help();
		if (strcmp(comando, "quit") == 0)
			run = 0;
		if (strncmp(comando, "set", 3) == 0)
			head = set(comando, head);
		if (strncmp(comando, "print", 5) == 0)
			print(head);
		if (strncmp(comando, "find", 4) == 0)
			find(comando, head);
		if (strncmp(comando, "search", 6) == 0)
			search(comando, head);
		if (strncmp(comando, "list", 4) == 0)
			list(comando, head);
		if (strncmp(comando, "delete", 6) == 0)
			head = delete(comando, head);
		while (i > 0)
			comando[i--] = '\0';
	}
	free_char(comando);
	return 0;
}