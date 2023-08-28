#-------------------Tri_fusion.py-----------------------#
#-------------Programme qui cherche à trier une liste de valeurs numériques par le principe du tri fusion---------#
#------------Desperrois Lucas ---------------#





#--------------------------------------------------------#
#----------Fonction tri_fuison(lg,ld)--------------------#
#-- param lg,ld : liste de valeurs nuémriques------------#
#-- Résultat de la fonction : une liste fusionné trié----#



def tri_fusion(lg,ld):
    i=0;  #gauche
    j=0; #droite
    ls=[]        
    while(i<len(lg) and j<len(ld)):			#Ici on va chercher à ranger dans la liste de résultat les élements des deux listes 
        if(lg[i]<ld[j]):
            ls.append(lg[i]);
            i=i+1;
        else:
            ls.append(ld[j]);
            j=j+1;
            
                                            
    while(i<len(lg)):
        ls.append(lg[i])
        i=i+1;
    
    while(j<len(ld)):
        ls.append(ld[j]);
        j=j+1;
        
    return ls;
    
            
            
#---------fonction fusion(l)-------------------------#
#--- param l : liste de valeurs numérique à trier----#
#-- résultat de la fonction : liste triée------------#
def fusion(l):
    
    if((len(l)==1)):				#condition d'arret : diviser pour mieux régner (on cherche à avoir un seul élement dans la liste)
        return l
    else:
        m=len(l)//2;           		#--On divise la taille pour découper la liste en deux
        lg=fusion(l[:m]);	   		#--On appelle récursivement ce découpage 
        ld=fusion(l[m:]);
        return tri_fusion(ld,lg);  	#-- puis on cherche à re-fusionner les listes découper dans l'ordre en remontant dans la récursivité
    
                    
print(fusion([200,10,786543,999,6,3]));		#test du tri_fusiob



#---------------------Fin du programme------------------#





        