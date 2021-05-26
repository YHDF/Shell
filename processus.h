#ifndef PROCESSUS_H
#define PROCESSUS_H
#define MAX_ARG 200

/*
    Fichier process.h : En-tÃªte des fonctions de gestion des
                        processus indÃ©pendants.
    Groupe : n 16
    Auteur : TIABI EL.MEHDI
    DÃ©pendances :
 */

#include <stdlib.h>
/*
 Structure processus_t permettant de dÃ©crire les paramÃ¨tres d'un
 processus lancÃ© ou Ã  lancer (PID, stdin, stdout, status, ...)
    Champs XXX :
    ...
 */
typedef struct processus_t {

  pid_t pid;
  int status;
  int _stdin;
  int _stdout,_stderr;
  char * argv[MAX_ARG];
  int bg;
  struct processus_t *next;
  struct processus_t *next_success;
  struct processus_t *next_failure;


} processus_t;

/*
  Fonction exec_processus : Permet le lancement d'un processu avec les
  propriÃ©tÃ©s choisies (redirections, lancement en "arriÃ¨re plan", ...)
      ParamÃ¨tre proc : pointeur sur une structure dÃ©crivant le processus
      Retourne 0 en cas de succÃ©s, une autre valeur en cas d'Ã©chec
 */
int exec_processus(processus_t* proc);

/*
 Fonction status_processus :  rÃ©cupÃ©rer le status d'un processus (en cours,
                              terminÃ©, ...)
      ParamÃ¨tre proc : pointeur sur une structure dÃ©crivant le processus
      Retourne le "status" d'un processus lancÃ© en arriÃ¨re plan
 */
int status_processus(processus_t* proc);
/*
Fonction afficher_proc: afficher les elements d'un processus
      ParamÃ¨tre proc : pointeur sur une structure dÃ©crivant le processus
*/
void afficher_proc(processus_t* proc);

#endif
