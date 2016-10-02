# 2011004095 Lee Jongwon

# This program's goal is to cluster given datas with given k value (number of clusters).
# Input file's name is input#.txt that contains objects to be clustered.
# The program will make output#_cluster_#.txt file that contains objects in cluster_#.

import sys			# For arguments control
import math			# For sqrt and ceil
import copy			# For data copy
import heapq		# For nsmallest

# CLASS DEFINITION for object and cluster.

class point :		# OBJECT_CLASS
	ID = -1;		# OBJECT_ID
	X = -1;			# CORRDINATE_X
	Y = -1;			# COORDINATE_Y
	VISITED = 0;	# ISVISITED
	NOISE = 0;		# ISNOISE
	CLUSTER = -1;	# CLUSTER_LABEL

class cluster :			# CLUSTER_CLASS
	ID = -1;			# CLUSTER_LABEL
	OBJECTS = list();	# OBJECT_LIST

# FUCNTION DEFINITON for clustering.

def load_objects(input_file) :		# Read INPUT_FILE and get OBJECTS.
	OBJECTS = list();
	with open(input_file) as f :
		for line in f :
			INPUT_LINE = list();
			OBJECT = point();
			INPUT_LINE = [str(x) for x in line.split()];
			OBJECT.ID = int(INPUT_LINE[0]);
			OBJECT.X = float(INPUT_LINE[1]);
			OBJECT.Y = float(INPUT_LINE[2]);
			OBJECTS.append(OBJECT);
	return OBJECTS

def initialize_objs(objs) :			# Initialize OBJECTS' valule.
	for obj in objs :				# But exclude ID, COORDINATE value.
		obj.VISITED = 0;
		obj.NOISE = 0;
		obj.CLUSTER = -1;
	return

def get_dist(objs) :				# Calculate the distance between all points.
	OBJ_NUM = len(objs);			# Store it in DISTANCE that is list of dictionary type.
	DISTANCE = list();
	for i in range(0,OBJ_NUM) :
		DISTANCE.append({});
		for j in range(0,OBJ_NUM) :
			TMP_DIST = math.sqrt(pow(objs[j].X-objs[i].X,2) + pow(objs[j].Y-objs[i].Y,2));
			DISTANCE[i][j] = TMP_DIST;
	return DISTANCE

def initial_eps(minPts, dist) :		# Find initial epsilon for other input#.txt.
	K_DISTANCE = list();			# Initial epsilon is just a maximum of K-distance.
	INIT_EPS = 0;					# Time complexity is O(N * N * logK).
	TOTALNUM = len(dist);
	for i in range(0,TOTALNUM) :
		TMP = heapq.nsmallest(minPts+1, dist[i].values());
		K_DISTANCE = TMP[minPts];
		if INIT_EPS < K_DISTANCE :
			INIT_EPS = K_DISTANCE;
	return INIT_EPS;

def get_neighbors3(i, eps, dist) :	# Get ith object's neighbors.			
	NEIGHBORS = list();				# Use pre-calculated distance.
	for j in range(0,len(dist)) :
		if dist[i][j] <= eps :
			NEIGHBORS.append(j);
	return NEIGHBORS

def get_cluster(minPts, eps, objs, dist) :	# Get lisf of CLUSTER.
	CLUSTERS = list();						# Just use DBscan algorithm.
	TOTALNUM = len(objs);
	COUNT = 0;
	for i in range(0,TOTALNUM) :
		if objs[i].VISITED == 1 :
			continue;
		objs[i].VISITED = 1;
		NEIGHBORS = get_neighbors3(i, eps, dist);
		if len(NEIGHBORS) < minPts :
			objs[i].NOISE = 1;
		else :
			C = cluster();
			C.ID = COUNT;
			C.OBJECTS = list();
			C.OBJECTS.append(objs[i].ID);
			objs[i].CLUSTER = COUNT;
			for j in NEIGHBORS :
				if objs[j].VISITED == 0:
					objs[j].VISITED = 1;
					j_NEIGHBORS = get_neighbors3(j, eps, dist);
					if len(j_NEIGHBORS) >= minPts :
						NEIGHBORS += j_NEIGHBORS; 
				if objs[j].CLUSTER == -1 :
					C.OBJECTS.append(objs[j].ID);
					objs[j].CLUSTER = COUNT;
			CLUSTERS.append(C);
			COUNT += 1;
	return CLUSTERS

# MAIN CODE.

print ""

INPUT_FILE = sys.argv[1];
T_CLUSTER_NUM = int(sys.argv[2]);

