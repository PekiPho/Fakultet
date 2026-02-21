

def pronadjiRec(nizovi,rec):
    red = len(nizovi)
    kolona = len(nizovi[0])
    broj_puteva=0


    def dfs(r,k,trenutno_slovo,poseceno):

        if r<0 or r>=red or k<0 or k>=kolona or nizovi[r][k]!=rec[trenutno_slovo] or (r,k) in poseceno:
            return 0
        
        if trenutno_slovo ==len(rec)-1:
            return 1
        
        poseceno.add((r,k))
        
        ukupno=0
        ukupno+=dfs(r+1,k,trenutno_slovo+1,poseceno)
        ukupno+=dfs(r-1,k,trenutno_slovo+1,poseceno)
        ukupno+=dfs(r,k+1,trenutno_slovo+1,poseceno)
        ukupno+=dfs(r,k-1,trenutno_slovo+1,poseceno)

        poseceno.remove((r,k))

        return ukupno

    for i in range(red):
        for j in range(kolona):
            if nizovi[i][j]==rec[0]:
                broj_puteva+=dfs(i,j,0,set())

    return broj_puteva


matrica = [['a', 'r', 'g', 'a'], ['g', 'e', 'č', 'a'], ['f', 'g', 'e', 'r'], ['f', 'g', 'h', 'm']]
print(pronadjiRec(matrica, 'reč'))


matrica_test = [
    ['M', 'A', 'M'],
    ['A', 'M', 'A'],
    ['M', 'A', 'M']
]
print(pronadjiRec(matrica_test, 'MAMA'))

