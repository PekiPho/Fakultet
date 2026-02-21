from functools import reduce

def napravi(lista):
    dict = {}

    for i in range(len(lista)):
        if len(lista[i]) <2:
            dict[lista[i][0]]=None
            continue

        dict[lista[i][0]]=reduce(lambda x,y: x*y, lista[i][1:])
    
    return dict


print(napravi([(1,),(3,4,5),(7,),(1,4,5),(6,2,1,3)]))


        