# Algorithms and Data Structures Course Projects
These small homework projects were developed in 2018 for the Algorithms & Data Structures class of my Electrical & Computer Engineering studies in University of Patras.

---

## Project 1 
For a vector of arbitrary size, find the largest sum of all it's sub-vectors, using an algorithm of complexity O(N^3), O(N^2) and O(N) respectively and compare the time of execution of each algorithm, as the input vector size increases.

The input vector is generated **statically** using random integer values in the range [-9 , 9]. 

Developed in C, the initial vector size and the rand() seed value can be set using the `ARRSIZE` and `ARR_SEED` constants respectively.

---

## Project 2
In a grid of approximately the size of Europe, an arbitrary amount of points that represent airport locations are generated, minding that no 2 points are less than 100km apart.

Then an arbitrary amount of connections between these points are generated and encoded into <u>**sparse matrix**</u> form, using the IDs of the start and destination airports.

Finally, a simple algorithm is implemented, that calculates the shortest connection for each airport and finally sums all the minimum paths.

Developed in C. The number of generated airports and connections between them can be set using the `NUM_AIRPORTS` and `NUM_CONNECTIONS` constants. 

Complimentary functions used for debugging are included in [project2_extra_functions.c](Project2/project2_extra_functions.c)

---

## Project 3
We begin by generating 1 million credit card transactions (card number and cost of transaction).

The card number string for each transaction is then hashed using polynomial hashing. The hash is then used to store the transaction in a **hash table**.

When appending to the hash table the following rules apply:
- If a 2 cards have a matching hash, a *collision* is counted, and remediated using the *open addressing* technique.

- Transactions using the same card number do not count as collisions. In this case the visits count of that card is incremented and the cost of the transaction is added to the existing cost for that card number.

The program finishes displaying the total number of collisions that happened during the creation of the hash table, the card with the largest amount spent and the card with the most visits.

<u>__Paradoxically__</u> (as this is an excercise on hash tables) the scenario we were given **cannot** utilise the biggest strength of hash tables, which is their ability to be searched in an *O(1)* fashion. 
This is because the properties we have search for (largest spender & most frequent visitor) **are not deterministic**, so a sorting algorithm has to be used in order to calculate the argmax in each case.

Developed in Python 3.6

---

## Project 4
We begin by generating 2 sets of numbers, that have at least half their elements in common (same values).

Afterwards we use four different approaches to determine the number of common numbers in these two sets:
1) **Linear search** ( **O{N^2}** )

2) **Hash table using open addressing** to deal with collisions ( **O{1}** )

3) **Hash table using chaining** to deal with collisions( **O{1}** )

4) Sorting one of the two sets using **merge sort** and then **binary searching** each element of the unsorted set in the sorted one ( **O{N\*log(N)}** )

The algorithms are timed, and the results, as well as the returned values are printed for comparison. In the case of hash tables, the number of collisions is also counted and printed for comparison.

Developed in Python 3.6.

---


- Included in each project folder is the relevant report I authored (in modern greek).

- Python codes are formatted using the [PEP 8 Style Guide](https://pep8.org/)