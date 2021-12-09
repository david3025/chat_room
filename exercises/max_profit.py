#--------------------------get_profit---------------------------
import sys

def get_profit(l):
    j=0
    maxnum = -sys.maxsize - 1
    first=l[0]
    
    for i in range(1,len(l)):
    
        distance =l[i] - l[j]
        
        if distance > maxnum:
            maxnum = distance
        if l[i] < first:
            j=i
            first = l[i]
    return maxnum

def test_get_profit():
    list=[10,19,35,1,20]
    print(get_profit(list))



#--------------------------one_plus---------------------------
def plusone1(digits):
    size = len (digits)
    sum = 0
    for i in range(size):
        #sum += sum*10 + digits[i]
        
        sum += digits[i]*pow(10,size - i -1)
    sum += 1
    return [int(i) for i in str(sum)]

def plusone2(digits):
    size = len(digits)
    for i in range(size-1,0,-1):
        if digits[i] != 9:
            digits[i] += 1
            break
        else:
            digits[i] = 0
    if digits[0] == 9:
        digits[0] = 0
        digits = [1] + digits
    return digits
            
def testplusone():
    digits1 = [1,2,4]
    digits2=[1,2,9,4,9]
    digits3 = [9,9,9,9]
    print(plusone2(digits2))       

#--------------------------max_continuous_sub-----------------------------
import sys

def max_continuous_sub(list):
    size = len(list)
    max = -sys.maxsize - 1
    total = list[0]
    for i in range(1,size):
        if list[i] > total and total < 0:
            total = 0
        total += list[i]
        if total > max:
            max = total
    return max

def test_max_continuous_sub():
    list1 = [3,-2,3,-4,1]
    list2 = [1,2,3]
    list3 = [1,-2,2,-3,-4]
    print(max_continuous_sub(list3))

#--------------------------kfibonachi-----------------------------
def k_bonacci(n, k):

    if n ==  0:
        return 0
        
    lst = [None] * k

    for i in range(k):
            lst[i] = i

    for i in range(n-k+1):
        lst_sum = sum(lst)
        lst.pop(0)
        lst.append(lst_sum)
       
    return lst[-1]

print(k_bonacci(5,3))
print(k_bonacci(0,2))
print(k_bonacci(7,2))
print(k_bonacci(5,3))
print(k_bonacci(7,3))
print(k_bonacci(0,9))
print(k_bonacci(9,9))
print(k_bonacci(0,3))
print(k_bonacci(0,2))



#--------------------------sort_colors-----------------------------


#--------------------------main-----------------------------

def main():
    pass
     
if __name__ == "__main__":
    main()
