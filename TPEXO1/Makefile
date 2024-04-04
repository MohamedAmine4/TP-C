# Nom du compilateur
CC=gcc

# Options de compilation
CFLAGS=-Wall -Wextra 

# Utiliser la variable t pour le nom de l'exécutable
t=TpExo1

# Liste des fichiers source
sources=$(wildcard *.c)

# Liste des fichiers objet
objets=$(sources:.c=.o)

# La première règle est la règle par défaut
all: $(t)

# Règle pour générer l'exécutable
$(t): $(objets)
		$(CC) $(CFLAGS) $^ -o $@

# Règle pour compiler un fichier source en fichier objet
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés lors de la compilation
clean:
		rm -f $(objets) $(t)
