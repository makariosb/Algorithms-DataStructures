import random
def makecards(numberofcards):
    numbers = "1234567890123456"
    letters = "ABCD"
    number_list = []
    cards_list = []
    for i in numbers:
        number_list.append(i)
    for i in range(0,numberofcards):
        positions = []
        for j in range(0,len(letters)):
            numberstring_index = random.randrange(0,len(numbers))
            while (numberstring_index in positions):
                numberstring_index = random.randrange(0,len(numbers))
            positions.append(numberstring_index)
        card = number_list.copy()
        for j in range(0,len(positions)):
            card[positions[j]] = letters[j]
        card = "".join(card)
        cards_list.append(card)
    return cards_list

def horner(x, coefficients):
    result = 0
    for coefficient in coefficients:
        result = result * x + coefficient
    return result

def polyhash(input_string):
    coeff = []
    for i in input_string:
        coeff.append(ord(i))
    return horner(33,coeff)


numberofcards = 1000
cards = makecards(numberofcards)
print(cards[0])
print(cards.count(cards[0]))
print(polyhash(cards[0]))
