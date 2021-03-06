

/*
    Fichier process.h :  fonctions de gestion de
                        la ligne de commande.
    Groupe : n 16
    Auteur : TIABI EL.MEHDI
    DÃ©pendances :
 */



#include "processus.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include  <stdlib.h>
#include  <wait.h>
#include <string.h>
#include "builtin.h"

/*
  Fonction init_process : Crée l'enchaînement de processus à partir du
                          tableau tokens
      Paramètre proc : pointeur sur la structure à remplir
      Paramètre tokens :  tableau (NULL-terminated) contenant les chaînes
                          de la ligne de commande à analyser
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int init_process(processus_t* proc, char* tokens[]){

	int Max_arg=count_tokens(tokens);

	for(int i=0;i<Max_arg;i++){
		proc[i]._stdin=0;
		proc[i]._stdout=1;
		proc[i]._stderr=2;
		proc[i].bg=0;
		clear_tokens(proc[i].argv);
		proc[i].next=NULL;proc[i].next_success=NULL;proc[i].next_failure=NULL;
	}

	int index_tok=0;
	int index_argv=0;
	int index_proc=0;

	for(;tokens[index_tok]!=NULL;index_tok++){

		if(strcmp(tokens[index_tok],";")==0){
			proc[index_proc].next=&proc[index_proc+1];
			index_proc++;index_argv=0;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],"&&")==0){
			proc[index_proc].next_success=&proc[index_proc+1];
			index_proc++;index_argv=0;
			continue;return 1;
		}

			if(strcmp(tokens[index_tok],"||")==0){
			proc[index_proc].next_failure=&proc[index_proc+1];
			index_proc++;index_argv=0;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],"&")==0){
			proc[index_proc].bg=1;
			index_proc++;index_argv=0;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],"|")==0){
			int fd[2];
			pipe(fd);
			proc[index_proc].next=&proc[index_proc+1];//proc[index_proc].next->_stdin=proc[index_proc]._stdout;
			proc[index_proc]._stdout=fileno(fopen(".pipe", "wr"));
			proc[index_proc+1]._stdin=fileno(fopen(".pipe", "wr"));
			index_proc++;index_argv=0;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],">>")==0){
		  proc[index_proc]._stdout=open(tokens[index_tok+1], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR | O_APPEND | O_TRUNC);
			index_tok++;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],">")==0){
		  proc[index_proc]._stdout=open(tokens[index_tok+1], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR | O_TRUNC);
		  index_tok++;
		  continue;return 1;
		}

		if(strcmp(tokens[index_tok],"2>")==0){
		  proc[index_proc]._stderr=open(tokens[index_tok+1],O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR  | O_TRUNC);
			index_tok++;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],"2>>")==0){
		  	proc[index_proc]._stderr=open(tokens[index_tok+1], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR | O_APPEND | O_TRUNC);
			index_tok++;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],"<")==0){
			proc[index_proc]._stdin=open(tokens[index_tok+1], O_RDONLY);

			index_tok++;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],">&2")==0){
			proc[index_proc]._stdout=proc[index_proc]._stderr;
			index_tok++;
			continue;return 1;
		}

		if(strcmp(tokens[index_tok],"2>&1")==0){
		  proc[index_proc]._stdout=proc[index_proc]._stderr;

			index_tok++;
			continue;return 1;
		}

		proc[index_proc].argv[index_argv]=tokens[index_tok];
		++index_argv;


	}
	return 0;

};

/*
  Fonction exec_cmdline : Lance les processus de la ligne de commande dans
                          l'ordre attendu en respect des conditions demandées
      Paramètre proc : la structure décrivant les processus à lancer
      Retroune 0 en cas de succés et une autre valeur en cas d'échec
 */


int exec_cmdline(processus_t* proc){

	int done=0;
  int stat=0;
	while(proc!=NULL){

	if(done==0)
		stat = exec_processus(proc);

		if(proc->next_success==NULL && proc->next_failure==NULL && proc->next==NULL)return 0;


		if(proc->next_success!=NULL  && stat==0){
			proc=proc->next_success;
			done=0;}
    else
		if(proc->next_success!=NULL  && stat!=0){
			proc=proc->next_success;
		  done=1;}
		else
		if(proc->next_failure!=NULL && stat!=0 ){
			proc=proc->next_failure;
			done=0;
		}
		else
		if(proc->next_failure!=NULL && stat==0 ){
			proc=proc->next_failure;
			done=1;
		}
		else
		if(proc->next!=NULL){
			proc=proc->next;
			done=0;
		}


	}


};
