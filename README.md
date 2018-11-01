## Benchmarking TDataFrame ROOT objects

### Details of the benchmarking

**ROOT versions**

**Python version**

**Input file**
  + number of events
  + number of branches (flat/vectors)


### Python vs C++ (using ROOT v6.14.04)

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

#### Interesting feature

Different executions of the same code lead to different results in term of selected events, as shown below.


**Python**
The following commands
```
python CompareTDF_v14.py
python CompareTDF_v14.py
python CompareTDF_v14.py
python CompareTDF_v14.py
```

leads to
```
TOTAL     -> 30.37s (422111 passed events over 883595)
TOTAL     -> 29.38s (422146 passed events over 883595)
TOTAL     -> 29.09s (422443 passed events over 883595)
TOTAL     -> 28.84s (422582 passed events over 883595)
```

**C++**

The following commands:
```
root
.L CompareTDF_v14.C+
RunTDF()
RunTDF()
RunTDF()
RunTDF()
```

leads to 
```
57.7551 seconds for 423074 passing events, over 883595
57.3376 seconds for 422117 passing events, over 883595
55.9797 seconds for 422891 passing events, over 883595
57.186  seconds for 422100 passing events, over 883595
```