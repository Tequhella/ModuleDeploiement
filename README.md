# ModuleDeploiement

## Dépendances

Ce projet nécessite les paquets suivants :

- libboost-dev
- libboost-test-dev
- libgtkmm-3.0-dev

Vous pouvez installer ces dépendances en exécutant le script `dep.sh` inclus dans ce dépôt :

```bash
sudo sh ./dep.sh
```

## Configuration du projet
Pour configurer ce projet, suivez les étapes suivantes :

1. Clonez le dépôt sur votre machine locale.
2. Naviguez jusqu'au répertoire du projet.
3. Exécutez le script `dep.sh` pour installer les dépendances nécessaires.
4. Une fois les dépendances installées, exécutez la commande :

```bash
cmake .
make
```

5. Pour lancer le program, exécutez la commande :

```bash
./MyApp
```

6. Pour lancer les tests :
```bash
make coverage
```