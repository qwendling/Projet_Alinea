# Projet_Alinea
##Fonctionnement de l'interpréteur:
###Donner une valeur à une variable :
nom_de_la_variable : valeur_de_la_variable

###Création de matrice:
nom_de_la_variable : matrix([a,b,c],[d,e,f]...)
a,b,... peuvent être des variables ou des floats

###Utilisation de fonction:
nom_de_la_fonction(arg1,arg2,...)
Toute les valeurs de retour des fonctions peuvent être misse dans des variables sauf
pour les fonctions sur les valeurs propres et la décomposition LU

###Liste des fonction:
addition(m1,m2)
Réalise l'addition des matrices m1 et m2

sub(m1,m2)
Réalise la soustraction des matrices m1 et m2

mult(m1,m2)
Réalise la multiplication des matrices m1 et m2

mult_scal(l,m)
Multiplie la matrice m par le scalaire l

expo(m,e)
Eléve m à la puissance e

transpose(m)
Renvoie la transpose de la matrice m

determinant(m)
Renvoie le déterminant de la matrice m

invert(m)
Renvoie l'inverse de la matrice m

rank(m)
Renvoie le rang de la matrice m

solve(A,B)
Renvoie la matrice X correspondant au systeme : AX=B

LU(m)
Renvoie la décomposition LU de la matrice

approx_vp(m)
Renvoie la plus grande valeur propre de la matrice m et son vecteur propre associé

all_vp(m)
Renvoie toutes les valeurs propres de m et leurs vecteurs propres associé
