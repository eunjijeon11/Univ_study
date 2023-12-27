def devide_matrix(matrix, x, y):
    new_size = int(len(matrix)/2)
    new_matrix = [[matrix[x*new_size+j][y*new_size+i] for i in range(new_size)] for j in range(new_size)]
    return new_matrix

def addition(a, b):
    c = [[] for _ in range(len(a))]
    for i in range(len(a)):
        for j in range(len(a)):
            c[i].append(a[i][j]+b[i][j])
    return c

def subtraction(a, b):
    c = [[] for _ in range(len(a))]
    for i in range(len(a)):
        for j in range(len(a)):
            c[i].append(a[i][j]-b[i][j])
    return c

def concat(a, b):
    for i in range(len(a)):
        a[i] = a[i] + b[i]
    return a

def strassen(a, b):

    if (len(a) == 1):
        return [[a[0][0]*b[0][0]]]
    
    a00 = devide_matrix(a, 0, 0)
    a01 = devide_matrix(a, 0, 1)
    a10 = devide_matrix(a, 1, 0)
    a11 = devide_matrix(a, 1, 1)

    b00 = devide_matrix(b, 0, 0)
    b01 = devide_matrix(b, 0, 1)
    b10 = devide_matrix(b, 1, 0)
    b11 = devide_matrix(b, 1, 1)

    m1 = strassen(addition(a00, a11), addition(b00, b11))
    m2 = strassen(addition(a10, a11), b00)
    m3 = strassen(a00, subtraction(b01, b11))
    m4 = strassen(a11, subtraction(b10, b00))
    m5 = strassen(addition(a00, a01), b11)
    m6 = strassen(subtraction(a10, a00), addition(b00, b01))
    m7 = strassen(subtraction(a01, a11), addition(b10, b11))

    c00 = subtraction(addition(addition(m1, m4), m7), m5)
    c01 = addition(m3, m5)
    c10 = addition(m2, m4)
    c11 = subtraction(addition(addition(m1, m3), m6), m2)

    return concat(c00, c01) + concat(c10, c11)

a = [[10, 8], [12, 11]]
b = [[4, 9], [8, 13]]

print(strassen(a, b))
