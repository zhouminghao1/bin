L = [('Bob', 75), ('Adam', 92), ('Bart', 66), ('Lisa', 88)]
def by_name(t):
    t=t[0].lower()
    return t
L2 = sorted(L, key=by_name)
print(L2)
def by_score(t):
    t = t[1] #从低到高
    #t = -t[1] #从高到低
    return t
L3 = sorted(L, key = by_score)
print(L3) 