rules = {
    1:
    {
        'left': 'A',
        'right': '!B!'
    },
    2: 
    {
        'left': 'B',
        'right': 'TB\''
    },
    3: 
    {
        'left': 'B\'',
        'right': 'e'
    },
    4: 
    {
        'left': 'B\'',
        'right': '+TB\''
    },
    5: 
    {
        'left': 'T',
        'right': 'MT\''
    },
    6: 
    {
        'left': 'T\'',
        'right': 'e'
    },
    7: 
    {
        'left': 'T\'',
        'right': '*MT\''
    },
    8: 
    {
        'left': 'M',
        'right': 'a'
    },
    9: 
    {
        'left': 'M',
        'right': 'b'
    },
    10: 
    {
        'left': 'M',
        'right': '(B)'
    }
}

T = ['!', '+', '*', '(', ')', 'a', 'b']
N = ['A', 'B', 'B\'', 'T', 'T\'', 'M']

cols = len(T) + 1 # число столбцов
rows = len(N) + len(T) + 1  # число строк


def form_table():
    table = [[0]*cols for _ in range(rows)]

    for i in range(1, cols):
        table[0][i] = T[i - 1]
    
    j = 0
    for i in range(1, rows):
        if (i < len(N) + 1):
            table[i][0] = N[i - 1]
        elif (i < rows):
            table[i][0] = T[j]
            j += 1 

    j = 1
    for i in range (len(N) + 1, rows):
        table[i][j] += -1
        j += 1
    
    table[1][1] = 1
    table[2][4] = 2; table[2][6] = 2; table[2][7] = 2
    table[3][1] = 3; table[3][2] = 4; table[3][5] = 3
    table[4][4] = 5; table[4][6] = 5; table[4][7] = 5
    table[5][1] = 6; table[5][2] = 6; table[5][3] = 7; table[5][5] = 6
    table[6][4] = 10; table[6][6] = 8; table[6][7] = 9

    return table

table = form_table()

def addtostack(stack, new): # добавить в стек
    if 'T\'' in new:
        new = new.replace('T\'', 'Y')
    elif 'B\'' in new:
        new = new.replace('B\'', 'V')

    # stack.insert(0, new)
    # first_element = stack.pop(0)
    stack = stack[1:]
    stack = list(new) + stack

    # Замена символов в стеке после добавления нового элемента
    stack = [x.replace('Y', 'T\'') for x in stack]
    stack = [x.replace('V', 'B\'') for x in stack]

    return stack


def ejection(string, stack): # выброс
    string = string[1:]
    stack.pop(0)
    return string, stack
   

def algorithm(string):
    stack = ['A']
    pi = []
    while stack and string: # проверка, что стек и строка не пусты
        if string[0] not in T:  # проверка, что текущий символ входит в алфавит T
            return f'Error: the character "{string[0]}" does not belong to the input alphabet'
        
        if stack[0] == 'e': #если 1 символ стека е, то его мы удаляем 
            stack.pop(0)
        else: # иначе находим ключ в таблице, который соответствует правилу, которое мы будем использовать
            for i in range(len(table)):
                if table[i][0] == stack[0]:
                    break
            for j in range(len(table[0])):
                if table[0][j] == string[0]:
                    break
            key = table[i][j]
            if key == 0:
                return 'Error: the rule is missing'
            elif key == -1:
                string, stack = ejection(string, stack)
            else:
                pi.append(key)
                stack = addtostack(stack, rules[key]['right'])
        if stack and stack[0] == string[0]:
            string, stack = ejection(string, stack)
    
    if not stack and not string:  # Если и стек, и строка пусты
        return pi
    else:
        return 'Error: unexpected end of a line or stack'
