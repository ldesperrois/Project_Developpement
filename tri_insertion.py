#-------Desperrois_Lucas---------#
#--------tri_insertion.py--------#
#--------Programme qui implémente le "insertion sort" d'une liste ----#




#--fonction tri_insertion---#
#--param l : paramètre d'entré qui est une liste d'entiers ou de float
#--résultat de la fonction : une liste trier
#-- si la liste est vide elle affiche que celle-ci est vide


def tri_insertion(l):
    j=0;
    if(len(l)!=0):
        for i in range(1,len(l)):
            j=i;
            while(l[j-1]>l[j] and j>0):
                l[j-1],l[j]=l[j],l[j-1];
                j=j-1;
    else:
        print("la liste est vide");
    return l;                             #résultat de la fonction

print(tri_insertion([15,9686579,99999,8,9,310000,10]));    #test de la fonction
