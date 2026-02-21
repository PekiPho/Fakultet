

def pronadjiPut(kv,goal,trenutni=0,putanja=None):
    if putanja is None:
        putanja =[trenutni]
    

    if trenutni == goal:
        return putanja
    
    moguci = kv.get(trenutni,[])
    moguci.sort(reverse= True)

    for skok in moguci:
        sledeci = trenutni + skok

        if(sledeci <=goal):

            putanja.append(sledeci)

            rezultat = pronadjiPut(kv,goal,sledeci,putanja)

            if rezultat:
                return rezultat
            
            putanja.pop()

    return None

graf_primer = {
    0: [1, 2], 1: [2, 4], 2: [2, 3], 3: [2, 4], 4: [4, 5],
    5: [3, 4, 5], 6: [3, 4], 7: [2, 3], 8: [1], 9: [1], 10: []
}
print(pronadjiPut(graf_primer, 7))