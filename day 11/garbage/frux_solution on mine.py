import setup

class Monkey:
	def __init__(self,items,oper,test,options):
		self.inspect_count = 0
		self.items = items
		self.oper = oper
		self.test = test
		self.options = options

	def inspect(self,old,div=None):
		self.inspect_count += 1
		if not div:
			self.items[0] = int(eval(self.oper)) // 3
		else:
			self.items[0] = int(eval(self.oper)) % div

	def outcome(self):
		return self.options[not self.items[0] % self.test == 0]

	def pass_to(self,other):
		other.items.append(self.items.pop(0))

m0 = Monkey(
		[74, 73, 57, 77, 74],
		"old * 11",
		19,
		(6, 7))
m1 = Monkey(
		[99, 77, 79],
		"old + 8",
		2,
		(6, 0))
m2 = Monkey(
		[64, 67, 50, 96, 89, 82, 82],
		"old + 1",
		3,
		(5, 3))
m3 = Monkey(
		[88],
		"old * 7",
		17,
		(5, 4))
m4 = Monkey(
		[80, 66, 98, 83, 70, 63, 57, 66],
		"old + 4",
		13,
		(0, 1))
m5 = Monkey(
		[81, 93, 90, 61, 62, 64],
		"old + 7",
		7,
		(1, 4))
m6 = Monkey(
		[69, 97, 88, 93],
		"old * old",
		5,
		(7, 2))
m7 = Monkey(
		[59, 80],
		"old + 6",
		11,
		(2, 3))

def part1():
	ms = [m0,m1,m2,m3,m4,m5,m6,m7]

	for _ in range(20):
		for m in ms:
			if m.items:
				for __ in range(len(m.items)):
					m.inspect(m.items[0])
					m.pass_to(ms[m.outcome()])

	for c, m in enumerate(ms):
		print(f'Monkey {c} inventory:')
		print(m.items)

	for c,m in enumerate(ms):
		print(f"Monkey {c} : {m.inspect_count}")
	# print(249 * 247)

def part2():
	ms = [m0,m1,m2,m3,m4,m5,m6,m7]
	bmod = 1
	for m in ms:
		bmod *= m.test
	for _ in range(10_000):
		for m in ms:
			if m.items:
				for __ in range(len(m.items)):
					m.inspect(m.items[0],bmod)
					m.pass_to(ms[m.outcome()])

	for c,m in enumerate(ms):
		print(f"Monkey {c} : {m.inspect_count}")

if __name__ == '__main__':
	part1()
	# part2()
	# print(131087 * 107420)