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

	while((dirent = readdir(dir)) != NULL)
	{
		if(strcmp(dirent->d_name,".") == 0 || strcmp(dirent->d_name,"..") == 0)
				continue;
                
        printf("%s\n", dirent->d_name);
		char * path = malloc(sizeof(char) * (strlen(config.s_dir) + strlen(dirent->d_name) + 1));
		strcat(path,config.s_dir);
		strcat(path,"/");		
    	strcat(path,dirent->d_name);
		if(!(exist(path)))
		{
            char * dest_path = malloc(sizeof(char) * (strlen(config.d_dir) + strlen(dirent->d_name) + 1));
		    strcat(dest_path,config.d_dir);
		    strcat(dest_path,"/");
		    strcat(dest_path,dirent->d_name);
		    printf("Usuwam %s\n", dest_path);
            if(dirent->d_type == DT_REG)
		        remove(dest_path);
            else if(dirent->d_type == DT_DIR)
                rm(dest_path);
            
            free(dest_path);
		}
		free(path);  
		
	}
}
