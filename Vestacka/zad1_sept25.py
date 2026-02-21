

def statistika(ucenici):

    pitanja={}

    for ucenik in ucenici:
        lista_odg = ucenik[-1]
        for odgovor in lista_odg:
            id=odgovor[1]
            bodovi=odgovor[2]

            if id not in pitanja:
                pitanja[id]=[0,0]

            if bodovi > 0:
                pitanja[id][0]+=1
            else:
                pitanja[id][1]+=1

    rezultat = []

    for id,counts in pitanja.items():
        tacni = counts[0]
        netacni = counts[1]

        ukupno = tacni+netacni

        procenat = (tacni/ukupno)* 100 if ukupno > 0 else 0

        rezultat.append([id,tacni,netacni,procenat])

    return rezultat


marko = [1, "Marko Markovic", "IV-1", [
    [1, "A", 5], 
    [2, "B", 0]
]]

ana = [2, "Ana Anic", "IV-2", [
    [1, "B", 10], 
    [2, "A", 8]
]]

test_data = [marko, ana]

for stavka in statistika(test_data):
    print(f"{stavka[0]}  | {stavka[1]}       | {stavka[2]}         | {stavka[3]}%")
                