# Bridge_and_torch
Scala assignment
There are 2 approaches to the solution that depend on the base conditions
	
	1. maintain the fastest runners at the opposit sides of the bridge;
	   let the slowest pairs cross and 
	    then returne the torch to the other side by one of the 2 fastest runners
	 2. let the fastest runner go back and forth across the bridge and take the rest 
	    to the other side
	 
The result is the minimun of the 2 above

All of the given examples (defined in briges-config.yaml) return the best time using the first approach
To prove the validity of the second approach the new yaml file is created briges-config-new-case.yaml. It returns beter 
crossing time using the second approach
File is successfully opened
Bridge of length 100
 "Slowest pair first" finished in 17
 "Fastest runner" finished in 19
Bridge of length 100 /////////////////////////this one is new!!!!!
 "Slowest pair first" finished in 19.6667
 "Fastest runner" finished in 17.6667 ----- min
Bridge of length 250
 "Slowest pair first" finished in 53
 "Fastest runner" finished in 60
Bridge of length 250
 "Slowest pair first" finished in 6.66667
 "Fastest runner" finished in 6.66667
Crossing time 94.3333
