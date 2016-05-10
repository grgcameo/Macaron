print 'Simple Assignment'
shoplist = ['apple', 'mango', 'carrot', 'banana']

print 'original shoplist is', shoplist

#mylist is just another name pointing to the same object
print 'mylist = shoplist'
mylist = shoplist

#I purchased the fist item, so I remove it from the list
#del shoplist[0]
del mylist[0]

print 'shoplist is', shoplist
print 'mylist is', mylist

#Notice that both shoplist and mylist both print
#the same list without the 'apple' confirming that
#they point to the same object
print
print 'Copy by making a full slice'
#Make a copy by doing a full slice

print 'mylist = shoplist[:]'
mylist = shoplist[:]
#Remove first item
del mylist[0]

print 'shoplist is', shoplist
print 'mylist is', mylist
#Notice that now the two lists are different
