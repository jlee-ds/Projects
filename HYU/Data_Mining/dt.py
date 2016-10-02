# 2011004095 Lee Jongwon

# This program's goal is to build decision tree.
# We will give training set(dt_train.txt) and testing set(dt_test.txt).
# the program will make dt_result.txt file that contains testing set that classified.

import sys			# For arguments control
import math			# For log function
import copy			# For data copy

# Load training set from the first argument file.
# Store the training set in TRAIN_SET.
def load_train_set(input_file) : 
	TRAIN_SET = list();
	with open(input_file) as f :
		for line in f :
			TRAIN_SET.append([str(x) for x in line.split()]);
	return TRAIN_SET

# Load test set from the second argument file.
# Store the test set in TEST_SET.
def load_test_set(input_file) :
	TEST_SET = list();
	with open(input_file) as f :
		f.readline();
		for line in f :
			TEST_SET.append([str(x) for x in line.split()]);
	return TEST_SET

# Count number of attribute's value and class_attribute's value on remained set.
# Store the attribute's value as Key and the count as Value.
# Classify the row about attribute and class_attribute and count how many.
def get_attr_cattr_class(attr, C_attr, R_row) :
	ATTR_N = {};
	C_ATTR_N = {};
	CLASS_N = {};
	for row in R_row :
		if row[attr] not in ATTR_N.keys() :
			CLASS_N[row[attr]] = {};
			ATTR_N[row[attr]] = 1;
		else :
			ATTR_N[row[attr]] += 1;
		if row[C_attr] not in C_ATTR_N.keys() :
			C_ATTR_N[row[C_attr]] = 1;
		else :
			C_ATTR_N[row[C_attr]] += 1;
		if row[C_attr] not in CLASS_N[row[attr]].keys() :
			CLASS_N[row[attr]][row[C_attr]] = 1;
		else :
			CLASS_N[row[attr]][row[C_attr]] += 1;
	return [ATTR_N, C_ATTR_N, CLASS_N];

# Get information gain about a certain attribute.
def get_info_gain(attr, C_attr, R_row) :
	BEFOREINFO = 0.0;
	AFTERINFO = 0.0;
	SPLITINFO = 0.0;
	TOTALNUM = len(R_row);
	ATTR_CATTR_CLASS = get_attr_cattr_class(attr, C_attr, R_row);
	ATTR_N = ATTR_CATTR_CLASS[0];
	C_ATTR_N = ATTR_CATTR_CLASS[1];
	CLASS_N = ATTR_CATTR_CLASS[2];

	for ckey in C_ATTR_N.keys() :
		P = C_ATTR_N[ckey] * 1.0 / TOTALNUM;
		BEFOREINFO += (-P) * (math.log(P,2));
	
	for akey in ATTR_N.keys() :
		NUM = ATTR_N[akey]
		DP = NUM * 1.0 / TOTALNUM;
		EACHINFO = 0.0
		EACHGINI = 1.0
		for ckey in CLASS_N[akey].keys() :
			P = CLASS_N[akey][ckey] * 1.0 / NUM;
			EACHINFO += (-P) * (math.log(P,2));
		AFTERINFO += DP * EACHINFO;
		SPLITINFO += (-1.0) * DP * (math.log(DP,2));  
	
	#print ATTR_N
	#print C_ATTR_N
	#print CLASS_N
	#print "Info(D) : ",
	#print BEFOREINFO
	#print "Info_A(D) : ",
	#print AFTERINFO
	#print "Gain(A) : ",
	#print (BEFOREINFO - AFTERINFO)
	print attr + "'s GainRatio(A) : ",
	print ((BEFOREINFO - AFTERINFO) / SPLITINFO); 

	#return BEFOREINFO - AFTERINFO;					# For Information Gain
	return (BEFOREINFO - AFTERINFO) / SPLITINFO; 	# For Gain Ratio

# Compare the information gains of remained attributes.
# The attribute that has maximum info_gain is returned.
def get_best_attr(R_attr, C_attr, R_row) :
	BESTATTR = "";
	REMAINDER = get_info_gain(R_attr[0], C_attr, R_row);
	BESTATTR = R_attr[0]
	for i in range(1,len(R_attr)) :
		TMP = get_info_gain(R_attr[i], C_attr, R_row)
		if REMAINDER < TMP :
			REMAINDER = TMP;
			BESTATTR = R_attr[i];
	print "Spliting attribute is " + BESTATTR
	return BESTATTR;

# Get majority of remained rows.
def get_majority(C_attr, R_row) :
	C_ATTR_N = {};
	MAJORITY = "";
	NUM = 0;
	for row in R_row :
		if row[C_attr] not in C_ATTR_N.keys() :
			C_ATTR_N[row[C_attr]] = 1;
		else :
			C_ATTR_N[row[C_attr]] += 1;
	for key in C_ATTR_N.keys() :
		TMP = C_ATTR_N[key];
		if TMP > NUM :
			MAJORITY = key;
			NUM = TMP;
	return MAJORITY;

