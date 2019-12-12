# DAN TRAN

# SPECIES EVOLUTION PROJECT


## Instructions

```shell
$> make
$> ./evolution n s <world.wdf >output.wdf
```
Where `n` is the # of iteration and `world.wdf` is the input World file and `output.wdf` is the output world file. `s` is the optional seed of the randomizer. Default seed is 1.

**WORLD FILE FORMAT:**

```
World h w
Eden h w
Plant Energy n
Reproduction Threshold t

(i j) d e | g[0] g[1] g[2] g[3] g[4] g[5] g[6] g[7] |
```

`h` : height
`w` : width
`n` : energy received from eating plant
`t` : once an animal's reach this value, it will reproduce
`i` : the y location of animal in world
`j` : the x location of animal in world
`d` : direction the animal is facing {0 ... 7}
`e` : energy of the animal
`g` : the genetics of the animal (`g > 0`)



**OUTPUTS ARE IN THE** `test` **DIRECTORY**


## Introduction to Simulation
This simulation is performed under the hypothesis that there are two distinct types of species when an Eden is placed in the world. In the Eden, food is more abundant so animals that circle the Eden would reproduce more children with the same circling genetics. Likewise, for the wandering animals, they would produce more children with forward movement to traverse the map for food.

The three predefined `.wdf` for testing are: 
```
world.wdf
world-eden.wdf
world-largemap-smalleden.wdf
```


## Experiment #1 - NO EDEN x1,000
```bash
./evolution 1000 323 <world.wdf >tests/out-no-eden-1000.wdf
```
`world.wdf` content:
```
World 100 100				# world height and width
Eden 0 0				# eden height and width
Plant Energy 80				# energy received from food
Reproduction Threshold 300		# threshold for multiplying
(0 0) 0 200 | 5 5 5 5 5 5 5 5 |		# from here on is critter stats
(99 99) 0 200 | 5 5 5 5 5 5 5 5 |	# from here on is critter stats
```

Outputs are in the `test/` directory. The population total up to 47.

Observing the locations of the animals, they all seem random due to not having an Eden.


## Experiment #2 - NO EDEN x10,000
This is the same as experiment 1 but with 10000 steps
```bash
./evolution 10000 323 <world.wdf >tests/out-no-eden-10000.wdf
```
`world.wdf` content: Same as Experiment #1

The population total up to 62. After 9000 steps the population only increase by 15. Still, the locations all appear scattered and random. However there are a couple of dominant g[0] animals.

## Experiment #3 - NO EDEN x100,000
```bash
./evolution 100000 323 <world.wdf >tests/out-no-eden-100000.wdf
```
`world.wdf` content: Same as Experiment #1

The population total up to 86. 
```
(43 44) 4 123 | 14 10 2 3 1 2 5 15 |
(40 47) 3 55 | 15 9 3 1 1 1 4 15 |
(61 48) 3 81 | 12 14 1 2 2 1 3 15 |
(62 37) 7 123 | 14 10 2 3 1 2 5 15 |
```
Above are 4 of the animals stats from this experiment. There is an obvious trait of having dominant g[0] g[1] and g[7] because there is no eden. Those three dominant genes are genes that make the animal travel forward. More forward movement implies less looping; There is no need for looping because there is no Eden.

## Experiment #4 - NO EDEN x1,000,000 & x10,000,000
```bash
./evolution 1000000 323 <world.wdf >tests/out-no-eden-1000000.wdf
./evolution 10000000 323 <world.wdf >tests/out-no-eden-10000000.wdf
```
`world.wdf` content: Same as Experiment #1

At this point, g[0] completely dominates all other genes. There are some levels of g[1] and g[7] but g[0] outscales them all. 
Also, the population seems to have peaked: They were 83 and 74 respectively. In fact the population decreased slightly.


