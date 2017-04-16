print("{.name = \"      No Effect     \", .name_short = \"No FX \"},")

for i in range(1,10,1):
    print("{.name = \"      Preset " + '%4s' % str(i) + "   \", .name_short = \"PR " + '%3s' %  str(i) + "\"},")
    
print ("};")
