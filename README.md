# TSP4
Traveling salesperson problem part 4 multithreading
by Yilian Liu Q75098
and Vinay Gopalan

The current tsp.cc compiles to a default nthreaded ga search. 
In the ga_search function, the MultiDeme part is commented out.
multi_deme is an attempted to solve the extra credit problem, the MultiDeme class inherits
from the Deme class but computes next generation in different threads.

Configuration:
2 million individuals, pop_size = 1000, mut_rate = 0.3 and nthreads = 4
Best result: 5844.92
Runtime: 5.765s

single thread runtime: 18.884s
