import sys
from ROOT import gSystem
gSystem.Load("libBNB_NC_bnbpi0")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing bnbpi0..."

sys.exit(0)

