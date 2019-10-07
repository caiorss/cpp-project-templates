import sys
import math

sys.path.append("./bin")

import SampleModule as m

print("\n======= C++ Function vectorCumulativeSum ==========")

xs = [15.6, 8.51, 9.35, 10.6, 87.1]
ys = m.vectorCumulativeSum(xs)

print("xs = ", xs)
print("ys = ", ys)

print("\n======= C++  Function Tabulate1 ========")

m.tabulate1(-20.0, 10, 2.5, lambda x: x * x  - 4 * x + 10.5)




