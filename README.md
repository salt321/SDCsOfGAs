# SDCsOfGAs
SDCs of GAs, experiment data and codes

Enviroment:
    LLVM
    LLFI

How to reproduce:
    1:cd to the repo that you want to run
    2:complile c to *.ll        clang -emit-llvm -S *.c
    3:instrument --readable knapsack.ll
    4:profile ./llfi/knapsack-profiling.exe
    5:injectfault ./llfi/knapsack-faultinjection.exe
    6:python3 measure.py
    
    
Different conditions:
    try to pull out the yaml files in the repo yaml-collections
    if want to test different circumstances.(include: 1 only do fault injection to load instructions
                                                      2 only do fault injection to getelementptr instructions
                                                      3 random FI
                                                      4 only do the FI and protect the knapsack initialize function initKnapsack)
                                                      
 Experiment data: in the folder: expData
 
 repo Oknapsack: experiment toward the original dynamic programming knapsack methods
 repo Genetic: experiment toward the genetic method
