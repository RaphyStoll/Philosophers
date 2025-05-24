#!/bin/bash

# Script de démonstration pour philosophers avec animation

echo "🍝 DEMONSTRATION PHILOSOPHERS ANIME 🍝"
echo "====================================="

# Vérifier si make est disponible
if ! command -v make &> /dev/null; then
    echo "❌ Make n'est pas installé!"
    exit 1
fi

# Nettoyer avant compilation
echo "🧹 Nettoyage des anciens fichiers..."
make fclean > /dev/null 2>&1

# Compiler la version animée
echo "📦 Compilation de la version animée..."
make anim

if [ $? -ne 0 ]; then
    echo "❌ Erreur de compilation!"
    echo "💡 Vérifiez que tous les fichiers sont présents et conformes à la norme."
    exit 1
fi

echo ""
echo "🎬 Lancement des démonstrations..."
echo "   Appuyez sur Ctrl+C pour arrêter une démo et passer au suivant"
echo ""

# Fonction pour lancer une démo
run_demo() {
    local desc="$1"
    local args="$2"
    echo "🎯 $desc"
    echo "   Commande: ./philo $args"
    echo ""
    timeout 30 ./philo $args
    echo ""
    echo "▶ Démo terminée. Appuyez sur Entrée pour continuer..."
    read -t 5  # timeout de 5 secondes
    clear
}

# Démonstrations
clear
run_demo "Démo 1: 4 philosophes (simulation stable)" "4 400 100 100"
run_demo "Démo 2: 5 philosophes avec nombre de repas limité" "5 800 200 200 7"
run_demo "Démo 3: Cas limite - mort d'un philosophe" "4 310 200 100"
run_demo "Démo 4: Cas spécial - 1 seul philosophe" "1 800 200 200"
run_demo "Démo 5: Beaucoup de philosophes" "8 600 150 150"

echo "🎉 Toutes les démonstrations sont terminées!"
echo "📝 Pour utiliser:"
echo "   • Version normale: make && ./philo [args]"
echo "   • Version animée:  make anim && ./philo [args]"
echo ""
echo "🔧 Pour nettoyer: make fclean"