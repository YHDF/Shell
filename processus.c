
/*
    Fichier processus.c :  fonctions de gestion des
                        processus indÃ©pendants.
    Groupe : n 16
    Auteur : TIABI EL.MEHDI
    DÃ©pendances :
 */
#include<unistd.h>
#include<stdio.h>
#include"utils.h"
#include <fcntl.h>
#include <sys/types.h>
#include  <stdlib.h>
#include  <wait.h>
#include <errno.h>
#include "builtin.h"
#include <string.h>
#include "processus.h"

//afficher structure d'un proc
void afficher_proc(processus_t* proc){
	printf("PID:%d\n",proc->pid);
	printf("Status:%d\n",proc->status);
	printf("Stdin:%d\n",proc->_stdin);
	printf("Stdout:%d\n",proc->_stdout);
	printf("Stderr:%d\n",proc->_stderr);
	printf("Background:%d\n",proc->bg);
	printf("Arguments:\n");
for(int i=0;i<count_tokens(proc->argv);i++)
puts(proc->argv[i]);
}


/*
  Fonction exec_processus : Permet le lancement d'un processu avec les
  propriétés choisies (redirections, lancement en "arrière plan", ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int exec_processus(processus_t* proc){



  if(strcmp(proc->argv[0],"cd")==0){

    return proc->status=cd(proc->argv[1]);
  }
  else if(strcmp(proc->argv[0],"export")==0){

    const char *str;
    str = (char *)malloc(MAX_ARG);

    str =strtok(proc->argv[1],"=");
    const char *arg[50];
    int i=0;
     while(str != NULL){
        arg[i]=str;
       printf("%s\n",str);
       str=strtok(NULL,"=");
       i++;
     }
     return export_(arg[1]);

  }
  else if(strcmp(proc->argv[0],"unset")==0){

    proc->argv[1]="VAR";
    return unset(proc->argv[1],2);

  }
  else if(strcmp(proc->argv[0],"env")==0){
    return env(1,2);
  }
  /* else if(strcmp(proc->argv[0],"exit")==0 ){
    return exit_(atoi(proc->argv[1]),1,2);
    }*/
  if(strcmp(proc->argv[0],"exit")==0){
      int a;
      if(proc->argv[1]!=NULL){
	if(sscanf(proc->argv[1],"%d",&a)!=0)
      return exit_(a,proc->_stdout,proc->_stderr);
      }
	else
	  printf("erreur\n");
      return 1;
      }
  else if(strcmp(proc->argv[0],getenv("PWD"))==0 ){
    return cwd(1,2);
  }
  if((proc->pid=fork())==0){
		char* tmp3;
       if(proc->_stdin ==-1 || proc->_stdout ==-1 ||proc->_stderr ==-1 ){
				 tmp3=(char*)malloc(sizeof(char)*1024);
		     strcpy(tmp3,"Fichier introuvable\n");
		     strcat(tmp3,proc->argv[0]);
		       write(proc->_stderr,tmp3,strlen(tmp3)+1);
		       exit(1);
			 }
        dup2(proc->_stdin,0);
        dup2(proc->_stdout,1);
        dup2(proc->_stderr,2);

// ajouter le chemin où la commande existe
    char tmp[20];
    char tmp2[50]="/usr/bin/";
    strcpy(tmp,proc->argv[0]);
    strcat(tmp2,tmp);


    if(execve(tmp2,proc->argv,NULL)<0){
    tmp3=(char*)malloc(sizeof(char)*1024);
    strcpy(tmp3,"erreur lors de l'executiom de la commande :");
    strcat(tmp3,proc->argv[0]);
      write(proc->_stderr,tmp3,strlen(tmp3)+1);
      exit(1);
    }
    return 1;
    }
    else{
        if(proc->bg==1){
            waitpid(proc->pid,&proc->status,0);
        }
        else wait(&proc->status);
        if(WEXITSTATUS(proc->status)!=0)return 1;
    }

    return 0;
};
