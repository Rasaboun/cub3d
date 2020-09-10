#include "test.h"

char    *parsing(char *str,int i);
int     *intparsing(char *str,int i);

data ft_parse(char *path)
{
    int     fd;
    char    *line;
    int i;
    data data;

    i = 0;
    line = NULL;
    fd = open(path,O_RDONLY);

    while(get_next_line(fd,&line))
    {
        if(line == NULL)
            exit(0);
        i = 0;
        while(line[i] != '\0' && ft_iswhitespace(line[i]) == 1)
            i++;
        if(line[i] == 'S' && line[i+1] != 'O')
        {
            i+=1;
            data.s = parsing(line,i);
        }
        else if(line[i] == 'N' && line[i+1] == 'O')
        {
            i += 2;
            data.no = parsing(line,i);
        }
        else if(line[i] == 'S' && line[i+1] == 'O')
        {
            i += 2;
            data.so = parsing(line,i);
        }
        else if(line[i] == 'W' && line[i+1] == 'E')
        {
            i += 2;
            data.we = parsing(line,i);
        }
        else if(line[i] == 'E' && line[i+1] == 'A')
        {
            i += 2;
            data.ea = parsing(line,i);
        }
        else if(line[i] == 'R')
        {
            i += 1;
            data.resolution = intparsing(line,i);
        }
        free(line);
    }
    free(line);
    close(fd);
    return(data);
}


char    *parsing(char *str,int i)
{
    char *s;
    int n;
    int nn;


    s = NULL;
    n = 0;

    while(str[i] != '\0' && ft_iswhitespace(str[i]) == 1)
        i++;
    nn = i;
    while(ft_isascii(str[nn]) == 1 && ft_iswhitespace(str[nn]) != 1 && str[nn] != '\0')
    {
        nn++;
        n++; 
    }
    s = ft_substr(str,i,n);
    return(s);
}
int     *intparsing(char *str,int i)
{
    int *ii;
    int n;
    int nn;

    n = 0;
    ii = malloc(sizeof(int) * 2);
    while (n < 2)
    {
    while(str[i] != '\0' && ft_iswhitespace(str[i]) == 1)
        i++;
    ii[n] = ft_atoi(str+i);
    while(ft_isdigit(str[i]))
    i++;
    n++;
    }
    return(ii);
}



int main()
{
    data dat;

    dat = ft_parse("/home/user42/Bureau/cub3d/map.cub");
    printf("%s\n",dat.s);
    printf("%s\n",dat.no);
    printf("%s\n",dat.so);
    printf("%s\n",dat.we);
    printf("%s\n",dat.ea);
    printf("%d\n",dat.resolution[1]);
    printf("%d\n",dat.resolution[0]);
    free(dat.resolution);
    free(dat.ea);
    free(dat.s);
    free(dat.no);
    free(dat.so);
    free(dat.we);

}