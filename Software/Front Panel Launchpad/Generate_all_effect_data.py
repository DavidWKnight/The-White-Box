print("{.preset_number = 0, .name = \"      No Effect     \", .name_short = \"No FX \"},")

for i in range(1,20,1):
    print("{.preset_number = " + str(i) + ", .name = \"      Preset " + '%4s' % str(i) + "   \", .name_short = \"PR " + '%3s' %  str(i) + "\"},")
    
