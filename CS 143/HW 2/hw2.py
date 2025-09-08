def get_col(pets: list, col: str) -> list:
    res = list()
    for pet in pets:
        res.append(pet[col])

    return res

def get_dogs(pets: list) -> list:
    res = list()
    for pet in pets:
        if pet['kind'] == 'dog':
            res.append(pet)

    return res

def is_dog(pet: dict) -> bool:
    return pet['kind'] == 'dog'

def selection(pets: list, f: callable) -> list:
    res = list()
    for pet in pets:
        if f(pet):
            res.append(pet)

    return res

def projection(pets: list, f: callable) -> list:
    res = list()
    for pet in pets:
        res.append(f(pet))

    return res

def cartesian(list1: list, list2: list) -> list:
    if list1 == list2:
        return list1
    
    res = list()
    for dict1 in list1:
        for dict2 in list2:
            res.append(dict1 | dict2)

    return res

def join(list1: list, list2: list, f: callable) -> list:
    return selection(cartesian(list1, list2), f)

def grouping1(pets: list) -> dict:
    res = {}
    for pet in pets:
        kind = pet['kind']
        if kind not in res:
            res[kind] = [pet]
        else:
            res[kind].append(pet)

    return res

def grouping2(pets: list, col: str) -> dict:
    res = {}
    for pet in pets:
        column = pet[col]
        if column not in res:
            res[column] = [pet]
        else:
            res[column].append(pet)

    return res

def groupby(pets: list, columns: list) -> dict:
    res = {}

    for pet in pets:
        tup = tuple(pet[column] for column in columns)
        if tup not in res:
            res[tup] = [pet]
        else:
            res[tup].append(pet)

    return res

def groupby_aggregate(table: list, names: list, agg: str, f: callable) -> dict:
    group = groupby(table, names)

    res = {}
    for group, rows in group.items():
        agg_col = [r[agg] for r in rows]

        res[group] = f(agg_col)

    return res

def y_to_z(S: list, y: str, z: str) -> dict:
    res = {}
    for row in S:
        res[row[y]] = row[z]

    return res

def R_join_S(R: list, S: list, x: str, y: str, z: str):
    S_dict = y_to_z(S, y, z)

    for row in R:
        print(row[x], S_dict[row[y]])

def y_to_z2(S: list, y: str, z: str) -> dict:
    res = {}
    for row in S:
        if row[y] not in res:
            res[row[y]] = [row[z]]
        else:
            res[row[y]].append(row[z])

    return res

def R_join_S2(R: list, S: list, x: str, y: str, z: str):
    S_dict = y_to_z2(S, y, z)

    for row in R:
        print(row[x], S_dict[row[y]])

def hashjoin(T1: list, T2: list, names: list) -> list:
    # basically we join the tables on the matching columns by merging the dicts

    group = {}
    for row in T2:
        key = tuple(row[name] for name in names)
        if key not in group:
            group[key] = [row]
        else:
            group[key].append(row)

    res = list()
    for row in T1:
        key = tuple(row[name] for name in names)
        if key in group:
            for dict in group[key]:
                res.append(row | dict)

    return res

pets = [
    {
        "name": "casa",
        "age": 8,
        "origin": "seattle",
        "kind": "cat",
        "person": "remy"
    },
    {
        "name": "luna",
        "age": 2,
        "origin": "seattle",
        "kind": "dog",
        "person": "remy"
    },
    {
        "name": "milo",
        "age": 1,
        "origin": "seattle",
        "kind": "dog",
        "person": "remy"
    },
    {
        "name": "gray",
        "age": 3,
        "origin": "california",
        "kind": "dog",
        "person": "leon"
    }
]

id = [
    {
        "userid": 222,
        "person": "leon"
    },
    {
        "userid": 9845,
        "person": "sound"
    },
    {
        "userid": 0,
        "person": "remy"
    }
]

info = [
    {
        "person": "leon",
        "origin": "california"
    },
    {
        "person": "sound",
        "origin": "texas"
    },
    {
        "person": "leon",
        "origin": "colorado"
    }
]

print(hashjoin(pets, id, ['person']))
