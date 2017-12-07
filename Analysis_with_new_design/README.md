# Simulink Test

Open MATLAB and run under the current directory. You may set `NUM_TESTS` to different values.

Run the following command to initialise several tests that move the crane from
the starting point to access randomly generated points.

```matlab
run_test_from_start
```

Example log:

```
Number of tests: 200
Start!
Running test #   1 ... Score:   4.300000 Time 4.261140 s
Running test #   2 ... Score:   3.300000 Time 3.954443 s
Running test #   3 ... Score:   3.000000 Time 3.955125 s
Running test #   4 ... Score:   3.100000 Time 3.924006 s
Running test #   5 ... Score:   4.900000 Time 3.982479 s
...
Running test # 192 ... Score:   6.400000 Time 4.056472 s
Running test # 193 ... Score:   3.000000 Time 4.043073 s
Running test # 194 ... Score:   4.700000 Time 4.023520 s
Running test # 195 ... Score:   4.500000 Time 4.092116 s
Running test # 196 ... Score:   5.800000 Time 4.107666 s
Running test # 197 ... Score:   4.600000 Time 4.036714 s
Running test # 198 ... Score:   5.000000 Time 4.047640 s
Running test # 199 ... Score:   5.000000 Time 4.039416 s
Running test # 200 ... Score:   5.200000 Time 4.110026 s
Done!
Total runtime:              816.052541 s
Average runtime:            4.080263 s
Average score:              5.317000
Maximum score:              12.800000
Targets reached percentage: 100.000000%
```