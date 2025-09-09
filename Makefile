# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
# Pour utiliser avec les threads, ajoutez -pthread
LDFLAGS = -pthread

# Nom de l'exécutable
NAME = philo

# Fichiers sources
SRCS = main.c philo.c philo1.c philo2.c philo3.c philo4.c

# Fichiers objets (générés automatiquement à partir des sources)
OBJS = $(SRCS:.c=.o)

# Fichier d'en-tête
HEADER = philo.h

# Règle principale
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

# Compilation des fichiers objets
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS)

# Nettoyage complet (objets + exécutable)
fclean: clean
	rm -f $(NAME)

# Recompilation complète
re: fclean all

# Protection contre les fichiers du même nom
.PHONY: all clean fclean re