#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

// Fonction de lecture
static int ft_read(int fd, char *tab)
{
    int count = read(fd, tab, BUFFER_SIZE);
    if (count < 0)
        return -1;  // Erreur de lecture
    tab[count] = '\0';
    return count;
}

// Fonction pour ajouter un caractère à la ligne
static char *append_c(char *ligne, char c)
{
    char *n_ligne;
    int len = 0;

    // Calculer la longueur de la ligne actuelle
    while (ligne[len] != '\0')
        len++;

    // Allouer de la mémoire pour la nouvelle ligne
    n_ligne = malloc(len + 2);  // +1 pour le caractère ajouté et +1 pour le '\0'
    if (!n_ligne)
    {
        free(ligne);
        return NULL;
    }

    // Copier l'ancienne ligne dans la nouvelle
    for (int i = 0; i < len; i++)
        n_ligne[i] = ligne[i];
    
    // Ajouter le caractère
    n_ligne[len] = c;
    n_ligne[len + 1] = '\0';

    // Libérer l'ancienne ligne et retourner la nouvelle
    free(ligne);
    return n_ligne;
}

// Fonction pour allouer une nouvelle ligne vide
static char *alloc(void)
{
    char *ligne = malloc(1);
    if (!ligne)
        return NULL;
    ligne[0] = '\0';
    return ligne;
}

// Fonction pour traiter les caractères et gérer la ligne
static char *ft_proce(char *ligne, char *tab, int *i)
{
    if (tab[*i] == '\n' || tab[*i] == '\0')
    {
        ligne = append_c(ligne, '\n');
        (*i)++;
    }
    else
    {
        ligne = append_c(ligne, tab[*i]);
        (*i)++;
    }
    return ligne;
}

// Fonction principale de lecture ligne par ligne
static char *fun_lin(int fd, char *tab)
{
    static int i = 0;
    static int j = 0;
    char *ligne = alloc();  // Allouer une ligne vide

    if (!ligne)
        return NULL;

    while (1)
    {
        if (i == j)  // Si tout le buffer a été traité
        {
            j = ft_read(fd, tab);  // Lire un nouveau bloc de BUFFER_SIZE
            if (j <= 0)  // Si rien n'a été lu ou fin de fichier
            {
                if (ligne[0] == '\0')  // Si la ligne est vide
                {
                    free(ligne);
                    return NULL;
                }
                break;  // Fin de lecture
            }
            i = 0;  // Réinitialiser l'index
        }

        // Traiter le caractère actuel dans le buffer
        ligne = ft_proce(ligne, tab, &i);
        if (tab[i - 1] == '\n' || tab[i - 1] == '\0')
            break;
    }
    return ligne;
}

// Fonction principale get_next_line
char *get_next_line(int fd)
{
    static char tab[BUFFER_SIZE + 1];  // Buffer statique partagé entre les appels
    char *ligne = fun_lin(fd, tab);  // Lire la prochaine ligne

    if (!ligne || ligne[0] == '\0')  // Si aucune ligne n'est lue ou si la ligne est vide
        return NULL;

    return ligne;
}
