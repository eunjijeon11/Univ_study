import random

x = []
y = []

for i in range(30):
    while(True):
        temp = random.random() * 10
        if temp not in x:
            x.append(temp)
            break
    while(True):
        temp = random.random() * 10
        if temp not in y:
            y.append(temp)
            break

## main

for i in range(len(x)):
    for j in range(len(x)-1):
        if (x[j] > x[j+1]):
            temp = x[j]
            x[j] = x[j+1]
            x[j+1] = temp
            temp = y[j]
            y[j] = y[j+1]
            y[j+1] = temp

def distance(x1, x2, y1, y2):
    return ((x1-x2)**2 + (y1-y2)**2)**(1/2)

def find_min(x, y):
    x1, x2, d = -1, -1, 10
    for i in range(len(x)):
        for j in range(len(x)):
            if i==j: continue
            if (d > distance(x[i], x[j], y[i], y[j])):
                x1 = i
                x2 = j
                d = distance(x[i], x[j], y[i], y[j])
    return x1, x2, d

def closest_pair(x, y):
    if (len(x) <= 3):
        return find_min(x, y)
        
    divide = int(len(x)/2)
    x1_1, x1_2, d1 = closest_pair(x[:divide], y[:divide])
    x2_1, x2_2, d2 = closest_pair(x[divide:], y[divide:])
    x2_1 += divide
    x2_2 += divide
    
    line = (x[divide-1] + x[divide]) / 2
    d = min(d1, d2)
    strip_x = []
    strip_y = []
    start = -1
    for i in range(len(x)):
        if (abs(x[i] - line) < d):
            if (start == -1): start = i
            strip_x.append(x[i])
            strip_y.append(y[i])
            
    x3_1, x3_2, d3 = find_min(strip_x, strip_y)
    x3_1 += start
    x3_2 += start

    min_x1, min_x2, d = x1_1, x1_2, d1
    if (d > d2): min_x1, min_x2, d = x2_1, x2_2, d2
    if (d > d3): min_x1, min_x2, d = x3_1, x3_2, d3

    return min_x1, min_x2, d

x1, x2, d = closest_pair(x, y)
print("closest pair:", (x[x1], y[x1]), (x[x2], y[x2]))
print("distance:", d)
