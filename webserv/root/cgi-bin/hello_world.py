from datetime import date

print("Content-type: text/plain\n")
print("The current date is " + str(date.today()) + "!")

# for i in range(10000000000000000000000000):
# 	print("f")

from time import sleep

sleep(10)

import os

# printing environment variables
print("ENV{\n", os.environ, "\n}")
