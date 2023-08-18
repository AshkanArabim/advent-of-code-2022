import os
from pathlib import Path

AOC_FILE_PATH = os.path.join(Path(__file__).parent,'AOC_INPUTS')

def import_files(name=None):
	rtn = ""
	if name:
		with open(os.path.join(AOC_FILE_PATH,name),'r') as f:
			rtn = f.read()
		return rtn
	rtn = []
	for file in os.listdir(AOC_FILE_PATH):
		with open(os.path.join(AOC_FILE_PATH,file),'r') as f:
			rtn.append(f.read())
	return rtn