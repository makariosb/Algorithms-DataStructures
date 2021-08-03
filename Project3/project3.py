import random


def addtolist(index, cards_list, card):
    """
    Adds a card to the hash table (cards_list) using open adressing and
    if there is a collision returns 1
    """
    if (cards_list[index] == 0):
        cards_list[index] = card
        return 0
    else:
        if (index == (87383 - 1)):  # if it's the last index of the table
            if(cards_list[index][0] == card[0]):
                cards_list[index][1] += card[1]  # add to the card's cost
                cards_list[index][2] += 1  # add a visit to the card
                return 0  # this doesn't count as a collision
            else:
                index = 0  # start from the top of the hash table
        for i in range(index, len(cards_list)-1):
            if (cards_list[i] == 0):
                cards_list[i] = card
                return 1
            elif (cards_list[i][0] == card[0]):  # find the previously hashed card
                cards_list[i][1] += card[1]  # add to the card's cost
                cards_list[i][2] += 1  # add a visit to the card
                return 0  # this doesn't count as a collision


def makecards(numberofcards, cards_list):
    """
    Takes an empty list and populates it with (numberofcards) lists that have a
    card_number string, a number for the total money spent with that card (cost)
    and a visits counter.
    As it populates the list it also keeps track of the collisions and finally
    returns the number of collisions that occured while creating the hash table
    """
    random.seed(1234567)
    numbers = "1234567890123456"
    letters = "ABCD"
    number_list = []
    collisions = 0

    for i in numbers:
        number_list.append(i)
    for i in range(0, numberofcards):
        positions = []
        for j in range(0, len(letters)):
            numberstring_index = random.randrange(0, len(numbers))
            while (numberstring_index in positions):
                numberstring_index = random.randrange(0, len(numbers))
            positions.append(numberstring_index)
        card_number = number_list.copy()
        for j in range(0, len(positions)):
            card_number[positions[j]] = letters[j]
        card_number = "".join(card_number)
        index = polyhash(card_number)
        cost = random.randrange(10, 1000)
        card = [card_number, cost, 0]  # card is a list with the number of the
        # card as a string, the cost(card[1]) and the number of visits (card[2])
        collision_flag = addtolist(index, cards_list, card)
        if collision_flag == 1:
            collisions += 1
            collision_flag = 0
    return collisions


def horner(x, coefficients):
    """
    Evaluates a polynomial f(x) wich is described by a list of its coefficients
    using Horner's method
    """
    result = 0
    for coefficient in coefficients:
        result = result * x + coefficient
    return result


def polyhash(input_string):
    """
    Hashes a string using each of its characters' ASCII number as a coefficient
    of a polynomial and then evaluating it using Horner's method at x = 33
    """
    coeff = []
    for i in input_string:
        coeff.append(ord(i))
    return horner(33, coeff) % 87383


def find_largest(cards_list):
    """
    Finds the hash table index of the largest spender and visitor and then returns
    them as a list
    """
    largest_spender_index = 0
    largest_visitor_index = 0
    max_cost = 0
    max_visits = 0
    for i in range(0, len(cards_list)):
        if (cards_list[i] == 0):
            continue
        else:
            if(cards_list[i][1] > max_cost):
                max_cost = cards_list[i][1]
                largest_spender_index = i
            if(cards_list[i][2] > max_visits):
                max_visits = cards_list[i][2]
                largest_visitor_index = i
    return [largest_spender_index, largest_visitor_index]


def main():
    # size of table prime_number = 87383;
    numberofcards = 1000000
    cards = [0] * 87383
    collisions = makecards(numberofcards, cards)
    [spender, visitor] = find_largest(cards)
    print('Number of collisions: %d' % collisions)
    print('Largest spender is %s with %d $ spent.' %
        (cards[spender][0], cards[spender][1]))
    print('Largest visitor is %s with %d visits.' %
        (cards[visitor][0], cards[visitor][2]))


if __name__ == "__main__":
    main()
