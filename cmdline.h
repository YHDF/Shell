#ifndef CMDLINE_H
#define CMDLINE_H

/*
    Fichier process.h :En-tête des fonctions de gestion de
                        la ligne de commande.
    Groupe : n 16
    Auteur : TIABI EL.MEHDI
    DÃ©pendances :
 */


#include "processus.h"

/*
  Fonction init_process : CrÃ©e l'enchaÃ®nement de processus Ã  partir du
                          tableau tokens
      ParamÃ¨tre proc : pointeur sur la structure Ã  remplir
      ParamÃ¨tre tokens :  tableau (NULL-terminated) contenant les chaÃ®nes
                          de la ligne de commande Ã  analyser
      Retourne 0 en cas de succÃ©s et une autre valeur en cas d'Ã©chec
 */
int init_process(processus_t* proc, char* tokens[]);

/*
  Fonction exec_cmdline : Lance les processus de la ligne de commande dans
                          l'ordre attendu en respect des conditions demandÃ©es
      ParamÃ¨tre proc : la structure dÃ©crivant les processus Ã  lancer
      Retroune 0 en cas de succÃ©s et une autre valeur en cas d'Ã©chec
 */
int exec_cmdline(processus_t* proc);



#endif
