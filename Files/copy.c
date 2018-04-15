#include "copy.h"
#include "check.h"

void work(char* s_dir, char* d_dir, off_t mmap_size, int recursive)
{
    DIR *dir = opendir(s_dir);
    struct dirent *dirent;
    int copy = 0;
    int create = 0;
    char src_full_path[128];
    char  dest_full_path[128];
    if(dir != NULL){
    while(dirent = readdir(dir))
    {        
        if(strcmp(dirent->d_name,".") == 0 || strcmp(dirent->d_name,"..") == 0)
				continue;

             snprintf(dest_full_path,FILENAME_MAX,"%s/%s",d_dir,dirent->d_name);
             snprintf(src_full_path,FILENAME_MAX,"%s/%s",s_dir,dirent->d_name);

            if(exists(dest_full_path))
            {
                if(compare_time(src_full_path, dest_full_path) == 0)
                    copy = 1; 
            }
            else
                {
                    copy = 1;
                    create = 1;
                }

            if(copy && dirent->d_type == DT_REG)
                {
                    if(create)
                        {
                            creat(dest_full_path, 0766);
                            syslog(LOG_INFO,"Tworzę plik: %s",dest_full_path);
                        }
                    make_copy(src_full_path, dest_full_path, mmap_size);
                    change_time(src_full_path,dest_full_path);
                }
            else if( copy && dirent->d_type == DT_DIR && recursive)
                {
                    if(create)
                        {
                         mkdir(dest_full_path, 0744);
                         syslog(LOG_INFO,"Tworzę katalog: %s",dest_full_path);
                        }
                        work(src_full_path, dest_full_path, mmap_size, 1);  
                }
                copy = 0;
                create = 0;
    } 
    }
    (void)closedir(dir);

}

void make_copy(char * src_f, char * dest_f,  off_t max_size)
{

    if(max_size < check_size(src_f))
        copy_mmap(src_f, dest_f);
    else
        copy_normal(src_f, dest_f); 
    syslog(LOG_INFO,"Kopiuję: %s",src_f);
}

void copy_normal(char* src_f, char* dest_f)
{
    int sf, df, f;
    char buf[1024];
    sf = open(src_f, O_RDONLY);
    df = open(dest_f, O_WRONLY  | O_CREAT, 0666);

    while((f = read(sf,buf,sizeof(buf)))>0)
        write(df,buf,f);

    close(sf);
    close(df);
}

void copy_mmap(char* src_f, char* dest_f)
{
    int sf, df;
    off_t size = check_size(src_f);
    char *src, *dest;

    sf = open(src_f, O_RDONLY);
    src = mmap(NULL, size, PROT_READ, MAP_PRIVATE,sf,0);

    df = open(dest_f, O_RDWR);
    truncate(dest_f,size);
    dest = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, df, 0);

    memcpy(dest,src,size);
    munmap(src,size);
    munmap(dest,size);

    close(sf);
    close(df);
} 