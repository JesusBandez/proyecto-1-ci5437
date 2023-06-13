echo "Astar"
echo ">>>>>>>>>> 12Easy"
time ./TopSpin12Token.a ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4_d_005
echo ""
echo ">>>>>>>>>> 12Medium"
time ./TopSpin12Token.a ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4.d=2000
echo ""

echo ">>>>>>>>>> 12Hard"
time ./TopSpin12Token.a ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4.d=2000000
echo ""

echo ">>>>>>>>>> 14Easy"
time ./TopSpin14Token.a ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=005
echo ""

echo ">>>>>>>>>> 14Medium"
time ./TopSpin14Token.a ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=2000
echo ""

echo ">>>>>>>>>> 14Hard"
time ./TopSpin14Token.a ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=2000000
echo ""

echo ">>>>>>>>>> 17Easy"
time ./TopSpin17Token.a ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=005
echo ""

echo ">>>>>>>>>> 17Medium"
time ./TopSpin17Token.a ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=2000
echo ""

echo ">>>>>>>>>> 17Hard"
time ./TopSpin17Token.a ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=2000000
echo ""