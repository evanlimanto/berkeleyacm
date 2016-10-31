maxflow\_ISAP.c
    - Improved Shortest Augmenting Path algorithm (popular term in China,
            don't know where it came from.)
    - SAP with distance labels
    - current arc optimization + gap optimization + collapsed manual recursion
    - (Doesn't seem to be push-relabel, despite similar name)
    - Complexity: O(V^2 E), same as Dinitz's
    - Actual speed: almost the same.  slightly faster/slower depending on dataset.
    - Code: shorter than most impls of Dinitz's
    - TODO benchmarking (compare to Stanford's Dinic)
    - TODO [FTRobbin's team's template](https://github.com/FTRobbin/Dreadnought-Standard-Code-Library/blob/master/SCL-collection/template/SCL/maxflow.tex) may be better
    - TODO turn it into template
        - make it self-contained
        - C++-fication

