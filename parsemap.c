#include "test.h"
#include "libft/libft.h"
#include "get_next_line.h"


void    create_charcub(char **tab,int width)
{
    int i;
    int n; 
    char *tmp;

    i = 0;
    n = 0;

    while(tab[n])
    {
        i = ft_strlen(tab[n]);
        if (i <= width)
        {
            tmp = ft_calloc((width-i)+1,sizeof(char));
            tab[n] = ft_strfjoin(tab[n],tmp);
        }
        n++;
    }
}
int     tab_width(char **tab)
{
    int i;
    int j;
    int new;
    int last;

    last = 0;
    new = 0;
    i = 0;
    j = 0;

    while(tab[i] != NULL)
    {
        j = 0;
        while(tab[i][j])
        {
            j++;
        }
        new = j;
        if(new > last)
            last = new;
        i++;
    }
    return(last);
}

void    sort_sprite(sprite **sprites,int posX,int posY,int size)
{
    int disorder;
    int dist1;
    int dist2;

    dist1 = 0;
    dist2 = 0;
    disorder = 1;
    sprite *tmp;
    while(disorder)
    {
        disorder = 0;
        for(int j = 0;j < size-1;j++)
        {
            dist1 = (posX - sprites[j]->x) * (posX - sprites[j]->x) + (posY - sprites[j]->y) * (posY - sprites[j]->y);
            dist2 = (posX - sprites[j+1]->x) * (posX - sprites[j+1]->x) + (posY - sprites[j+1]->y) * (posY - sprites[j+1]->y);
    

            if (dist1 < dist2)
            {
                tmp = sprites[j+1];
                sprites[j+1] = sprites[j];
                sprites[j] = tmp;
                disorder = 1;
            }
        }
    }
}
sprite **get_sprites(t_list *lst,parse *pars)
{
    sprite **sprites;
    int i;

    i = 0;
    i = ft_lstsize(lst);
    sprites = (sprite**)malloc((sizeof(sprite*) * i) + 1);
    i = 0;
    while(lst != NULL)
    {
        sprites[i] = (sprite*)lst->content;
        lst = lst->next;
        i++;
    }
    sprites[i] = NULL;
    return(sprites);
}




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
    free(pars->tab);
}
void    freetext(parse *pars)
{
    free(pars->ea);
    free(pars->no);
    free(pars->s);
    free(pars->so);
    free(pars->we);
}
int checkmap(parse *pars,t_list **lst)
{
    int linecount;
    int i;
    int j;
    char mapf;
    int player;
    char *play;

    play = NULL;
    mapf = '\0';
    player = 0;
    linecount = 0;
    i = 0;
    j = 0;
    sprite *sprites;
        t_list *new;
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
            {
                play = ft_strchr("NSWE",mapf);
                pars->play.x = i;
                pars->play.y = j;
                pars->play.direction = mapf;
                player++;
                pars->tab[i][j] = '0';
            }
            if(ft_strchr("2",mapf))
            {
                sprites = malloc(sizeof(sprite));
                sprites->x = i;
                sprites->y = j;
                new = ft_lstnew(sprites);
                ft_lstadd_back(lst,new);
                pars->tab[i][j] = '0';
            }
            if (mapf == '0' || mapf == '2' || mapf == 'N' || mapf == 'S' || mapf == 'W' || mapf == 'E')
                if (!(close_map(pars,i,j)))
                    return (0);
            j++;
        }
        i++;
    }
    return (1);
}

char **ft_lstdtab(t_list *lst)
{
    char    **tab;
    int     i;
    int     size;
    int     n;
    t_list *list;
    t_list *next;

    n = 0;
    list = lst;
    i = -1;
    size = ft_lstsize(list);
    next = NULL;

    if (!(tab = (char **)malloc((sizeof(char*) * (size + 1)))))
        exit(0);
    while(i++ < size)
    tab[i] = NULL;
    i = 0;
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

    n = 0;
    first = NULL;
    map = NULL;

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
void    freepars(parse *pars)
{
    free(pars->ea);
    free(pars->no);
    free(pars->s);
    free(pars->so);
    free(pars->we);
}
void init_pars(parse *pars)
{
    parse parsing;
    parsing.c = 0;
    parsing.ea = NULL;
    parsing.f = 0;
    parsing.no = NULL;
    parsing.r.i = 0;
    parsing.r.ii = 0;
    parsing.row = 0;
    parsing.s = NULL;
    parsing.so = NULL;
    parsing.tab = NULL;
    parsing.we = NULL;
    pars = &parsing;
}

parse *cub_skip_header(int fd)
{
    char *line;
    int n;
    t_list *first;
    parse *pars;
    t_list *lst;
    sprite **sprites;
    lst = NULL;
    n = 0;
    line = NULL;

    pars = malloc(sizeof(parse));
    init_pars(pars);
    while (get_next_line(fd,&line))
    {
        if(line == NULL)
            exit(0);
        n  = 0;
        while(ft_iswhitespace(line[n]) && line[n] != '\0')
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
        else
        {
            free(line);
        }
    }
    free(line);
    pars->tab = ft_lstdtab(first);
    create_charcub(pars->tab,tab_width(pars->tab));
    checkmap(pars,&lst);
    //printf("map is %d\n",checkmap(pars,&lst));
    sprites = get_sprites(lst,pars);
    pars->sprites = sprites;
/*int e = 0;

    while(pars->tab[e])
    {
        printf("%s\n",pars->tab[e]);
        e++;
    }*/
    /*printf("pars.c %d\n",pars->c);
    printf("pars.f %d\n",pars->f);
    printf("pars.no %s\n",pars->no);
    printf("pars.row %d\n",pars->row);
    printf("pars.s %s\n",pars->s);
    printf("pars.so %s\n",pars->so);
    printf("pars.we %s\n",pars->we);*/
   // freemap(&pars);
   // freepars(&pars);
    return(pars);
}

/*int main(){

int fd;
fd = 0;
fd = open("/home/user42/Bureau/cub3d/map.cub",O_RDWR);
if (fd > 0)
    cub_skip_header(fd);
close(fd);
}
*/