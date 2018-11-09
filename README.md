# Benchmarking TDataFrame ROOT objects

The whole discussion about the test being done here can be found [this post](https://root-forum.cern.ch/t/tdataframe-feedback-performance-comparisons-df-count-instability) of the ROOT forum.

## Details of the benchmarking

**ROOT versions**

  + v6.12.06, with `ROOT.Experimental.TDataFrame()`
  + v6.14.04, with `ROOT.RDataFrame()`

**Python version**

  + python 2.7

**Input file**

  + number of events: 0.9 millions
  + number of branches: 455 (flat and vector)


## ROOT v6.12 vs v6.14 (python)

**v6.12** `TDataFrame` where is seems that `df.Define()` command is not lazy (as it should be)

```
Loading   -> 0.47s
Defining  -> 3.82s
Filtering -> 0.44s
Snap      -> 110.09s
TOTAL     -> 114.82s (883595 input events)
Selected events:
  - df.Count(): 423074
  - TTree.GetEntries(): 423074
```


**v6.14** `RDataFrame` where the running time is divided by ~4 (`df.Define()` is now very fast, probably lazy as it should be).

```
Loading   -> 0.31s
Defining  -> 0.16s
Filtering -> 0.13s
Snap      -> 27.90s
TOTAL     -> 28.50s (883595 input events)
Selected events:
  - df.Count(): 421633
  - TTree.GetEntries(): 421633
```


## Python vs C++ - using ROOT v6.14.04

**Python**
```
Loading   -> 0.31s
Defining  -> 0.16s
Filtering -> 0.13s
Snap      -> 29.77s
TOTAL     -> 30.37s (422111 passed events over 883595)
```

**C++** is almost twice slower.
```
57.7551 seconds for 423074 passing events, over 883595
```

## Python vs C++ - using ROOT v6.12.06

**Python**
```
Loading   -> 0.47s
Defining  -> 3.82s
Filtering -> 0.44s
Snap      -> 110.09s
TOTAL     -> 114.82s (883595 input events)
Selected events:
  - df.Count(): 423074
  - TTree.GetEntries(): 423074
```


**C++**
```
261.37 seconds for 883595 input events.
```



## Unstable number of selected events

Different executions of the same code lead to different results in term of selected events, as shown below. *This is not observed in ROOT v12.06, where results are always the same.*


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


## Comparison with an explicit event loop

Without computing new variable (and selecting half of the events to be saved)
```
19.5094 seconds for 883595 input events.
```


## Wishlist for `ROOT.DataFrame`

  + If there is no event passing, store an empty `TTree` with the expected structure. Right now, the file is simply empty. 