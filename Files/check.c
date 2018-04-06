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

void rm_files(conf config)
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
                    recursive_rm(dest_path);
                    remove(dest_path);
                }       
		}

        
	}
}

void recursive_rm(char* dirname) {

  DIR *d;
  d = opendir(dirname);
  struct dirent *de;
  char path[FILENAME_MAX];
  
  if (d != NULL)
    {
      while (de = readdir (d)) {
        struct stat stFileInfo;

        snprintf(path, FILENAME_MAX, "%s/%s", dirname, de->d_name);

        if (lstat(path, &stFileInfo) < 0)
            perror (path);

        if(S_ISDIR(stFileInfo.st_mode)) {
            if(strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
                //rozpoczynanie usuwania katalogu;
                recursive_rm(path);
          }
        }
        else {
            //usuwanie pliku
            remove(path);
        }
       }
      (void)closedir(d);
    }
  else
    perror ("Błąd otwarcia katalogu");

  remove(dirname);

}

