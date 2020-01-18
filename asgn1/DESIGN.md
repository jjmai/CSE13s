INPUT: scanf() seed and players
OUTPUT: Prints player rolls and diceplay then winner at end

Procedure:
	1. Create array with matching index with name array
		i.make initial value $3
		ii.If they call specific index, the name will equal value
	2. Create a while loop that breaks if only one index value !=0
		i.use for loop to go through index and check values
		ii.index < player # only
	3. use rand() to get index #
		i. only roll max of 3 times
		ii.dice roll equal to money amount for each index
	4. create a separate function for printing output
		i.(diceplay(rand(), index, players)
		ii.if rand()==0 or LEFT : print output
		(current index[value]-1) and leftindex[value]+1
		iii.if rand()==1 or RIGHT: print output
		(current index[value]-1 and rightindex[value]+1)
		iv. if rand()==2 or CENTER: print output
		(current index[value]-1 and add 1 to pot money)
		v. else pass
		vi. return pot amount
	5. itereate through name list after dice role
		i.++index
	6.if (only 1 value in money[index] then done
		i.print name[index] wins pot amount with money[index] left

