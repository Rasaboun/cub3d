#include "test.h"
#include "libft/libft.h"
#include "get_next_line.h"

int    parsecolor(char *line,int n)
{
    int r;
    int g;
    int b;
    int rgb;

    while(ft_iswhitespace(line[n]))
        n++;
    r = ft_atoi(line+n);
    while(ft_isdigit(line[n]))
        n++;
    n += 1;
    g = ft_atoi(line+n);
    n += 1;
    b = ft_atoi(line+n);

    rgb = r << 16 | g << 8 | b;
    return (rgb);
}



doubleint    parsesize(char *line,int n)
{
    doubleint dint;

    dint.i = 0;
    dint.ii = 0;

    while(ft_iswhitespace(line[n]))
        n++;
    dint.i = ft_atoi(line+n);
    while(ft_isdigit(line[n]))
        n++;
    while(ft_iswhitespace(line[n]))
        n++;
    dint.ii = ft_atoi(line+n);
    return (dint);
}


char    *parsetex(char *line,int n)
{
    int y;
    int nn;
    char *s1;

    y = 0;

    while(ft_iswhitespace(line[n]))
        n++;
    nn = n;
    while (line[n] >= 33 && line[n] <= 126)
        {
            y++;
            n++;
        }
    s1 = ft_substr(line,nn,y);
    return (s1);
}
void recup(char *line, parse *pars)
{
    int n;
    n = 0;

    if (line[n] == 'S' && line[n+1] != 'O')
    {
        n++;
        pars->s = parsetex(line,n);
    }
    if (line[n] == 'R')
    {
        n++;
       pars->r = parsesize(line,n);
    }
    if (line[n] == 'N' && line[n+1] == 'O')
    {
        n += 2;
        pars->no = parsetex(line,n);
    }
    if (line[n] == 'S' && line[n+1] == 'O')
    {
        n += 2;
        pars->so = parsetex(line,n);
    }
    if (line[n] == 'W' && line[n+1] == 'E')
    {
        n += 2;
        pars->we = parsetex(line,n);
    }
    if (line[n] == 'E' && line[n+1] == 'A')
    {
        n += 2;
        pars->ea = parsetex(line,n);
    }
    if (line[n] == 'F')
    {
        n++;
        pars->f = parsecolor(line,n);
    }
    if (line[n] == 'C')
    {
        n++;
        pars->f = parsecolor(line,n);
    }
}
