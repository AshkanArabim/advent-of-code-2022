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
		[65, 58, 93, 57, 66],
		"old * 7",
		19,
		(6,4))
m1 = Monkey(
	[76, 97, 58, 72, 57, 92, 82],
	"old + 4",
	3,
	(7,5))
m2 = Monkey(
	[90, 89, 96],
	"old * 5",
	13,
	(5,1))
m3 = Monkey(
	[72, 63, 72, 99],
	"old * old",
	17,
	(0,4))
m4 = Monkey(
	[65],
	"old + 1",
	2,
	(6,2))
m5 = Monkey(
	[97, 71],
	"old + 8",
	11,
	(7,3))
m6 = Monkey(
	[83, 68, 88, 55, 87, 67],
	"old + 2",
	5,
	(2,1))
m7 = Monkey(
	[64, 81, 50, 96, 82, 53, 62, 92],
	"old + 5",
	7,
	(3,0))

def part1():
	
	ms = [m0,m1,m2,m3,m4,m5,m6,m7]
	for _ in range(20):
		for m in ms:
			if m.items:
				for __ in range(len(m.items)):
					m.inspect(m.items[0])
					m.pass_to(ms[m.outcome()])

	for c,m in enumerate(ms):
		print(f"Monkey {c} : {m.inspect_count}")
	print(249 * 247)

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