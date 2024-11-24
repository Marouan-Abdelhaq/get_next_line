#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42 // Valeur par défaut si BUFFER_SIZE n'est pas défini
#endif

// Fonction qui calcule la longueur d'une chaîne
size_t	ft_strlen(const char *str)
{
	size_t i = 0;
	while (str[i])
		i++;
	return i;
}

// Fonction qui joint deux chaînes de caractères
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t len_s1 = ft_strlen(s1);
	size_t len_s2 = ft_strlen(s2);
	char *str = (char *)malloc(len_s1 + len_s2 + 1);
	if (!str)
		return NULL;

	size_t i = 0;
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	size_t j = 0;
	while (j < len_s2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return str;
}

// Fonction de lecture dans un tampon
static int ft_read(int fd, char *tab)
{
	int count = read(fd, tab, BUFFER_SIZE);
	if (count < 0)
		return -1;
	tab[count] = '\0';
	return count;
}

// Fonction qui ajoute un caractère à la ligne
static char *append_c(char *ligne, char c)
{
	char tmp[2] = {c, '\0'};
	char *new_ligne = ft_strjoin(ligne, tmp);
	free(ligne);
	return new_ligne;
}

// Fonction principale pour obtenir une ligne
char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1]; // Tampon statique pour la lecture
	static int i = 0, j = 0;
	char *ligne = malloc(1);
	if (!ligne)
		return NULL;

	ligne[0] = '\0'; // Initialisation de la ligne à une chaîne vide

	// Lire dans le fichier tant qu'on n'a pas trouvé une ligne complète
	while (1)
	{
		// Si on a déjà tout lu, on recharge le tampon
		if (i == j)
		{
			j = ft_read(fd, buffer);
			i = 0;

			// Si on a atteint la fin du fichier ou une erreur, on termine
			if (j <= 0)
			{
				if (ligne[0] == '\0') // Si la ligne est vide, on retourne NULL
				{
					free(ligne);
					return NULL;
				}
				break; // Sinon, on retourne la ligne lue (même si elle est incomplète)
			}
		}

		// Ajouter les caractères au fur et à mesure à la ligne
		if (buffer[i] == '\n') // Si on trouve une nouvelle ligne
		{
			ligne = append_c(ligne, '\n');
			i++;
			break;
		}
		else
		{
			ligne = append_c(ligne, buffer[i]);
			i++;
		}
	}

	return ligne;
}

// Fonction main pour tester le code
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}

	// Test de lecture du fichier ligne par ligne
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return 0;
}
