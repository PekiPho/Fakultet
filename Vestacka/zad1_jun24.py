
def razdvoji(koll):
    poredjani = sorted(koll,key=lambda k:k[1],reverse=True)

    sredina = len(poredjani)//2

    return [poredjani[:sredina],poredjani[sredina:]]


def konacno(kol11,kol12,kol21,kol22,min):
    sve = kol11 + kol12 + kol21 + kol22

    sume = {}
    [sume.update({id: sume.get(id,0) + bod}) for id,bod in sve]

    return [[id,ukupno] for id,ukupno in sume.items() if ukupno> min]


kol1 = [[11, 45], [33, 15], [22, 25], [66, 30], [55, 20], [44, 40]]


kol11 = [[11, 45], [44, 40], [66, 30]]
kol12 = [[22, 25], [55, 20], [33, 15]]
kol21 = [[44, 35], [66, 25], [11, 45]]
kol22 = [[55, 40], [22, 20], [33, 25]]
minimalni_bodovi = 50

print(razdvoji(kol1))
print(konacno(kol11,kol12,kol21,kol22,minimalni_bodovi))