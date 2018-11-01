# Benchmarking TDataFrame ROOT objects

## Details of the benchmarking

**ROOT versions**

**Python version**

**Input file**
  + number of events
  + number of branches (flat/vectors)


## Python vs C++  - using ROOT v6.14.04

**Python**
```
Loading   -> 0.31s
Defining  -> 0.16s
Filtering -> 0.13s
Snap      -> 29.77s
TOTAL     -> 30.37s (422111 passed events over 883595)
```

**C++**
```
57.7551 seconds for 423074 passing events, over 883595
```

## Interesting feature

Different executions of the same code lead to different results in term of selected events, as shown below.


**Python** four successive executions of the python script lead to the four following outputs. Both `Count()` and `TTree.GetEntries()` output change (but they are always equal to each other).
```
TOTAL     -> 28.84s (883595 input events)
Selected events:
  - df.Count(): 421186
  - TTree.GetEntries(): 421186
```

```
TOTAL     -> 28.92s (883595 input events)
  - df.Count(): 421150
  - TTree.GetEntries(): 421150
```

```
TOTAL     -> 29.55s (883595 input events)
Selected events:
  - df.Count(): 420208
  - TTree.GetEntries(): 420208

```

```
TOTAL     -> 29.39s (883595 input events)
Selected events:
  - df.Count(): 421638
  - TTree.GetEntries(): 421638

```

**C++** The output of `Count()` varies but the number of saved events if always the same. 

```
52.4492 seconds for 883595 input events.
Selected events:
  - df.Count(): 422593
  - TTree.GetEntries(): 421638
```

```
52.7641 seconds for 883595 input events.
Selected events:
  - df.Count(): 422595
  - TTree.GetEntries(): 421638
```

```
51.6665 seconds for 883595 input events.
Selected events:
  - df.Count(): 423074
  - TTree.GetEntries(): 421638
```

```
53.2065 seconds for 883595 input events.
Selected events:
  - df.Count(): 420172
  - TTree.GetEntries(): 421638
```