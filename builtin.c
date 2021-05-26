

 /*
    Fichier builtin.h : En-tÃªte des fonctions des commandes
                        internes du minishell
    Groupe : n 16
    Auteur : Youness Houdaifa
    DÃ©pendances :
 */


 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<unistd.h>
 #include <signal.h>
#include <sys/types.h>

 int cd(const char* path){
   char* new_path;
   new_path=(char*)malloc(sizeof(char)*1024);
   chdir(path);
   if (getcwd(new_path, 1024) != NULL) printf("Nouveau répertoire: %s\n", new_path);
 }

 int export_(const char* env){
   const char *name = "VAR";
   setenv(name,env,1);
   printf("%s\n",getenv(name));
   printf("export\n");
 }

 int unset(const char* env, int fderr){

     if(getenv("VAR") != NULL){
     printf("ok22%s\n" );
     unsetenv(env);
     return 0;
   }else{
     write(fderr,"variable undefined\n",strlen("variable undefined\n"));
     return 1;
   }

 }

 int env(int fdout, int fderr){
   extern char **environ;
     for(int i=0;environ[i];++i){
     int  w=write(fdout,environ[i],strlen(environ[i])*sizeof(*environ[i]));
     if(w<0){
       write(fderr,"Erreur au niveau de la recuperation des variables d'environnemnt\n",strlen("Erreur au niveau de la recuperation des variables d'environnemnt\n"));
       return 1;
     }
     }
 return 0;
   }

  int exit_(int val, int fdout, int fderr){
   write(fdout,"fin du shell\n",strlen("fin du shell")+1);
   exit(val);
   write(fderr,"fin du shell\n",strlen("fin du shell")+1);

      return val;
  }

  int cwd(int fdout, int fderr){if(system("pwd")==0){
      write(fdout,"",strlen(""));
      return 0;
  }else{
  write(fderr,"Operation undefined",strlen("Operation undefined"));
  return 1;
  }
 }
