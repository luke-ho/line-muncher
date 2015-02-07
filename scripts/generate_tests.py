#!/usr/bin/python

# Purpose: Output a file containing a sequence of numbers in order separated
# by new lines

class TestMaker:
	def __init__(self, start_range, end_range, filename):
		self.start_range = start_range
		self.end_range = end_range
		self.filename = filename
		self.create()
	
	def create(self):
		f1 = open(self.filename, "w")
		for i in range(self.start_range, self.end_range+1):
			print >>f1, str(i)

		f1.close()


if __name__ == "__main__":
	first  = TestMaker(1,100, "../tests/1_nl.txt")
	second = TestMaker(1,4096, "../tests/2_nl.txt")
	third  = TestMaker(1,9999, "../tests/3_nl.txt")
	#fourth = TestMaker(1,9999 * 9999,"../tests/4.txt")
