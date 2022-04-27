# Vivado High-Level Synthesis (HLS)
These RTL files are generated using Vivado HLS. You may open a Vivado HLS project in this directory and import these scripts, together with `input.dat`, `dimension.dat` and `out.gold.dat` into the project for simulation and synthesis by your own.

# DUT and testbench
`HLS-3x3_median_filter.cpp` is the DUT whereas `TB_HLS-3x3_median_filter.cpp` is its testbench. Both of them are still subject to further changes.

# Synthesized RTL (Verilog and VHDL)
`bubbleSort` (fastest), `insertionSort` and `selectionSort` (slowest) are three RTL solutions generated through HLS. Their detailed reports and analysis can be viewed in `<solution name>/syn/report/`.
