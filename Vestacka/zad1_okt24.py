
def napraviSpisak(indeksi,imena,bodovi):
    imena = {sifra: ime for sifra, ime in imena}
    bodovi= {sifra: bodovi for sifra,bodovi in bodovi}
    
    return [[rb,sifra,imena[sifra],bodovi[sifra]] for rb,sifra in indeksi]


indeksi_test = [(1, 321), (2, 222), (3, 123)]
imena_test = [(123, "Jovan"), (222, "Jana"), (321, "Janko")]
bodovi_test = [(123, 85), (222, 55), (321, 70)]

rezultat = napraviSpisak(indeksi_test, imena_test, bodovi_test)

for stavka in rezultat:
    print(stavka)