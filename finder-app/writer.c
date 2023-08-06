// In the name of Allah

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>




void str_copy(char* from , char* to) {
    while ((*to++ = *from++) != '\0')
        ;
}


int main(int argc , char * argv[]) {

    openlog(NULL , 0 , LOG_USER) ;
     

   if(argc < 3) {
    printf("Please provide two arguments - filesDir and searchStr\n") ;
    syslog(LOG_ERR , "Please provide two arguments - filesDir and searchStr") ;
    return 1 ; 
   }
   
  
   char* writeFile = malloc(strlen(argv[1]) + 1) ;
   str_copy(argv[1] , writeFile) ;
   
   
   char* dirPath = dirname(writeFile) ;
   
   char* writestr = argv[2] ;
   
   // Check to see if directory exists
   struct stat stats ;
   stat(dirPath ,& stats) ;
  
   
   if(!S_ISDIR(stats.st_mode))  {

   // directory does not exist - need to create it
   printf("Directory does not exist - creating drirectory structure...") ;
   syslog(LOG_INFO , "Directory does not exist - creating drirectory structure...") ;
   // syslog
   
   int check = mkdir(dirPath , 0777) ;

   if(check != 0) {
   	// error occurred while making directory
        perror("Error while creating directory : ") ;
        syslog(LOG_ERR , "Error while creating directory : %s" , strerror(errno)) ;
        // syslog
   	return 1 ;
   }
   
   }
   
   FILE* descriptor ;
   descriptor = fopen(argv[1] , "w+") ;
   if(descriptor == NULL) {
   	// error while accessing file 
        perror("Error while accessing file: ") ;
        syslog(LOG_ERR , "Error while accessing file: %s" , strerror(errno)) ;
           // syslog
   	return 1 ;
   }
   
   
   // If all ok then write to the file
   int num = sizeof(writestr) ;
   
   if(!fputs(writestr , descriptor)) {
     // error has occured while writing to the file
     perror("Error while writing to file : ") ;
     syslog(LOG_ERR , "Error while writing to file : %s" , strerror(errno)) ;
        // syslog
     return 1 ;
   }
   
   // syslog
   syslog(LOG_DEBUG , "Writing %s to %s" ,writestr, argv[1]) ;
   
   fclose(descriptor) ;
   
   free(writeFile) ;
   
   
   
return 0 ;

}
