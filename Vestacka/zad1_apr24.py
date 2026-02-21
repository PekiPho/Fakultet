from functools import reduce

def logika(dan):
    danL=len(dan)

    dan.sort(reverse = True)
    broj = dan[danL//2] if  danL%2!=0 else (dan[danL//2-1]+ dan[danL//2]) /2

    return broj

def prosek(temp):
    lista_medijana = [logika(dan) for dan in temp]
    avg = reduce(lambda x,y: x+y,lista_medijana) / len(lista_medijana)

    return avg


print(prosek([[8,-15,4,9],[3,2,33],[2,4,4],[8,2,12],[3,5,1,15]]))