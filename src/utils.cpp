#include "utils.h"

#define MAX_BUF_LEN 1024 * 1024

void executeCMD(const QString &cmd, QString &result)   
{   
    char *buf_ps = new char[MAX_BUF_LEN];   
    char *result_buf = new char[MAX_BUF_LEN];   
    memset(result_buf, 0, MAX_BUF_LEN);
    memset(buf_ps, 0, MAX_BUF_LEN);
    FILE *ptr;
    if((ptr=popen(cmd.toLocal8Bit().data(), "r"))!=NULL)   
    {   
        while(fgets(buf_ps, MAX_BUF_LEN, ptr)!=NULL)   
        {   
           strcat(result_buf, buf_ps);   
           if(strlen(result_buf) > MAX_BUF_LEN)   
               break;   
        }   
        pclose(ptr);   
        ptr = NULL;   
        result = result_buf;
    }   
    else  
    {   
        printf("popen %s error\n", cmd.toLocal8Bit().data());   
    }   
    delete [] buf_ps;
    delete [] result_buf;
}  
