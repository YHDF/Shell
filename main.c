
/*
    Fichier utils.c :Fonction Main
    Groupe : n 16
    Auteur : TIABI EL.MEHDI
    DÃ©pendances :
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "processus.h"
#include "cmdline.h"
#include "utils.h"
#include <unistd.h>



processus_t proc[200];
int main(int argc, char* argv[]){
  char* str;
  char cwds[100];
  char* tokens[1024];
  printf("\ngrp16@MiniShell %s >$",getcwd(cwds,100));

  do{
    str=(char*)malloc(sizeof(char)*MAX_LINE_SIZE);
    for(int i = 0; i < 100; i++){*(tokens+i)=(char*)malloc(sizeof(char)*1024);}
    fgets(str,1024,stdin);
    trim_str(str);clean_str(str);tokenize_str(str, tokens);
    env_str(tokens);
    init_process(proc,tokens);
    exec_cmdline(proc);
    printf("User@MiniShell %s >$",getcwd(cwds,100));

  }while(strcmp(str,"q"));

  return 0;
}
