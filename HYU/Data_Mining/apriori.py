# 2011004095 Jongwon Lee

# This program's goal is to find association rules.
# We will give transaction lists(input.txt) and minimum support for input.
# Confidence of association rule doesn't make matter.
# After making the rules, 
# the program will make output.txt file that contains rule data.

# 0. Definite the global variables.
t_items = []
freq_itemset = []

# 1. Definite the function to load transaction lists.
# Transaction lists will be stored in list variable which is t_items.
# t_items is 2-dimensional list variable.
# ex1) t_items[3] means third transaction.
# ex2) t_items[3][4] means fourth item in third transaction.
# Calculate the total transaction number and store it in global variable.
# Return the list[][] that contains all transactions.
def load_transactions(input_file) : 
	with open(input_file) as f :
		t_items = []
		global total_sup
		total_sup = 0 
		for line in f :
			t_items.append([int(x) for x in line.split()])
			total_sup += 1
	return t_items
			
# 2. Definite the function to find frequent items.
# Scan all items in transaction and count the support number of it.
# And then only the items that are frequent are stored in list.
# Return the list of frequent items.
def find_freqItem(min_sup) :
	item_Num = []
	item_supNum = []
	freq_items = []
	for i in range(0, total_sup) :
		for j in range(0,len(t_items[i])) :
			if t_items[i][j] in item_Num :
				item_supNum[item_Num.index(t_items[i][j])] += 1
			else :
				item_Num.append(t_items[i][j])
				item_supNum.append(1)
	for i in range(0, len(item_Num)) : 
		if item_supNum[i] >= total_sup*min_sup/(100*1.0) :
			freq_items.append(item_Num[i])	
	return freq_items

# 3. Definite the function to make K-item-set from K-1-item-set.
# All sets in (K-1)-frequent-item-set are UNIONed each other.
# If the result-set's length is K and isn't checked before,
# 		check "Are its all subsets in (K-1)-frequent-item-set?"
#		--> Yes - add the result-set to candidate_itemset_list.
#		--> No - check others recursively.
# And then, add the result-set to already_checked.
# Return candidate_itemset_list.
def make_candidate_itemset(item_set_list, k) :
	candidate_itemset_list = []
	for i in range(0,len(item_set_list)-1) : 
		for j in range(i+1,len(item_set_list)) :
			new_set = item_set_list[i] | item_set_list[j]
			if (k==2) :
				candidate_itemset_list.append(new_set)
			elif (len(new_set) == k) : 
				if new_set not in candidate_itemset_list : 
					subset = map(set, itertools.combinations(new_set, k-1))
					subset.remove(item_set_list[i])
					subset.remove(item_set_list[j])
					for s in subset : 
						if s in item_set_list : 
							flag = 1
						else : 
							flag = 0
							break
					if flag == 1 :
						candidate_itemset_list.append(new_set)
	return candidate_itemset_list
				
# 4. Definite the function to find support number of an item-set.
# Make a transaction to set and then take intersection with target_set.
# If result_set of intersection equals target_set, it means target_set in that transaction.
# So increase count.
# Return count.
def find_supNum(target_set) :
	count = 0
	for i in range(0,total_sup) :
		transaction = set(t_items[i])
		intersection = target_set & transaction
		if target_set == intersection :
			count += 1
	return count

# 5. Main program source.
# import sys for use [sys.argv] to read arguments.
# import itertools for use [itertools.combination(s,k)] to make subset.
# Exception handling for the situation that not enough arguments is submitted.
import sys
import itertools

if len(sys.argv) != 4 :
	print "Please check your arguments."
	print "Arguments are minimum_support(%), input_file and output_file."
	exit(1)

min_sup = int(sys.argv[1])
input_file = sys.argv[2]
output_file = sys.argv[3]

print " - Load the transactions from input file."
t_items = load_transactions(input_file)
print " + Done."
print " - Find the frequent items(K=1)."
freq_items = find_freqItem(min_sup)
freq_items.sort()
print "   ",
print (freq_items)
print " + Done."

print " - Find the frequent item-set"
freq_items = set(freq_items)
beforeSet_list = map(set, itertools.combinations(freq_items, 1))
for k in range(2,len(freq_items)+1) :
	tmpSet_list = make_candidate_itemset(beforeSet_list, k)
	print "   ",
	print "Process about K = %d is progressing now." % k
	if len(tmpSet_list) == 0 : 
		# the case that there is no candidate item set.
		break
	afterSet_list = []
	for s in tmpSet_list :
		sup_Num = find_supNum(s)
		if sup_Num >= total_sup*min_sup/(100*1.0) :
			afterSet_list.append(s)
			freq_itemset.append(s)
	if len(afterSet_list) == 0 : 
		# the case that there is no frequent item set that's length is k.
		break
	beforeSet_list = afterSet_list
print " + Done."

print " - Find association rules from frequent item-set."
association_rule = []
print "   ",
print "Please wait..." 
for s in freq_itemset :
	s_sup = find_supNum(s)
	sup_percent = round(s_sup*100.0/total_sup, 2)
	for k in range(1,len(s)) :
		sub_set = map(set, itertools.combinations(s, k))
		for ss in sub_set :
			ds = s - ss
			ss_sup = find_supNum(ss)
			confi_percent = round(s_sup*100.0/ss_sup, 2)
			association_rule.append([ss, ds, sup_percent, confi_percent])
print " + Done."
print " + All process is done. Please check output.txt file."

# Make output.txt file and write the association rules.
with open("output.txt", 'w') as f :
	if len(association_rule) == 0 : 
		f.write("")
	else :
		for i in range(0,len(association_rule)) :
			s1 = list(association_rule[i][0])
			s2 = list(association_rule[i][1])
			data1 = "{"
			for j in range(0,len(s1)) :
				if j == len(s1) - 1 : 
					data1 += "%d}\t" % s1[j]
				else : data1 += "%d," % s1[j]
			data2 = "{"
			for k in range(0,len(s2)) :
				if k == len(s2) - 1 : 
					data2 += "%d}\t" % s2[k]
				else : data2 += "%d," % s2[k]
			data3 = "%0.2f\t" % association_rule[i][2]
			data4 = "%0.2f\n" % association_rule[i][3]
			f.write(data1+data2+data3+data4)


