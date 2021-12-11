import csv

firstList = []
lastList = []

with open('lastNames.txt', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        if row[0] not in firstList:
            firstList.append(row[0])

firstList.sort()

for name in firstList:
    print("\"" + name + "\",", end='')
    # print("{\"" + name + "\", vector<Data *>()},", end='')
