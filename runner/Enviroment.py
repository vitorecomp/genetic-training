import os

class Enviroment:
	@staticmethod
	def getAll(path):
		i = 0
		envirioment = [path]
		for root, dirs, files in os.walk(path):
			envirioment += dirs
		return envirioment

	def getImages(paths, extention, path, result_path):
		files = []
		results = []
		for path in paths:
			for root, dirs, files_l in os.walk(path):
				for i in files_l:
					occ = i.rfind(".")
					extention_l = i[occ:]
					if extention_l == extention:
						file_n = path + i
						files += [file_n];
						result = file_n.replace(path, result_path)
						results += [result]

		return files, results
