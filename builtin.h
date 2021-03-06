
#ifndef BUILTIN_H
#define BUILTIN_H

/*
    Fichier builtin.h : En-tÃªte des fonctions des commandes
                        internes du minishell
    Groupe : n 16
    Auteur : Youness Houdaifa
    DÃ©pendances :
 */



int cd(const char* path);

int export_(const char* env);

int unset(const char* env, int fderr);

int env(int fdout, int fderr);

int exit_(int val, int fdout, int fderr);

int cwd(int fdout, int fderr);

#endif
