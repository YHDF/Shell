

/*
    Fichier utils.c : fonctions utilitaires.
    Groupe : n 16
    Auteur : TIABI EL.MEHDI
    DÃ©pendances :
 */


#include <stdlib.h>

/*
 Fonction count_tokens :  Compte le nombre de tokens dans le tableau
                          NULL-terminated
      Paramètre tokens :  tableau NULL-terminated de chaînes de caractères
      Retourne le nombre de chaînes dans le tableau.
 */
size_t count_tokens(char* tokens[]){
		int count=0,offset=0;
		while (tokens[offset]!=NULL)
    {
        count++;
        offset++;
    }
    return count;
};

/*
  Fonction clear_tokens : Vide le tableau tokens
      Paramètre tokens : le tableau à réinitialiser
      Retourne le pointeur sur le tableau ou NULL en cas d'erreur
 */
char** clear_tokens(char* tokens[]){
		size_t s=count_tokens(tokens);
	if(s!=0){
	for(int i=0;i<s;i++)
    tokens[i]=NULL;
	return tokens;
	}
	return NULL;
};

/*
  Fonction insert : Insert les éléments de elts dans tokens à partir
                    de la position pos
      Paramètre tokens : le tableau dans lequel on insert les valeurs
      Paramètre elts : le tableau des éléments à insérer
      Paramètre pos : la position à laquelle on insert les éléments
      Retourne le pointeur sur tokens ou NULL en cas d'erreur
 */
char** insert(char* tokens[], char* elts[], size_t pos){

	 if(pos>=0){
	    	size_t s=count_tokens(elts);
			size_t t=count_tokens(tokens);

	    	for (int i = t - 1; i >= pos - 1; i--)
	        {tokens[i+s] = tokens[i];s--;}
	    	  s=count_tokens(elts);
	    	for(int i=0;i<s;i++)
			 tokens[pos+1+i]=elts[i];

	    	 return tokens;
		}
		else return NULL;
};

/*
  Fonction del_token : Supprime un élément dans tokens
      Paramètre tokens : le tableau duquel on veut retirer l'élément
      Paramètre pos : la position de l'élément à supprimer
      Retourne le pointeur sur tokens ou NULL en cas d'erreur
 */
char** del_token(char* tokens[], size_t pos){
		size_t s=count_tokens(tokens);
	if(s>0 && pos >=0){

	for(int i=pos;i<s;i++){
		tokens[i]=tokens[i+1];
	}
	tokens[s-1]=NULL;
	return tokens;

	}
	return NULL;
};
