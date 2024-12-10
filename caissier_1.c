#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "biblio__1.h"

int verify_caissier(FILE* CAISS_fichier){
    char input_password[10];
    char nom[10];
    int idinput;
    int idtest;
    printf("IDENTIFIANT DU CAISSIER : ");
    scanf("%d",&idinput);
    printf("MOT DE PASSE : ");
    scanf("%s", input_password);
    if (strcmp(input_password, PASSWORD) != 0) {
        printf("ERREUR : MOT DE PASSE INCORRECT.\n");
        return 0;
    }
    if (CAISS_fichier == NULL) {
        printf("ERREUR D OUVERTURE DU FICHIER caissiers.txt.\n");
        return 0;
    }
    fseek(CAISS_fichier, 0, SEEK_SET);
    while(fscanf(CAISS_fichier,"%d %s",&idtest,nom)==2){
        if(idtest==idinput){
            return 1;
        }
    }
    printf("ERREUR : IDENTIFIANT NON TROUVEE.\n");
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////
float calcul(int service,FILE*L_fichier,FILE*C_fichier,FILE*comm_fichier) {
    int idl;
    switch (service) {
    case 1: {
        if (L_fichier== NULL) {
            printf("Erreur d'ouverture du fichier lavages.txt.\n");
            return -1;
        }
        Lavage nouveau_lavage;
        printf("DONNER L'ID DE VOTRE LAVAGE : ");
        scanf("%d", &idl);
        fseek(L_fichier, 0, SEEK_SET);
        while (fscanf(L_fichier, "%d %s %f %s %d %d %ld %ld",
                  &nouveau_lavage.id_lavage,
                  nouveau_lavage.type,
                  &nouveau_lavage.prix,
                  nouveau_lavage.immatriculation,
                  &nouveau_lavage.statut,
                  &nouveau_lavage.etat_recup,
                  &nouveau_lavage.datedeb,
                  &nouveau_lavage.datefin)!=EOF) {
            printf("%d %s %f %s %d %d %ld %ld\n",
                  nouveau_lavage.id_lavage,
                  nouveau_lavage.type,
                  nouveau_lavage.prix,
                  nouveau_lavage.immatriculation,
                  nouveau_lavage.statut,
                  nouveau_lavage.etat_recup,
                  nouveau_lavage.datedeb,
                  nouveau_lavage.datefin);
            if (nouveau_lavage.id_lavage == idl) {
                printf("%f\n",nouveau_lavage.prix);
                return nouveau_lavage.prix;
            }
        }
        printf("ID DE LAVAGE NON TROUV�.\n");
        return -1;
    }

    case 2: {
        if (C_fichier== NULL) {
            printf("Erreur d'ouverture du fichier carburant.txt.\n");
            return -1;
        }
        printf("DONNER L'ID DE VOTRE TRANSACTION CARBURANT : ");
        scanf("%d", &idl);
        Carburant nouvelle_transaction;
        fseek(C_fichier, 0, SEEK_SET);
        while (fscanf(C_fichier, "%d %s %f %.3f %.3f",&nouvelle_transaction.id_transaction, nouvelle_transaction.type,
               &nouvelle_transaction.quantite,&nouvelle_transaction.prix_litre,&nouvelle_transaction.montant_total)!=EOF) {
            if (nouvelle_transaction.id_transaction== idl) {
                return nouvelle_transaction.montant_total;
            }
        }
        printf("ID DE TRANSACTION NON TROUV�.\n");
        return -1;
    }
    case 3: {
        if (comm_fichier == NULL) {
            printf("Erreur d'ouverture du fichier commandes.txt.\n");
            return -1;
        }
        Commande commande;
        printf("DONNER LE NUM�RO DE COMMANDE : ");
        scanf("%d", &idl);
        fseek(comm_fichier, 0, SEEK_SET);
        while (fscanf(comm_fichier, "%d %d %49s %f %d %f",&commande.numero_commande,&commande.code_produit,commande.nom,
        &commande.prix_unite,&commande.quantite,&commande.prix_total) == 6) {
            if (idl == commande.numero_commande) {
                return commande.prix_total;
            }
        }

        printf("NUM�RO DE COMMANDE NON TROUV�.\n");
        return -1;
    }

    default:
        printf("SERVICE INVALIDE.\n");
        return -1;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void traitement_paiment(float m,float argent) {
        if (argent< m) {
            printf("MONTANT INSUFFISANT. VEILLEZ REESSAYER.\n");
        } else if (argent>=m) {
            float rendu = argent-m;
            printf("MONNAIE A RENDRE : %.3f TND\n", rendu);
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
