import sys
import os

print((os.path.getsize(sys.argv[1]) + 511) / 512)
