# Philosophers

## Description

Projet "Philosophers" de l'école 42. L'objectif est de résoudre le problème classique du dîner des philosophes en utilisant la synchronisation de processus.

## Fonctionnalités supportées

- Création de plusieurs philosophes.
- Utilisation de fourchettes pour éviter les conflits entre les philosophes.
- Mise en œuvre d'un mécanisme pour éviter les interblocages.

## Comment utiliser

1. Clonez le dépôt : `git clone <lien du dépôt>`.
2. Naviguez dans le répertoire `philosophers`.
3. Exécutez `make` pour compiler l'exécutable `philo`.
4. Vous pouvez maintenant utiliser l'exécutable `philo` pour simuler le problème du dîner des philosophes.

## Exemples

```bash
./philo 4 410 200 200

Argument	Description
1	        Nombre de philosophes
2	        Temps en millisecondes avant la mort sans manger
3	        Temps en millisecondes pour manger
4	        Temps en millisecondes pour dormir
5	        Nombre maximal de fois qu'un philosophe doit manger (optionnel)