## Experiment #5 - WITH EDEN x1,000
```bash
./evolution 1000 323 <world-eden.wdf >tests/out-with-eden-1000.wdf
```
`world-eden.wdf` content:
```
World 100 100				# world height and width
Eden 10 10				# eden height and width
Plant Energy 80				# energy received from food
Reproduction Threshold 300		# threshold for multiplying
(0 0) 0 200 | 5 5 5 5 5 5 5 5 |		# from here on is critter stats
(99 99) 0 200 | 5 5 5 5 5 5 5 5 |	# from here on is critter stats
```

This experiment has an Eden size of 10 x 10. The population was a lot higher than the experiments with no eden, being 212. With only 1000 iterations, there are no noticeable pattern in the genetics.


## Experiment #6 - WITH EDEN x1,000,000
```bash
./evolution 1000000 323 <world-eden.wdf >tests/out-with-eden-1000000.wdf
```
`world-eden.wdf` content: Same as Experiment #5

The population went down to 159. There is now a distinct separation between two groups. Thanks to the output file being sorted, the top half are filled with g[0], g[1], and g[7] dominated animals. The lower portion of the output show animals with dominant g[2], g[3], g[4], and g[5] genes. g[3] and g[5] are the most dominate out of the four. 


## Experiment #7 - WITH EDEN - x10,000,000
```bash
./evolution 10000000 323 <world-eden.wdf >tests/out-with-eden-10000000.wdf
```
`world-eden.wdf` content: Same as Experiment #5

The population went up to 172. The distinction between the two species are now clear. 
The first species have dominant g[0] gene, with sub dominant g[7] and somewhat dominant g[1] gene. The second species have dominant g[4] gene, with g[3] and g[5] genes being a couple values behind. 

The first species strongly indicated forward movements. The second species strongly indicated circling movements. This means that there are wandering animals that scavenge the entire map and there are circling animals that circles the Eden. This proves the initial hypothesis for this experiment to be true.


## Experiment #8 - LARGE MAP, SMALL EDEN - x1,000
```bash
./evolution 1000 323 <world-largemap-smalleden.wdf >tests/out-largemap-smalleden-1000.wdf
```
`world-largemap-smalleden.wdf` content:
```
World 1000 1000				# world height and width
Eden 10 10				# eden height and width
Plant Energy 80				# energy received from food
Reproduction Threshold 300		# threshold for multiplying
(0 0) 0 200 | 5 5 5 5 5 5 5 5 |		# from here on is critter stats
(99 99) 0 200 | 5 5 5 5 5 5 5 5 |	# from here on is critter stats
```

Animals are scattered around everywhere. There is no noticeable pattern in genetics.


## Experiment #9 - LARGE MAP, SMALL EDEN - x1,000,000
```bash
./evolution 1000000 323 <world-largemap-smalleden.wdf >tests/out-largemap-smalleden-1000000.wdf
```
`world-largemap-smalleden.wdf` content:
```
World 100000 100000				# world height and width
Eden 5 5				# eden height and width
Plant Energy 80				# energy received from food
Reproduction Threshold 300		# threshold for multiplying
(0 0) 0 200 | 5 5 5 5 5 5 5 5 |		# from here on is critter stats
(99 99) 0 200 | 5 5 5 5 5 5 5 5 |	# from here on is critter stats
```

The entire population of 75 is now has dominant g[4] gene with subdominant g[3] and g[5] genes with the lowest level of forward-moving genes. Even with a small Eden, the populations eventually get dominated by circling species. This is most likely because animals wander the huge world and die from hunger, and the only ones left are the few that circles the eden. Eventually those few repopulate and their genetics dominate.



## Conclusion and Other Statements

We confirm that the hypothesis is true: Two species exist in this simulation. One circles the Eden with dominant g[3], g[4], and g[5] genes. The other wander the entire map with dominant g[0], g[1], and g[7] genes.

As for the world specs, not all world ensure survival of species. For example if the world is big and there is no Eden, eventually all the animals will wander and die. If there is an Eden of any size, even if its very tiny, as long as a handful of animals circle the Eden, the population will most likely survive. 


