maxflow\_ISAP.c
- Improved Shortest Augmenting Path algorithm (popular term in China,
        don't know where it came from.)
- SAP with distance labels
- current arc optimization + gap optimization + collapsed manual recursion
- <del>(Doesn't seem to be push-relabel, despite similar name)</del>
    - Nvm, maybe it is [push-relabel](https://github.com/jalman/StanfordCardinal/blob/0b24d3fbce61db4a6fa25a4bc28df7983caebef2/Stanford%20University%20ACM%20Team%20Notebook%20(2013-14).pdf)...
- Complexity: O(V^2 E), same as Dinitz's
- Practical speed: almost the same. [varies from problem to problem](http://poj.org/status?problem_id=3469&user_id=lrg213&result=&language=) (ISAP: 12357038, possibly unoptimized Dinic: 12358252)
- Shorter code
- TODO benchmarking (compare to Stanford's Dinic/Push-relabel)
- TODO [FTRobbin's team's template](https://github.com/FTRobbin/Dreadnought-Standard-Code-Library/blob/master/SCL-collection/template/SCL/maxflow.tex) may be better
- TODO turn it into template
    - make it self-contained
    - C++-fication

