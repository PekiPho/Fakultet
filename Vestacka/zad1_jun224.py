

def mrv(domen,resenje=None):
    if resenje is None:
        resenje = {}

    if not domen:
        return resenje
    
    trenutni = min(domen.keys(), key = lambda k: len(domen[k]))

    pokusaj = domen[trenutni]
    for boja in pokusaj:

        novi_domen = {cvor : [b for b in boje if b!=boja] for cvor,boje in domen.items() if cvor != trenutni}

        if any(len(b) ==0 for b in novi_domen.items()):
            continue

        resenje[trenutni] = boja
        konacno = mrv(novi_domen,resenje)

        if konacno:
            return konacno
        
        del resenje[trenutni]
    return None



test = {
    'A': ['red', 'green', 'blue', 'yellow'],
    'B': ['red', 'green'],
    'C': ['red', 'green', 'blue']
}

print(mrv(test))