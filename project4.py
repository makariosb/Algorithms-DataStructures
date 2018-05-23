import random
from time import time
#from sympy import nextprime
random.seed(1046895)
from math import sqrt
from math import ceil
#Creates 2 arrays of length n between wich the first half is the same and the
#second half is different random generated integers in range(0,10*n).
#Returns the generated sets of numbers.
def makesets(n):
    set1 = []
    set2 = []
    for i in range(0,n//2):
        num = random.randrange(0,10*n)
        set1.append(num)
        set2.append(num)
    for i in range(0,n//2 + n%2):
        set1.append(random.randrange(0,10*n))
        set2.append(random.randrange(0,10*n))
    return set1,set2

#Evaluates a polynomial f(x) wich is described by a list of its coefficients
#using Horner's method
def horner(x, coefficients):
    result = 0
    for coefficient in coefficients:
        result = result * x + coefficient
    return result

#Hashes an integer using each of its digits as coefficients
#of a polynomial and then evaluating it using Horner's method at x = 33
def polyhash(input_int):
    str_input = str(input_int)
    coeff = []
    for i in str_input:
        coeff.append(int(i))
    return horner(33,coeff)

#Executes a linear search algorithm to determine how many of the values of set1
#are present in set2 and returns their count.
def linsearch(set1,set2):
    t = time()
    common_numbers = 0
    for i in set1:
        for j in range(0,len(set2)):
            if (i == set2[j]):
                common_numbers += 1
                break
    t = time()-t
    print('Linear Search ran for %0.7f sec.'%t)
    return common_numbers

#Creates a hash table using open addressing as a colission dealing method.
#The original integers are hashed using polynomial hashing (polyhash)
#and then modded to the desired limits. Uses the nextprime function
#in order to calculate the next biggest prime number after 2*len(set2) .
#Finally it returns the hash table that was created.
def hashtable_open_addr(set2):
    table_size = nextprimefind(2*len(set2))
    table = [-1]*table_size
    collisions = 0
    for val in set2:
        index = polyhash(val) % table_size
        j = index
        if (table[j] != -1):
            collisions += 1
        while(True):
            if(j == table_size-1):
                if (table[j] == -1):
                    table[j] = val
                    break
                elif (table[j] == val):
                    break
                else:
                    j = 0
                    continue
            else:
                if(table[j] == -1):
                    table[j] = val
                    break
                elif (table[j] == val):
                    break
                else:
                    j += 1
                    continue
    print('Open Addressing Collisions: %d' %collisions)
    return table

#Creates a hash table using chaining as a colission dealing method. The original
#integers are hashed using polynomial hashing polyhash().
#Finally it returns the hash table that was created.
def hashtable_chaining(set2):
    table_size = nextprimefind(2*len(set2))
    table = [[]]*table_size
    collisions = 0
    for val in set2:
        index = polyhash(val)%table_size
        table_chain = table[index].copy()
        if (table_chain != []):
            collisions += 1
        if(val in table_chain):
            continue
        else:
            table_chain.append(val)
            table[index] = table_chain
    print('Chaining Collisions : %d' %collisions)
    return table

#Searches a hash table, wich uses open addressing, for a given value and
#returns 1 if it is found.
def open_addr_search(table,value):
    index = polyhash(value) % len(table)
    j = index
    while(True):
        if (table[j] == -1):
            return 0
        elif(j == len(table)-1):
            if(table[j] == value):
                return 1
            else:
                j = 0
                continue
        else:
            if(table[j] == value):
                return 1
            else:
                j += 1
                continue
#Searches a hash table, wich uses chaining, for a given value and returns 1 if
#it is found.
def chain_search(table,value):
    index = polyhash(value) % len(table)
    if value in table[index]:
        return 1
    else:
        return 0

#Creates the two hash tables (one w/ open addressing and one w/ chaining method)
#then counts how many of the values of set1 are hashed in those tables and
#returns the counted amounts.
def hash_searches(set1,set2):
    open_table = hashtable_open_addr(set2)
    open_count = 0
    chain_table = hashtable_chaining(set2)
    chain_count = 0

    t = time()
    for val in set1:
        open_count += open_addr_search(open_table,val)
    print('Open addresing Search ran for %0.7f sec.'%(time() - t))

    t = time()
    for val in set1:
        chain_count += chain_search(chain_table,val)
    print('Chaining Search ran for %0.7f sec.'%(time() - t))

    return open_count,chain_count


#Merges two subarrays of arr[] in a sorted fashion.
#First subarray is arr[l:mid]
#Second subarray is arr[mid+1:r]
#Overwrites the original array
def merge_subarr(array, l, mid, r):
    #Subarray sizes
    n1 = mid - l + 1
    n2 = r - mid

    #Temporary array creation
    L = [0] * n1
    R = [0] * n2

    #Copy data to temporary arrays L[] and R[]
    for i in range(0 , n1):
        L[i] = array[l+i]

    for i in range(0 , n2):
        R[i] = array[mid+1+i]

    #Merge the temporary arrays back into arr[l:r] in a sorted fashion
    l_index = 0 #Initial index of left subarray
    r_index = 0 #Initial index of right subarray
    arr_index = l #Initial index of merged subarray

    while l_index < n1 and r_index < n2 :
        if L[l_index] <= R[r_index]:
            array[arr_index] = L[l_index]
            l_index += 1
        else:
            array[arr_index] = R[r_index]
            r_index += 1
        arr_index += 1

    #Copy the remaining elements of L[] and R[], if there are any
    while l_index < n1:
        array[arr_index] = L[l_index]
        l_index += 1
        arr_index += 1

    while r_index < n2:
        array[arr_index] = R[r_index]
        r_index += 1
        arr_index += 1

#Executes a merge sorting algorithm recursively
#inputs are the array to be sorted, the leftmost element of the array and the
#rightmost element of the array.
def merge_sort(array,l,r):
    if l < r:
        mid = (l+r)//2

        # Sort first and second halves
        merge_sort(array, l, mid)
        merge_sort(array, mid+1, r)
        merge_subarr(array, l, mid, r)

#Executes a binary search for the given value in a sorted array
#Returns 1 if found else returns 0
def binsearch(sorted_arr,value):
    l = 0 #leftmost index
    r = len(sorted_arr)-1 #rightmost index
    mid = (r+l)//2  #middle index


    while(l <= r):
        if(sorted_arr[mid] == value):
            return 1
        if(sorted_arr[mid] < value):
            l = mid + 1
        else:
            r = mid - 1
        mid = (r+l)//2
    return 0

#Sorts set2 then uses the binsearch function to count how many values of set1
#are present in set2 and returns the counted sum.
def bin_count(set1,set2):
    merge_sort(set2,0,len(set2)-1)
    t = time()
    bincounter = 0
    for val in set1:
        bincounter += binsearch(set2,val)
    print('Binary Search ran for %0.7f sec.'%(time()-t))
    return bincounter

#Checks if a number is prime.
def checkprime(num):
    if(sqrt(num).is_integer()):
        return 0
    for i in range(2,ceil(sqrt(num))+1):
        if(num%i==0):
            return 0
    return 1
    pass

#Finds the next largest prime number from num.
def nextprimefind(num):
    isprime = checkprime(num)
    i = num+1
    while(isprime==0):
        if(checkprime(i)==1):
            return i
        i+=1
    return num

#main
n = 100000 #size of the random number sets
set1,set2 = makesets(n)
print('Number Set size (N) is:  %d' %n)
#print('Linear Search found %d common numbers\n-----' %linsearch(set1,set2))
open_addr,chaining = hash_searches(set1,set2) #counts using hash tables
print('Hashing with Open addresing search found: %d common numbers' %open_addr)
print('Hashing with Chaining search found %d common numbers\n-----' %chaining)
#print('Merge Sort and then Binary Search found %d common numbers'%bin_count(set1,set2))