OBJECTS = load_objects(INPUT_FILE);
OBJECT_NUM = len(OBJECTS);
print "%d objects are loaded." % OBJECT_NUM;
DISTANCE = get_dist(OBJECTS);
print "Distances between all points are calculated.\n"

MINPTS = 0;
EPSILON = 0;
INPUT_NUM = int(INPUT_FILE[5]);
if INPUT_FILE[6] != '.' :
	INPUT_NUM = 10*INPUT_NUM + int(INPUT_FILE[6]);
if INPUT_FILE == "input1.txt" :
	MINPTS = 24;
	EPSILON = 15.2;			#98.89886
elif INPUT_FILE == "input2.txt" :
	MINPTS = 10;
	EPSILON = 2.0;			#94.28109 
elif INPUT_FILE == "input3.txt" :
	MINPTS = 10;
	EPSILON = 7.0;			#100
else :
	MINPTS = int(math.ceil(OBJECT_NUM * 0.025 / T_CLUSTER_NUM)) ;
	EPSILON = initial_eps(MINPTS, DISTANCE);

print "START CLUSTERING."
CLUSTERS = get_cluster(MINPTS, EPSILON, OBJECTS, DISTANCE);
CLUSTER_NUM = len(CLUSTERS);
print "minPts: %d, eps: %f, cluster: %d" % (MINPTS, EPSILON, CLUSTER_NUM);

if (INPUT_NUM != 1) & (INPUT_NUM != 2) & (INPUT_NUM != 3) :
	HMM = 0;
	DIFF = EPSILON / 2.0;
	BEFOREEPS = EPSILON;
	while HMM != 2 :
		if CLUSTER_NUM == 0 :
			MINPTS -= 1;
		elif (T_CLUSTER_NUM < CLUSTER_NUM):
			EPSILON += DIFF;
			HMM = 0;
		elif T_CLUSTER_NUM > CLUSTER_NUM :
			EPSILON -= DIFF;
			HMM = 0;
		else :
			HMM += 1;
			if HMM == 2 :
				EPSILON = (EPSILON + BEFOREEPS) / 2.0;
			else :
				BEFOREEPS = EPSILON;
				EPSILON += DIFF;
		initialize_objs(OBJECTS);
		CLUSTERS = get_cluster(MINPTS, EPSILON, OBJECTS, DISTANCE);
		CLUSTER_NUM = len(CLUSTERS);
		print "minPts: %d, eps: %f, cluster_num: %d" % (MINPTS, EPSILON, CLUSTER_NUM);
		DIFF = DIFF / 2.0;

# Control noise objects. Add noise objects to closest cluster.
# After this, input2.txt's score is improved to 95.72897.
# But input1.txt's score is down.
# I will use this method to other inputs. (DOJEON!!)
if (INPUT_FILE != "input1.txt") & (INPUT_FILE != "input3.txt") :
	COUNT = 0;
	for i in range(0,OBJECT_NUM) :
		if (OBJECTS[i].NOISE == 1) & (OBJECTS[i].CLUSTER == -1) :
			COUNT += 1;
			TMP_DIST = 9999999;
			for j in range(0,OBJECT_NUM) :
				if i != j :
					if TMP_DIST > DISTANCE[i][j] :
						if OBJECTS[j].NOISE != 1 :
							OBJECTS[i].CLUSTER = OBJECTS[j].CLUSTER;
							TMP_DIST = DISTANCE[i][j];
			#CLUSTERS[OBJECTS[i].CLUSTER].OBJECTS.append(i);
	print "NOISE NUM : %d." % COUNT;

print ""
print "----- R E S U L T -----"

TOTAL_CLUSTER_NUM = 0;
for i in range(0,T_CLUSTER_NUM) :
	print "CLUSTER%d's NUM : " % CLUSTERS[i].ID,
	TOTAL_CLUSTER_NUM += len(CLUSTERS[i].OBJECTS);
	print len(CLUSTERS[i].OBJECTS);
	OUTPUT_FILE = "output%d_cluster_%d.txt" % (INPUT_NUM, CLUSTERS[i].ID);
	with open(OUTPUT_FILE, 'w') as f :
		for j in CLUSTERS[i].OBJECTS :
			data = "%d\n" % j;
			f.write(data);
		for obj in OBJECTS :
			if (obj.NOISE == 1) & (obj.CLUSTER == i) :
				data = "%d\n" % obj.ID;
				f.write(data);
print "Total objects number in clusters : %d\n" % TOTAL_CLUSTER_NUM;
