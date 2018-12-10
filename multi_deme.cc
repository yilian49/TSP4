#include "cities.hh"
#include "climb_chromosome.hh"
#include "multi_deme.hh"

#include <cassert>
#include <cstdlib>
#include <thread>
#include <mutex>

void 
MultiDeme::threaded_compute_next_generation(unsigned nthread)
{
	auto newpop = std::vector<Chromosome*>();

	assert(pop_.size() % 2 == 0 && "Even population size required!");
	auto best_mutex = std::mutex();	

	auto run_one_thread = [&]()
	{
		while (newpop.size() < pop_.size())
		{
			auto p1 = select_parent();
			auto p2 = select_parent();

			static std::uniform_real_distribution<> dist(0.0, 1.0);
			if (dist(generator_) <= mut_rate_) 
			{ p1->mutate(); }
			if (dist(generator_) <= mut_rate_) 
			{ p2->mutate(); }

			auto guard1 = std::lock_guard(best_mutex);
			
			auto children = p1->recombine(p2);
			if (newpop.size() < pop_.size()-2)
			{
				auto guard2 = std::lock_guard(best_mutex);
				if (newpop.size() < pop_.size()-2)
				{
					newpop.push_back(children.first);
					newpop.push_back(children.second);
				}
			}
		}
	};

	std::vector<std::thread> threads;
	for (unsigned i = 0; i < nthread; ++i)
	{
		threads.push_back(std::thread(run_one_thread));
	}

	for (auto& t : threads)
	{
		t.join();
	}
	
}

