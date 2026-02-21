

def mrv(domen):
    mrv_cvor = min(domen.keys(),key= lambda k:len(domen[k]))

    return mrv_cvor


def mrvCeo(domen,resenje=None):
    if resenje is None:
        resenje={}

    if not domen:
        return resenje

    trenutni = min(domen.keys(),key= lambda k:len(domen[k]))

    pokusaj=domen[trenutni]
    for boja in pokusaj:
        novi = {
            cvor: [b for b in boje if b != boja]
            for cvor, boje in domen.items() if cvor != trenutni
        }

        if any(len(b) ==0 for b in novi.values()):
            continue

        resenje[trenutni]=boja
        konacno=mrvCeo(novi,resenje)

        if konacno:
            return konacno
        
        del resenje[trenutni]

    return None


test_domen = {'A': ['red', 'green', 'blue'], 'B': ['red', 'green'], 'C': ['red']}
print(mrv(test_domen))

test = {
    'A': ['red', 'green', 'blue', 'yellow'],
    'B': ['red', 'green'],
    'C': ['red', 'green', 'blue']
}

print(mrvCeo(test))