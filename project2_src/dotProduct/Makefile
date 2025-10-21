all: dotProduct_updated

dotProduct_updated: dotProduct_updated.cpp walltime.h
	g++ -O3 -fopenmp $< -o $@

clean:
	rm -rf dotProduct_updated