# Make decision tree and store it in DECISION_TREE which is dictionary.
def get_decision_tree(R_attr, C_attr, R_row) :
	PP = 99.99; 			# Pruning Percent. 
	CLASSNUM = {};
	CLASSDP = {};
	TOTALNUM = len(R_row);
	for row in R_row :
		if row[C_attr] not in CLASSNUM.keys() :
			CLASSNUM[row[C_attr]] = 1;
		else :
			CLASSNUM[row[C_attr]] += 1;
	for key in CLASSNUM.keys() :
		CLASSDP[key] = CLASSNUM[key] * 100.0 / TOTALNUM;
	if len(CLASSNUM) == 1 :
		return CLASSNUM.keys()[0];
	else : 
		for key in CLASSDP.keys() :
			if CLASSDP[key] > PP : 
				return key;
	if len(R_attr) == 0 :
		return get_majority(C_attr, R_row);
	DECISION_TREE = {};
	BESTATTR = get_best_attr(R_attr, C_attr, R_row);
	DECISION_TREE[BESTATTR] = {};
	DIVIDE_ROW = {};
	REMAIN_ATTR = copy.deepcopy(R_attr);
	REMAIN_ATTR.remove(BESTATTR);
	for row in R_row :
		if row[BESTATTR] not in DIVIDE_ROW.keys() :
			DIVIDE_ROW[row[BESTATTR]] = list();
		DIVIDE_ROW[row[BESTATTR]].append(row);
	for key in DIVIDE_ROW.keys() :
		DECISION_TREE[BESTATTR][key] = get_decision_tree(REMAIN_ATTR, C_attr, DIVIDE_ROW[key]);
	DECISION_TREE[BESTATTR][None] = get_majority(C_attr, R_row)
	print DECISION_TREE
	return DECISION_TREE

# Travel decision tree with one test set.
# Classify it and return the class.
def get_class(d_tree, T_row) :	
	if not isinstance(d_tree, dict) :
		return d_tree;
	else :
		for key in d_tree.keys() :
			if T_row[key] not in d_tree[key].keys() :
				return d_tree[key][None]
			elif isinstance(d_tree[key][T_row[key]], dict) :
				return get_class(d_tree[key][T_row[key]], T_row)
			else :
				return d_tree[key][T_row[key]]

# ------------------------- MAIN FUNCTION -------------------------

TRAIN_FILE = sys.argv[1];
TEST_FILE = sys.argv[2];
RESULT_FILE = "dt_result.txt"

TRAIN_LIST = load_train_set(TRAIN_FILE);
TEST_LIST = load_test_set(TEST_FILE);
ATTR = copy.deepcopy(TRAIN_LIST[0]);
ATTR_NUM = len(ATTR);
TRAIN_LIST.remove(TRAIN_LIST[0]);

TRAIN_DIC = {};
TRAIN_DIC_LIST = list();
for row in TRAIN_LIST :
	for i in range(ATTR_NUM) :
		TRAIN_DIC[ATTR[i]] = row[i];
	TRAIN_DIC_LIST.append(copy.deepcopy(TRAIN_DIC));

TEST_DIC = {};
TEST_DIC_LIST = list();
for row in TEST_LIST :
	for i in range(ATTR_NUM-1) :
		TEST_DIC[ATTR[i]] = row[i];
	TEST_DIC_LIST.append(copy.deepcopy(TEST_DIC));

#REMAINDER = get_info_gain(ATTR[0], ATTR[ATTR_NUM-1], TRAIN_DIC_LIST)
#BESTATTR = get_best_attr(ATTR[0:ATTR_NUM-1], ATTR[ATTR_NUM-1], TRAIN_DIC_LIST)
#MAJORITY = get_majority(ATTR[ATTR_NUM-1], TRAIN_DIC_LIST)

#print ATTR[0:ATTR_NUM-2]
#print TRAIN_DIC_LIST
#print TEST_DIC_LIST
#print REMAINDER
#print BESTATTR
#print MAJORITY

DECISION_TREE = get_decision_tree(ATTR[0:ATTR_NUM-1], ATTR[ATTR_NUM-1], TRAIN_DIC_LIST)
with open(RESULT_FILE, 'w') as f :
	new_attr_line = ""
	for i in range(ATTR_NUM-1) :
		new_attr_line += ATTR[i] + "\t"
	new_attr_line += ATTR[ATTR_NUM-1] + "\n"
	f.write(new_attr_line)
	for test in TEST_DIC_LIST :
		classOftarget = get_class(DECISION_TREE, test)
		data = ""
		for a in ATTR : 
			if a not in test.keys() :
				data += classOftarget + "\n"
			else : 
				data += test[a] + "\t"
		f.write(data)



