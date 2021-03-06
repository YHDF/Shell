
/*
    Fichier utils.c : fonctions de traitement de
                      la ligne de commande
    Groupe : n 16
    Auteur : Youness Houdaifa
    DÃƒÂ©pendances :
 */

 #include <stdio.h>
 #include "parser.h"
 #include <string.h>
 #include <stdlib.h>

 char** tmp_token;
 char* tmp_str;

 void init(){
   tmp_token=(char**)malloc(sizeof(char*));
   for(int i = 0; i < 1024; i++){*(tmp_token+i)=(char*)malloc(sizeof(char)*1024);}
   tmp_str=(char*)malloc(sizeof(char)*1024);
 }



 int trim_str(char* str){
   init();
   int prev = 0;
   int counter = 0;

   while(counter < strlen(str)){
     if(*(str+counter)== ' ' || *(str+counter)== '\t'){
       for(int next = 1; next < strlen(str); next++)
         *(str+prev++) = *(str+next);
       prev = 0;
     }
     else
       break;
     counter=0;
   }
   counter = strlen(str) - 1;
   while(counter > 0){
     if(*(str+counter)== ' ' || *(str+counter)== '\t')
       *(str+counter) = 0;
     else
       break;
     counter--;
   }
   strcpy(tmp_str,str);
   return 0;
 }



 int clean_str(char* str){
   trim_str(str);
   int next = 1,prev=0;
   while(prev < strlen(str)){
     if(*(str+prev) == ' ' && *(str+next) == ' ' || *(str+prev) == '\t' && *(str+next) == '\t'){
       int after=next;
       for(int counter = prev; counter < strlen(str); counter++){
         *(str+counter) = *(str+after++);
       }
     }
     else{
       prev++;
       next++;
     }
   }
   strcpy(tmp_str,str);
   return 0;
 }




 int tokenize_str(char* str, char* tokens[]){
   clean_str(str);
   int string=0,letter=0,word=0;
   while(string < strlen(str)){
     while(*(str+string) != ' ' && *(str+string) != '\t'){
       if(*(str+string) == 0 || *(str+string) == '\n'){
         break;
       }
       *(tokens[word]+letter) = *(str+string);
       letter++;
       string++;
     }
     string++;
     word++;
     letter = 0;
   }
   //init();
   for(int i=0;i<word;i++){strcpy(*(tmp_token+i), tokens[i]);}
   *(tokens+word)=NULL;
   *(tmp_token+word)=NULL;
   return 0;
 }




 int env_str(char* tokens[]){
   int index = 0;
   while(*(tmp_token+index)!=NULL){
     if(getenv(tmp_token[index])!=NULL){
       strcpy(tmp_token[index],getenv(tmp_token[index]));
       index++;
     }else{
       strcpy(tmp_token[index],tmp_token[index]);
       index++;
     }
   }

   for(int i=0;i<index;i++){strcpy(*(tokens+i), tmp_token[i]);}
   return 0;
 }
