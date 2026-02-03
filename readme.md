## Descripteurs et sélecteurs de segments (GDT)

Ce noyau utilise une **GDT (Global Descriptor Table)** pour définir les segments mémoire en **mode protégé x86**, avec une séparation claire entre le **noyau (ring 0)** et les **processus utilisateurs (ring 3)**.

Chaque entrée de la GDT correspond à un **sélecteur de segment**, chargé dans un registre de segment (CS, DS, SS, etc.), et définit les **droits d’accès**, le **type de segment** et le **niveau de privilège**.

---

### Organisation de la GDT

| Index | Sélecteur | Segment | Ring | Usage |
|------:|----------:|--------|------|-------|
| 0 | 0x00 | Null | — | Descripteur nul obligatoire |
| 1 | 0x08 | Code noyau | 0 | Code du kernel (CS) |
| 2 | 0x10 | Données noyau | 0 | Données du kernel (DS/ES/FS/GS) |
| 3 | 0x18 | Stack noyau | 0 | Pile du kernel (SS) |
| 4 | 0x20 | Code utilisateur | 3 | Code des processus user (CS) |
| 5 | 0x28 | Données utilisateur | 3 | Données user (DS/ES/FS/GS) |
| 6 | 0x30 | Stack utilisateur | 3 | Pile utilisateur (SS) |

---

### Description des segments

- **Descripteur nul (index 0)**  
  Entrée invalide obligatoire. Toute tentative d’utilisation provoque une exception.

- **Code noyau (ring 0)**  
  Contient le code du noyau. Exécutable uniquement en mode privilégié.

- **Données noyau (ring 0)**  
  Regroupe les variables globales, structures internes et buffers du noyau.

- **Stack noyau (ring 0)**  
  Pile utilisée lors des interruptions, des appels système et des changements de contexte.

- **Code utilisateur (ring 3)**  
  Code des programmes utilisateurs, isolé du noyau par les mécanismes de privilèges.

- **Données utilisateur (ring 3)**  
  Mémoire des processus utilisateurs (heap, variables globales, zones mappées).

- **Stack utilisateur (ring 3)**  
  Pile utilisée par les processus utilisateurs pour les appels de fonctions.

---

### Notes importantes

- Tous les segments utilisent un **modèle mémoire plat**  
  → base = 0, limite = 4 Go
- La protection mémoire repose sur les **rings de privilèges (0 et 3)**
- En architecture x86, un segment de **stack est techniquement un segment de données**
- La GDT définit les **permissions et niveaux de privilège**,  
  l’allocation et l’isolation mémoire fine étant assurées par le **paging**
