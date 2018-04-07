#include "copy.h"
#include "check.h"

void work(conf config)
{
    DIR *dir = opendir(config.s_dir);
    while(1)
    {
        //przepisuj pliki
    }

}

void make_copy(char * src, char * dest, char * filename, off_t max_size)
{
    char src_f[FILENAME_MAX];
    char dest_f[FILENAME_MAX];

    strcat(src_f, src);
    strcat(src_f,"/");
    strcat(src_f, filename);

    strcat(dest_f, dest);
    strcat(dest_f,"/");
    strcat(dest_f,filename);

    if(max_size < check_size(dest_f))
        copy_mmap(src_f, dest_f);
    else
        copy_normal(src_f, dest_f); 
}

void copy_normal(char* src_f, char* dest_f)
{
    int sf, df, f;
    char buf[1024];
    sf = open(src_f, O_RDONLY);
    df = open(dest_f, O_WRONLY);

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