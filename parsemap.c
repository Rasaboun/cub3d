#include "test.h"
#include "libft/libft.h"
#include "get_next_line.h"

void recup(char *line, parse *pars);
char    *parsetex(char *line,int n);
doubleint    parsesize(char *line,int n);

int    parsecolor(char *line,int n);


int     close_map(parse *pars, int i, int j)
{
    int linecount;

    linecount = 0;
    while(pars->tab[linecount])
        linecount++;
    if (i == 0  || i == linecount - 1 || j == 0 || j == (int)ft_strlen(pars->tab[i]) - 1)
        return (0);
    if (pars->tab[i + 1][j] == ' ' || pars->tab[i - 1][j] == ' ' || pars->tab[i][j + 1] == ' ' || pars->tab[i][j - 1] == ' ')
        return (0);
    if (pars->tab[i + 1][j] == '\0' || pars->tab[i - 1][j] == '\0' || pars->tab[i][j + 1] == '\0' || pars->tab[i][j - 1] == '\0')
        return (0);
    return (1);
}
void freepars(parse *pars)
{
    free(pars);
}
void    freemap(parse *pars)
{
    int i;

    i = 0;
    while(pars->tab[i] != NULL)
    {
        free(pars->tab[i]);
        i++;
    }
    free(pars->tab[i]);
}
void    freetext(parse *pars)
{
    free(pars->ea);
    free(pars->no);
    free(pars->s);
    free(pars->so);
    free(pars->we);
}
int checkmap(parse *pars)
{
    int linecount;
    int i;
    int j;
    char mapf;
    int player;

    mapf = '\0';
    player = 0;
    linecount = 0;
    while(pars->tab[linecount])
        linecount++;
    i = 0;
    while (i < linecount)
    {
        j = 0;
        while (pars->tab[i][j])
        {
            mapf = pars->tab[i][j];
            if (!(ft_strchr("012 NSWE",mapf)))
                return (0);
            if (ft_strchr("NSWE",mapf))
                player++;
            if (mapf == '0' || mapf == '2' || mapf == 'N' || mapf == 'S' || mapf == 'W' || mapf == 'E')
                if (!(close_map(pars,i,j)))
                    return (0);
            j++;
        }
        i++;
    }
    return (1);
}

char ** ft_lstdtab(t_list *lst)
{
    char    **tab;
    int     i;
    int     size;
    int     n;
    t_list *list;
    t_list *next;

    list = lst;
    i = 0;
    size = ft_lstsize(list);
    if (!(tab = (char **)malloc((sizeof(char*) * (size + 1)))))
        exit(0);
    while(i < size)
    {
         next = list->next;
         tab[i] = list->content;
         free(list);
         list = next;
         i++;
    }
    free(list);
    tab[size] = NULL;
    return (tab);
}


t_list    *recupmap(int fd, char *line)
{
    int n;
    t_list *first;
    t_list *map;

    first = ft_lstnew(line);
    while (get_next_line(fd,&line))
    {
        map = ft_lstnew(line);
        ft_lstadd_back(&first,map);
    }
        map = ft_lstnew(line);
        ft_lstadd_back(&first,map);
    return(first);
}


void cub_skip_header(int fd)
{
    char *line;
    int n;
    parse *pars;
    n = 0;
    line = NULL;
    t_list *first;

    while (get_next_line(fd,&line))
    {
        if(line == NULL)
            exit(0);
        n  = 0;
        while(ft_iswhitespace(line[n]))
            n++;
        recup(line+n,pars);
        if (line[n] == '0')
        {
            ft_putstr_fd("ERROR MAP",1);
            exit(EXIT_FAILURE);
        }
        if (line[n] == '1')
        {
            first = recupmap(fd, line);
        }
    }
    
    pars->tab = ft_lstdtab(first);
    checkmap(pars);
    //printf("map is %d\n",checkmap(pars));
    freemap(pars);
    freetext(pars);
    freepars(pars);
    //printf("map is %d\n",checkmap(pars));
    //printf("tab c %c",pars->tab[15][z]);
    //printf("%s\n",pars->tab[0]);
    /*while(first->next != NULL)
    {
    printf("%s\n",first->content);
    first  = first->next;
    }
    printf("%s\n",first->content);
    printf("lst count %d\n",ft_lstsize(first));
    printf("f %d\n",pars->f);
    printf("NO %s\n",pars->no);
    printf("r1 %d r2 %d\n",pars->r.i,pars->r.ii);
    printf("s %s\n",pars->s);
    printf("so %s\n",pars->so);
    printf("we %s\n",pars->we);
    printf("ea %s\n",pars->ea);
    printf("c %d\n",pars->c);*/
}

int main(){

char *line;
parse *par;
int fd;
int n = 0;
fd = 0;
fd = open("/home/user42/cub1d/map.cub",O_RDWR);
if (fd > 0)
    cub_skip_header(fd);

close(fd);
}
