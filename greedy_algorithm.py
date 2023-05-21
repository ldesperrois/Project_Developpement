#--------Desperrois_Lucas-----#
#-------greedy_algorithm.py---#
#-------program which effectuates the greedy algorithm to know the best making change of monney---#


monetary_system = [500,200,100,50,20,10,5,2,1,0.5,0.20,0.10,0.05,0.02,0.01];        										#list that represents the european monetary system



def greedy(amont_due):
    keep=amont_due;
    i=0;		
    count_list=[0 for i in range(len(monetary_system))];    								#list that represents the nombers
    while((i<len(monetary_system)) and (amont_due>=0)):
        if(amont_due>=monetary_system[i]):
            amont_due=round(amont_due-monetary_system[i],2);
            count_list[i]=count_list[i]+1;  
        else:
            i=i+1;  
    print("the number of ticket(s) or coin(s) to be returned for the sum of",keep,":\n");	#part which showes the number of ticket(s) or coin to give back the money
    for i in range(len(count_list)):
        if(count_list[i]>0 and monetary_system[i]<5):
            print(count_list[i]," coin(s) of " ,monetary_system[i]);
        elif(count_list[i]>0):
            print(count_list[i]," ticket(s) of " ,monetary_system[i]);
            

def verif(amont_due):
    result = True;
    if(amont_due!=round(amont_due,2)):
        result = False;
    return result;


def main():
    
    amont_due=float(input("give an amont due of money"));
    while(verif(amont_due)==False):
        print("\nthe sum you enter has more than two decimal places\n");
        amont_due=float(input("give an amont due of money"));
    greedy(amont_due);
    
main();





        

          