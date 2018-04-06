#include "check.h"


int check_dir(const char * name){
    DIR * dir = opendir(name);
    if(dir){
        closedir(dir);
        return 1;
    }
    return 0;
}

int dir_in_dir(const char * src, const char * dest){

    char *path_1, *path_2;
    char buf_1[128], buf_2[128];

    path_1 = realpath(src, buf_1);
    path_2 = realpath(dest, buf_2);
    int l_1 = strlen(path_1);
    int l_2 = strlen(path_2);
    int length = l_1 > l_2 ? l_2 : l_1;
    if(strncmp(path_1, path_2, length) == 0)
        return 1;
    else
        return 0;
}

int exist(char * fname)
{
	if(access(fname,F_OK) != -1)
		return 1;
	else
		return 0;
}

void  rm_files(conf config)
{
    DIR *dir = opendir(config.d_dir);
	struct dirent *dirent;
    char path[128];
    char dest_path[128];
	while((dirent = readdir(dir)) != NULL)
	{
        strcpy(path,"");
        strcpy(dest_path,"");
		if(strcmp(dirent->d_name,".") == 0 || strcmp(dirent->d_name,"..") == 0)
				continue;

        printf("%s\n", dirent->d_name);
		strcat(path,config.s_dir);
		strcat(path,"/");		
    	strcat(path,dirent->d_name);
		if(!(exist(path)))
		{
		    strcat(dest_path,config.d_dir);
		    strcat(dest_path,"/");
		    strcat(dest_path,dirent->d_name);
            if(dirent->d_type == DT_REG)
		        remove(dest_path);
            else if(dirent->d_type == DT_DIR)
                {
                    printf("Wysyłam do recursive: %s\n", dest_path);
                    (void)recursiveDelete(dest_path);
                    remove(dest_path);
                }       
		}

        
	}
}

int recursiveDelete(char* dirname) {

  DIR *dp;
  struct dirent *ep;

  char abs_filename[FILENAME_MAX];

  dp = opendir (dirname);
  if (dp != NULL)
    {
      while (ep = readdir (dp)) {
        struct stat stFileInfo;

        snprintf(abs_filename, FILENAME_MAX, "%s/%s", dirname, ep->d_name);

        if (lstat(abs_filename, &stFileInfo) < 0)
          perror ( abs_filename );

        if(S_ISDIR(stFileInfo.st_mode)) {
          if(strcmp(ep->d_name, ".") && 
             strcmp(ep->d_name, "..")) {
            printf("%s directory\n",abs_filename);
            recursiveDelete(abs_filename);
          }
        } else {
          printf("%s file\n",abs_filename);
                  remove(abs_filename);
        }
          }
      (void) closedir (dp);
        }
  else
    perror ("Couldn't open the directory");


  remove(dirname);
  return 0;

}

