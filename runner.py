import time
import sys
sys.path.insert(0, './runner/')

from Programs import Program
from Enviroment import Enviroment

def main():
	programs = Program.getPrograms()
	for program in programs:
		program.getExecuted();
		program.execute([]);
		program.save();

	for program in programs:
		program.makeResults();

if __name__ == "__main__":
	main()
