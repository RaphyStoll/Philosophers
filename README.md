🍝 Philosophers - Version Animée Interface visuelle en temps réel pour le projet Philosophers de 42.

🚀 Utilisation Version normale bash make ./philo 4 400 100 100 Version animée ⭐ bash make anim
./philo 4 400 100 100 Script de démonstration bash chmod +x demo.sh ./demo.sh 🎬 Interface Animée
L'interface affiche en temps réel :

🍝 Table ronde au centre avec les spaghettis 👤 Philosophes autour de la table avec émojis d'état :
🤔 Bleu : Réflexion (thinking) 🍽️ Vert : Mange (eating) 😴 Magenta : Dort (sleeping) 🍴 Jaune :
Prend une fourchette 💀 Rouge : Mort 📊 Statistiques en temps réel 📋 Log d'activité en bas d'écran
🎯 Exemples de Tests bash

# Simulation stable

make anim && ./philo 4 400 100 100

# Avec limite de repas

make anim && ./philo 5 800 200 200 7

# Test de mort

make anim && ./philo 4 310 200 100

# Cas spécial 1 philosophe

make anim && ./philo 1 800 200 200

# Beaucoup de philosophes

make anim && ./philo 8 600 150 150 🛠 Fonctionnalités ✅ Interface temps réel - Mise à jour fluide ✅
Émojis & couleurs - États visuels clairs ✅ Stats dynamiques - Compteurs en direct ✅ Positions
circulaires - Vraie table ronde ✅ Thread-safe - Synchronisation parfaite ✅ Compatible norme 42 -
Code propre ✅ Math.h intégré - Calculs de position

🔧 Architecture sources/ ├── animation.c # Interface principale ├── animation_utils.c # Fonctions de
dessin └── ...

header/ ├── animation.h # Prototypes animation └── ... 📝 Notes Techniques Flag de compilation :
-DANIMATION activé par make anim Bibliothèque math : -lm pour les positions circulaires ANSI Escape
Codes : Pour l'affichage terminal Thread-safe : Mutex dédié pour l'animation Performance : Mise à
jour optimisée Appuyez sur Ctrl+C pour arrêter une simulation.
