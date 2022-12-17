#include<stdio.h>
#include<string.h>

int main()
{
    FILE *fp,*enc;
    int i;
    char ch,take[30],x[50];
    printf("Give the file name to decrypt: ");
    gets(take);
    strcpy(x,"decrypted_");
    strcat(x,take);
    fp=fopen(take,"r");
    enc=fopen(x,"w");
    if(fp==NULL)
    {
        printf("File can't be opened");
        return 2;
    }
    while(1)
    {
        ch=getc(fp);
        if(ch==EOF)
            break;
        else
        {
            i=ch;
            i=i-15;
            ch=i;
            fputc(ch,enc);
        }
    }
    fclose(fp);
    fclose(enc);
    return 2;

}
