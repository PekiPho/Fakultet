
def prekidaci(a):
    n = len(a)

    grupe="".join('1' if x else '0' for x in a).split('0')

    return [1 if len(g)%2==0 else 2 for g in grupe if len(g)>0]


A = [True, True, True, False, True, True]
print(prekidaci(A))