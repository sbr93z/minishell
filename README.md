# Minishell

Minishell est un projet du cursus 42 qui consiste à implémenter un shell simple mais fonctionnel, conforme au standard POSIX. L'objectif est de recréer un shell de type Unix (similaire à `bash --posix`), capable d'exécuter des commandes, de gérer les redirections, les pipes, et les variables d'environnement. 

## Description

- **Shell POSIX** : Le programme doit être compatible avec les comportements de base d'un shell Unix (comme Bash en mode `--posix`), tout en prenant en charge des fonctionnalités comme la gestion des builtins, des redirections, des pipes, et des variables d'environnement.
- **Builtins** : Gère les commandes internes sans lancer de processus externe :
  - `echo` (avec l’option `-n`)
  - `cd` (avec seulement un chemin relatif ou absolu)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **Commandes externes** : Toutes les autres commandes sont prises en charge via `execve`.
- **Redirections** : Implémentation de redirections simples (`>`, `>>`, `<`).
- **Pipes** : Gère les pipes (`|`) pour chaîner plusieurs commandes.
- **Variables d'environnement** : Permet de définir, modifier et accéder aux variables d'environnement.
- **Gestion de la mémoire** : Utilisation d'un garbage collector personnalisé pour gérer la mémoire et éviter les fuites, avec les fonctions `gc_malloc` et `gc_free_all`.

## Installation

```bash
git clone https://github.com/sbr93z/minishell.git
cd minishell
make
```

## Utilisation

Lancez le programme depuis le terminal :
```bash
./minishell
```

## Exemple d'utilisation :
```bash
Minishell > echo "Hello, World!" > file.txt
Minishell > cat file.txt
Hello, World!
Minishell > cd /path/to/directory
Minishell > pwd
/path/to/directory
```

Le shell supporte les commandes standards, les redirections (`>`, `>>`, `<`) et les pipes (`|`).

## Commandes Makefile
```
make : Compile le programme.

make clean : Supprime les fichiers objets.

make fclean : Supprime les fichiers objets et les exécutables.

make re : fclean puis make.
```

## Fonctionnement

Minishell fonctionne en boucle infinie, lisant les commandes et les exécutant dans un environnement POSIX.

    Builtins : Implémentation complète des commandes internes listées ci-dessus.

    Commandes externes : Exécutées via fork et execve.

    Redirections : Prise en charge des redirections standard.

    Pipes : Chaînage des commandes à l’aide des pipes.

    Variables d'environnement : Gestion et expansion dynamique des variables.

Le shell est conforme au comportement attendu de Bash en mode --posix, en respectant les conventions de redirection, de gestion des processus, et d'interprétation des commandes.

Le gestionnaire de mémoire personnalisé assure une gestion efficace de la mémoire pour éviter les fuites, et l'utilisation de gc_malloc permet de mieux contrôler l'allocation dynamique.
