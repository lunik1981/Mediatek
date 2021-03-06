#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "autok.h"
#define BUF_LEN     1024

int get_node_data(const char *filename, char **data, int *len)
{
    int fd_rd = 0;
    int result = -1;
    int length=0;
    char rBuf[PAGE_SIZE] = "";
    *len = 0;
    *data = NULL;
    fd_rd = open(filename, O_RDONLY, 0000);
    if(fd_rd == -1)
        return result;
    if ((length = read(fd_rd, rBuf, PAGE_SIZE)) == -1) {
        LOGE("Can't read %s\n", filename);
        goto EXIT_GET_NODE_DATA;
    }
    //printf("GETNODE_LENGTH:%d\n", length);
    *len = length;
    *data = (char*)malloc(length+1);
    memset((*data)+length, 0, 1);
    //goto EXIT_GET_NODE_DATA;
    memcpy(*data, rBuf, length);
    
    result = 0;
EXIT_GET_NODE_DATA:
    if(fd_rd)
        close(fd_rd);
    return result;
}

int set_node_data(const char *filename, char *data, int len)
{
    int fd_wr = 0;
    int result = -1;
    fd_wr = open(filename, O_WRONLY, 0000);
    if(fd_wr == -1)
        return result;
    if(write(fd_wr, data, len) == -1){
        printf("Can't write %s\n", filename);
        goto EXIT_SET_NODE_DATA;
    }
    result = 0;
EXIT_SET_NODE_DATA:
    if(fd_wr)
        close(fd_wr);
    return result;
}

int from_dev_to_data(char *from, char *to)
{
    char *data_buf;
    int data_count;
    FILE * pFile = NULL;
    get_node_data(from, &data_buf, &data_count);
    pFile = fopen (to, "wb");
    if(pFile == NULL)
        return 0;
    fwrite (data_buf , sizeof(char), data_count, pFile);
    if(pFile != NULL)
        fclose(pFile);
    free(data_buf);
    return 0;
}

int data_copy(char *from, char *to)
{
    char *data_buf;
    FILE * inFile;
    FILE * outFile;
    long lSize = -1;
    
    inFile = fopen (from, "rb");
    if (inFile==NULL) {
        printf("File error"); 
        return -1;
    }
    outFile = fopen (to, "wb");
    if (outFile==NULL) {
        printf("File error"); 
        if(inFile!=NULL)
            fclose (inFile); 
        return -1;
    }    
    fseek (inFile , 0 , SEEK_END);
    lSize = ftell (inFile);
    rewind (inFile);
    data_buf = (char*) malloc (sizeof(char)*lSize);
    fread (data_buf, 1, lSize, inFile);    
    fwrite (data_buf , sizeof(char), lSize, outFile);
    fclose (inFile); 
    fclose (outFile);
    free (data_buf);
    return lSize;
}

int write_to_file(char *filename, char *data_buf, int length)
{
    FILE * outFile;
    outFile = fopen(filename, "wb");
    if (outFile==NULL) {
        printf("File error"); 
        return -1;
    }
    fwrite (data_buf , sizeof(char), length, outFile);
    if(outFile != NULL)
        fclose(outFile);   
    return 0;
}