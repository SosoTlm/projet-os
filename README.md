# 💻 ProjetOS – Template Faux OS en SDL2 (1 fichier)

Bienvenue dans **ProjetOS**, un faux système d’exploitation développé en C avec la bibliothèque SDL2.

Ce projet a été conçu pour faire un template simple tout en restant léger et customisable à souhait pour creer un faux os en C pour surprendre vos amis!

---

## 🚀 Fonctionnalités incluses

- ✅ Fenêtre redimensionnable (style desktop)
- ✅ Boot screen animé
- ✅ Notification de bienvenue personnalisée
- ✅ Barre des tâches persistante
- ✅ Bouton "Menu" cliquable avec mini-menu intégré
- ✅ Interface propre, en mode faux OS

---

## 📦 Dépendances requises

Tu dois avoir les librairies suivantes installées :

- **SDL2**
- **SDL2_ttf**
- Un fichier `.ttf` (ex: FreeSans.ttf) il y a deja des fonts intégrées mais tu peut y customiser!

---

## 🛠️ Compilation (Linux / WSL)

```bash
gcc main.c -o VanilleOS $(sdl2-config --cflags --libs) -lSDL2_ttf
```
- Sur Windows, utilise MinGW avec les bons headers SDL2.

## 🧠 Structure du code (Résumé)

- main() : Initialise SDL + fenêtre

- drawText() : Fonction de rendu texte

- afficherNotification() : Affiche un popup au démarrage

- Taskbar & menu Linux-style toujours visibles

- Boucle principale de rendu fluide à 60 FPS

---

## 🤝 Contribuer
Ce projet est pensé pour s’amuser avec la SDL tout en simulant un OS. Forke-le, bricole, **fais-toi plaisir** !
Tu peux même l’intégrer dans un launcher ou en fond d’un simulateur de boot.

---

## Information
Ce projet sera et restera maintenu avec des mise à jours pour corriger des bugs, améliorer des choses, etc...
