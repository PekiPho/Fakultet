

def pretvori(recenica):
    reci = recenica.split()
    duzine = set(len(r) for r in reci)

    return {d: [r.upper() if len(r)>= 5 else r.lower() for r in reci if len(r)==d] for d in duzine}


print(pretvori("The Quick Brown Fox Jumps Over The Lazy Dog."))